#include "window.h"
#include <iostream>

// Constructor to accept the GLFW window pointer
Window::Window(GLFWwindow* window) : window_(window) {}

void Window::ShowExampleImGuiPopup() {
    if (show_popup_) {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiCond_FirstUseEver);
        ImGui::Begin("Example Popup", &show_popup_);
        ImGui::Text("Hello, world!");
        if (ImGui::Button("Close")) {
            show_popup_ = false;  // Hide the popup window
        }
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}

// Define the static error callback function
void Window::glfw_error_callback(int error, const char* description) {
    std::cout << "Glfw Error " << error << ": " << description << std::endl;
}
