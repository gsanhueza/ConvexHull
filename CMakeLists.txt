cmake_minimum_required(VERSION 2.6)
project(tarea_2)

macro(use_cxx11)
  if (CMAKE_VERSION VERSION_LESS "3.1")
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
      set (CMAKE_CXX_FLAGS "--std=gnu++11 ${CMAKE_CXX_FLAGS}")
    endif ()
  else ()
    set (CMAKE_CXX_STANDARD 11)
  endif ()
endmacro(use_cxx11)

add_executable(tarea_2 Stopwatch.cpp main.cpp)

install(TARGETS tarea_2 RUNTIME DESTINATION bin)
