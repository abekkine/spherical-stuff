#ifndef TEST_SPHERE_HPP
#define TEST_SPHERE_HPP

#include "SphereRenderer.h"

class TestSphere : public SphereRenderer {
public:
    TestSphere() {}
    ~TestSphere() {}
    void Init() {
        points_.clear();
        AddRegularPoints(0.1);
    }
};

#endif // TEST_SPHERE_HPP
