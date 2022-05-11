#ifndef GRAPHICS_HPP_
#define GRAPHICS_HPP_

#include "Viewport.hpp"
#include "Vector.hpp"

#include <string>
#include <vector>
#include <functional>
#include <stdexcept>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#ifdef _WIN32
#undef APIENTRY
#endif

#define GFX Graphics::Instance()

typedef std::vector<std::string> StringList;

class Graphics {
public:
    enum {
        button__NONE = 0,
        button__LEFT = 1,
        button__MIDDLE = 2,
        button__RIGHT = 3,
        button__PRESSED = 4,
        button__RELEASED = 5,

        mod__NONE = 0,
        mod__SHIFT = 1,
        mod__CTRL = 2,
        mod__ALT = 4,
        mod__WIN = 8,
    };
private:
    // members
    GLFWwindow * window_;
    int width_;
    int height_;
    int window_x_, window_y_;
    std::string title_;
    bool full_screen_;
    Viewport viewport_;
    std::function<void(const int, const int)> key_cb_;
    std::function<void(const double &, const double &)> cursor_cb_;
    std::function<void(const int, const int, const int)> button_cb_;
    std::function<void(const double &)> scroll_cb_;
    std::function<void(StringList)> drop_cb_;

public:
    // methods
    static Graphics & Instance() {
        static Graphics instance;
        return instance;
    }
    GLFWwindow *& GetWindow() {
        return window_;
    }
    void Init() {

        if (!glfwInit()) {
            throw std::runtime_error("Unable to initialize GLFW!");
        }
        glfwWindowHint(GLFW_SAMPLES, 8);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        viewport_.SetWindowSize(width_, height_);
        viewport_.Update();
        if (full_screen_) {
            window_ = glfwCreateWindow(
                width_, height_,
                title_.c_str(),
                glfwGetPrimaryMonitor(),
                NULL
            );
        }
        else {
            window_ = glfwCreateWindow(
                width_, height_,
                title_.c_str(),
                NULL,
                NULL
            );
        }

        if (!window_) {
            Quit();
            throw std::runtime_error("Unable to create window!");
        }

        glfwSetWindowPos(window_, window_x_, window_y_);
        glfwMakeContextCurrent(window_);

        glfwSetKeyCallback(window_, key_callback);
        glfwSetCursorPosCallback(window_, cursor_callback);
        glfwSetMouseButtonCallback(window_, mouse_callback);
        glfwSetScrollCallback(window_, scroll_callback);
        glfwSetDropCallback(window_, drop_callback);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_MULTISAMPLE);
    }
    void SetWindowTitle(const std::string & title) {
        title_ = title;
    }
    void SetWindowPosition(const int x, const int y) {
        window_x_ = x;
        window_y_ = y;
    }
    void SetWindowSize(const int width, const int height) {

        width_ = width;
        height_ = height;
    }
    void SetPixelSize(const double & size) {

        viewport_.SetPixelSize(size);
        viewport_.Update();
    }
    double GetPixelSize() {
        const double ps = viewport_.GetPixelSize();
        return ps;
    }
    void SetCenter(const double & x, const double & y) {
        viewport_.SetCenter(Vector(x, y));
        viewport_.Update();
    }
    void GetViewport(Viewport* & vp) {
        vp = &viewport_;
    }
    void Quit() {
        glfwDestroyWindow(window_);
        glfwTerminate();
    }
    bool QuitCondition() {
        return glfwWindowShouldClose(window_);
    }
    void RequestQuit() {
        glfwSetWindowShouldClose(window_, GLFW_TRUE);
    }
    void Hide() {
        glfwIconifyWindow(window_);
    }
    void Show() {
        glfwRestoreWindow(window_);
    }
    void UiMode() {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0.0, width_, height_, 0.0, -1.0, 1.0);
        glMatrixMode(GL_MODELVIEW);
    }
    void WorldMode() {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        viewport_.Ortho();
        glMatrixMode(GL_MODELVIEW);
    }
    void PreRender() {
        glClear(GL_COLOR_BUFFER_BIT);
    }
    void PostRender() {
        glfwSwapBuffers(window_);
        glfwPollEvents();
    }
    void RegisterKeyProcessor(std::function<void(const int, const int)> cb) {
        key_cb_ = cb;
    }
    void RegisterCursorProcessor(std::function<void(const double &, const double &)> cb) {
        cursor_cb_ = cb;
    }
    void RegisterMouseProcessor(std::function<void(const int, const int, const int)> cb) {
        button_cb_ = cb;
    }
    void RegisterScrollCallback(std::function<void(const double &)> cb) {
        scroll_cb_ = cb;
    }
    void RegisterDropCallback(std::function<void(StringList)> cb) {
        drop_cb_ = cb;
    }

    void KeyCallback(const int key, const int mods) {
        key_cb_(key, mods);
    }
    void CursorCallback(const double & x, const double & y) {
        cursor_cb_(x, y);
    }
    void MouseCallback(const int button_id, const int button_action, const int mods) {
        button_cb_(button_id, button_action, mods);
    }
    void ScrollCallback(const double & offset) {
        scroll_cb_(offset);
    }
    void DropCallback(StringList paths) {
        drop_cb_(paths);
    }

private:
    // methods
    Graphics()
    : window_(0)
    , width_(200)
    , height_(200)
    , window_x_(50)
    , window_y_(50)
    , title_("None")
    , full_screen_(false)
    {
        key_cb_ = [] (const int key, const int mods) {
            // Quit if ESC pressed.
            if (key == GLFW_KEY_ESCAPE) {
                GFX.RequestQuit();
            }
        };
        cursor_cb_ = [] (const double & x, const double & y) {
            (void)x;
            (void)y;
            // Do nothing.
        };
        button_cb_ = [] (const int id, const int action, const int mods) {
            (void)id;
            (void)action;
            (void)mods;
            // Do nothing.
        };
        scroll_cb_ = [] (const double & offset) {
            (void)offset;
            // Do nothing.
        };
        drop_cb_ = [] (StringList paths) {
            (void)paths;
            // Do nothing.
        };
    }
    ~Graphics() {}

private:
    // static callbacks
    static void key_callback(GLFWwindow * win, int key, int scancode, int action, int mods) {
        (void)win;
        (void)scancode;

        if (GLFW_RELEASE == action) {
            GFX.KeyCallback(key, mods);
        }
    }
    static void cursor_callback(GLFWwindow * win, double x, double y) {
        (void)win;
        
        GFX.CursorCallback(x, y);
    }
    static void mouse_callback(GLFWwindow * win, int button, int action, int mods) {
        (void)win;
        (void)mods;

        int button_action = button__NONE;
        switch (action) {
        case GLFW_PRESS:
            button_action = button__PRESSED; break;
        case GLFW_RELEASE:
            button_action = button__RELEASED; break;
        }

        int button_id = button__NONE;
        switch(button) {
        case GLFW_MOUSE_BUTTON_LEFT:
            button_id = button__LEFT; break;
        case GLFW_MOUSE_BUTTON_MIDDLE:
            button_id = button__MIDDLE; break;
        case GLFW_MOUSE_BUTTON_RIGHT:
            button_id = button__RIGHT; break;
        }

        GFX.MouseCallback(button_id, button_action, mods);
    }
    static void scroll_callback(GLFWwindow * win, double xoffset, double yoffset) {
        (void)win;
        (void)xoffset;
        // Use only y-offset for mouse wheel scroll.
        GFX.ScrollCallback(yoffset);
    }
    static void drop_callback(GLFWwindow * win, int count, const char** paths) {
        (void)win;
        StringList path_list;
        for (int i=0; i<count; ++i) {
            path_list.push_back(std::string(paths[i]));
        }
        GFX.DropCallback(path_list);
    }
};

#endif // GRAPHICS_HPP_
