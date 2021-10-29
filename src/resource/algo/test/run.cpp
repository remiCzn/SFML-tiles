#include "./run.hpp"

void Noise::runAlgo() {
    std::ofstream ofs("../src/resource/algo/test/res.json");
    if(ofs.is_open())
    {   
        Json::Value res;
        for(int x = 0; x < 200; x++) {
            float X = x + 0.5;
            res.append(Json::Value());
            for (int y = 0; y < 200; y++)
            {
                float Y = y + 0.5;
                res[x].append(Noise::noise(X/20.f, Y/20.f));
            }
        }
        ofs << res;
        ofs.close();
    }
}