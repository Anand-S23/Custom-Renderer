@echo off

set sdl=..\..\SDL2
set sdl_lib=%sdl%\lib\solo_x64
set glew=..\..\glew

set compiler_options=/nologo /FC /Zi /MD
set linker_options=user32.lib gdi32.lib Shell32.lib winmm.lib opengl32.lib
set external=-I%sdl%\include -I%glew%\include %sdl_lib%\SDL2.lib %sdl_lib%\SDL2main.lib %glew%\lib\glew32.lib

set build_file=../src/win32_platform.c

if not exist build mkdir build 
pushd build 
cl %compiler_options% %build_file% %external% %linker_options% -link /machine:x64 /out:custom.exe /entry:mainCRTStartup -subsystem:WINDOWS 
popd
