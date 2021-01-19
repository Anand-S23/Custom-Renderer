#include <SDL.h>
#include <GL/glew.h>
#include <stdio.h>

#include "win32_platform.h" 

global b32 Global_Running;

internal void HandleEvent(SDL_Event *event)
{
    switch (event->type)
    {
        case SDL_QUIT:
        {
            Global_Running = 0;
        } break;

        case SDL_KEYUP:
        case SDL_KEYDOWN:
        {
            if (event->key.repeat == 0)
            {
                switch (event->key.keysym.scancode)
                {
                    case SDL_SCANCODE_SPACE:
                    {
                    } break;

                    case SDL_SCANCODE_ESCAPE:
                    {
                    } break;
                }
           }
        } break;

        case SDL_MOUSEBUTTONDOWN:
        {
        } break;

        case SDL_MOUSEBUTTONUP:
        {
        } break;

        case SDL_MOUSEMOTION:
        {
        } break;
    }
}

int main(int argc, char** argv)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL_Init failed: %s", SDL_GetError());
    }

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
                                          640, 480, SDL_WINDOW_OPENGL);

    if (window)
    {
        SDL_GLContext gl_context = SDL_GL_CreateContext(window);

        if (gl_context)
        {
            GLenum status = glewInit();
            if (status != GLEW_OK)
            {
                printf("Error while initalizing glew");
            }

            Global_Running = 1;
            while (Global_Running)
            {
                SDL_Event event;
                while (SDL_PollEvent(&event))
                {
                    HandleEvent(&event);
                }

                glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT);

                SDL_GL_SwapWindow(window);
            }
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

