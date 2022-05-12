#ifndef MODEL_TRANSFORMER_HPP
#define MODEL_TRANSFORMER_HPP

#include "Graphics.hpp"

class ModelTransformer {
private:
    double angle_;

public:
    ModelTransformer() {
        angle_ = 0.0;
    }
    void Update() {
        glRotatef(angle_, 0.0, 0.0, 1.0);
        glPointSize(3.0);
        glColor3f(1.0, 0.5, 0.0);

        angle_ += 0.5;
    }
};

#endif // MODEL_TRANSFORMER_HPP
