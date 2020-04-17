#include "particles.h"
#include <vector>

namespace nautilus {

	class ParticleForceGenerator
	{
	public:
		virtual void update_force(Particle* particle, real duration) = 0;
	};

	class ParticleForceRegistry
	{
	public:

		struct ParticleForceRegistration
		{
			Particle* particle;
			ParticleForceGenerator* force_gen;
		};

		typedef std::vector<ParticleForceRegistration> Registry;
		Registry registrations;

		void add(Particle* particle, ParticleForceGenerator* force_gen);

		void remove(Particle* particle, ParticleForceGenerator* force_gen);

		void clear();

		void update_forces(real duration);
	};

	class ParticleGravity : public ParticleForceGenerator
	{

		Vector3 gravity;

	public:

		ParticleGravity(const Vector3& gravity);

		virtual void update_force(Particle* particle, real duration);
	};

	class ParticleDrag : public ParticleForceGenerator
	{
		real k1;

		real k2;

	public:

		ParticleDrag(real k1, real k2);

		virtual void update_force(Particle* particle, real duration);
	};

	class ParticleSpring : public ParticleForceGenerator
	{
		Particle* other;

		real spring_const;
		real rest_length;

	public:	

		ParticleSpring(Particle* other, real spring_const, real rest_length);

		virtual void update_force(Particle* particle, real duration);
	};

	class ParticleAnchoredSpring : public ParticleForceGenerator
	{
		Vector3* anchor;

		real spring_const;
		real rest_length;

	public:

		ParticleAnchoredSpring(Vector3* anchor, real spring_const, real rest_length);

		virtual void update_force(Particle* particle, real duration);
	};

	class ParticleBungee : public ParticleForceGenerator
	{
		Particle* other;

		real spring_const;
		real rest_length;

	public:

		ParticleBungee(Particle* other, real spring_const, real rest_length);

		virtual void update_force(Particle* particle, real duration);
	};

	class ParticleBuoyancy : public ParticleForceGenerator
	{
		real max_depth;
		real volume;
		real water_height;
		real liquid_density;

	public:

		ParticleBuoyancy(real max_depth, real volume, real water_height, real liquid_density = 1000.0f);

		virtual void update_force(Particle* particle, real duration);
	};

	class ParticleFakeSpring : public ParticleForceGenerator
	{
		Vector3* anchor;

		real spring_const;
		real damping;

	public:

		ParticleFakeSpring(Vector3* anchor, real spring_const, real damping);

		virtual void update_force(Particle* particle, real duration);
	};
}