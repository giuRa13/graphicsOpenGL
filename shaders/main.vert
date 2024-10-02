#version 460 

in vec3 vertexIn;
in vec3 colorIn;
out vec3 colorOut;

uniform mat4 model;

void main()
{
    colorOut = colorIn;
    gl_Position = model * vec4(vertexIn, 1.0);
};
