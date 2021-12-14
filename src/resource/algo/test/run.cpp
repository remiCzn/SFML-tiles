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
    float lacunarity = 20.f;
    float persistence = 0.5;
    float X = x + 0.5f;
    float Y = y + 0.5f;
    float res = 0;
    for (int i = 0; i < 3; i++)
    {
        res += pow(persistence, i) * Noise::noise(X / pow(lacunarity, i + 1), Y / pow(lacunarity, i + 1));
    }
    return res;
}