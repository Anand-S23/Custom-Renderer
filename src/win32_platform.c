#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#include "win32_platform.h" 

internal void FramebufferCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

internal void HandleInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, 1);
    }
}

int main(int argc, char **argv)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1280, 720, "Custom", NULL, NULL);
    if (window)
    {
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, FramebufferCallback);

        if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            while (!glfwWindowShouldClose(window))
            {
                HandleInput(window);

                glfwSwapBuffers(window);
                glfwPollEvents();
            }
        }
        else
        {
            printf("GLAD failed to intialize");
        }
    }
    else
    {
        printf("Error creating window");
    }

    glfwTerminate();
    return 0;
}
