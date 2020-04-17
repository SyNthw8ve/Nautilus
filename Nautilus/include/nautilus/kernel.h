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

			void invert();

			real get_x() const;
			real get_y() const;
			real get_z() const;

			void set_x(real x_);
			void set_y(real y_);
			void set_z(real z_);

			real magnitude() const;

			real square_magnitude() const;

			void normalize();

			void operator*=(const real value);

			Vector3 operator*(const real value) const;

			void operator+=(const Vector3& v);

			Vector3 operator+(const Vector3& v);

			void operator-=(const Vector3& v);

			Vector3 operator-(const Vector3& v);

			void add_scaled_vector(const Vector3& v, real scale);

			Vector3 entry_product(const Vector3& v) const;

			void entry_product_update(const Vector3& v);

			real dot_product(const Vector3& v) const;

			Vector3 cross_product(const Vector3& v) const;

			void get_orthonormal_basis(Vector3* a, Vector3* b, Vector3* c);

			void clear();

	};
}
