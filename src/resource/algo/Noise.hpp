#ifndef NOISE_H
#define NOISE_H

namespace Noise
{
    float fade(float t);
    int floor(float t);
    float lerp(float t, float a, float b);
    float grad(int hash, float x, float y);
    float noise(float x, float y);
} // namespace Noise


#endif