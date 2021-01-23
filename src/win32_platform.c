#include <SDL.h>
#include <GL/glew.h>
#include <stdio.h>

#include "win32_platform.h" 
#include "app.c"

global platform Global_Platform = {0};

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


            Global_Platform.running = 1;
            while (Global_Platform.running)
            {
                SDL_Event event;
                while (SDL_PollEvent(&event))
                {
                    HandleEvent(&event);
                }

                UpdateApp(&Global_Platform);

                SDL_GL_SwapWindow(window);
            }

            // glDeleteVertexArrays(1, &VAO);
            // glDeleteBuffers(1, &VBO);
            // glDeleteProgram(shader_program);
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

