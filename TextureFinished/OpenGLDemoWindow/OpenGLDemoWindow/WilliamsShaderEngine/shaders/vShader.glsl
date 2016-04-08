#version 430

layout (location = 0) in vec3 position;

out vec2 fragUV;

void main()
{
	gl_Position = vec4(position, 1);
	vec2 something = vec2(position.x*1.5f, position.y*1.5f);
	fragUV = something.xy;
}