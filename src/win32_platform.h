#ifndef WIN32_PLATFORM_H
#define WIN32_PLATFORM_H

#include <stdint.h>

typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef float  f32;
typedef double f64;

typedef i32 b32;

#define internal static
#define global static
#define local_persist static

#define Assert(expr) if(!(expr)) {*(int *)0 = 0;}

inline u32 SafeTruncateUInt64(u64 value)
{
    Assert(value <= 0xFFFFFFFF);
    return (u32)value;
}

enum {
#define Key(name, str) KEY_##name,
#include "platform_key_list.h"
    KEY_MAX
};

typedef struct platform
{
    b32 running;

    // Offscreen buffer
    void *memory;
    int width; 
    int height; 
    int pitch; 
    int bytes_per_pixel;

    // Input
    b32 key_down[KEY_MAX];
    int mouse_x;
    int mouse_y;
    b32 left_mouse_down;
    b32 right_mouse_down;
    b32 middle_mouse_down;

    // App memory
    b32 initialized;
    void *storage;
    u64 storage_size; 
    void *transient_storage; 
    u32 transient_storage_size;
} platform;

#endif
