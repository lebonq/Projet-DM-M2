cmake_minimum_required(VERSION 3.11)

project(Projet_DM_Quentin_Lebon)

include(FetchContent)

# Set the folder where the executables are created
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})

# Include glimac
add_subdirectory(glimac)

# Avoid warning about DOWNLOAD_EXTRACT_TIMESTAMP in CMake 3.24:
if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
    cmake_policy(SET CMP0135 NEW)
endif()

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

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
target_link_libraries(${TARGET_NAME} glimac nlohmann_json::nlohmann_json)

# Copy the assets and the shaders to the output folder (where the executable is created)
include("CMakeUtils/files_and_folders.cmake")
Cool__target_copy_folder(${TARGET_NAME} assets)
Cool__target_copy_folder(${TARGET_NAME} src/shaders)
