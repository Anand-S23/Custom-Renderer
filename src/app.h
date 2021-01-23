#ifndef APP_H
#define APP_H

typedef struct app_state
{
    memory_arena permanent_arena;
    memory_arena transient_arena;

    int shader_program;
    unsigned int VBO;
    unsigned int VAO;
} app_state;


#endif
