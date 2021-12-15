#include "./run.hpp"

void Noise::runAlgo()
{
    std::ofstream ofs("../src/resource/algo/test/res.json");
    if (ofs.is_open())
    {
        Json::Value res;
        for (int x = 0; x < 200; x++)
        {
            res.append(Json::Value());
            for (int y = 0; y < 200; y++)
            {

                res[x].append(Noise::generate(x, y));
            }
        }
        ofs << res;
        ofs.close();
    }
}

float Noise::generate(int x, int y)
{
    float lacunarity = 2.f;
    float persistence = 0.5;
    float X = x + 0.5f;
    float Y = y + 0.5f;
    float res = 0;
    for (int i = 0; i < 3; i++)
    {
        float frequence = pow(lacunarity, i);
        float amplitude = pow(persistence, i);
        res += amplitude * Noise::noise(X * frequence / 20.f, Y * frequence / 20.f);
    }
    return res;
}