#pragma once

#include "includes.h"
#include "structs/Vector3.hpp"

namespace Offsets {

	// BASEMODULE + o_local_player
	inline uintptr_t o_local_player = 0x2A5730;

	inline uintptr_t o_entity_list = 0x346C90;

	inline uintptr_t o_player_count = 0x346C9C;

	inline uintptr_t o_view_matrix = 0x32D040;

	inline uintptr_t o_game_mode = 0x26F6B0;

	inline uintptr_t o_game_timer = 0x26DD4C;



	class PlayerPadded {
	public:
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

	inline uintptr_t player_health_offset = 0x0178;

	inline uintptr_t player_view_offset = 0x003C;

}
