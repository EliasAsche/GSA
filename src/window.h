#pragma once
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

class Window {
public:
    Window(GLFWwindow* window);
    void ShowExampleImGuiPopup();
    static void glfw_error_callback(int error, const char* description);

private:
    GLFWwindow* window_;
    bool show_popup_ = true;  // Popup visibility
};
