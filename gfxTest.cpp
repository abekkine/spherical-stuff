#include "Graphics.hpp"

#include <iostream>
#include <cmath>

// Camera stuff
#include <glm.hpp>
#include <ext.hpp>
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtx/rotate_vector.hpp>
#include <gtc/matrix_inverse.hpp>
// End

glm::mat4 mProjection(1.0);
glm::mat4 mView(1.0);
void camera_update() {
    glLoadIdentity();
    mView = glm::lookAt(
        glm::vec3(250.0, 0.0, 150.0),
        glm::vec3(0.0, 0.0, 0.0),
        glm::vec3(0.0, 0.0, 1.0)
    );
    mProjection = glm::perspective(
        glm::radians(60.0),
        1.0,
        0.0,
        1000.0
    );
    glm::mat4 mvp = mProjection * mView;
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(mvp));
}

void render_sphere() {
    const double kPi = 3.141592653;
    const double r = 100.0;
    static float a = 0.0;
    glRotatef(a, 0.0, 0.0, 1.0);
    a += 0.5;
    glPointSize(3.0);
    glColor3f(1.0, 0.5, 0.0);
    glBegin(GL_POINTS);
    for (double theta=0.0; theta < 2.0 * kPi; theta += 0.1 * kPi) {
        for (double phi=-kPi; phi < kPi; phi += 0.1 * kPi) {
            double x, y, z;
            x = r * cos(theta) * cos(phi);
            y = r * sin(theta) * cos(phi);
            z = r * sin(phi);
            glVertex3d(
                x,
                y,
                z
            );
        }
    }
    glEnd();
}

int main() {

    GFX.SetWindowSize(800, 800);
    GFX.SetWindowPosition(1970, 50);
    GFX.SetWindowTitle("spherical");
    GFX.SetCenter(0.0, 0.0);
    GFX.SetPixelSize(1.0);
    GFX.RegisterKeyProcessor([](const int key, const int mods){
        switch (key) {
        case GLFW_KEY_ESCAPE:
            GFX.RequestQuit(); break;
        }
    });
    GFX.Init();
   
    while (!GFX.QuitCondition()) {
        GFX.PreRender();
        GFX.WorldMode();

        // Render World
        camera_update();
        render_sphere();

        // GFX.UiMode();
        // TODO : Render UI

        GFX.PostRender();
    }

    GFX.Quit();

    return 0;
}