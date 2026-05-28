cmake_minimum_required(VERSION 4.2.3)
project(OctoCore)

add_executable(OctoCore)
target_sources(OctoCore
    PRIVATE
        src/main.c
        src/cpu.c
        src/display.c
        src/keyboard.c

    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS
            includes
        FILES
            includes/cpu.h
            includes/display.h
            includes/keyboard.h
)
add_subdirectory(vendor/SDL EXCLUDE_FROM_ALL)
target_link_libraries(OctoCore
    PRIVATE
        SDL3::SDL3
)
if (WIN32)
    add_custom_command(
        TARGET OctoCore POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy $<TARGET_FILE:SDL3::SDL3-shared> $<TARGET_FILE_DIR:OctoCore>
        VERBATIM
    )
endif()
