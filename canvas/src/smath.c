#include "types.h"

void mat4_print(mat4 m) {
    int v = 0;

    printf("%f %f %f %f\n", m.v[0], m.v[1], m.v[2], m.v[3]);
    printf("%f %f %f %f\n", m.v[4], m.v[5], m.v[6], m.v[7]);
    printf("%f %f %f %f\n", m.v[8], m.v[9], m.v[10], m.v[11]);
    printf("%f %f %f %f\n", m.v[12], m.v[13], m.v[14], m.v[15]);
}

mat4 mat4_identity() {
    mat4 out = {};
    mat4_set_identity(&out);

    return out;
}

void mat4_set_identity(mat4* out) {
    out->v[0] = 1;
    out->v[1] = 0;
    out->v[2] = 0;
    out->v[3] = 0;
    out->v[4] = 0;
    out->v[5] = 1;
    out->v[6] = 0;
    out->v[7] = 0;
    out->v[8] = 0;
    out->v[9] = 0;
    out->v[10] = 1;
    out->v[11] = 0;
    out->v[12] = 0;
    out->v[13] = 0;
    out->v[14] = 0;
    out->v[15] = 1;
}

mat4 mat4_ortho(float left, float right, float bottom, float top, float near, float far) {
    mat4 out = mat4_identity();

    float rl = right - left;
    float tb = top - bottom;
    float fn = far - near;

    out.v[0] = 2 / rl;
    out.v[1] = 0;
    out.v[2] = 0;
    out.v[3] = 0;
    out.v[4] = 0;
    out.v[5] = 2 / tb;
    out.v[6] = 0;
    out.v[7] = 0;
    out.v[8] = 0;
    out.v[9] = 0;
    out.v[10] = -2 / fn;
    out.v[11] = 0;
    out.v[12] = -(left + right) / rl;
    out.v[13] = -(top + bottom) / tb;
    out.v[14] = -(far + near) / fn;
    out.v[15] = 1;

    return out;
}

mat4 mat4_translate(vec3 t) {
    mat4 out = mat4_identity();
    mat4_set_translate(&out, t);

    return out;
}

void mat4_set_translate(mat4* out, vec3 t) {
    out->v[12] = out->v[0] * t.v[0] + out->v[4] * t.v[1] + out->v[8] * t.v[2] + out->v[12];
    out->v[13] = out->v[1] * t.v[0] + out->v[5] * t.v[1] + out->v[9] * t.v[2] + out->v[13];
    out->v[14] = out->v[2] * t.v[0] + out->v[6] * t.v[1] + out->v[10] * t.v[2] + out->v[14];
    out->v[15] = out->v[3] * t.v[0] + out->v[7] * t.v[1] + out->v[11] * t.v[2] + out->v[15];
}
