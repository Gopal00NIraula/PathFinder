#ifndef SAMPLER_H
#define SAMPLER_H

#include <vector>
#include <random>

class Sampler {
public:
    Sampler(int n);
    int getSample();

private:
    std::vector<int> elements;
    std::mt19937 rng;
};

#endif // SAMPLER_H
