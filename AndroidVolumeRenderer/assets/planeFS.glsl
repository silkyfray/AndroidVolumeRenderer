#version 310 es
precision highp float;

uniform sampler2D tex;
in vec2 fsTexCoord;
out vec4 color;

void main()
{
	color = texture(tex, fsTexCoord);
}  


// #version 310 es
// precision highp float;

// uniform sampler2D tex;
// in vec2 fsTexCoord;
// out vec4 color;

// void main()
// {
// 	color = texture(tex, fsTexCoord);
// }  