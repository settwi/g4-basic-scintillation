cmake_minimum_required(VERSION 3.18)
set(CMAKE_CXX_STANDARD 20)
project(scintExample)

set(EXC_OUT scintExample)

find_package(Geant4 REQUIRED ui_all vis_all)
include(${Geant4_USE_FILE})
add_executable(${EXC_OUT} main.cc)

include_directories("${PROJECT_SOURCE_DIR}/include")

add_subdirectory(src)
add_subdirectory(include)

target_sources(${EXC_OUT}
  PRIVATE
    main.cc
)

target_link_libraries(scintExample ${Geant4_LIBRARIES})

file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/data-out")
file(CREATE_LINK "${CMAKE_SOURCE_DIR}/macros" "${CMAKE_CURRENT_BINARY_DIR}/macros" SYMBOLIC)

add_compile_options(-Wall -Wextra -Wpedantic -pedantic -Werror)
add_compile_definitions(CMAKE_CURRENT_BINARY_DIR="${CMAKE_CURRENT_BINARY_DIR}")
