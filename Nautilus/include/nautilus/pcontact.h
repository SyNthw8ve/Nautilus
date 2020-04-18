#include "particles.h"

namespace nautilus {

	class ParticleContact
	{
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
}