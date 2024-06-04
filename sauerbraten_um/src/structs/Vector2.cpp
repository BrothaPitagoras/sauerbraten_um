#include "structs/Vector2.hpp"

Vector2::Vector2() {}

Vector2::Vector2(float x, float y) {
	this->x = x;
	this->y = y;
}

float Vector2::getDistance(Vector2* vec) {
	return sqrt((this->x * vec->x) * (this->x * vec->x) + (this->y * vec->y) * (this->y * vec->y));
}

std::ostream& operator<<(std::ostream& Str, Vector2 const& v) {
	Str << "(" << v.x << ", " << v.y << ")";
	return Str;
}