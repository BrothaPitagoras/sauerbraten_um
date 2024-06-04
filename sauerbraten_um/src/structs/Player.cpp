#include "structs/player.hpp"

Player::Player(uintptr_t pointerPlayer) {
	this->pointerPlayer = pointerPlayer;
	this->playerPadded = getPlayerPadded(pointerPlayer);
	this->feetpos = this->playerPadded.pos - Vector3(0.0f, 0.0f, 16.0f);
}

Offsets::PlayerPadded Player::getCachedPlayer() {
	return this->playerPadded;
};

Offsets::PlayerPadded Player::getPlayerPadded(uintptr_t addr) {
	return ProcessManagement::ReadMemory<Offsets::PlayerPadded>(addr);
};

void Player::refreshPlayerPadded() {
	this->playerPadded = getPlayerPadded(pointerPlayer);
	this->feetpos = this->playerPadded.pos - Vector3(0.0f, 0.0f, 16.0f);
};

bool Player::setView(Vector3& viewVector) {
	return ProcessManagement::WriteMemory<Vector3>(pointerPlayer + Offsets::player_view_offset, viewVector);
}

bool Player::setHealth(int health) {
	return ProcessManagement::WriteMemory<int>(pointerPlayer + Offsets::player_health_offset, health);
}
