#include "../../headers/headers.hpp"
#include "./Noise.hpp"

float Noise::fade(float t) {
    return t * t * t * (t * (t * 6 - 15) + 10);
}

int Noise::floor(float t) {
    if(t > (int)t) {
        return (int)t;
    } else {
        return(int)(t-1);
    }
}

float Noise::lerp(float t, float a, float b) {
    return a + t * (b - a);
}

float Noise::grad(int hash, float x, float y) {
    int h = hash & 7;
    float u = h < 4 ? x : y;
    float v = h < 4 ? y : x;
    return ((h&1)? -u : u) + ((h&2)? -2.f*v : 2.f*v);
}