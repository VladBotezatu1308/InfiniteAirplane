#version 330

uniform sampler2D texture_1;

// TODO: get color value from vertex shader
in float light;
in vec2 texcoord;
in float alpha;

layout(location = 0) out vec4 out_color;

void main()
{
	// TODO: write pixel out color
	vec4 texture = texture2D(texture_1, texcoord);
	vec3 color = texture.xyz * light;
	float new_alpha = texture.a * alpha;
	out_color = vec4(color, new_alpha);
}