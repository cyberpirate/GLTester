// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW. Always include it before gl.h and glfw.h, since it's a bit magic.
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <iostream>
#include <memory>
#include <ctime>
#include <chrono>
#include <vector>
#include "utils/glmUtils.hpp"
#include "Drawables.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768
#define DEG_PER_SEC 90.0f
#define ZOOM_PER_SEC 2.0f

using namespace glm;
using namespace std::chrono;

std::vector<std::unique_ptr<Drawable>> drawables;

void initialize(std::vector<std::unique_ptr<Drawable>>& drawables);
void update(float dt);

int main() {

// Initialise GLFW
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL

// Open a window and create its OpenGL context
    GLFWwindow *window; // (In the accompanying source code, this variable is global for simplicity)
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Tutorial 01", NULL, NULL);
    if (window == NULL) {
        fprintf(stderr,
                "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); // Initialize GLEW
    glewExperimental = true; // Needed in core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }

// Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    vec4 cameraPos = vec4(4, 3, 3, 1);
    mat4 mViewMatrix = lookAt(
            vec3(
                    cameraPos.x,
                    cameraPos.y,
                    cameraPos.z
            ),
            glm::vec3(0,0,0), // and looks at the origin
            glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
    );

    mat4 mProjMatrix = glm::perspective(
            glm::radians(45.0f),  // The vertical Field of View, in radians: the amount of "zoom". Think "camera lens". Usually between 90° (extra wide) and 30° (quite zoomed in)
            4.0f / 3.0f,          // Aspect Ratio. Depends on the size of your window. Notice that 4/3 == 800/600 == 1280/960, sounds familiar ?
            0.1f,                 // Near clipping plane. Keep as big as possible, or you'll get precision issues.
            100.0f                // Far clipping plane. Keep as little as possible.
    );

    initialize(drawables);

    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    high_resolution_clock::time_point t2;
    duration<float> time_span;

    do {

        t2 = high_resolution_clock::now();
        time_span = duration_cast<duration<double>>(t2 - t1);
        t1 = t2;

        float dt = time_span.count();

        vec4 camPerp = vec4(cameraPos.x, 0, cameraPos.z, 1) * rotate(mat4(), glm::radians(90.0f), glm::vec3(0, 1, 0));
        float angle = getAngleToTop(vec3(cameraPos));

        //calculate camera movement
        if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            if(angle > 3.14f*0.05f) {
                cameraPos = cameraPos * rotate(mat4(), glm::radians(DEG_PER_SEC * dt), -vec3(camPerp));
            }
        }

        if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            cameraPos = cameraPos * rotate(mat4(), glm::radians(DEG_PER_SEC * dt), vec3(0, 1, 0));
        }

        if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            if(angle < 3.14f*0.95f) {
                cameraPos = cameraPos * rotate(mat4(), glm::radians(DEG_PER_SEC * dt), vec3(camPerp));
            }
        }

        if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            cameraPos = cameraPos * rotate(mat4(), glm::radians(DEG_PER_SEC * dt), vec3(0, -1, 0));
        }

        if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
            if(length(cameraPos) <= 0.5f) {
                cameraPos = normalize(cameraPos) * 0.5f;
            } else {
                cameraPos = cameraPos - normalize(cameraPos)*ZOOM_PER_SEC*dt;
            }
        }

        if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {

            if(length(cameraPos) >= 100.0f) {
                cameraPos = normalize(cameraPos) * 100.0f;
            } else {
                cameraPos = cameraPos + normalize(cameraPos)*ZOOM_PER_SEC*dt;
            }
        }


        mViewMatrix = lookAt(
                vec3(
                        cameraPos.x,
                        cameraPos.y,
                        cameraPos.z
                ),
                glm::vec3(0,0,0),
                glm::vec3(0,1,0)
        );

        update(dt);

        mat4 vp = mProjMatrix * mViewMatrix;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for(int i = 0; i < drawables.size(); i++) {
            drawables[i]->draw( vp );
        }

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    } // Check if the ESC key was pressed or the window was closed
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0);

}