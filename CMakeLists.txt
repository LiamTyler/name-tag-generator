cmake_minimum_required(VERSION 3.0)
project(NametagGenerator)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_CURRENT_BINARY_DIR}/bin)

set(PROGRESSION_DIR ${CMAKE_SOURCE_DIR}/ext/Progression)
add_subdirectory(${PROGRESSION_DIR})

list(APPEND CMAKE_MODULE_PATH ${PROGRESSION_DIR}/cmake)
include(Progression)

include_directories(
    ${CMAKE_SOURCE_DIR}
	C:/Users/Tyler/Downloads/freetype-2.9/include
    )

link_directories(
	C:/Users/Tyler/Downloads/freetype-2.9/build/Release
    )

set(SOURCES
    src/main.cpp
    src/ui_manager.cpp
    src/ui_image.cpp
    src/ui_textbox.cpp
    src/ui_widget.cpp
    )

set(INCLUDES
    include/ui_manager.h
    include/ui_image.h
    include/ui_textbox.h
    include/ui_widget.h
    )

add_executable(${PROJECT_NAME} ${SOURCES} ${INCLUDES})
set_target_properties(
    ${PROJECT_NAME} 
    PROPERTIES
    DEBUG_POSTFIX _debug
    )

set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} ${PROGRESSION_LIBS} freetype.lib)
