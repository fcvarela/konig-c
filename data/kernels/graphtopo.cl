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
    float coulomb_constant = 200.0f;
    for (int i=0; i<total; i++) {
        float3 d = in[id].pos.xyz - in[i].pos.xyz;
        float distance = length(d)+0.00001f;
        float3 direction = normalize(d);
        float3 force = (direction * coulomb_constant) / (distance*distance*0.5f);
        out[id].acc.xyz += force;
    }
}

__kernel void edge_step(__global struct Edge *ein, __global struct Particle *in, __global struct Particle *out) {
    int id = get_global_id(0);
    int id1 = ein[id].idx1;
    int id2 = ein[id].idx2;

    float spring_length = 4.0f;
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

    float4 centerpos = in[0].pos;

    // integrate
    out[id].vel = (in[id].vel + dt * out[id].acc)*0.8f;
    out[id].pos = in[id].pos + out[id].vel*dt - centerpos;
}
