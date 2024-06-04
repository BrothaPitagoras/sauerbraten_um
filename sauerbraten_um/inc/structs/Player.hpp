#pragma once

#include "includes.h"
#include "offsets/Offsets.hpp"
#include "structs/Vector3.hpp"
#include "processManagement.hpp"

class Player
{
public:

	uintptr_t pointerPlayer;
	Offsets::PlayerPadded playerPadded;
	Vector3 feetpos;

	Player(uintptr_t pointerPlayer);

	Player(Vector3 pointerPlayer);


	Offsets::PlayerPadded getCachedPlayer();

	Offsets::PlayerPadded getPlayerPadded(uintptr_t addr);

	void refreshPlayerPadded();

	bool setView(Vector3& viewVector);

	bool setHealth(int health);

};