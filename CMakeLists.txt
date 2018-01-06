cmake_minimum_required(VERSION 3.5)
project(GLTester)

set(CMAKE_CXX_STANDARD 11)

set(THIRDPARTY_DIR "${CMAKE_SOURCE_DIR}/thirdparty")

#compile options
add_definitions(-DENABLE_CHECK_GL=TRUE)

#OpenGL
find_package(OpenGL REQUIRED)

#GLFW3 configuration
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory("${THIRDPARTY_DIR}/glfw-3.2.1")
#GLFW3 configuration end


#GLM configuration
#add_subdirectory("${THIRDPARTY_DIR}/glm")
#find_package(glm REQUIRED)
include_directories("${THIRDPARTY_DIR}/glm")
#GLM configuration end

#GLEW configuration
add_subdirectory("${THIRDPARTY_DIR}/glew-2.1.0")
add_definitions(-DGLEW_STATIC)
#GLEW configuration end

add_executable(GLTester
        main.cpp
        Drawable.cpp
        Initializer.cpp
)

include_directories(GLTester
        ${CMAKE_SOURCE_DIR}/enginecore/
        ${GLEW_INCLUDE_DIRS}
        ${OPENGL_INCLUDE_DIR}
        ${glm_SOURCE_DIR}
)

target_link_libraries(GLTester
        glfw
        glew-cmake
        ${OPENGL_gl_LIBRARY}
        ${OPENGL_glu_LIBRARY}
)

#copy assets
file(GLOB_RECURSE ASSET_FILES "${CMAKE_SOURCE_DIR}/assets/*")

foreach(ASSET_FILE ${ASSET_FILES})
    string(REPLACE ${CMAKE_SOURCE_DIR} "" ASSET_FILE_BUILD ${ASSET_FILE})
    configure_file(${ASSET_FILE} "${CMAKE_BINARY_DIR}${ASSET_FILE_BUILD}" COPYONLY)
endforeach(ASSET_FILE)
