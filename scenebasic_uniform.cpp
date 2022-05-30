#include "scenebasic_uniform.h"
#include <sstream>
#include <cstdio>
#include <cstdlib>

#include <string>
using std::string;

#include <iostream>
using std::cerr;
using std::endl;

#include <GLFW/glfw3.h>
#include "helper/glutils.h"
#include <glm/gtc/matrix_transform.hpp>

using glm::vec3;
using glm::mat4;

SceneBasic_Uniform::SceneBasic_Uniform() : torus(0.7f, 0.3f, 150, 150) {} // construct torus with high polymesh more rings and sides
    
void SceneBasic_Uniform::initScene()
{
    compile();
    glEnable(GL_DEPTH_TEST);

    /*Initialise the model matrix using:*/
    model = mat4(1.0f);

    // Load texture
    texID = Texture::loadTexture("texture/me_textile.png");
    /*texID = Texture::loadTexture("texture/moss.png");*/
    /*texID = Texture::loadTexture("texture/flower.png");*/
    /*texID = Texture::loadTexture("texture/ogre_diffuse.png");*/
    /*texID = Texture::loadTexture("texture/fire.png");*/
    /*texID = Texture::loadTexture("texture/bluewater.png");*/


    glActiveTexture(GL_TEXTURE0); // Activate texture slot 0
    glBindTexture(GL_TEXTURE_2D, texID);
    prog.setUniform("Tex1", 0);

    //model = glm::rotate(model, glm::radians(-35.0f), vec3(1.0f, 0.0f, 0.0f));  //rotate model around z-axis
    //model = glm::rotate(model, glm::radians(10.0f), vec3(0.0f, 1.0f, 0.0f));   //rotate model around y-axis
    view = glm::lookAt(cameraPos, vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
    projection = mat4(1.0f);

    prog.setUniform("Material.Kd", 0.0f, 0.1f, 0.5f);
    prog.setUniform("Material.Ks", 0.9f, 0.9f, 0.9f);
    prog.setUniform("Material.Ka", 0.5f, 0.5f, 0.5f);
    prog.setUniform("Material.Shininess", 180.0f);

    // Pass the shader Diffuse and specular light intensity
    prog.setUniform("Lights[0].Position", glm::vec4(5.0f, 0.0f, 0.0f, 1.0f));
    prog.setUniform("Lights[1].Position", glm::vec4(0.0f, 0.0f, 5.0f, 1.0f));
    prog.setUniform("Lights[2].Position", glm::vec4(2.0f, 0.0f, 2.0f, 1.0f));

    // Pass the shader Diffuse and specular light intensity
    prog.setUniform("Lights[0].L", vec3(0.0f, 0.0f, 0.8f));
    prog.setUniform("Lights[1].L", vec3(0.0f, 0.8f, 0.0f));
    prog.setUniform("Lights[2].L", vec3(0.8f, 0.0f, 0.0f));

    // Pass the shader ambient intensity
    prog.setUniform("Lights[0].La", vec3(0.0f, 0.0f, 0.8f));
    prog.setUniform("Lights[1].La", vec3(0.0f, 0.8f, 0.0f));
    prog.setUniform("Lights[2].La", vec3(0.8f, 0.0f, 0.0f));

}

void SceneBasic_Uniform::compile()
{
    try {
        prog.compileShader("shader/blinnPhong.vert");
        prog.compileShader("shader/blinnPhong.frag");
        prog.link();
        prog.use();
    }
    catch (GLSLProgramException& e) {
        cerr << e.what() << endl;
        exit(EXIT_FAILURE);
    }
}

void SceneBasic_Uniform::update(float t)
{
    float deltaTime = std::min(t - lastFrameTime, 0.1f);
    lastFrameTime = t;

    // Update camera position
    angle += glm::radians(40.0f) * deltaTime; 
    cameraPos = glm::vec3(glm::cos(angle) * 5.0f, 0.0f, glm::sin(angle) * 5.0f);
    prog.setUniform("cameraPos", cameraPos);
    view = glm::lookAt(cameraPos, vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
}


void SceneBasic_Uniform::render()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
 
    model = mat4(1.0f);
    //model = glm::rotate(model, glm::radians(90.0f), vec3(0.0f, 1.0f, 0.0f));

    setMatrices();

    torus.render();
}

void SceneBasic_Uniform::setMatrices()
{
    mat4 mv = view * model; //create model view matrix

    prog.setUniform("ModelViewMatrix", mv); //set the uniform “ModelViewMatrix” and pass mv matrix
    prog.setUniform("NormalMatrix", glm::mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2]))); // set the uniform for “NormalMatrix”
    prog.setUniform("MVP", projection * mv); //set the uniform for model view projection matrix called “MVP” and pass in projection matrix * model view matrix
        
}

void SceneBasic_Uniform::resize(int w, int h)
{
    width = w;
    height = h;
    glViewport(0, 0, w, h);
    projection = glm::perspective(glm::radians(30.0f), (float)w / h, 0.3f, 100.0f);
        
}
