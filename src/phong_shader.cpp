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
    double cosineD;
	l = world.lights[recursion_depth]->position - intersection_point;
	color_light = world.lights[recursion_depth]->Emitted_Light(ray) * (1 / l.magnitude_squared());
	if(same_side_normal.magnitude() != 0)
	{
		cosineD = dot(l.normalized(), same_side_normal.normalized());
	}
    vec3 color_material = color_diffuse * l;
    vec3 diffuse;
    if(is_exiting)
    {
		diffuse = color_material * color_light * std::max(dot(l, -(same_side_normal)), 0.0) * cosineD;
	}
	else
	{
		diffuse = color_material * color_light * std::max(dot(l, same_side_normal), 0.0) * cosineD;
    }
    
    vec3 r;
	r = 2 * dot(l.normalized(), same_side_normal) * same_side_normal - l.normalized();
	double cosineS;
	cosineS = dot(r.normalized(), -(ray.direction.normalized()));
	//vec3 color_material_spec = color_specular * l;
    vec3 specular = color_specular * l * color_light * pow(std::max(dot(r.normalized(), -(ray.direction.normalized())), 0.0), specular_power) * cosineS;
    
    color = ambient + diffuse + specular;
    
    return color;
}
