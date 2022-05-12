#ifndef SPHERE_RENDERER_H
#define SPHERE_RENDERER_H

#include <memory>
#include <vector>
#include <random>
#include <cmath>

#include <glm.hpp>

class SphereRenderer {
protected:
    const double kPi = 3.141592653;
    const double kR = 100.0;

    struct Point {
        double x, y, z;
        Point(const double& x, const double& y, const double& z)
        : x(x), y(y), z(z) {}
    };
    typedef std::shared_ptr<Point> PointPtr;
    std::vector<PointPtr> points_;

    glm::vec3 PointToVec3(PointPtr p) {
        return glm::vec3(p->x, p->y, p->z);
    }
    void AddRandomPoints(const int num_points) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> distTheta(0.0, 2.0*kPi);
        std::uniform_real_distribution<> distPhi(-kPi, kPi);

        // create random points on sphere surface...
        double phi, theta;
        for (int i=0; i<num_points; ++i) {
            phi = distPhi(gen);
            theta = distTheta(gen);
            points_.push_back(std::make_shared<Point>(
                kR * cos(theta) * cos(phi),
                kR * sin(theta) * cos(phi),
                kR * sin(phi)
            ));
        }   
    }
    void AddRegularPoints(const double step) {
        for (double theta=0.0; theta < 2.0 * kPi; theta += step * kPi) {
            for (double phi=-kPi; phi < kPi; phi += step * kPi) {
                points_.push_back(std::make_shared<Point>(
                    kR * cos(theta) * cos(phi),
                    kR * sin(theta) * cos(phi),
                    kR * sin(phi)
                ));
            }
        }
    }

public:
    virtual ~SphereRenderer() {}
    virtual void Init() = 0;
    virtual void Update(const double& dT=0.0167) {}

    void Render() {
        glBegin(GL_POINTS);
        for (auto p : points_) {
            glVertex3d(p->x, p->y, p->z);
        }
        glEnd();
    }
};

typedef std::shared_ptr<SphereRenderer> SpherePtr;

#endif // SPHERE_RENDERER_H
