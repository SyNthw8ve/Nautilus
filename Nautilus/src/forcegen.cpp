#include "../include/nautilus/forcegen.h"
#include <emscripten/bind.h>

using namespace nautilus;
using namespace emscripten;


void ParticleForceRegistry::add(Particle* particle, ParticleForceGenerator* force_gen)
{
	ParticleForceRegistry::ParticleForceRegistration registration;
	registration.particle = particle;
	registration.force_gen = force_gen;

	ParticleForceRegistry::registrations.push_back(registration);
}

void ParticleForceRegistry::remove(Particle* particle, ParticleForceGenerator* force_gen)
{

}

void ParticleForceRegistry::clear()
{
	ParticleForceRegistry::registrations.clear();
}

void ParticleForceRegistry::update_forces(real duration)
{
	Registry::iterator i = registrations.begin();

	for (; i != registrations.end(); i++)
	{
		i->force_gen->update_force(i->particle, duration);
	}
}

void ParticleGravity::update_force(Particle* particle, real duration)
{

	if (!particle->has_finite_mass()) return;

	particle->add_force(gravity * particle->get_mass());
}

void ParticleDrag::update_force(Particle* particle, real duration)
{
	Vector3 force;
	particle->get_velocity(&force);

	real drag_coeff = force.magnitude();
	drag_coeff = k1 * drag_coeff + k2 * drag_coeff * drag_coeff;

	force.normalize();
	force *= -drag_coeff;

	particle->add_force(force);
}

void ParticleSpring::update_force(Particle* particle, real duration)
{
	Vector3 force;
	particle->get_position(&force);
	force -= other->get_position();

	real magnitude = force.magnitude();
	magnitude = real_abs(magnitude - rest_length);
	magnitude *= spring_const;

	force.normalize();
	force *= -magnitude;
	particle->add_force(force);
}

void ParticleAnchoredSpring::update_force(Particle* particle, real duration)
{
	Vector3 force;
	particle->get_position(&force);
	force -= *anchor;

	real magnitude = force.magnitude();
	magnitude = (rest_length - magnitude) * spring_const;

	force.normalize();
	force *= magnitude;
	particle->add_force(force);
}

void ParticleBungee::update_force(Particle* particle, real duration)
{
	Vector3 force;
	particle->get_position(&force);
	force -= other->get_position();

	real magnitude = force.magnitude();
	if (magnitude <= rest_length) return;

	magnitude = spring_const * (rest_length - magnitude);

	force.normalize();
	force *= -magnitude;
	particle->add_force(force);
}

void ParticleBuoyancy::update_force(Particle* particle, real duration)
{
	real depth = particle->get_position().y;

	if (depth >= water_height + max_depth) return;

	Vector3 force(0, 0, 0);

	if (depth <= water_height - max_depth)
	{
		force.y = liquid_density * volume;
		particle->add_force(force);
		return;
	}

	force.y = liquid_density * volume * (depth - max_depth - water_height) / 2 * max_depth;
	particle->add_force(force);
}

void ParticleFakeSpring::update_force(Particle* particle, real duration)
{
	if (!particle->has_finite_mass()) return;

	Vector3 position;
	particle->get_position(&position);
	position -= *anchor;

	real gamma = 0.5f * real_sqrt(4 * spring_const - damping * damping);

	if (gamma == 0.0f) return;

	Vector3 c = position * (damping / (2.0f * gamma)) + particle->get_velocity() * (1.0f / gamma);

	Vector3 target = position * real_cos(gamma * duration) + c * real_sin(gamma * duration);
	target *= real_exp(-0.5f * duration * damping);

	Vector3 accel = (target - position) * (1.0f / duration * duration) - particle->get_velocity() * duration;

	particle->add_force(accel * particle->get_mass());
}

EMSCRIPTEN_BINDINGS(particle_registry) {

	class_<nautilus::ParticleForceRegistry>("ParticleForceRegistry")
		.property("registrations", &nautilus::ParticleForceRegistry::registrations)
		.function("add", &nautilus::ParticleForceRegistry::add, allow_raw_pointers())
		.function("remove", &nautilus::ParticleForceRegistry::remove, allow_raw_pointers())
		.function("clear", &nautilus::ParticleForceRegistry::clear)
		.function("update_forces", &nautilus::ParticleForceRegistry::update_forces)
		;

	register_vector<nautilus::ParticleForceRegistry::ParticleForceRegistration>("vector<ParticleForceRegistration>");

}