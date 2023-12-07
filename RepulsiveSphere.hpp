#ifndef REPULSIVE_SPHERE_HPP
#define REPULSIVE_SPHERE_HPP

#include "SphereRenderer.h"

class RepulsiveSphere : public SphereRenderer {
private:
    const int kNumPoints = 100;

public:
    RepulsiveSphere() {}
    ~RepulsiveSphere() {}
    void Init() {
        points_.clear();
        AddRandomPoints(kNumPoints);
    }
    void Update(const double& dT) {
        for (int i=0; i<kNumPoints; ++i) {
            glm::vec3 vRep(0.0, 0.0, 0.0);
            glm::vec3 vi = PointToVec3(points_[i]);
            for (int j=0; j<kNumPoints; ++j) {
                if (i != j) {
                    glm::vec3 vj = PointToVec3(points_[j]);
                    glm::vec3 vi2j = vj - vi;
                    auto size = glm::length(vi2j);
                    vRep = vRep - (vi2j / size);
                }
            }
            vRep = glm::normalize(vRep);
            points_[i]->x = kR * vRep.x;
            points_[i]->y = kR * vRep.y;
            points_[i]->z = kR * vRep.z;
        }
    }
};

#endif // REPULSIVE_SPHERE_HPP
