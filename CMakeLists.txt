cmake_minimum_required(VERSION 3.26)
project(dv_calculator2)

set(CMAKE_CXX_STANDARD 17)

add_executable(dv_calculator2 main.cpp
        calc.cpp)

set(FLTK_SKIP_FLUID true)
find_package(FLTK REQUIRED)
include_directories(${FLTK_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${FLTK_BASE_LIBRARY} ${FLTK_PLATFORM_DEPENDENT_LIBS})
