cmake_minimum_required(VERSION 3.15)
project(ParallelBastion VERSION 1.0.0 LANGUAGES CXX)

# C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SDL2 REQUIRED)

file(GLOB_RECURSE SOURCES 
    "src/*.cpp"
)

add_executable(parallel_bastion ${SOURCES})

target_include_directories(parallel_bastion PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${SDL2_INCLUDE_DIRS}
)

# Ensure SDL2 include path for Apple Silicon/Homebrew
if(EXISTS "/opt/homebrew/include/SDL2")
    include_directories(/opt/homebrew/include/SDL2)
endif()

target_link_libraries(parallel_bastion PRIVATE
    ${SDL2_LIBRARIES}
)

if(WIN32)
    target_compile_definitions(parallel_bastion PRIVATE WIN32_LEAN_AND_MEAN)
    if(SDL2_DLL)
        add_custom_command(TARGET parallel_bastion POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${SDL2_DLL} $<TARGET_FILE_DIR:parallel_bastion>
        )
    endif()
elseif(UNIX AND NOT APPLE)
    target_link_libraries(parallel_bastion PRIVATE pthread)
elseif(APPLE)
    target_link_libraries(parallel_bastion PRIVATE pthread)
endif()

if(MSVC)
    target_compile_options(parallel_bastion PRIVATE /W4)
else()
    target_compile_options(parallel_bastion PRIVATE -Wall -Wextra -Wpedantic)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(parallel_bastion PRIVATE DEBUG_BUILD)
else()
    target_compile_definitions(parallel_bastion PRIVATE RELEASE_BUILD)
endif()
