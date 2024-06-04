#include "structs/player.hpp"

Player::Player(uintptr_t pointerPlayer, ProcessManagement* proc) {
	this->pointerPlayer = pointerPlayer;
	this->paddedPlayer = proc->ReadMemory<PaddedPlayer>(pointerPlayer);
}

bool Player::setView(Vector3& viewVector, ProcessManagement* proc) {
	return proc->WriteMemory<Vector3>(pointerPlayer + Offsets::player_view_offset, viewVector);
}

bool Player::setHealth(int health, ProcessManagement* proc) {
	return proc->WriteMemory<int>(pointerPlayer + Offsets::player_health_offset, health);
}

PaddedPlayer Player::getCachedPlayer() {
	return this->paddedPlayer;
}

Vector3 Player::getFeetPos() {
	return this->paddedPlayer.pos - Vector3(0.0f, 0.0f, 16.0f);
}

