#include "structs/EntityList.hpp"

EntityList::EntityList(uintptr_t entityListAddr, int size, ProcessManagement* proc) {
	EntityList::playerList = std::vector<Player>();
	
	for (int i = 0; i < size; i++)
	{
		uintptr_t entityAddr = proc->ReadMemory<uintptr_t>(entityListAddr + (i * 0x08));
		EntityList::playerList.push_back(Player(entityAddr, proc));
	}
}

Player* EntityList::getClosestTargetToCrosshair(Player* localPlayer, Matrix* viewMatrix)
{
	Vector2 centerScreen{ (float)Imgui_Framework::window_width / 2, (float)Imgui_Framework::window_height / 2 };
	Vector2 entityHeadPos2D;

	Player* bestTarget = nullptr;

	int closestToCrosshair{ INT32_MAX };
	float fov = 300.0f;

	for (auto otherPlayer = this->playerList.begin(); otherPlayer != this->playerList.end(); ++otherPlayer)
	{
		bool enemy = localPlayer->getCachedPlayer().team != localPlayer->getCachedPlayer().team;


		if (otherPlayer->getCachedPlayer().entity_state != 1 && enemy && otherPlayer->pointerPlayer != NULL) {

			viewMatrix->WorldToScreen(otherPlayer->getCachedPlayer().pos, Imgui_Framework::window_width, Imgui_Framework::window_height, entityHeadPos2D);

			float distance = sqrt((centerScreen.x - entityHeadPos2D.x) * (centerScreen.x - entityHeadPos2D.x) + (centerScreen.y - entityHeadPos2D.y) * (centerScreen.y - entityHeadPos2D.y));

			if (CheatOptions::Aimbot_FOV_Enable) {
				if (distance < CheatOptions::Aimbot_FOV && distance < closestToCrosshair)
				{
					bestTarget = &(*otherPlayer);
					closestToCrosshair = distance;
				}
			}
			else {
				if (distance < fov)
				{
					fov = distance;
					bestTarget = &(*otherPlayer);
				}
			}
		}

	}

	return bestTarget;
}