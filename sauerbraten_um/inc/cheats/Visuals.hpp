#pragma once
#include "includes.h"
#include "structs/Player.hpp"
#include "structs/EntityList.hpp"
#include "offsets/Offsets.hpp"
#include "offsets/CheatOptions.hpp"
#include "imgui_framework.hpp"
#include "processManagement.hpp"

namespace Cheats::Visuals {

	void ESP(Player* localPlayer, ProcessManagement* proc);

	void drawBox(ImVec2* headPos, ImVec2* feetPos, ImVec4* color);

	void drawFovCircle();
}