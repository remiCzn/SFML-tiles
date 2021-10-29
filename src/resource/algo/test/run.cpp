#include "./run.hpp"

void Noise::runAlgo() {
    std::ofstream ofs("../src/resource/algo/test/res.json");
    if(ofs.is_open())
    {   
        Json::Value res;
        res["x"] = Json::Value();
        res["y"] = Json::Value();
        for(int x = 0; x < 20; x++) {
            res["x"].append(x);
            res["y"].append(Noise::grad(123456789, x, 234));
        }
        ofs << res;
        ofs.close();
    }
}