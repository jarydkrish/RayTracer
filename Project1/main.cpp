#include "color.h"
#include "ray.h"
#include "vec3.h"

color ray_color(const ray& r)
{
	vec3 unit_direction = unit_vector(r.direction());
	double t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * color(1.0, 1.0, 1.0) + (t * color(0.5, 0.7, 1.0));
}

int main()
{
	// Image deets
	const double aspect_ratio = 16.0 / 9.0;
	const int image_width = 400;
	const int image_height = static_cast<int>(image_width / aspect_ratio);

	// Camera

	double viewport_height = 2.0;
	double viewport_width = aspect_ratio * viewport_height;
	double focal_length = 1.0;
	point3 origin = point3(0.0, 0.0, 0.0);
	vec3 horizontal = vec3(viewport_width, 0.0, 0.0);
	vec3 vertical = vec3(0.0, viewport_height, 0.0);
	point3 lower_left_corner = origin - (horizontal / 2) - (vertical / 2) - vec3(0.0, 0.0, focal_length);


	// Render

	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int height_pixel = image_height - 1; height_pixel >= 0; height_pixel--)
	{
		std::cerr << "\rScanlines remaining: " << height_pixel << ' ' << std::flush;
		for (int width_pixel = 0; width_pixel < image_width; width_pixel++)
		{
			double u = double(width_pixel) / (static_cast<__int64>(image_width) - 1);
			double v = double(height_pixel) / (static_cast<__int64>(image_height) - 1);
			ray r(origin, lower_left_corner + u * horizontal + v * horizontal - origin);
			color pixel_color = ray_color(r);
			write_color(std::cout, pixel_color);
		}
	}
}