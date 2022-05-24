cmake_minimum_required(VERSION 3.12)
project(OpenGL)
 
set(CMAKE_CXX_STANDARD 14)
 
set(GLFW_H ${CMAKE_SOURCE_DIR}/3rdparty/glfw-3.3.7/include/GLFW)
set(GLAD_H ${CMAKE_SOURCE_DIR}/3rdparty/glad/include)
set(KH_H ${CMAKE_SOURCE_DIR}/3rdparty/glad/include/KHR)
include_directories(${GLEW_H} ${GLFW_H} ${GLAD_H} ${KH_H})
 
# 添加目标链接
set(GLFW_LINK ${CMAKE_SOURCE_DIR}/3rdparty/glfw-3.3.7/lib-universal/libglfw.3.dylib)
link_libraries(${OPENGL} ${GLFW_LINK})

set(OpenCV_DIR ${CMAKE_SOURCE_DIR}/3rdparty/OpenCV-3.4.2/share/OpenCV)
find_package(OpenCV REQUIRED)

# 执行编译命令
# 这个glad.c在第2步中说过要拉到项目中，注意路径
#set(SOURCE_FILES "3rdparty/glad/src/glad.c" "example/main.cpp")
#add_executable(test ${SOURCE_FILES})
 
set(SOURCE_FILES "example/test.cpp")
add_executable(test ${SOURCE_FILES})
# mac下这步很重要
#if (APPLE)
    message(STATUS "Using MacOS for Complie Project")
    target_link_libraries(test "-framework OpenGL" "-framework GLUT" ${OpenCV_LIBS})
#endif()

