#include "structs/EntityList.hpp"

EntityList::EntityList(uintptr_t entityListAddr, int size, ProcessManagement* proc) {
	
	for (int i = 0; i < size; i++)
	{
		uintptr_t entityAddr = proc->ReadMemory<uintptr_t>(entityListAddr + (i * 0x08));
		EntityList::playerList.emplace_back(entityAddr, proc);
	}
}

Player* EntityList::getClosestTargetToCrosshair(Player* localPlayer, Matrix* viewMatrix)
{
	Vector2 centerScreen{ (float)Imgui_Framework::window_width / 2, (float)Imgui_Framework::window_height / 2 };
	Vector2 entityHeadPos2D;

	Player* bestTarget = nullptr;

	float closestToCrosshair{ INT32_MAX * 1.0f };
	float fov = 300.0f;

	for (auto otherPlayer = this->playerList.begin(); otherPlayer != this->playerList.end(); ++otherPlayer)
	{
		bool enemy = localPlayer->getCachedPlayer().team != otherPlayer->getCachedPlayer().team;


		if (otherPlayer->getCachedPlayer().entity_state != 1 && enemy && otherPlayer->pointerPlayer != NULL) {

			viewMatrix->WorldToScreen(otherPlayer->getCachedPlayer().pos, Imgui_Framework::window_width, Imgui_Framework::window_height, entityHeadPos2D);

			float distance = centerScreen.getDistance(&entityHeadPos2D);


			if (CheatOptions::Aimbot_FOV_Enable 
				&& distance < CheatOptions::Aimbot_FOV && distance < closestToCrosshair) {
				bestTarget = std::to_address(otherPlayer);
				closestToCrosshair = distance;
			}
			else if (distance < fov){
				fov = distance;
				bestTarget = std::to_address(otherPlayer);
			}
		}

	}

	return bestTarget;
}