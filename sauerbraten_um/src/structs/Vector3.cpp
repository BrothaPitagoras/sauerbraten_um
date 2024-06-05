#include "structs/Vector3.hpp"

Vector3::Vector3() {}

Vector3::Vector3(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3 Vector3::operator-(const Vector3& other) const {
	return { this->x - other.x, this->y - other.y, this->z - other.z };
}

std::string Vector3::toString(){
	return std::format("{}, {}, {}", this->x, this->y, this->z);
}

Vector3 Vector3::operator+(const Vector3& other) const {
	return { x + other.x, y + other.y, z + other.z };
}