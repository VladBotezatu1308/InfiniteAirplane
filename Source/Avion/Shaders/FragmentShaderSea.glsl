#version 330


// TODO: get color value from vertex shader
flat in float light;


layout(location = 0) out vec4 out_color;

void main()
{
	// TODO: write pixel out color
	out_color = vec4(vec3(0.5,0.9,1) * light, 0.8);
}