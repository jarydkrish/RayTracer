#include "ray.h"

inline point3 ray::at(double t) const {
	return orig + (t * dir);
}
