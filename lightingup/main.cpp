#include <SFML/Graphics.hpp>
#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>

#include "Shader.h"
#include "Camera.h"

int main()
{
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 0;

    sf::Window window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, settings);

    glewInit();

    float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
    };

    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    glm::vec4 pointLightPositions[] = {
        glm::vec4( 0.7f,  0.2f,  2.0f, 1.0f),
        glm::vec4( 2.3f, -3.3f, -4.0f, 1.0f),
        glm::vec4(-4.0f,  2.0f, -12.0f, 1.0f),
        glm::vec4( 0.0f,  0.0f, -3.0f, 1.0f)
    };  

    // Setting up box VAO
    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)) );
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)) );
    glEnableVertexAttribArray(2);

    glBindVertexArray(0); 

    // Setting up light VAO
    GLuint lampVAO;
    glGenVertexArrays(1, &lampVAO);
    glBindVertexArray(lampVAO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Load texture
    int width, height;
    unsigned char* image = SOIL_load_image("../container.png", &width, &height, 0, SOIL_LOAD_RGB);
    
    if(!image)
        std::cout << "unable to load image" << std::endl;

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Load texture 2
    image = SOIL_load_image("../container_specular.png", &width, &height, 0, SOIL_LOAD_RGB);
    
    if(!image)
        std::cout << "unable to load image" << std::endl;

    GLuint texture2;
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);

    //glPolygonMode(GL_FRONT, GL_TRIANGLES);

    //???????? ?????????????? ?????? ?????????????????????? ?????????????????????? ??????????????????
    glEnable(GL_DEPTH_TEST);

    bool keys[sf::Keyboard::KeyCount] = {false};

    window.setMouseCursorVisible(false);
    window.setMouseCursorGrabbed(true);

    Camera cam(&window);
    cam.setKeys(keys);

    Shader shader(&cam, "../combined_light.vert", "../combined_light.frag");
    Shader lampShader(&cam, "../lamp.vert", "../lamp.frag");

    sf::Vector2i center(window.getSize().x / 2, window.getSize().y / 2);
    sf::Vector2i mouse;

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::Resized)
            {
                // adjust the viewport when the window is resized
                glViewport(0, 0, event.size.width, event.size.height);
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                keys[event.key.code] = true;
            }
            else if (event.type == sf::Event::KeyReleased)
            {
                keys[event.key.code] = false;
            }
        }

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        cam.update();

        //GLfloat angle = clock.getElapsedTime().asSeconds()*50.0f; 
        //model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));

        glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
        glm::vec3 diffuseColor = lightColor   * glm::vec3(0.5f); // decrease the influence
        glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // low influence

        shader.Use();
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture); 

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2); 

        //glActiveTexture(GL_TEXTURE2);
        //glBindTexture(GL_TEXTURE_2D, texture3); 

        //shader.uniform("lightColor", lightColor);
        shader.uniform("material.diffuse", 0);  
        shader.uniform("material.specular", 1);  
        //shader.uniform("material.emission", 2);
        shader.uniform("material.shininess", 64.0f);

        shader.uniform("dirLight.direction", cam.View()*glm::vec4(-0.1f, -0.4f, -1.4f, 0.0f));  
        shader.uniform("dirLight.ambient", ambientColor);
        shader.uniform("dirLight.diffuse", diffuseColor);
        shader.uniform("dirLight.specular", glm::vec3(1.0f));

        for (int i = 0; i < 4; i++)
        {
            std::string s("pointLights[");
            s += std::to_string(i) + "]";
            shader.uniform((s+".ambient").c_str(), ambientColor);
            shader.uniform((s+".diffuse").c_str(), diffuseColor); // darken the light a bit to fit the scene
            shader.uniform((s+".specular").c_str(), glm::vec3(1.0f));
            shader.uniform((s+".constant").c_str(), 1.0f);
            shader.uniform((s+".linear").c_str(), 0.09f);
            shader.uniform((s+".quadratic").c_str(), 0.032f); 
            shader.uniform((s+".position").c_str(), cam.View()*pointLightPositions[i]);
        }

        glm::vec3 camPos = cam.View()*glm::vec4(cam.Position(), 1.0f);
        glm::vec3 camDir = glm::normalize(cam.View()*glm::vec4(cam.Direction(), 0.0f));
        shader.uniform("projectedLight.position", camPos);
        shader.uniform("projectedLight.direction", camDir);
        shader.uniform("projectedLight.ambient", ambientColor);
        shader.uniform("projectedLight.diffuse", diffuseColor);
        shader.uniform("projectedLight.specular",glm::vec3(1.0f));
        shader.uniform("projectedLight.cutOff", glm::cos(glm::radians(12.5f)));
        shader.uniform("projectedLight.cutOffOut", glm::cos(glm::radians(17.5f)));
        shader.uniform("projectedLight.constant", 1.0f);
        shader.uniform("projectedLight.linear", 0.09f);
        shader.uniform("projectedLight.quadratic", 0.032f);
        
        shader.uniform("viewPos", cam.Position());   

        glBindVertexArray(VAO); 
        for(unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i + clock.getElapsedTime().asMilliseconds()/40;
            //model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            shader.uniform("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }     
        glBindVertexArray(0);

        // Rendering lamp
        lampShader.Use();
        glBindVertexArray(lampVAO);  

        for(int i = 0; i < 4; i++)
        {
            glm::mat4 model(1.0f);
            glm::vec3 vec(pointLightPositions[i].x, pointLightPositions[i].y, pointLightPositions[i].z);
            model = glm::translate(model, vec);
            model = glm::scale(model, glm::vec3(0.2f));
            lampShader.uniform("model", model);        
            glDrawArrays(GL_TRIANGLES, 0, 36);        
        }
        glBindVertexArray(0);
        


        //swap buffers
        window.display();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    return 0;
}