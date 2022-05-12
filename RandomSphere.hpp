#ifndef RANDOM_SPHERE_HPP
#define RANDOM_SPHERE_HPP

#include "SphereRenderer.h"
#include "Graphics.hpp"

#include <vector>
#include <random>
#include <cmath>

class RandomSphere : public SphereRenderer {
private:
    const int kNumPoints = 100;
    const double kPi = 3.141592653;
    const double kR = 100.0;
    std::vector<Point> points_;

public:
    RandomSphere() {}
    ~RandomSphere() {}
    void Init() {

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> distTheta(0.0, 2.0*kPi);
        std::uniform_real_distribution<> distPhi(-kPi, kPi);

        // TODO : create random points on sphere surface...
        double phi, theta;
        for (int i=0; i<kNumPoints; ++i) {
            phi = distPhi(gen);
            theta = distTheta(gen);
            points_.push_back(Point(
                kR * cos(theta) * cos(phi),
                kR * sin(theta) * cos(phi),
                kR * sin(phi)
            ));
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

#endif // RANDOM_SPHERE_HPP
