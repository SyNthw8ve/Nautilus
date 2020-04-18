#include "particles.h"

namespace nautilus {

	class ParticleContact
	{
	public:
		Particle* particle[2];

		real restitution;
		real penetration;

		Vector3 contact_normal;
		Vector3 particle_movement[2];

	public:

		void resolve(real duration);
		real calculate_separating_velocity() const;

	private:

		void resolve_velocity(real duration);
		void resolve_interpenetration(real duration);
	};

	class ParticleContactResolver
	{
	public:

		unsigned iterations;
		unsigned iterations_used;

		ParticleContactResolver(unsigned iterations) : iterations(iterations) {}

		void set_iterations(unsigned iterations);

		void resolve_contacts(ParticleContact* contact_array, unsigned num_contacts, real duration);

	};
}