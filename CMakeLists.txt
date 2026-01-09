cmake_minimum_required(VERSION 3.23)
project(mygame LANGUAGES C CXX)

# ---------------------------------------------
# Global configuration
# ---------------------------------------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# ---------------------------------------------
# SDL and EnTT (vendored)
# ---------------------------------------------
# Build SDL3 from the vendored folder.
# SDL_INSTALL, SDL_TESTS and other flags are controlled by CMakePresets.
add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)
add_subdirectory(vendored/entt EXCLUDE_FROM_ALL)

# ---------------------------------------------
# Executable
# ---------------------------------------------
add_executable(mygame
    src/main.cpp
    src/Game.cpp
    src/ecs/systems/RenderSystem.cpp
    src/ecs/systems/MovementSystem.cpp
    src/ecs/EntityFactory.cpp
)

target_link_libraries(mygame
    PRIVATE
        SDL3::SDL3
        EnTT::EnTT
)

target_include_directories(mygame
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src
)

# ---------------------------------------------
# Copy SDL3 shared library next to the executable (Windows only)
# ---------------------------------------------
if (WIN32 AND SDL_SHARED)
    add_custom_command(
        TARGET mygame POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:SDL3::SDL3>
            $<TARGET_FILE_DIR:mygame>
    )
endif()

# ---------------------------------------------
# Copy MSYS2 UCRT64 runtime DLLs automatically
# (libstdc++-6.dll, libgcc_s_seh-1.dll, libwinpthread-1.dll)
# ---------------------------------------------
if(WIN32 AND "${CMAKE_CXX_COMPILER}" MATCHES "msys64/.*/ucrt64")

    get_filename_component(MSYS_ROOT "${CMAKE_CXX_COMPILER}" DIRECTORY)
    set(MSYS_UCRT64_BIN "${MSYS_ROOT}")

    set(RUNTIME_DLLS
        "${MSYS_UCRT64_BIN}/libstdc++-6.dll"
        "${MSYS_UCRT64_BIN}/libgcc_s_seh-1.dll"
        "${MSYS_UCRT64_BIN}/libwinpthread-1.dll"
    )

    foreach(DLL ${RUNTIME_DLLS})
        add_custom_command(TARGET mygame POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${DLL}"
            "$<TARGET_FILE_DIR:mygame>"
        )
    endforeach()

endif()

# ---------------------------------------------
# Installation (optional for Linux)
# ---------------------------------------------
install(TARGETS mygame)