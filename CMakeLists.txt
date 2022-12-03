cmake_minimum_required(VERSION 3.8)

project(SimpleGlimac)

# Set the folder where the executables are created
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})

# Include glimac
add_subdirectory(glimac)

# Create a target for each TP
function(setup_tp TP_NUMBER EXO_NUMBER)
    set(TARGET_NAME ${TP_NUMBER}_${EXO_NUMBER}_exe)
    add_executable(${TARGET_NAME})
    target_compile_features(${TARGET_NAME} PRIVATE cxx_std_11)

    # Enable many good warnings
    if (MSVC)
        target_compile_options(${TARGET_NAME} PRIVATE /WX /W3)
    else()
        target_compile_options(${TARGET_NAME} PRIVATE -Werror -W -Wall -Wextra -Wpedantic -pedantic-errors -J=8)
    endif()
    
    # Add all the source and header files
    target_include_directories(${TARGET_NAME} PRIVATE ${TP_NUMBER})
    file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS ${TP_NUMBER}/${EXO_NUMBER}*)
    target_sources(${TARGET_NAME} PRIVATE ${MY_SOURCES})

    # Add glimac as a dependency
    target_link_libraries(${TARGET_NAME} glimac)

    # Copy the assets and the shaders to the output folder (where the executable is created)
    include("CMakeUtils/files_and_folders.cmake")
    Cool__target_copy_folder(${TARGET_NAME} assets)
    Cool__target_copy_folder(${TARGET_NAME} ${TP_NUMBER}/shaders)
endfunction(setup_tp)

setup_tp(TP1 exo1)
setup_tp(TP1 exo2)
setup_tp(TP1 exo3)
setup_tp(TP1 exo4)
setup_tp(TP2 exo1)
setup_tp(TP3 exo1)
setup_tp(TP4 exo1)
setup_tp(TP5 exo1)
setup_tp(TP6 exo1)
setup_tp(TP7 exo1)
setup_tp(TP8 exo1)
setup_tp(TP9 exo1)