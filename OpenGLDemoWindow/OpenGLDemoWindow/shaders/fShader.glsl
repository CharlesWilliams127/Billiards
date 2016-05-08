#version 430

in vec2 fragUV;

uniform sampler2D myTexture;

void main()
{
	//if(fragUV.x < 0 && fragUV.y < 0)
	//{
	//	gl_FragColor = vec4(-fragUV.x * .6, -fragUV.y * .75, -fragUV.x * .8, fragUV.y * .8);
	//}
	//else if(fragUV.x < 0)
	//{
	//	gl_FragColor = vec4(-fragUV.x * .6, fragUV.y * .75, -fragUV.x * .8, fragUV.y * .8);
	//}
	//else if(fragUV.y < 0)
	//{
	//	gl_FragColor = vec4(fragUV.x * .6, -fragUV.y * .75, -fragUV.x * .8, fragUV.y * .8);
	//}
	//else
	//{
	//	gl_FragColor = vec4(fragUV.x * .6, fragUV.y * .75, -fragUV.x * .8, fragUV.y * .8);
	//}
	
	gl_FragColor = texture(myTexture, fragUV);
	
	//gl_FragColor = vec4(0, 0, 0, 1);
}