cmake_minimum_required(VERSION 3.30)

set(BUILD_TYPE "Debug and Release" CACHE STRING "Choose Build type")
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CONFIGURATION_TYPES Debug Release)

add_definitions(-DUNICODE)
add_definitions(-D_UNICODE)

# set the project name
project(VR-PointCloud-Editor)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

set(CMAKE_CXX_FLAGS_DEBUG "/MP /Zi /W3 /D IMGUI_IMPL_OPENGL_LOADER_GLEW /D WIN32 /D _WINDOWS /D _DEBUG /D FE_DEBUG_ENABLED")
set(CMAKE_CXX_FLAGS_RELEASE "/MP /W3 /Gy /sdl /GL /D IMGUI_IMPL_OPENGL_LOADER_GLEW /D NDEBUG /D WIN32 /D _WINDOWS")

# Turn on the ability to create folders to organize projects (.vcproj)
# It creates "CMakePredefinedTargets" folder by default and adds CMake
# defined projects like INSTALL.vcproj and ZERO_CHECK.vcproj
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build FEBasicApplication as a shared library" FORCE)
set(USE_STATIC_RUNTIME ON CACHE BOOL "Use static runtime (/MT) instead of dynamic (/MD)" FORCE)

if(NOT TARGET FocalEngine)
	add_subdirectory(SubSystems/FocalEngine)
endif()

# Extract the relative path of the engine folder
file(RELATIVE_PATH RELATIVE_PATH_TO_ENGINE_FOLDER "${CMAKE_CURRENT_SOURCE_DIR}" "${ENGINE_FOLDER}")
# We need to re-configure the Config.h file for the engine
# This is necessary for any project that will include FocalEngine
# to make sure that the engine can find its dependencies
set(ENGINE_FOLDER "${RELATIVE_PATH_TO_ENGINE_FOLDER}")
configure_file(${ENGINE_FOLDER}/ResourceManager/Config.h.in ${ENGINE_FOLDER}/ResourceManager/Config.h @ONLY)

if(USE_STATIC_RUNTIME)
    # Add standard FocalEngine native scripts
    # TODO: This should be done in the FocalEngine project, or make it simpler to add it user projects
    file(GLOB Unpacked_NativeScript_2B7956623302254F620A675F_SRC
	    "SubSystems/FocalEngine/Resources/UserScriptsData/ExtractedScriptModules/2B7956623302254F620A675F/FirstScript.h"
	    "SubSystems/FocalEngine/Resources/UserScriptsData/ExtractedScriptModules/2B7956623302254F620A675F/FirstScript.cpp"
    )
endif()

file(GLOB Main_SRC
	"main.cpp"
)

link_directories(${GLEW_LIB_DIR})
link_directories(${GLFW_LIB_DIR})

set(EXTRACTED_NATIVE_SCRIPTS "")
if(USE_STATIC_RUNTIME)
	list(APPEND EXTRACTED_NATIVE_SCRIPTS
		${Unpacked_NativeScript_2B7956623302254F620A675F_SRC}
	)

    add_definitions(-DGLEW_STATIC)
endif()

# add the executable
add_executable(VR-PointCloud-Editor WIN32
	                                ${Main_SRC}		  
)

target_link_libraries(VR-PointCloud-Editor 
    PRIVATE 
        FocalEngine
	
)

source_group("Source Files" FILES ${Main_SRC})
if(USE_STATIC_RUNTIME)
	source_group("Source Files/FocalEngine/2B7956623302254F620A675F" FILES ${EXTRACTED_NATIVE_SCRIPTS})
endif()

# set the startup project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT VR-PointCloud-Editor)

include_directories(
	${GLEW_INCLUDE_DIR}
	${BASICAPP_THIRDPARTY_DIR}
	${BASICAPP_DIR}
	${FOCAL_ENGINE_THIRD_PARTY_DIR}
)