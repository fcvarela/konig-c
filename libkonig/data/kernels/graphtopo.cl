struct __attribute__ ((packed)) Particle {
    float4 pos;
    float4 vel;
    float4 acc;
};

struct __attribute__ ((packed)) Edge {
    int idx1;
    int idx2;
};

__kernel void vertex_step(__global struct Particle *in, __global struct Particle *out) {
    int total = get_global_size(0);
    int id = get_global_id(0);

    // coulomb
    out[id].acc.xyz = (float3)(0.0f);
    float coulomb_constant = 400.0f;
    for (int i=0; i<total; i++) {
        float3 d = in[id].pos.xyz - in[i].pos.xyz;
        float distance = length(d) + 0.1f;
        float3 direction = normalize(d);
        float3 force = (direction * coulomb_constant) / (distance*distance*0.5f);
        out[id].acc.xyz += force;
    }
    
    // calculate system energy
    out[0].pos.w = 0.0f;
    barrier(CLK_GLOBAL_MEM_FENCE);
    out[0].pos.w += (0.5 * length(in[id].vel)*length(in[id].vel));
    barrier(CLK_GLOBAL_MEM_FENCE);
}

__kernel void edge_step(__global struct Edge *ein, __global struct Particle *in, __global struct Particle *out) {
    int id = get_global_id(0);
    int id1 = ein[id].idx1;
    int id2 = ein[id].idx2;

    float spring_length = 1.0f;
    float hooke_constant = 400.0f;

    // hooke
    float3 d = in[id2].pos.xyz - in[id1].pos.xyz;
    float displacement = spring_length - length(d);
    float3 direction = normalize(d);
    float3 force = direction * (hooke_constant * displacement * 0.5f);

    out[id1].acc.xyz -= force;
    out[id2].acc.xyz += force;
}

__kernel void integrate(__global struct Particle *in, __global struct Particle *out, const float dt) {
    int id = get_global_id(0);

    // attract to centre
    float3 direction = -in[id].pos.xyz;
    out[id].acc.xyz += direction * 400.0f/50.0f;

    if (out[0].pos.w == 0.0) {
        out[id].vel.xyz = (float3)(0.0);
    } else {
        out[id].vel.xyz = in[id].vel.xyz + out[id].acc.xyz*dt*0.5f;
    }

    // integrate
    out[id].pos = in[id].pos + out[id].vel*dt + out[id].acc*dt*dt*0.5f;
}
