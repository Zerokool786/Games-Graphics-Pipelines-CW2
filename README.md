# CW2COMP3015 Optimised Developer Tool

 # Which version Visual Studio and Operating System you used to test/write the code locally?

 I used Visual Studio Community 2019 Version 16.11.11 to write the code running on Windows 10 19044.1620, Version = 21H2

 # How does it work?
 
  I have created a blinnPhong reflection model which is a more efficent shader for the torus object also giving it a texture  
 
 - The vertex shader has the main method where calculations for vertex manipulations are done such as normal vector n and s which defines the direction of the surface point
   of the light source 
 - sdotn calcuates the dot product of s and n to diffuse the formula for calculating light then it is passed through the fragment shader 
   so that the light intensity can diffuse with the color of the material
   from diffusing to lighting to positioning 
 - the main.cpp calls to run the scene
 - torus object is constructed with a high polymesh with 150 nrings and 150 sides and having outer radius of 0.7f and inner radius being 0.3f
 - initScene() is responsible for compiling, initialising the model with 4x4 identity matrix
 - model is rotated with defined vectors and radians around both axis
 - projection matrix is initialised using mat4
 - uniforms are present to change the materials values, values for lighting, vaLues for positioning the light on the scene
 
  
 # How does your code fit together and how should a programmer navigate it 
 - main.cpp runs the scene
 - initScene  has the main body of the program where uniforms are declared for the light,materials and positioning which is inside the scenebasic_uniform.cpp 
 - the data of the model torus is passed through basic_uniform.vert and basic_uniform.frag respectively
 - torus object is created in torus.cpp with defined parameters
 
 
 
 # Anything else which will help us to understand how your prototype works?
  I utilized the given project template to build my prototype 
 # Link to Youtube Video
 
 
 
