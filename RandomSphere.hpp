#ifndef RANDOM_SPHERE_HPP
#define RANDOM_SPHERE_HPP

#include "SphereRenderer.h"

class RandomSphere : public SphereRenderer {
private:
    const int kNumPoints = 100;

public:
    RandomSphere() {}
    ~RandomSphere() {}
    void Init() {
        points_.clear();
        AddRandomPoints(kNumPoints);
    }
};

#endif // RANDOM_SPHERE_HPP
