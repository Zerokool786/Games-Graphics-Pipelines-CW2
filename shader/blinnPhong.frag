#version 460

   //light information struct
 struct LightInfo 
 {
  vec4 Position; // Light position in eye coords.
  vec3 La; // Ambient light intensity
  vec3 L; // Diffuse and specular light intensity 
 }; 
 
uniform LightInfo Lights[3];

  //material information struct
uniform struct MaterialInfo
{
  vec3 Ka;            // Ambient reflectivity
  vec3 Kd;            //Diffuse reflectivity
  vec3 Ks;            // Specular reflectivity
  float Shininess; // Specular shininess factor
} Material;

uniform sampler2D Tex1;
uniform vec3 cameraPos;

in vec3 WorldPosition;
in vec3 Normal;
in vec2 texCoords;

vec3 blinnPhong(vec3 ambient, vec3 position, vec3 L, vec3 texColor );

out vec4 FragColor;

void main() 
{
	vec3 texColor = texture(Tex1, texCoords).rgb;

	vec3 color = vec3(0.0);
    for( int i = 0; i < 3; i++ )
	{
	    color += blinnPhong( Lights[i].La, vec3(Lights[i].Position), Lights[i].L, texColor);
	}
     
	FragColor = vec4(color, 1.0f);
}


vec3 blinnPhong(vec3 ambient, vec3 position, vec3 L, vec3 texColor )
{
	vec3 s = normalize(position - WorldPosition); //calculate s vector
	vec3 normal = normalize(Normal);
	float sDotN = max(dot(s, normal), 0.0); //calculate dot product between s and n

	vec3 diffuse = texColor * sDotN; //calculate diffuse
	
	vec3 spec = vec3(0.0);
	if( sDotN > 0.0 )
	{
		vec3 v = normalize(cameraPos - WorldPosition); // View direction (camera -> surface)
		vec3 h = normalize( v + s ); // Halfway vector

		spec = Material.Ks * pow( max(dot(h, normal), 0.0 ), Material.Shininess);
	}

	return ambient + L * (diffuse + spec);
} 