#include "cheats/Visuals.hpp"

void Cheats::Visuals::ESP(Player* player, ProcessManagement* proc) {
	int playerCount = proc->ReadMemory<int>(proc->moduleBaseAddress + Offsets::o_player_count);
	Matrix* viewMatrix = proc->ReadMatrix(proc->moduleBaseAddress + Offsets::o_view_matrix);
	
	uintptr_t entityListaddr = proc->ReadMemory<uintptr_t>(proc->moduleBaseAddress + Offsets::o_entity_list);

	auto entityList = new EntityList(entityListaddr, playerCount, proc);
	ImVec4* color;

	for (auto otherPlayer = entityList->playerList.begin(); otherPlayer != entityList->playerList.end(); ++otherPlayer)
	{
		Vector2 headScreenPos{};
		Vector2 footScreenPos{};

		bool enemy = player->getCachedPlayer().team != otherPlayer->getCachedPlayer().team;

		if (otherPlayer->getCachedPlayer().entity_state == 1) {
			continue;
		}

		if (enemy)
		{
			color = new ImVec4(255.0f, 0.0f, 0.0f, 255.0f);
		}
		else {
			color = new ImVec4(0.0f, 255.0f, 0.0f, 255.0f);
		}

		// if any w2s false then continue
		if (!viewMatrix->WorldToScreen(otherPlayer->getCachedPlayer().pos, Imgui_Framework::window_width, Imgui_Framework::window_height, headScreenPos)
			|| !viewMatrix->WorldToScreen(otherPlayer->getFeetPos(), Imgui_Framework::window_width, Imgui_Framework::window_height, footScreenPos)) {
			continue;
		}

		ImVec2* guiHeadPos = new ImVec2(headScreenPos.x, headScreenPos.y);
		ImVec2* guiFootPos = new ImVec2(footScreenPos.x, footScreenPos.y);

		drawBox(guiHeadPos, guiFootPos, color);
	}

}



void Cheats::Visuals::drawBox(ImVec2* headPos, ImVec2* feetPos, ImVec4* color) {

	float boxHeight = headPos->y - feetPos->y;
	float boxWidth = boxHeight / 2.6f;

	float halfBoxWidth = boxWidth / 2.0f;

	ImVec2 startBoxPos(headPos->x - halfBoxWidth, headPos->y);
	ImVec2 endBoxPos(feetPos->x + halfBoxWidth, feetPos->y);

	ImGui::GetBackgroundDrawList()->AddRect(startBoxPos, endBoxPos, IM_COL32(color->x, color->y, color->z, color->w), 0.0f, NULL, 1.5f);
}

void Cheats::Visuals::drawFovCircle() {
	ImVec2 center{ (float)Imgui_Framework::window_width / 2, (float)Imgui_Framework::window_height / 2 + 12 /* magic number*/};
	ImGui::GetBackgroundDrawList()->AddCircle(center, CheatOptions::Aimbot_FOV, IM_COL32(255, 255, 255, 255), 0, 0.001f);
}
