#include "Sampler.h"
#include <algorithm>

Sampler::Sampler(int n) : elements(n), rng(std::random_device{}()) {
    // Initialize elements with values [0, n-1]
    for (int i = 0; i < n; ++i) {
        elements[i] = i;
    }
    std::shuffle(elements.begin(), elements.end(), rng);
}

int Sampler::getSample() {
    if (elements.empty()) return -1;
    int sample = elements.back();
    elements.pop_back();
    return sample;
}
