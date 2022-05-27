#version 460


//input vars

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;


//output vars


out vec3 LightIntensity;

//light information struct
uniform struct LightInfo
{
  vec4 Position;      //light position in eye coordinates
  vec3 Ld;            //Diffuse light source intensity
} Light;


//material information struct
uniform struct MaterialInfo
{
  vec3 Kd;            //Diffuse reflectivity
} Material;

//uniforms for matrices required in shader
uniform mat4 ModelViewMatrix;      //model view matrix
uniform mat3 NormalMatrix;          //normal matrix
uniform mat4 MVP;                   //model view projection matrix

void main()
{
    //transform vertex normal from model coordinates to the view coordinates
    vec3 n = normalize( NormalMatrix * VertexNormal);

    //transform vertex position from model coordinates to the view coordinates
    vec4 pos = ModelViewMatrix * vec4(VertexPosition,1.0);

    //calculate the light direction to the vertex point
    vec3 s = normalize(vec3(Light.Position - pos));

    //calculating the dot product for vector s and n using max
    float sDotN = max(dot(s,n), 0.0);

    //diffuse the formula for light calculations
    vec3 diffuse = Light.Ld * Material.Kd * sDotN;

    //passing color to LightIntensity which then will transfer it to fragment shader
    LightIntensity = diffuse;

    //this turns any vertex postion into MV Projection
    gl_Position = MVP * vec4(VertexPosition,1.0);
}
