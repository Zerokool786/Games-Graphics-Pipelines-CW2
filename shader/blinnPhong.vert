#version 460


//input vars

 layout (location = 0) in vec3 VertexPosition;
 layout (location = 1) in vec3 VertexNormal;
 //layout (location = 2) in vec2 TextureCoords;

//output vars
 out vec3 WorldPosition;
 out vec3 Normal;
 //out vec2 texCoords;

//uniforms for matrices required in shader
uniform mat4 ModelViewMatrix;      //model view matrix
uniform mat3 NormalMatrix;          //normal matrix
uniform mat4 MVP;                   //model view projection matrix

void main()
{
    Normal = normalize( NormalMatrix * VertexNormal);
    WorldPosition = ( ModelViewMatrix * vec4(VertexPosition,1.0) ).xyz;

	gl_Position = MVP * vec4(VertexPosition,1.0);
}





