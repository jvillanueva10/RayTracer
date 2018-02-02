#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"
#include "object.h"
#include <algorithm>

vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& same_side_normal,int recursion_depth,bool is_exiting) const 
{
    vec3 color;
    // TODO: determine the color
    vec3 ambient = world.ambient_color * world.ambient_intensity * color_ambient;
    color = ambient;
    
    vec3 l;
    vec3 color_light;
    vec3 diffuse;
    vec3 r;
    vec3 specular;
    for(unsigned i = 0; i < world.lights.size(); i++)
    {
		l = world.lights[i]->position - intersection_point;
		color_light = world.lights[i]->Emitted_Light(ray) / l.magnitude_squared();
		r = 2 * dot(l.normalized(), same_side_normal) * same_side_normal - l.normalized();
		//diffuse += color_diffuse * color_light * std::max(dot(l.normalized(), same_side_normal), 0.0);
		if(world.enable_shadows)
		{
			Ray lightRay(intersection_point, l);
			Hit dummyh;
			Object* obj = world.Closest_Intersection(lightRay, dummyh);
			//const vec3 intPoint = lightRay.Point(dummyh.t);
			if(obj != NULL)
			{
				vec3 blkPos = lightRay.endpoint + (dummyh.t * lightRay.direction);
				if(blkPos.magnitude() < (world.lights[i]->position - intersection_point).magnitude());
				{
					continue;
				}
			}
			
			diffuse += color_diffuse * color_light * std::max(dot(l.normalized(), same_side_normal), 0.0);
		/*if(!is_exiting)
		{
			diffuse = diffuse + color_diffuse * color_light * std::max(dot(l.normalized(), same_side_normal), 0.0);
		}
		else
		{
			diffuse = diffuse + color_diffuse * color_light * std::max(dot(l.normalized(), -(same_side_normal)), 0.0);
		}*/
    
    
		//l = world.lights[i]->position - intersection_point;
		//color_light = world.lights[j]->Emitted_Light(ray) * (1 / l.magnitude_squared());
		//vec3 color_material_spec = color_specular * l;
		//specular += color_specular * color_light * pow(std::max(dot(r.normalized(), -(ray.direction)), 0.0), specular_power);
			/*Ray lightRay(world.lights[i]->position, l);
			Hit dummyh;
			Object* obj = world.Closest_Intersection(lightRay, dummyh);*/
			//const vec3 intPoint = lightRay.Point(dummyh.t);
			/*if(obj != NULL)
			{
				vec3 blkPos = lightRay.endpoint + (dummyh.t * lightRay.direction);
				if(blkPos.magnitude() < (world.lights[i]->position - intersection_point).magnitude());
				{
					continue;
				}
			}*/
			specular += color_specular * color_light * pow(std::max(dot(r.normalized(), -(ray.direction)), 0.0), specular_power);
		}
		else
		{
			diffuse += color_diffuse * color_light * std::max(dot(l.normalized(), same_side_normal), 0.0);
			specular += color_specular * color_light * pow(std::max(dot(r.normalized(), -(ray.direction)), 0.0), specular_power);
		}
	}
    
    color += diffuse + specular;
    
    return color;
}
