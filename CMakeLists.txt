cmake_minimum_required (VERSION 3.12)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
    cmake_policy(SET CMP0141 NEW)
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("nokia-jam-six")

# Raylib dependency
set(RAYLIB_VERSION 5.0)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
    include(FetchContent)
    FetchContent_Declare(
        raylib
        DOWNLOAD_EXTRACT_TIMESTAMP OFF
        URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
        set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif()
endif()

# set(raylib_VERBOSE 1)

add_executable (nokia-jam-six
        src/PickupItem.h
        src/PickupItem.cpp
        src/Player.cpp
        src/Player.h
        src/Witch.cpp
        src/Witch.h
        src/Timer.h
)
target_sources(nokia-jam-six PRIVATE "src/nokia-jam-six.cpp")
target_include_directories(nokia-jam-six PUBLIC include)
target_link_libraries(${PROJECT_NAME} raylib)

set_property(TARGET nokia-jam-six PROPERTY CXX_STANDARD 20)
add_custom_command(TARGET nokia-jam-six POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:nokia-jam-six>/resources)
# TODO: Add tests and install targets if needed.
