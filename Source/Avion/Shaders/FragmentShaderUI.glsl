#version 330

uniform sampler2D texture_1;

// TODO: get color value from vertex shader
in float light;
in vec2 texcoord;

layout(location = 0) out vec4 out_color;

void main()
{
	// TODO: write pixel out color
	out_color = texture2D(texture_1, texcoord);
	if (out_color.a < 0.2)
		discard;
}