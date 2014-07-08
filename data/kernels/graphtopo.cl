struct __attribute__ ((packed)) Particle {
    float4 pos;
    float4 vel;
};

struct __attribute__ ((packed)) Edge {
    int idx1;
    int idx2;
};

__kernel void vertex_step(__global struct Particle *in, __global struct Particle *out, const float dt) {
    float4 acc = (float4)(0.0f, 0.0f, 0.0f, 0.0f);
    int total = get_global_size(0);
    int id = get_global_id(0);
    
    for (int i=0; i<total; i++) {
        float4 d = in[id].pos - in[i].pos;
        float invr = 1.0/sqrt(length(d)+0.0001);
        float invr3 = invr*invr*invr;
        float f = invr3; // times mass if applicable
        acc += f * d;
    }
    out[id].pos = in[id].pos + dt*in[id].vel + 0.5f*dt*dt*acc;

    float4 vel = in[id].vel + acc * dt;
    if (length(vel) > 10.0)
        vel = normalize(vel) * 10.0f;

    out[id].vel = vel;
}

__kernel void edge_step(__global struct Edge *in, __global struct Particle *out, const float dt) {
    int id = get_global_id(0);

    // calculate force that p1 exerts on p2
    float4 d = (out[in[id].idx1].pos - out[in[id].idx2].pos) - 100.0f;
    float invr = 1.0/sqrt(length(d)+0.0001);
    float invr3 = invr*invr*invr;
    float f = invr3; // times mass if applicable
    float4 acc = f*d*10.0f;

    float4 vel = acc * dt;
    if (length(vel) > 10.0)
        vel = normalize(vel) * 10.0f;

    out[in[id].idx2].vel += vel;
    out[in[id].idx1].vel -= vel;
}