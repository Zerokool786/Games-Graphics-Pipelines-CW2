#include "scenebasic_uniform.h"
#include <sstream>
#include <cstdio>
#include <cstdlib>

#include <string>
using std::string;

#include <iostream>
using std::cerr;
using std::endl;

#include "helper/glutils.h"
#include <glm/gtc/matrix_transform.hpp>

using glm::vec3;
using glm::mat4;

SceneBasic_Uniform::SceneBasic_Uniform() : torus(0.7f, 0.3f, 100, 100) {} // construct torus with high polymesh more rings and sides

    
void SceneBasic_Uniform::initScene()
{
    compile();
    glEnable(GL_DEPTH_TEST);

    /*Initialise the model matrix using:*/
    model = mat4(1.0f);

    model = glm::rotate(model, glm::radians(-35.0f), vec3(1.0f, 0.0f, 0.0f));  //rotate model around z-axis
    model = glm::rotate(model, glm::radians(10.0f), vec3(0.0f, 1.0f, 0.0f));   //rotate model around y-axis
    view = glm::lookAt(vec3(0.0f, 0.0f, 2.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
        

    projection = mat4(1.0f);

    prog.setUniform("Material.Kd", 0.3f, 0.7f, 0.9f); 
    prog.setUniform("Light.Ld", 2.0f, 0.7f, 2.0f);

    prog.setUniform("LightPosition", view * glm::vec4(5.0f, 5.0f, 2.0f, 1.0f));  
        




}

void SceneBasic_Uniform::compile()
{
    try {
        prog.compileShader("shader/basic_uniform.vert");
        prog.compileShader("shader/basic_uniform.frag");
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

 

}


void SceneBasic_Uniform::render()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

    setMatrices();

    torus.render();

    

;
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
    projection = glm::perspective(glm::radians(70.0f), (float)w / h, 0.3f, 100.0f);
        
}
