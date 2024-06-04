#include "imgui_framework.hpp"


// Forward declarations of helper functions
bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void CreateRenderTarget();
void CleanupRenderTarget();
// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Win32 message handler
// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (wParam == SIZE_MINIMIZED)
            return 0;
        Imgui_Framework::g_ResizeWidth = (UINT)LOWORD(lParam); // Queue resize
        Imgui_Framework::g_ResizeHeight = (UINT)HIWORD(lParam);
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }
    return ::DefWindowProcW(hWnd, msg, wParam, lParam);
}

void setWindowSize() {
    HWND gameWindow = FindWindow(nullptr, L"Cube 2: Sauerbraten");
    if (gameWindow != nullptr) {
        RECT targetWindow{};
        GetWindowRect(gameWindow, &targetWindow);
        Imgui_Framework::window_width = targetWindow.right - targetWindow.left;
        Imgui_Framework::window_height = targetWindow.bottom - targetWindow.top;

        GetWindowRect(gameWindow, &Imgui_Framework::windows_pos);
    }
}

void updateWindow(const HWND& window) {
    HWND gameWindow = FindWindow(nullptr, L"Cube 2: Sauerbraten");
    GetWindowRect(gameWindow, &Imgui_Framework::windows_pos);
    Imgui_Framework::window_width = Imgui_Framework::windows_pos.right - Imgui_Framework::windows_pos.left;
    Imgui_Framework::window_height = Imgui_Framework::windows_pos.bottom - Imgui_Framework::windows_pos.top;
    MoveWindow(window, Imgui_Framework::windows_pos.left, Imgui_Framework::windows_pos.top, Imgui_Framework::window_width, Imgui_Framework::window_height, true);
}

namespace Imgui_Framework {

    bool Imgui_Framework::initialize(HINSTANCE instance) {
        // Create application window
        //ImGui_ImplWin32_EnableDpiAwareness();
        WNDCLASSEXW wc = {};


        wc.cbSize = sizeof(WNDCLASSEXW);
        wc.style = CS_HREDRAW | CS_VREDRAW;
        wc.hInstance = instance;
        wc.lpfnWndProc = WndProc;
        wc.lpszClassName = L"External Overlay";

        setWindowSize();

        ::RegisterClassExW(&wc);
        hwnd = ::CreateWindowExW(
            WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED,
            wc.lpszClassName,
            L"Overlay",
            WS_POPUP,
            0,
            0,
            window_width,
            window_height,
            nullptr,
            nullptr,
            wc.hInstance,
            nullptr
        );

        SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), BYTE(255), LWA_ALPHA);
        
        {
            RECT clientArea{};
            GetClientRect(hwnd, &clientArea);

            RECT windowArea{};
            GetWindowRect(hwnd, &windowArea);

            POINT diff{};
            ClientToScreen(hwnd, &diff);

            const MARGINS margins{
                windowArea.left + (diff.x - windowArea.left),
                windowArea.top + (diff.y - windowArea.top),
                clientArea.right,
                clientArea.bottom
            };

            DwmExtendFrameIntoClientArea(hwnd, &margins);
        }

        // Initialize Direct3D
        if (!CreateDeviceD3D(hwnd))
        {
            CleanupDeviceD3D();
            ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
            return 1;
        }

        // Show the window
        ::ShowWindow(hwnd, SW_SHOW);
        ::UpdateWindow(hwnd);

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsLight();

        // Setup Platform/Renderer backends
        ImGui_ImplWin32_Init(hwnd);
        ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

        Imgui_Framework::running = true;

        // Load Fonts
        // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
        // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
        // - If the file cannot be loaded, the function will return a nullptr. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
        // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
        // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
        // - Read 'docs/FONTS.md' for more instructions and details.
        // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
        //io.Fonts->AddFontDefault();
        //io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
        //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
        //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
        //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
        //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
        //IM_ASSERT(font != nullptr);

        return running;
    }

    void Imgui_Framework::newFrame() {
        // Poll and handle messages (inputs, window resize, etc.)
        // See the WndProc() function below for our to dispatch events to the Win32 backend.
        MSG msg;
        while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                running = false;
        }

        // Handle window being minimized or screen locked
        //if (Imgui_Framework::g_SwapChainOccluded && Imgui_Framework::g_pSwapChain->Present(0, DXGI_PRESENT_TEST) == DXGI_STATUS_OCCLUDED)
        //{
        //    ::Sleep(10);
        //    continue;
        //}
        //Imgui_Framework::g_SwapChainOccluded = false;

        //// Handle window resize (we don't resize directly in the WM_SIZE handler)
        //if (Imgui_Framework::g_ResizeWidth != 0 && Imgui_Framework::g_ResizeHeight != 0)
        //{
        //    CleanupRenderTarget();
        //    Imgui_Framework::g_pSwapChain->ResizeBuffers(0, Imgui_Framework::g_ResizeWidth, Imgui_Framework::g_ResizeHeight, DXGI_FORMAT_UNKNOWN, 0);
        //    Imgui_Framework::g_ResizeWidth = Imgui_Framework::g_ResizeHeight = 0;
        //    CreateRenderTarget();
        //}


        // Start the Dear ImGui frame
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

    }

    void Imgui_Framework::render() {

        updateWindow(Imgui_Framework::hwnd);
        // Rendering
        ImGui::Render();
        const float clear_color_with_alpha[4] = { 0.f, 0.f, 0.f, 0.f };
        Imgui_Framework::g_pd3dDeviceContext->OMSetRenderTargets(1, &Imgui_Framework::g_mainRenderTargetView, nullptr);
        Imgui_Framework::g_pd3dDeviceContext->ClearRenderTargetView(Imgui_Framework::g_mainRenderTargetView, clear_color_with_alpha);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        // Present
        HRESULT hr = Imgui_Framework::g_pSwapChain->Present(1, 0);   // Present with vsync
        //HRESULT hr = g_pSwapChain->Present(0, 0); // Present without vsync
        Imgui_Framework::g_SwapChainOccluded = (hr == DXGI_STATUS_OCCLUDED);
    }

    void Imgui_Framework::destroy() {
        // Cleanup
        ImGui_ImplDX11_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();

        CleanupDeviceD3D();
        ::DestroyWindow(hwnd);
        ::UnregisterClassW(window_class.lpszClassName, window_class.hInstance);
    }
}


bool CreateDeviceD3D(HWND hWnd)
{
    // Setup swap chain
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 2;
    sd.BufferDesc.Width = 0;
    sd.BufferDesc.Height = 0;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    UINT createDeviceFlags = 0;
    //createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
    HRESULT res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &Imgui_Framework::g_pSwapChain, &Imgui_Framework::g_pd3dDevice, &featureLevel, &Imgui_Framework::g_pd3dDeviceContext);
    if (res == DXGI_ERROR_UNSUPPORTED) // Try high-performance WARP software driver if hardware is not available.
        res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_WARP, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &Imgui_Framework::g_pSwapChain, &Imgui_Framework::g_pd3dDevice, &featureLevel, &Imgui_Framework::g_pd3dDeviceContext);
    if (res != S_OK)
        return false;

    CreateRenderTarget();
    return true;
}

void CleanupDeviceD3D()
{
    CleanupRenderTarget();
    if (Imgui_Framework::g_pSwapChain) { Imgui_Framework::g_pSwapChain->Release(); Imgui_Framework::g_pSwapChain = nullptr; }
    if (Imgui_Framework::g_pd3dDeviceContext) { Imgui_Framework::g_pd3dDeviceContext->Release(); Imgui_Framework::g_pd3dDeviceContext = nullptr; }
    if (Imgui_Framework::g_pd3dDevice) { Imgui_Framework::g_pd3dDevice->Release(); Imgui_Framework::g_pd3dDevice = nullptr; }
}

void CreateRenderTarget()
{
    ID3D11Texture2D* pBackBuffer;
    Imgui_Framework::g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    Imgui_Framework::g_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &Imgui_Framework::g_mainRenderTargetView);
    pBackBuffer->Release();
}

void CleanupRenderTarget()
{
    if (Imgui_Framework::g_mainRenderTargetView) { Imgui_Framework::g_mainRenderTargetView->Release(); Imgui_Framework::g_mainRenderTargetView = nullptr; }
}