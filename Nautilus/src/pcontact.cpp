#include "../include/nautilus/pcontact.h"

using namespace nautilus;

void ParticleContact::resolve(real duration)
{
	resolve_velocity(duration);
	resolve_interpenetration(duration);
}

real ParticleContact::calculate_separating_velocity() const
{
	Vector3 relative_velocity = particle[0]->get_velocity();

	if (particle[1]) relative_velocity -= particle[1]->get_velocity();

	return relative_velocity.dot_product(contact_normal);
}

void ParticleContact::resolve_velocity(real duration)
{
	real separating_velocity = calculate_separating_velocity();

	if (separating_velocity > 0)
	{
		return;
	}

	real new_sep_velocity = -separating_velocity * restitution;

	Vector3 acc_caused_velocity = particle[0]->get_acceleration();

	if (particle[1]) acc_caused_velocity -= particle[1]->get_acceleration();

	real acc_caused_sep_velocity = acc_caused_velocity.dot_product(contact_normal) * duration;

	if (acc_caused_sep_velocity < 0)
	{
		new_sep_velocity += restitution * acc_caused_sep_velocity;

		if (new_sep_velocity < 0) new_sep_velocity = 0;
	}

	real delta_velocity = new_sep_velocity - separating_velocity;

	real total_inverse_mass = particle[0]->get_inverse_mass();

	if (particle[1]) total_inverse_mass += particle[1]->get_inverse_mass();

	if (total_inverse_mass <= 0) return;

	real impulse = delta_velocity / total_inverse_mass;

	Vector3 impulse_per_mass = contact_normal * impulse;

	particle[0]->set_velocity(particle[0]->get_velocity() + impulse_per_mass * particle[0]->get_inverse_mass());

	if (particle[1])
	{
		particle[1]->set_velocity(particle[1]->get_velocity() + impulse_per_mass * -particle[1]->get_inverse_mass());
	}
}

void ParticleContact::resolve_interpenetration(real duration)
{
	if (penetration <= 0) return;

	real total_inverse_mass = particle[0]->get_inverse_mass();

	if (particle[1]) total_inverse_mass += particle[1]->get_inverse_mass();

	if (total_inverse_mass <= 0) return;

	Vector3 move_per_mass = contact_normal * (penetration / total_inverse_mass);

	particle_movement[0] = move_per_mass * particle[0]->get_inverse_mass();

	if (particle[1])
	{
		particle_movement[1] = move_per_mass * -particle[1]->get_inverse_mass();
	}
	else
	{
		particle_movement[1].clear();
	}

	particle[0]->set_position(particle[0]->get_position() + particle_movement[0]);

	if (particle[1])
	{
		particle[1]->set_position(particle[1]->get_position() + particle_movement[1]);
	}
}

void ParticleContactResolver::set_iterations(unsigned iterations)
{
	ParticleContactResolver::iterations = iterations;
}

void ParticleContactResolver::resolve_contacts(ParticleContact* contact_array, unsigned num_contacts, real duration)
{
	unsigned i;

	iterations_used = 0;

	while (iterations_used < iterations)
	{
		real max = REAL_MAX;
		unsigned max_index = num_contacts;

		for (i = 0; i < num_contacts; i++)
		{
			real sep_vel = contact_array[i].calculate_separating_velocity();

			if (sep_vel < max &&
				(sep_vel < 0 || contact_array[i].penetration > 0))
			{
				max = sep_vel;
				max_index = i;
			}
		}

		if (max_index == num_contacts) break;

		contact_array[max_index].resolve(duration);

		iterations_used++;
	}
}