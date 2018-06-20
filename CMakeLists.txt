cmake_minimum_required(VERSION 3.0)
project(NametagGenerator)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_CURRENT_BINARY_DIR}/bin)

#include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)
include(ExternalProject)

set(OGLS_ROOT ${CMAKE_SOURCE_DIR}/ext/OpenGL_Starter)

#ExternalProject_Add(
#    OpenGL_Starter
#    GIT_REPOSITORY https://github.com/LiamTyler/OpenGL_Starter.git
#    GIT_TAG origin/windows
#    UPDATE_COMMAND ""
#    PREFIX ${OGLS_ROOT}
#    TMP_DIR ${OGLS_ROOT}/tmp
#    STAMP_DIR ${OGLS_ROOT}/tmp
#    DOWNLOAD_DIR ${OGLS_ROOT}
#    SOURCE_DIR ${OGLS_ROOT}
#    BINARY_DIR ${OGLS_ROOT}/build
#    CMAKE_ARGS -DBUILD_EXAMPLES=OFF
#    #CMAKE_GENERATOR "Visual Studio 15 2017 Win64"
#)

# Path to main directory of GLEW and SDL2
set(GLEW_DIR C:/GLEW)
set(SDL_DIR C:/SDL2)

# store the location of the DLL's
set(GLEW_DLL ${GLEW_DIR}/bin/Release/x64/glew32.dll)
set(SDL_DLL ${SDL_DIR}/lib/x64/SDL2.dll)

file(COPY ${GLEW_DLL} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin)
file(COPY ${SDL_DLL}  DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin)


include_directories(
    ${CMAKE_SOURCE_DIR}
    ${GLEW_DIR}/include
    ${SDL_DIR}/include
    ext/
    ${OGLS_ROOT}/project
    ${OGLS_ROOT}/project/src
    ${OGLS_ROOT}/ext
    ${OGLS_ROOT}/build/include
	C:/Users/Tyler/Downloads/freetype-2.9/include
    )

link_directories(
    ${GLEW_DIR}/lib/Release/x64
    ${SDL_DIR}/lib/x64
    ${OGLS_ROOT}/build/lib
	C:/Users/Tyler/Downloads/freetype-2.9/build/Release
    )

set(SOURCES
    src/main.cpp
    src/ui_manager.cpp
    src/ui_image.cpp
    src/ui_text.cpp
    )

set(INCLUDES
    include/ui_manager.h
    include/ui_image.h
    include/ui_text.h
    )

add_executable(${PROJECT_NAME} ${SOURCES} ${INCLUDES})
set_target_properties(
    ${PROJECT_NAME} 
    PROPERTIES
    DEBUG_POSTFIX _debug
    )

# Tell visual studio to build & run this project instead of ALL_BUILD by default.
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
#set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

#add_dependencies(${PROJECT_NAME} OpenGL_Starter)

target_link_libraries(
    ${PROJECT_NAME}
    debug OpenGL_Starter_debug.lib
    optimized OpenGL_Starter.lib
    opengl32.lib
    glew32s.lib
    SDL2.lib
    SDL2main.lib
	freetype.lib
    )
