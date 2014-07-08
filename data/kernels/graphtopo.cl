struct __attribute__ ((packed)) Particle {
    float4 pos;
    float4 vel;
};

__kernel void vertex_step(__global struct Particle *in, __global struct Particle *out, const float dt) {
    float4 acc = (float4)(0.0f, 0.0f, 0.0f, 0.0f);
    int total = get_global_size(0);
    int id = get_global_id(0);
    
    for (int i=0; i<total; i++) {
        float4 d = in[i].pos - in[id].pos;
        float invr = 1.0/sqrt(length(d)+0.0001);
        float invr3 = invr*invr*invr;
        float f = invr3; // times mass if applicable
        acc += f * d;
    }
    out[id].pos = in[id].pos + dt*in[id].vel + 0.5f*dt*dt*acc;
    out[id].vel = in[id].vel + acc * dt;
}
