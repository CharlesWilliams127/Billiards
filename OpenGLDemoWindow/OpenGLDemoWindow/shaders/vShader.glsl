#version 430

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 2) uniform mat4 modelWorld;
layout (location = 3) uniform mat4 cameraMat;
layout (location = 4) in vec3 normal;

out vec2 fragUV;
out vec3 cameraLoc;
out vec3 fragLoc;
out vec3 fragNorm;

void main()
{
	//gl_Position = modelWorld * vec4(position, 1);

	gl_Position = cameraMat * modelWorld * vec4(position, 1);
	fragLoc = gl_Position.xyz;
	fragUV = uv;
	fragNorm = normalize((modelWorld * vec4(normal, 0)).xyz);
	cameraLoc = vec3(inverse(cameraMat)[3]);
}