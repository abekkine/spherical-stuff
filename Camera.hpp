#ifndef CAMERA_HPP
#define CAMERA_HPP

#define GLM_ENABLE_EXPERIMENTAL

#include <glm.hpp>
#include <ext.hpp>
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtx/rotate_vector.hpp>
#include <gtc/matrix_inverse.hpp>

class Camera {
private:
    glm::mat4 projection_;
    glm::mat4 view_;

public:
    Camera() {
        projection_ = glm::mat4(1);
        view_ = glm::mat4(1);
    }
    void Update() {
        glLoadIdentity();
        view_ = glm::lookAt(
            glm::vec3(250.0, 0.0, 150.0),
            glm::vec3(0.0, 0.0, 0.0),
            glm::vec3(0.0, 0.0, 1.0)
        );
        projection_ = glm::perspective(
            glm::radians(60.0),
            1.0,
            0.0,
            1000.0
        );
        glm::mat4 mvp = projection_ * view_;
        glMatrixMode(GL_PROJECTION);
        glLoadMatrixf(glm::value_ptr(mvp));
    }
};

#endif // CAMERA_HPP