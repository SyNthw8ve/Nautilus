#include "precision.h"
#include <math.h>

namespace nautilus
{

	class Vector3
	{

		public:
			real x;
			real y;
			real z;

		private:
			real pad;

		public:
			Vector3() : x(0), y(0), z(0) {}

			Vector3(const real x, const real y, const real z)
				: x(x), y(y), z(z) {}

			void invert()
			{
				x = -x;
				y = -y;
				z = -z;
			}

			real magnitude() const
			{
				return sqrt(x * x + y * y + z * z);
			}

			real square_magnitude() const
			{
				return x * x + y * y + z * z;
			}

			void normalize()
			{
				real l = magnitude();

				(*this) *= ((real)1) / l;
			}

			void operator*=(const real value)
			{
				x *= value;
				y *= value;
				z *= value;
			}

			Vector3 operator*(const real value) const
			{
				return Vector3(x * value, y * value, z * value);
			}

			void operator+=(const Vector3& v)
			{
				x += v.x;
				y += v.y;
				z += v.z;
			}

			Vector3 operator+(const Vector3& v)
			{
				return Vector3(x + v.x, y + v.y, z + v.z);
			}

			void operator-=(const Vector3& v)
			{
				x -= v.x;
				y -= v.y;
				z -= v.z;
			}

			Vector3 operator-(const Vector3& v)
			{
				return Vector3(x - v.x, y - v.y, z - v.z);
			}

			void add_scaled_vector(const Vector3& v, real scale)
			{
				x += v.x * scale;
				y += v.y * scale;
				z += v.z * scale;
			}

			Vector3 entry_product(const Vector3& v) const
			{
				return Vector3(x * v.x, y * v.y, z * v.z);
			}

			void entry_product_update(const Vector3& v)
			{
				x *= v.x;
				y *= v.y;
				z *= v.z;
			}

			real dot_product(const Vector3& v) const
			{
				return x * v.x + y * v.y + z * v.z;
			}

			Vector3 cross_product(const Vector3& v) const
			{
				return Vector3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
			}

			void get_orthonormal_basis(Vector3* a, Vector3* b, Vector3* c)
			{
				a->normalize();
				*c = a->cross_product(*b);

				if (c->square_magnitude() == 0.0) return;

				c->normalize();
				*b = c->cross_product(*a);
			}

			void clear()
			{
				x = y = z = 0;
			}

	};
}