cmake_minimum_required(VERSION 2.8)
project(Stargazer)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake-Modules/")

include(EnableCPP11Flag)
ENABLE_CPP11()

find_package(OpenGL REQUIRED)
find_package(GLFW REQUIRED)
find_package(Springbok REQUIRED)
find_package(OpenAL REQUIRED)

include_directories(${SPRINGBOK_INCLUDE_DIR})

set(SRC_GAME Stargazer.cpp
             GameCode/GameWorld.cpp GameCode/Assets.cpp GameCode/Ship.cpp GameCode/GameObject.cpp GameCode/StarSystem.cpp
	           LibCode/Controls.cpp
	 )
file(GLOB_RECURSE HEADERS "*.h" "*.hpp")

add_executable(Stargazer main.cpp 
												${SRC_GAME}
												${HEADERS})

target_link_libraries(Stargazer ${SPRINGBOK_LIBRARY} ${OPENGL_LIBRARY} ${GLFW_LIBRARY} ${OPENAL_LIBRARY})