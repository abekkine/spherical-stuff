#include "Graphics.hpp"
#include "SphereFactory.hpp"
#include "Camera.hpp"
#include "ModelTransformer.hpp"

#include <iostream>
#include <cmath>

int main(int argc, char** argv) {

    std::string name = "testSphere";
    if (argc > 1) {
        name = std::string(argv[1]);
    }

    auto sphere = SphereFactory::getSphere(name);
    if (sphere == nullptr) {
        std::cout << "There's no such sphere named as [" << name << "]!\n";
        return 0;
    }

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

    sphere->Init();

    auto camera = std::make_unique<Camera>();

    auto transform = std::make_unique<ModelTransformer>();

    double angle = 0.0;
    while (!GFX.QuitCondition()) {
        GFX.PreRender();
        GFX.WorldMode();

        // Render World
        camera->Update();

        transform->Update();

        sphere->Render();

        GFX.PostRender();
    }

    GFX.Quit();

    return 0;
}