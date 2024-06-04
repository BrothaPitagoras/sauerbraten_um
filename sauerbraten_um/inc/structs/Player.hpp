#pragma once

#include "includes.h"
#include "offsets/Offsets.hpp"
#include "structs/Vector3.hpp"
#include "processManagement.hpp"

struct PaddedPlayer {
	Vector3 pos;		//0x0000
	char pad_000C[48];	//0x000C
	Vector3 view;		//0x003C
	char pad_0048[47];	//0x0048
	int8_t entity_state; //0x0077
	char pad_0078[256]; //0x0078
	uint32_t health;	//0x0178
	char pad_017C[128]; //0x017C
	int8_t shooting;	//0x01FC
	char pad_01FD[119]; //0x01FD
	char name[16];		//0x0274
	char pad_0284[256]; //0x0284
	char team[4];		//0x0384
};

class Player
{
public:

	uintptr_t pointerPlayer;
	PaddedPlayer paddedPlayer;

	Player(uintptr_t pointerPlayer, ProcessManagement* proc);

	bool setView(Vector3& viewVector, ProcessManagement* proc);

	bool setHealth(int health, ProcessManagement* proc);

	PaddedPlayer getCachedPlayer();

	Vector3 getFeetPos();

};

