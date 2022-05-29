#version 460

   //light information struct
 uniform struct LightInfo 
 {

  vec4 Position; // Light position in eye coords.
  vec3 La; // Ambient light intensity
  vec3 L; // Diffuse and specular light intensity
    
 } Lights[3];

  //material information struct
uniform struct MaterialInfo
{
  vec3 Ka;            // Ambient reflectivity
  vec3 Kd;            //Diffuse reflectivity
  vec3 Ks;            // Specular reflectivity
  float Shininess; // Specular shininess factor
} Material;

in vec3 WorldPosition;
in vec3 Normal;

vec3 blinnPhong(vec3 ambient, vec3 position, vec3 L );

out vec4 FragColor;

void main()
{
	vec3 color = vec3(0.0);
     for( int i = 0; i < 3; i++ )
	 {
		color += blinnPhong( Lights[i].La, vec3(Lights[i].Position), Lights[i].L );
	 }
     
	 //					R   G      B
	 FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}


vec3 blinnPhong(vec3 ambient, vec3 position, vec3 L )
{
	vec3 s = normalize(position - WorldPosition); //calculate s vector
	float sDotN = max(dot(s, Normal), 0.0); //calculate dot product between s and n

	vec3 diffuse = Material.Kd * sDotN; //calculate diffuse
	vec3 spec = vec3(0.0);
	if( sDotN > 0.0 )
	{
		vec3 v = normalize(-position.xyz);
		vec3 h = normalize( v + s );
		spec = Material.Ks * pow( max(dot(h, Normal), 0.0 ), Material.Shininess);
	}
	return ambient + L * (diffuse + spec);
} 