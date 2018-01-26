#include "plane.h"
#include "ray.h"
#include <cfloat>


// Intersect with the half space defined by the plane.  The plane's normal
// points outside.  If the ray starts on the "inside" side of the plane, be sure
// to record a hit with t=0 as the first entry in hits.
bool Plane::
Intersection(const Ray& ray, std::vector<Hit>& hits) const
{
    // TODO
    if(dot(normal, ray.direction) == 0)		//Checks denomenator of following t equation. 
											//If equal to 0, then ray is inside plane, therefore no hit
    {
		return false;
	}
    double t = dot(normal, x1 - ray.endpoint) / dot(normal, ray.direction);
    
    if(t >= 0)			//If t >= 0, then there is a hit, otherwise there is no hit
    {
		Hit hit1;
		hit1.object = this;
		hit1.t = t;
		hit1.ray_exiting = false;
		hits.push_back(hit1);
		return true;
	}
	return false;
}

vec3 Plane::
Normal(const vec3& point) const
{
    return normal;
}
