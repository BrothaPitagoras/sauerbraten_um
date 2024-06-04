#pragma once

#include "includes.h"
#include "structs/Player.hpp"
#include "processManagement.hpp"
#include "imgui_framework.hpp"
#include "offsets/CheatOptions.hpp"

namespace Cheats::Aimbot {

	void Aimbot(Player* localPlayer);

	Player* getClosestTargetToCrosshair(Player* localPlayer, Matrix* viewMatrix, uintptr_t& entityList, int playerCount);

}