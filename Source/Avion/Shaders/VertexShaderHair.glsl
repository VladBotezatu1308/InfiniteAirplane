#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

// Uniforms for light properties
uniform float time;
uniform vec3 light_position;
uniform vec3 eye_position;
uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;
uniform float ambient_light;

uniform vec3 object_color;
uniform float object_alpha;

// Output value to fragment shader
out float light;
out vec2 texcoord;
out float alpha;

void main()
{
	// TODO: compute world space vectors
	vec3 world_pos = vec3(Model * vec4(v_position, 1));
	vec3 N = normalize(mat3(Model)*v_normal);
	vec3 L = normalize(light_position - world_pos);
	vec3 R = reflect(-L, N);
	vec3 V = normalize(eye_position - world_pos);
	vec3 H = normalize(L + V);

	float dist = distance(light_position, world_pos);
	

	// TODO: define ambient light component

	// TODO: compute diffuse light component
	float diffuse_light = material_kd * max(dot(N,L), 0);

	// TODO: compute specular light component
	float specular_light = material_ks * pow(max(dot(N, H), 0), material_shininess);

	// if (diffuse_light <= 0)
	// {
	// 	specular_light = 0;
	// }

	// TODO: compute light
	light = ambient_light +  1/(pow(dist,2) + 1) * (diffuse_light + specular_light);
	texcoord = v_texture_coord;
	alpha = object_alpha;

	float amplitude = 0.3 * sin((1.2 - v_position.x)*0.7);
	if( (1.2 -v_position.x) < 0.3)
		amplitude = 0;
	vec3 new_pos = vec3(v_position.x, v_position.y + sin(12*time) * amplitude , v_position.z);

	gl_Position = Projection * View * Model * vec4(new_pos, 1.0);
}
