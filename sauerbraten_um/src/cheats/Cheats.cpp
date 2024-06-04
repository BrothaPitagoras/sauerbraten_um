#include "cheats/Cheats.hpp"

void Cheats::run() {
	Player* localPlayer = new Player(ProcessManagement::ReadMemory<uintptr_t>(ProcessManagement::moduleBaseAddress + Offsets::o_local_player));

	if (CheatOptions::ESP)
	{
		Cheats::Visuals::ESP(localPlayer);
	}

	if (GetAsyncKeyState(VK_LCONTROL)) {

		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), ImGui::GetFontSize(), ImVec2(200, 350), IM_COL32(255, 255, 255, 255), localPlayer->getCachedPlayer().view.toString().c_str());

	}
	if (CheatOptions::Aimbot_Enable)
	{
		if (GetAsyncKeyState(VK_LMENU)) {
			
			Cheats::Aimbot::Aimbot(localPlayer);
		}
	}


}