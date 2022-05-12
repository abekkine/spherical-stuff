#ifndef TEST_SPHERE_RENDERER_HPP
#define TEST_SPHERE_RENDERER_HPP

#include "SphereRenderer.h"
#include "Graphics.hpp"

#include <vector>

#include <cmath>

class TestSphereRenderer : public SphereRenderer {
private:
    struct Point {
        double x, y, z;
        Point(const double& x, const double& y, const double& z)
        : x(x), y(y), z(z) {}
    };
    std::vector<Point> points_;

public:
    TestSphereRenderer() {}
    ~TestSphereRenderer() {}
    void Init() {
        points_.clear();
        const double kPi = 3.141592653;
        const double r = 100.0;
        for (double theta=0.0; theta < 2.0 * kPi; theta += 0.1 * kPi) {
            for (double phi=-kPi; phi < kPi; phi += 0.1 * kPi) {
                double x, y, z;
                points_.push_back(Point(
                    r * cos(theta) * cos(phi),
                    r * sin(theta) * cos(phi),
                    r * sin(phi)
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

#endif // TEST_SPHERE_RENDERER_HPP
