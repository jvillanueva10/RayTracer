#include "sphere.h"
#include "ray.h"


// Determine if the ray intersects with the sphere
bool Sphere::Intersection(const Ray& ray, std::vector<Hit>& hits) const
{
    // TODO
    //double discriminant = pow(dot(ray.direction, (ray.endpoint - center)), 2) - dot((ray.endpoint - center), (ray.endpoint - center)) - pow(radius, 2);
    double discriminant = pow(dot(ray.direction, (ray.endpoint - center)), 2) - (dot(ray.direction, ray.direction) * dot(ray.endpoint - center, ray.endpoint - center) - pow(radius, 2));
    
    if(discriminant > 0)
    {
		double t1 = ( - (dot(ray.direction, (ray.endpoint - center)) + sqrt(discriminant)) / dot(ray.direction, ray.direction));
		//double t1 = dot(ray.direction, (ray.endpoint - center)) - sqrt(discriminant);
		//double t2 = dot(ray.direction, (ray.endpoint - center)) + sqrt(discriminant);
		double t2 = ( - (dot(ray.direction, (ray.endpoint - center)) - sqrt(discriminant)) / dot(ray.direction, ray.direction));
		
		if(t1 > 0)
		{
			Hit hit1;
			hit1.object = this;
			hit1.t = t1;
			hit1.ray_exiting = false;
			hits.push_back(hit1);
			
			Hit hit2;
			hit2.object = this;
			hit1.t = t2;
			hit2.ray_exiting = true;
			hits.push_back(hit2);
		}
		return true;
	}
	else
		return false;
}

vec3 Sphere::Normal(const vec3& point) const
{
    vec3 normal;
    // TODO: set the normal
    return normal;
}
