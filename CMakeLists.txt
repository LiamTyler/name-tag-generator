cmake_minimum_required(VERSION 3.0)
project(NametagGenerator)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_CURRENT_BINARY_DIR}/bin)


include_directories(
    ${CMAKE_SOURCE_DIR}
	C:/Users/Tyler/Downloads/freetype-2.9/include
    ext/
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
    src/image.cpp
    src/texture.cpp
    src/shader.cpp
    src/canvas.cpp
    )

set(INCLUDES
    include/ui_manager.h
    include/ui_image.h
    include/ui_textbox.h
    include/ui_widget.h
    include/image.h
    include/texture.h
    include/shader.h
    include/stb_image.h
    include/stb_image_write.h
    include/canvas.h
    )

add_executable(${PROJECT_NAME} ${SOURCES} ${INCLUDES})
set_target_properties(
    ${PROJECT_NAME} 
    PROPERTIES
    DEBUG_POSTFIX _debug
    )

set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

add_subdirectory(ext/nanogui)
include_directories(ext/nanogui/include)
include_directories(${NANOGUI_EXTRA_INCS})
add_definitions(${NANOGUI_EXTRA_DEFS})

target_link_libraries(${PROJECT_NAME} freetype.lib nanogui ${NANOGUI_EXTRA_LIBS})
