#pragma once

#include "includes.h"
#include "structs/Player.hpp"
#include "processManagement.hpp"
#include "imgui_framework.hpp"
#include "offsets/CheatOptions.hpp"

class EntityList
{
public:
	std::vector<Player> playerList{};

	EntityList(uintptr_t entityListAddr, int size, ProcessManagement* proc);

	Player* getClosestTargetToCrosshair(Player* localPlayer, Matrix* viewMatrix);

};
