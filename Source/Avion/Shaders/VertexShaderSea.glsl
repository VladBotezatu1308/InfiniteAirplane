#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;
layout(location = 3) in vec2 v_color;

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
uniform vec3 reference_point;

// Output value to fragment shader
flat out float light;
out vec2 texcoord;

void main()
{
	// TODO: compute world space vectors
	vec3 normal = normalize(v_position - vec3(0,0, v_position.z));
	vec3 world_pos = vec3(Model * vec4(v_position, 1));
	vec3 N = normalize(mat3(Model)*normal);
	vec3 L = normalize(light_position - world_pos);
	vec3 R = reflect(-L, N);
	vec3 V = normalize(eye_position - world_pos);
	vec3 H = normalize(L + V);

	float dist = distance(light_position, world_pos);
	

	// TODO: define ambient light component
	float ambient_light = 0.75;

	// TODO: compute diffuse light component
	float diffuse_light = material_kd * max(dot(N,L), 0);

	// TODO: compute specular light component
	float specular_light = 0;//material_ks * pow(max(dot(N, H), 0), material_shininess);

	if (diffuse_light <= 0)
	{
		specular_light = 0;
	}

	// TODO: compute light
	light = ambient_light + 1/(pow(dist,2) + 1) * (diffuse_light + specular_light);
	texcoord = v_texture_coord;

	float dist_to_reference_point = pow(distance(v_position, vec3(-2,-2 ,-10)), 3);
	
	float amplitude = -sin(dist_to_reference_point) * 0.02 *sin( 0.5 *time);
	
  	gl_Position = Projection* View * Model * vec4(v_position + v_position * amplitude, 1);
}
