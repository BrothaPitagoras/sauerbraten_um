#include "cheats/Cheats.hpp"

void Cheats::run(ProcessManagement* proc) {


	Player* localPlayer = new Player(proc->ReadMemory<uintptr_t>(proc->moduleBaseAddress + Offsets::o_local_player), proc);

	if (CheatOptions::ESP)
	{
		Cheats::Visuals::ESP(localPlayer, proc);
	}

	if (GetAsyncKeyState(VK_LCONTROL)) {

		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), ImGui::GetFontSize(), ImVec2(200, 350), IM_COL32(255, 255, 255, 255), localPlayer->getCachedPlayer().view.toString().c_str());

	}
	if (CheatOptions::Aimbot_Enable)
	{
		if (GetAsyncKeyState(VK_LMENU)) {
			
			Cheats::Aimbot::Aimbot(localPlayer, proc);
		}
		if (CheatOptions::Aimbot_FOV_Enable)
		{
			Cheats::Visuals::drawFovCircle();
		}
	}


}