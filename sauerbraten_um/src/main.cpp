// Dear ImGui: standalone example application for DirectX 11

// Learn about Dear ImGui:
// - FAQ                  https://dearimgui.com/faq
// - Getting Started      https://dearimgui.com/getting-started
// - Documentation        https://dearimgui.com/docs (same as your local docs/ folder).
// - Introduction, links and more at the top of imgui.cpp

#include "includes.h"
#include "imgui_framework.hpp"
#include "MainGui.hpp"
#include "cheats/Cheats.hpp"
#include "processManagement.hpp"

void CreateRenderTarget();
void CleanupRenderTarget();

// Main code
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT nCmdShow)
{
    Imgui_Framework::initialize(hInstance);

    auto procMainExe = ProcessManagement();

    if (!procMainExe.AttachAndFillModuleBaseAddress(L"sauerbraten.exe")) {
        return 0;
    }

    // Main loop
    while (Imgui_Framework::running)
    {
        Imgui_Framework::newFrame();

        MainGui::renderGui();

        Cheats::run(&procMainExe);

        Imgui_Framework::render();
    }

    Imgui_Framework::destroy();

    return 0;
}