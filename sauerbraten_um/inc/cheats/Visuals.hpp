#pragma once
#include "includes.h"
#include "structs/Player.hpp"
#include "offsets/Offsets.hpp"
#include "imgui_framework.hpp"
#include "processManagement.hpp"

namespace Cheats::Visuals {

	void ESP(Player* localPlayer);

	void drawBox(ImVec2* headPos, ImVec2* feetPos, ImVec4* color);
}