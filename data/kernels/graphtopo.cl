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
    out[id].vel = in[id].vel + acc * dt;
}

__kernel void edge_step(__global struct Edge *in, __global struct Particle *out, const float dt) {
    int id = get_global_id(0);

    // calculate force that p1 exerts on p2
    float4 d = out[in[id].idx1].pos - out[in[id].idx2].pos;
    float invr = 1.0/sqrt(length(d)+0.0001);
    float invr3 = invr*invr*invr;
    float f = invr3; // times mass if applicable
    float4 acc = f*2000.0f*d;

    // update both particles
    out[in[id].idx2].pos += 0.5f*dt*dt*acc;
    out[in[id].idx1].pos -= 0.5f*dt*dt*acc;

    out[in[id].idx2].vel += acc*dt;
    out[in[id].idx1].vel -= acc*dt;
}