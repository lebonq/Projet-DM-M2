cmake_minimum_required(VERSION 3.11)

project(Projet_DM_Quentin_Lebon)

include(FetchContent)

# Avoid warning about DOWNLOAD_EXTRACT_TIMESTAMP in CMake 3.24:
if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
    cmake_policy(SET CMP0135 NEW)
endif()

# Print with color
if(NOT WIN32)
  string(ASCII 27 Esc)
  set(Reset "${Esc}[m")
  set(Red         "${Esc}[31m")
  set(Green       "${Esc}[32m")

endif()


message(STATUS "${Green} # - Starting Cmake Build - # ${Reset}")

# Set the folder where the executables are created
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})

# Include glimac
add_subdirectory(glimac)


FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)
message(STATUS "${Green} Downloading JSON for modern C++ ${Reset}")
FetchContent_Declare(
	freetype
	GIT_REPOSITORY https://github.com/aseprite/freetype2.git
	GIT_TAG		   master
)
FetchContent_GetProperties(freetype)
if(NOT freetype_POPULATED)
	FetchContent_Populate(freetype)
	add_subdirectory(${freetype_SOURCE_DIR} ${freetype_BINARY_DIR})
endif()
message(STATUS "${Green} Downloading FreeType2 ${Reset}")


set(TARGET_NAME ${PROJECT_NAME}_exe)
add_executable(${TARGET_NAME})
target_compile_features(${TARGET_NAME} PRIVATE cxx_std_11)

# Enable many good warnings
if (MSVC)
    target_compile_options(${TARGET_NAME} PRIVATE /WX /W3)
else()
    target_compile_options(${TARGET_NAME} PRIVATE -Wall -J=8)
endif()

# Add all the source and header files
target_include_directories(${TARGET_NAME} PRIVATE)
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS src/*)
target_sources(${TARGET_NAME} PRIVATE ${MY_SOURCES})

# Add glimac as a dependency
target_link_libraries(${TARGET_NAME} glimac nlohmann_json::nlohmann_json freetype)

# Copy the assets and the shaders to the output folder (where the executable is created)
include("CMakeUtils/files_and_folders.cmake")
Cool__target_copy_folder(${TARGET_NAME} assets)
Cool__target_copy_folder(${TARGET_NAME} src/shaders)
