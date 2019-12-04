add_library(Triangle SHARED triangle.cpp )
add_library(Square SHARED square.cpp)

if(NOT APPLE)
    link_libraries("-Wl,--no-as-needed -ldl")
endif(NOT APPLE)

add_executable(Test main.cpp)