#ifndef SPHERE_RENDERER_H
#define SPHERE_RENDERER_H

#include <memory>

class SphereRenderer {
public:
    virtual ~SphereRenderer() {}
    virtual void Init() = 0;
    virtual void Render() = 0;
};

typedef std::shared_ptr<SphereRenderer> SpherePtr;

#endif // SPHERE_RENDERER_H
