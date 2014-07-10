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
        if (i == id) continue;
        float3 d = in[id].pos.xyz - in[i].pos.xyz;
        float distance = length(d) + 0.1f;
        float3 direction = normalize(d);
        float3 force = (direction * coulomb_constant) / (distance*distance*0.5f);
        out[id].acc.xyz += force;
    }
}

__kernel void edge_step(__global struct Edge *ein, __global struct Particle *in, __global struct Particle *out) {
    int id = get_global_id(0);
    int id1 = ein[id].idx1;
    int id2 = ein[id].idx2;

    float spring_length = 1.0f;
    float hooke_constant = 200.0f;

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

    if (id == 0) {
        out[0].pos.w = 0.0;
    }

    // accumulate system energy into first particle's w coord
    out[0].pos.w += (0.5 * length(in[id].vel)*length(in[id].vel));

    // attract to centre
    float3 direction = -in[id].pos.xyz;
    out[id].acc.xyz += direction * 200.0f/50.0f;

    out[id].vel = in[id].vel + out[id].acc*dt*0.5f;
    out[id].pos = in[id].pos + out[id].vel*dt + out[id].acc*dt*dt*0.5f;

    // zero energy? stop system
    if (id == get_global_size(0)-1 && out[0].pos.w <= 0.001) {
        for (int i=0; i<get_global_size(0); i++) {
            out[i].vel.xyz = (float3)(0.0);
            out[i].acc.xyz = (float3)(0.0);
        }
    }

    out[id].acc.xyz = float3(0.0f);
}
