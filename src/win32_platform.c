#include <SDL.h>
#include <GL/glew.h>
#include <stdio.h>

#include "win32_platform.h" 

global platform Global_Platform = {0};

global const char *vertex_shader_source = "#version 330 core\n"
    "layout (location = 0) in vec3 pos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);\n"
    "}\0";

global const char *fragment_shader_source = "#version 330 core\n"
    "out vec4 frag_color;\n"
    "void main()\n"
    "{\n"
    "   frag_color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

// TODO: Add in keyboard and mouse input
internal void HandleEvent(SDL_Event *event)
{
    switch (event->type)
    {
        case SDL_QUIT:
        {
            Global_Platform.running = 0;
        } break;

        case SDL_KEYUP:
        case SDL_KEYDOWN:
        {
            if (event->key.repeat == 0)
            {
                // TODO: Keyboard input
                switch (event->key.keysym.scancode)
                {
                }
           }
        } break;

        case SDL_MOUSEBUTTONDOWN:
        {
            if (event->button.button == SDL_BUTTON_LEFT)
            {
                Global_Platform.left_mouse_down = 1;
            }

            else if (event->button.button == SDL_BUTTON_RIGHT)
            {
                Global_Platform.right_mouse_down = 1;
            }

            else if (event->button.button == SDL_BUTTON_MIDDLE)
            {
                Global_Platform.middle_mouse_down = 1;
            }
        } break;

        case SDL_MOUSEBUTTONUP:
        {
            if (event->button.button == SDL_BUTTON_LEFT)
            {
                Global_Platform.left_mouse_down = 0;
            }

            else if (event->button.button == SDL_BUTTON_RIGHT)
            {
                Global_Platform.right_mouse_down = 0;
            }

            else if (event->button.button == SDL_BUTTON_MIDDLE)
            {
                Global_Platform.middle_mouse_down = 0;
            }
        } break;

        case SDL_MOUSEMOTION:
        {
            SDL_GetMouseState(&Global_Platform.mouse_x, 
                              &Global_Platform.mouse_y);
        } break;
    }
}

int main(int argc, char** argv)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL_Init failed: %s", SDL_GetError());
    }

    // Set SDL OpenGL attributes
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
			            SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_Window *window = SDL_CreateWindow("Custom",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          800, 580, SDL_WINDOW_OPENGL);

    if (window)
    {
        // Create SDL gl context rather than a renderer
        SDL_GLContext gl_context = SDL_GL_CreateContext(window);

        if (gl_context)
        {
            GLenum status = glewInit();
            if (status != GLEW_OK)
            {
                printf("Error while initalizing glew");
            }

            // Create vertex_shader
            int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
            glCompileShader(vertex_shader);

            // Check for shader compile errors
            int success;
            char info_log[512];
            glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
                printf("Shader compile error: %s", info_log);
            }

            // fragment shader
            int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
            glCompileShader(fragment_shader);

            // check for shader compile errors
            glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
                printf("Shader compile error: %s", info_log);
            }
            
            // link shaders
            int shader_program = glCreateProgram();
            glAttachShader(shader_program, vertex_shader);
            glAttachShader(shader_program, fragment_shader);
            glLinkProgram(shader_program);

            // check for linking errors
            glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader_program, 512, NULL, info_log);
                printf("Shader link error: %s", info_log);
            }

            // Delete both shaders after linking
            glDeleteShader(vertex_shader);
            glDeleteShader(fragment_shader);

            // set up vertex data
            float vertices[] = {
                // lower triangle
                -0.5f, -0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
                -0.5f,  0.5f, 0.0f,

                // upper triangle
                -0.5f, 0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
                0.5f,  0.5f, 0.0f
            }; 

            unsigned int VBO, VAO;
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            glBindVertexArray(VAO);

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
                         vertices, GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                                  3 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            glBindBuffer(GL_ARRAY_BUFFER, 0); 

            glBindVertexArray(0); 

            Global_Platform.running = 1;
            while (Global_Platform.running)
            {
                SDL_Event event;
                while (SDL_PollEvent(&event))
                {
                    HandleEvent(&event);
                }

                glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT);

                glUseProgram(shader_program);
                glBindVertexArray(VAO);
                glDrawArrays(GL_TRIANGLES, 0, 6);

                SDL_GL_SwapWindow(window);
            }

            glDeleteVertexArrays(1, &VAO);
            glDeleteBuffers(1, &VBO);
            glDeleteProgram(shader_program);
        }
        else
        {
            printf("SDL_CreateRenderer failed: %s", SDL_GetError());
        }
    }
    else
    {
        printf("SDL_CreateWindow failed: %s", SDL_GetError());
    }

    SDL_Quit();
    return 0;
}

