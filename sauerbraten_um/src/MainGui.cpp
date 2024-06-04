#include "MainGui.hpp"

void MainGui::renderGui() {

    if (GetAsyncKeyState(VK_END) & 1) {
        MainGui::shouldRender = !MainGui::shouldRender;

        long style = GetWindowLongPtr(Imgui_Framework::hwnd, GWL_EXSTYLE);
        style = MainGui::shouldRender ? (style & ~WS_EX_LAYERED) : (style | WS_EX_LAYERED);
        SetWindowLongPtr(Imgui_Framework::hwnd, GWL_EXSTYLE, style);

        SetForegroundWindow(MainGui::shouldRender ? Imgui_Framework::hwnd : FindWindow(nullptr, L"Cube 2: Sauerbraten"));
    }

    // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
    if (shouldRender){
        ImGui::Begin("MainMenu");                          

        if (ImGui::CollapsingHeader("ESP Config"))
        {
            ImGui::Checkbox("ESP", &CheatOptions::ESP);
        }

        if (ImGui::CollapsingHeader("Aimbot"))
        {
            ImGui::Checkbox("Enable Aimbot", &CheatOptions::Aimbot_Enable);
            ImGui::Checkbox("Enable Aimbot FOV", &CheatOptions::Aimbot_FOV_Enable);
            if (CheatOptions::Aimbot_FOV_Enable)
            {
                ImGui::SliderFloat("Aimbot FOV", &CheatOptions::Aimbot_FOV, 0.0f, 300.0f);
            }
        }


        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
    }
}