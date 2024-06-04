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
	return std::to_string(this->x) + ", " + std::to_string(this->y) + ", " + std::to_string(this->z);
}

Vector3 Vector3::operator+(const Vector3& other) const {
	return { x + other.x, y + other.y, z + other.z };
}

std::ostream& operator<<(std::ostream& Str, Vector3 const& v) {
	Str << "(" << v.x << ", " << v.y << ", " << v.z << ")";
	return Str;
}