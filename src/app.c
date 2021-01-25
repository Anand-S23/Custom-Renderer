#include "memory.c"
#include "app.h"
#include "renderer.c"

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


internal void UpdateApp(platform *platform)
{
    Assert(sizeof(app_state) <= platform->storage_size);

    app_state *state = (app_state *)platform->storage;
    if (!platform->initialized)
    {
        state->permanent_arena = 
            InitMemoryArena(platform->storage, platform->storage_size);

        state->transient_arena = 
            InitMemoryArena(platform->transient_storage, platform->transient_storage_size);

        AllocateMemoryArena(&state->permanent_arena, sizeof(app_state));

        state->shader_program = CreateShaderProgram(vertex_shader_source,
                                                    fragment_shader_source);

        glGenVertexArrays(1, &state->VAO);
        glGenBuffers(1, &state->VBO);
        glBindVertexArray(state->VAO);

        platform->initialized = 1;
    }

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

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // SetData(state, vertices);
    glBindBuffer(GL_ARRAY_BUFFER, state->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
                 vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                          3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    glBindVertexArray(0); 

    // DisplayProgram(state, 6);
    glUseProgram(state->shader_program);
    glBindVertexArray(state->VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
