#ifndef TEST_SPHERE_HPP
#define TEST_SPHERE_HPP

#include "SphereRenderer.h"
#include "Graphics.hpp"

#include <vector>

#include <cmath>

class TestSphere : public SphereRenderer {
private:
    const double kPi = 3.141592653;
    const double kR = 100.0;
    std::vector<Point> points_;

public:
    TestSphere() {}
    ~TestSphere() {}
    void Init() {
        points_.clear();
        for (double theta=0.0; theta < 2.0 * kPi; theta += 0.1 * kPi) {
            for (double phi=-kPi; phi < kPi; phi += 0.1 * kPi) {
                points_.push_back(Point(
                    kR * cos(theta) * cos(phi),
                    kR * sin(theta) * cos(phi),
                    kR * sin(phi)
                ));
            }
        }
    }
    void Render() {
        glBegin(GL_POINTS);
        for (auto &p : points_) {
            glVertex3d(p.x, p.y, p.z);
        }
        glEnd();
    }
};

#endif // TEST_SPHERE_HPP
