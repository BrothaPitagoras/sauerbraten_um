#pragma once

#include "includes.h"

#include <tchar.h>
#include <dwmapi.h>

namespace Imgui_Framework {

	// Data
	inline ID3D11Device*			g_pd3dDevice = nullptr;
	inline ID3D11DeviceContext*		g_pd3dDeviceContext = nullptr;
	inline IDXGISwapChain*			g_pSwapChain = nullptr;
	inline bool                     g_SwapChainOccluded = false;
	inline UINT                     g_ResizeWidth = 0, g_ResizeHeight = 0;
	inline ID3D11RenderTargetView*	g_mainRenderTargetView = nullptr;

	inline RECT						windows_pos;
	inline int						window_width = 1600;
	inline int						window_height = 900;
	inline bool						running = false;

	inline WNDCLASSEXW window_class = { };
	inline HWND hwnd{ nullptr };


	bool initialize(HINSTANCE instance);
	void newFrame();
	void render();
	void destroy();
}