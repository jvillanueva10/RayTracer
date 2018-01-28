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
    
    vec3 l;
    vec3 color_light;
    vec3 diffuse;
    for(unsigned i = 0; i < world.lights.size(); i++)
    {
		l = world.lights[i]->position - intersection_point;
		color_light = world.lights[i]->Emitted_Light(ray) * (1 / l.magnitude_squared());
		diffuse = diffuse + color_diffuse * color_light * std::max(dot(l.normalized(), same_side_normal), 0.0);
		/*if(!is_exiting)
		{
			diffuse = diffuse + color_diffuse * color_light * std::max(dot(l.normalized(), same_side_normal), 0.0);
		}
		else
		{
			diffuse = diffuse + color_diffuse * color_light * std::max(dot(l.normalized(), -(same_side_normal)), 0.0);
		}*/
	}
    /*if(is_exiting)
    {
		diffuse = color_material * color_light * std::max(dot(l.normalized(), -(same_side_normal).normalized()), 0.0) * cosineD;
	}
	else
	{
		diffuse = color_material * color_light * std::max(dot(l, same_side_normal), 0.0) * cosineD;
    }*/
    
    vec3 r;
    vec3 specular;
    for(unsigned j = 0; j < world.lights.size(); j++)
    {
		l = world.lights[j]->position - intersection_point;
		color_light = world.lights[j]->Emitted_Light(ray) * (1 / l.magnitude_squared());
		r = 2 * dot(l.normalized(), same_side_normal) * same_side_normal - l.normalized();
		//vec3 color_material_spec = color_specular * l;
		specular = specular + color_specular * color_light * pow(std::max(dot(r.normalized(), -(ray.direction.normalized())), 0.0), specular_power);
	}
    
    color = ambient + diffuse + specular;
    
    return color;
}
