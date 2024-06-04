#include "cheats/Aimbot.hpp"

void Cheats::Aimbot::Aimbot(Player* localPlayer) {
	int playerCount = ProcessManagement::ReadMemory<int>(ProcessManagement::moduleBaseAddress + Offsets::o_player_count);
	uintptr_t entityList = ProcessManagement::ReadMemory<uintptr_t>(ProcessManagement::moduleBaseAddress + Offsets::o_entity_list);
	Matrix* viewMatrix = ProcessManagement::ReadMatrix(ProcessManagement::moduleBaseAddress + Offsets::o_view_matrix);

	Player* target = Cheats::Aimbot::getClosestTargetToCrosshair(localPlayer, viewMatrix, entityList, playerCount);

	if (target == NULL) {
		return;
	}

	std::string resultText = std::string(target->getCachedPlayer().name);

	ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), ImGui::GetFontSize(), ImVec2(200, 200), IM_COL32(255, 255, 255, 255), resultText.c_str());


	Vector3 resultVector = target->getCachedPlayer().pos - localPlayer->getCachedPlayer().pos;

	ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), ImGui::GetFontSize(), ImVec2(200, 300), IM_COL32(255, 255, 255, 255), resultVector.toString().c_str());


	float yaw = -atan2(resultVector.x, resultVector.y) * (180 / M_PI);
	float pitch = atan2(resultVector.z, sqrt(resultVector.x * resultVector.x + resultVector.y * resultVector.y)) * (180 / M_PI);

	Vector3 view = Vector3(yaw, pitch, 0.0f);

	ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), ImGui::GetFontSize(), ImVec2(200, 350), IM_COL32(255, 255, 255, 255), view.toString().c_str());
	
	localPlayer->setView(view);
}



Player* Cheats::Aimbot::getClosestTargetToCrosshair(Player* localPlayer, Matrix* viewMatrix, uintptr_t& entityList, int playerCount)
{
	Vector2 centerScreen{ (float)Imgui_Framework::window_width/ 2, (float)Imgui_Framework::window_height/ 2 };
	Vector2 entityHeadPos2D;

	Player* bestTarget = NULL;

	int closestToCrosshair{ INT32_MAX };
	float fov = 300.0f;

	for (int i = 0; i < playerCount; i++)
	{
		uintptr_t entityAddr = ProcessManagement::ReadMemory<uintptr_t>(entityList + (0x8 * i));
		Player* otherPlayer = new Player(entityAddr);
		bool enemy = localPlayer->getCachedPlayer().team != localPlayer->getCachedPlayer().team;


		if (otherPlayer->getCachedPlayer().entity_state != 1 && enemy && otherPlayer->pointerPlayer != NULL) {

			viewMatrix->WorldToScreen(otherPlayer->getCachedPlayer().pos, Imgui_Framework::window_width, Imgui_Framework::window_height, entityHeadPos2D);

			float distance = sqrt((centerScreen.x - entityHeadPos2D.x) * (centerScreen.x - entityHeadPos2D.x) + (centerScreen.y - entityHeadPos2D.y) * (centerScreen.y - entityHeadPos2D.y));

			if (CheatOptions::Aimbot_FOV_Enable) {
				if (distance < CheatOptions::Aimbot_FOV && distance < closestToCrosshair)
				{
					bestTarget = otherPlayer;
					closestToCrosshair = distance;
				}
			}
			else {
				if (distance < fov)
				{
					fov = distance;
					bestTarget = otherPlayer;
				}
			}
		}

	}

	return bestTarget;
}
