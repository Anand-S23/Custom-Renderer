@echo off

set glfw=w:\glfw\include
set glad=w:\glad\include
set glfw_lib=W:\glfw\glfw\lib-vc2019
set glad_src=w:\glad\src

set compiler_options=/nologo /FC /Zi /MD
set linker_options=user32.lib gdi32.lib Shell32.lib winmm.lib
set external=%glad_src%/glad.c %glfw_lib%/glfw3.lib %glfw_lib%/glfw3dll.lib -I%glad% -I%glfw%

set build_file=../src/win32_platform.c

if not exist build mkdir build 
pushd build 
cl %compiler_options% %build_file% %external% %linker_options% -link /machine:x64 /out:custom.exe /entry:mainCRTStartup -subsystem:WINDOWS 
popd