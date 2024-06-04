#include "cheats/Aimbot.hpp"

void Cheats::Aimbot::Aimbot(Player* localPlayer, ProcessManagement* proc) {
	int playerCount = proc->ReadMemory<int>(proc->moduleBaseAddress + Offsets::o_player_count);
	uintptr_t entityListPtr = proc->ReadMemory<uintptr_t>(proc->moduleBaseAddress + Offsets::o_entity_list);
	
	auto entityList = new EntityList(entityListPtr, playerCount, proc);

	Matrix* viewMatrix = proc->ReadMatrix(proc->moduleBaseAddress + Offsets::o_view_matrix);

	Player* target = entityList->getClosestTargetToCrosshair(localPlayer, viewMatrix);

	if (target == nullptr) {
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
	
	localPlayer->setView(view, proc);
}


