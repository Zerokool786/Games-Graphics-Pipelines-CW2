# CW2COMP3015 Optimised Developer Tool

 # Which version Visual Studio and Operating System you used to test/write the code locally?

 I used Visual Studio Community 2019 Version 16.11.11 to write the code running on Windows 10 19044.1620, Version = 21H2

 # How does it work?
 
  I have created a blinnPhong reflection model which is a more efficent shader for the torus object also giving it a texture 
  blinnPhong calculates the halfway vector between view direction "v" and the light's direction "s" it differs from the Phong model because it only calculates the reflection vector and viewing vector
 
 - The vertex shader has the main method where calculations for vertex manipulations are done such as normal vector n and s which defines the direction of the surface point
   of the light source 
 - The fragment shader is responsible for shading the mesh's fragments. This is done by calculating the light's direction (vector s) and computing the dot product of vectors s (the light direction) and vector n (the surface normal). 
   so that the light intensity can affect the color of the material
  
 - the main.cpp calls to run the scene
 - torus object is constructed with a high polymesh with 150 nrings and 150 sides and having outer radius of 0.7f and inner radius being 0.3f
 - initScene() is responsible for compiling, initialising the model with 4x4 identity matrix
 - the camera orbits around the mesh "torus"
 - projection matrix is initialised using mat4
 - uniforms are present to change the materials values, values for lighting, vaLues for positioning the light on the scene
 - uniform sampler2D Tex1 is responsible for telling the shader what texture the torus is using.
 - uniform vec3 cameraPos is responsible for telling the shader where our camera is positioned in world space.
 
  
 # How does your code fit together and how should a programmer navigate it 
 - main.cpp runs the scene
 - initScene  has the main body of the program where uniforms are declared for the light,materials and positioning which is inside the scenebasic_uniform.cpp 
 - the data of the model torus is passed through blinnPhong.vert and blinnPhong.frag respectively
 - torus object is created in torus.cpp with defined parameters
 - scenebasic updates the loading and defining the locations of textures 
 - scenebasic sets up all the uniforms 
 - scenebasic update functions updates the scene every frame
 - the scenebasic render function renders the torus object every frame
 
 
 
 # Anything else which will help us to understand how your prototype works?
  I utilized the given project template to build my prototype 
 # Link to Youtube Video
 
 
 
