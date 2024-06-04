#include "cheats/Visuals.hpp"

void Cheats::Visuals::ESP(Player* player) {
	int playerCount = ProcessManagement::ReadMemory<int>(ProcessManagement::moduleBaseAddress + Offsets::o_player_count);
	Matrix* viewMatrix = ProcessManagement::ReadMatrix(ProcessManagement::moduleBaseAddress + Offsets::o_view_matrix);
	
	uintptr_t entityList = ProcessManagement::ReadMemory<uintptr_t>(ProcessManagement::moduleBaseAddress + Offsets::o_entity_list);

	ImVec4* color;

	for (int i = 0; i < playerCount; ++i)
	{
		Vector2 headScreenPos{};
		Vector2 footScreenPos{};

		uintptr_t entityAddr = ProcessManagement::ReadMemory<uintptr_t>(entityList + (0x8 * i));

		Player* otherPlayer = new Player(entityAddr);
		Offsets::PlayerPadded playerpadded = otherPlayer->getCachedPlayer();
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
			|| !viewMatrix->WorldToScreen(otherPlayer->feetpos, Imgui_Framework::window_width, Imgui_Framework::window_height, footScreenPos)) {
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
