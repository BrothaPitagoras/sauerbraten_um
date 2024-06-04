#include "structs/Vector4.hpp"

Vector4::Vector4() {}

Vector4::Vector4(float x, float y, float z, float w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

std::ostream& operator<<(std::ostream& Str, Vector4 const& v) {
	Str << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
	return Str;
}