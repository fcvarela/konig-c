MSTRINGIFY(
struct __attribute__ ((packed)) Particle {
    float4 pos;
    float4 vel;
    float4 acc;
    float4 pad;
};

struct __attribute__ ((packed)) Edge {
    uint idx1;
    uint idx2;
    uint pad1;
    uint pad2;
};

__kernel void vertex_step(__global struct Particle *in, __global struct Particle *out) {
    int id = get_global_id(0);

    out[id].acc = (float4)(0.0f);
    float coulomb_constant = 300.0f;

    for (int i=0; i<id; i++) {
        float4 d = in[id].pos - in[i].pos;
        float distance = max(length(d), 1.0f);
        float4 direction = normalize(d);
        float4 force = (direction * coulomb_constant) / (distance*distance);
        out[id].acc += force;
        out[i].acc -= force;
    }
}

__kernel void edge_step(__global struct Edge *ein, __global struct Particle *in, __global struct Particle *out) {
    int id = get_global_id(0);
    int id1 = ein[id].idx1;
    int id2 = ein[id].idx2;

    float spring_length = 10.0f;
    float hooke_constant = 250.0f;

    // hooke
    float4 d = in[id2].pos - in[id1].pos;
    float displacement = spring_length - length(d);
    float4 direction = normalize(d);
    float4 force = direction * hooke_constant * displacement;

    out[id1].acc -= force;
    out[id2].acc += force;
}

__kernel void integrate(__global struct Particle *in, __global struct Particle *out, const float dt) {
    int id = get_global_id(0);

    float4 centerpos = in[0].pos;

    // integrate
    out[id].vel = (in[id].vel + dt * out[id].acc) * 0.8f;
    out[id].pos = in[id].pos + out[id].vel*dt - centerpos;
}

);
