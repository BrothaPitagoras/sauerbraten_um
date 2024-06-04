#pragma once

#include "includes.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_win32.h>
#include <imgui/imgui_impl_dx11.h>
#include <d3d11.h>
#include <tchar.h>
#include <dwmapi.h>
#include "imgui_framework.hpp"
#include "offsets/CheatOptions.hpp"

namespace MainGui {
	inline bool shouldRender = true;

	void renderGui();
}