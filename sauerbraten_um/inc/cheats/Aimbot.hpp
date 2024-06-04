#pragma once

#include "includes.h"
#include "structs/Player.hpp"
#include "processManagement.hpp"
#include "imgui_framework.hpp"
#include "offsets/CheatOptions.hpp"
#include "structs/EntityList.hpp"

namespace Cheats::Aimbot {

	void Aimbot(Player* localPlayer, ProcessManagement* proc);

}