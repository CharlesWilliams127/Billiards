#version 430

uniform sampler2D myTexture;
in vec2 fragUV;
layout (location = 5) uniform vec3 lightLocation;
layout (location = 6) uniform vec3 cameraLocation;
in vec3 fragmentLocation;
in vec3 fragmentNormal;

void main()
{	
	float ambient = .9;
	vec4 color = texture(myTexture, fragUV);
	float lambert = max(dot(lightLocation, fragmentNormal), 0);
	float diffuse = .75 * lambert + 1;
	vec3 viewDirection = normalize(cameraLocation - fragmentLocation);
	vec3 halfDirection = normalize(lightLocation + viewDirection);
	float specularAngle = max(dot(halfDirection, fragmentNormal), 0);
	float specular = pow(specularAngle, 90.0);
	float light = ambient + diffuse * specular;
	
	gl_FragColor = vec4(color.rgb * light, color.a);
}