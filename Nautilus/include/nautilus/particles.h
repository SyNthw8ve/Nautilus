#include "kernel.h"

namespace nautilus {

	class Particle
	{
	public:
		Particle(const Vector3& position, const Vector3& velocity, const Vector3& acceleration, const Vector3& force_accum, real damping, real inverse_mass) :
			position(position), velocity(velocity), acceleration(acceleration), force_accum(force_accum), 
			damping(damping), inverse_mass(inverse_mass) {}

	public:
		Vector3 position;
		Vector3 velocity;
		Vector3 acceleration;
		Vector3 force_accum;

		real damping;
		real inverse_mass;

		void integrate(real duration);
		void clear_accumulator();
		void add_force(const Vector3 &force);

		void set_mass(const real mass);
		void set_inverse_mass(const real inverse_mass);
		void set_damping(const real damping);
		void set_position(const Vector3 &position);
		void set_position(const real x, const real y, const real z);
		void set_velocity(const Vector3 &velocity);
		void set_velocity(const real x, const real y, const real z);
		void set_acceleration(const Vector3 &acceleration);
		void set_acceleration(const real x, const real y, const real z);
		void set_force(const Vector3& force);

		real get_mass() const;
		real get_inverse_mass() const;
		real get_damping() const;

		void get_position(Vector3 *position) const;
		void get_velocity(Vector3 *velocity) const;
		void get_acceleration(Vector3* acceleration) const;

		Vector3 get_position() const;
		Vector3 get_velocity() const;
		Vector3 get_acceleration() const;
		Vector3 get_force() const;

		bool has_finite_mass() const;
	};

}

