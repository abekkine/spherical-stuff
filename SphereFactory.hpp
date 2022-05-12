#ifndef SPHERE_FACTORY_HPP
#define SPHERE_FACTORY_HPP

#include "SphereRenderer.h"
#include "TestSphere.hpp"
#include "RandomSphere.hpp"
#include "RepulsiveSphere.hpp"

#include <functional>
#include <unordered_map>

class SphereFactory {
private:
    typedef std::function<SpherePtr()> SphereCreatorFn;

    static SpherePtr getTestSphere() {
        return std::make_shared<TestSphere>();
    }
    static SpherePtr getRandomSphere() {
        return std::make_shared<RandomSphere>();
    }
    static SpherePtr getRepulsiveSphere() {
        return std::make_shared<RepulsiveSphere>();
    }

public:
    static SpherePtr getSphere(const std::string& name) {
        static std::unordered_map<std::string, SphereCreatorFn> creator_map_ = {
            { "test", getTestSphere },
            { "random", getRandomSphere },
            { "repulsive", getRepulsiveSphere }
        };

        auto it = creator_map_.find(name);
        if (it != creator_map_.end()) {
            return it->second();
        } else {
            return nullptr;
        }
    }
};

#endif // SPHERE_FACTORY_HPP
