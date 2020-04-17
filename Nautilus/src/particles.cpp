#include <assert.h>
#include <emscripten/bind.h>
#include "../include/nautilus/particles.h"

using namespace nautilus;
using namespace emscripten;

void Particle::integrate(real duration)
{
	if (inverse_mass <= 0.0f) return;

	assert(duration > 0.0);

	position.add_scaled_vector(velocity, duration);

	Vector3 resulting_acc = acceleration;

	velocity.add_scaled_vector(resulting_acc, duration);

	velocity *= real_pow(damping, duration);

	clear_accumulator();
}

void Particle::set_mass(const real mass)
{
	assert(mass != 0);

	Particle::inverse_mass = ((real)1.0) / mass;
}

real Particle::get_mass() const
{
	if (inverse_mass == 0) return REAL_MAX;

	return ((real)1.0) / inverse_mass;
}

void Particle::set_inverse_mass(const real inverse_mass)
{
	Particle::inverse_mass = inverse_mass;
}

real Particle::get_inverse_mass() const
{
	return inverse_mass;
}

bool Particle::has_finite_mass() const
{
	return inverse_mass >= 0.0f;
}

void Particle::set_damping(const real damping)
{
	Particle::damping = damping;
}

real Particle::get_damping() const
{
	return Particle::damping;
}

void Particle::set_position(const Vector3& position)
{
	Particle::position = position;
}

void Particle::set_position(const real x, const real y, const real z)
{
	position.x = x;
	position.y = y;
	position.z = z;
}

void Particle::get_position(Vector3* position) const
{
	*position = Particle::position;
}

Vector3 Particle::get_position() const
{
	return Particle::position;
}

void Particle::set_velocity(const Vector3 &velocity)
{
	Particle::velocity = velocity;
}

void Particle::set_velocity(const real x, const real y, const real z)
{
	velocity.x = x;
	velocity.y = y;
	velocity.z = z;
}

void Particle::get_velocity(Vector3 *velocity) const
{
	*velocity = Particle::velocity;
}

Vector3 Particle::get_velocity() const
{
	return Particle::velocity;
}

void Particle::set_acceleration(const Vector3 &acceleration)
{
	Particle::acceleration = acceleration;
}

void Particle::set_acceleration(const real x, const real y, const real z)
{
	acceleration.x = x;
	acceleration.y = y;
	acceleration.z = z;
}

void Particle::get_acceleration(Vector3* acceleration) const
{
	*acceleration = Particle::acceleration;
}

Vector3 Particle::get_acceleration() const
{
	return Particle::acceleration;
}

void Particle::clear_accumulator()
{
	force_accum.clear();
}

void Particle::add_force(const Vector3& force)
{
	force_accum += force;
}

EMSCRIPTEN_BINDINGS(particle_class) {
	class_<nautilus::Particle>("Particle")
		.property("position", 
			select_overload<Vector3()const>(&nautilus::Particle::get_position),
			select_overload<void(const Vector3&)>(&nautilus::Particle::set_position))
		.property("velocity",
			select_overload<Vector3()const>(&nautilus::Particle::get_velocity),
			select_overload<void(const Vector3&)>(&nautilus::Particle::set_velocity))
		.property("acceleration",
			select_overload<Vector3()const>(&nautilus::Particle::get_acceleration),
			select_overload<void(const Vector3&)>(&nautilus::Particle::set_acceleration))
		.property("damping", &nautilus::Particle::get_damping, &nautilus::Particle::set_damping)
		.property("inverse_mass", &nautilus::Particle::get_inverse_mass, &nautilus::Particle::set_inverse_mass)
		.function("integrate", &nautilus::Particle::integrate)
		.function("clear_accumulator", &nautilus::Particle::clear_accumulator)
		.function("add_force", &nautilus::Particle::add_force)
		.function("has_finite_mass", &nautilus::Particle::has_finite_mass)
		;
}