#set(GLEW_FOUND TRUE)
#set(GLEW_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include" PARENT_SCOPE)
#set(GLEW_SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/glew.c" PARENT_SCOPE)


cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

find_package(OpenGL REQUIRED)

add_library(glew-cmake STATIC "${CMAKE_CURRENT_SOURCE_DIR}/src/glew.c")
target_include_directories(glew-cmake PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" ${OPENGL_INCLUDE_DIR})
target_link_libraries(glew-cmake ${OPENGL_gl_LIBRARY})

set(GLEW_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include" PARENT_SCOPE)
