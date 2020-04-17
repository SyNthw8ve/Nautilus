#include "../include/nautilus/kernel.h"
#include <emscripten/bind.h>

using namespace nautilus;
using namespace emscripten;

void Vector3::invert()
{
	x = -x;
	y = -y;
	z = -z;
}

real Vector3::get_x() const { return x; }
real Vector3::get_y() const { return y; }
real Vector3::get_z() const { return z; }

void Vector3::set_x(real x_) { x = x_; }
void Vector3::set_y(real y_) { y = y_; }
void Vector3::set_z(real z_) { z = z_; }

real Vector3::magnitude() const
{
	return sqrt(x * x + y * y + z * z);
}

real Vector3::square_magnitude() const
{
	return x * x + y * y + z * z;
}

void Vector3::normalize()
{
	real l = magnitude();

	(*this) *= ((real)1) / l;
}

void Vector3::operator*=(const real value)
{
	x *= value;
	y *= value;
	z *= value;
}

Vector3 Vector3::operator*(const real value) const
{
	return Vector3(x * value, y * value, z * value);
}

void Vector3::operator+=(const Vector3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
}

Vector3 Vector3::operator+(const Vector3& v)
{
	return Vector3(x + v.x, y + v.y, z + v.z);
}

void Vector3::operator-=(const Vector3& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
}

Vector3 Vector3::operator-(const Vector3& v)
{
	return Vector3(x - v.x, y - v.y, z - v.z);
}

void Vector3::add_scaled_vector(const Vector3& v, real scale)
{
	x += v.x * scale;
	y += v.y * scale;
	z += v.z * scale;
}

Vector3 Vector3::entry_product(const Vector3& v) const
{
	return Vector3(x * v.x, y * v.y, z * v.z);
}

void Vector3::entry_product_update(const Vector3& v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;
}

real Vector3::dot_product(const Vector3& v) const
{
	return x * v.x + y * v.y + z * v.z;
}

Vector3 Vector3::cross_product(const Vector3& v) const
{
	return Vector3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

void Vector3::get_orthonormal_basis(Vector3* a, Vector3* b, Vector3* c)
{
	a->normalize();
	*c = a->cross_product(*b);

	if (c->square_magnitude() == 0.0) return;

	c->normalize();
	*b = c->cross_product(*a);
}

void Vector3::clear()
{
	x = y = z = 0;
}

EMSCRIPTEN_BINDINGS(vector_class) {
	class_<nautilus::Vector3>("Vector3")
		.constructor<>()
		.constructor<float, float, float>()
		.property("x", &nautilus::Vector3::get_x, &nautilus::Vector3::set_x)
		.property("y", &nautilus::Vector3::get_y, &nautilus::Vector3::set_y)
		.property("z", &nautilus::Vector3::get_z, &nautilus::Vector3::set_z)
		.function("magnitude", &nautilus::Vector3::magnitude)
		.function("invert", &nautilus::Vector3::invert)
		.function("square_magnitude", &nautilus::Vector3::square_magnitude)
		.function("normalize", &nautilus::Vector3::normalize)
		.function("add_scaled_vector", &nautilus::Vector3::add_scaled_vector)
		.function("entry_product", &nautilus::Vector3::entry_product)
		.function("entry_product_update", &nautilus::Vector3::entry_product_update)
		.function("dot_product", &nautilus::Vector3::dot_product)
		.function("cross_product", &nautilus::Vector3::cross_product)
		.function("get_orthonormal_basis", &nautilus::Vector3::get_orthonormal_basis, allow_raw_pointers())
		.function("clear", &nautilus::Vector3::clear)
		.function("scale", &nautilus::Vector3::operator*=)
		.function("scale_vec", &nautilus::Vector3::operator*)
		.function("add", &nautilus::Vector3::operator+=)
		.function("add_vec", &nautilus::Vector3::operator+)
		.function("sub", &nautilus::Vector3::operator-=)
		.function("sub_vec", &nautilus::Vector3::operator-)
		;
}