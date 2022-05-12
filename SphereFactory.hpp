#ifndef SPHERE_FACTORY_HPP
#define SPHERE_FACTORY_HPP

#include "SphereRenderer.h"
#include "TestSphereRenderer.hpp"

#include <functional>
#include <unordered_map>

class SphereFactory {
private:
    typedef std::function<SpherePtr()> SphereCreatorFn;

    static SpherePtr getTestSphere() {
        return std::make_shared<TestSphereRenderer>();
    }

public:
    static SpherePtr getSphere(const std::string& name) {
        static std::unordered_map<std::string, SphereCreatorFn> creator_map_ = {
            { "testSphere", getTestSphere }
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
