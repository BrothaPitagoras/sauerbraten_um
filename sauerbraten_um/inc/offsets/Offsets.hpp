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

	inline uintptr_t player_health_offset = 0x0178;

	inline uintptr_t player_view_offset = 0x003C;

}
