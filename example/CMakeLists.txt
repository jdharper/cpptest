project (example CXX)
include_directories(..)

add_executable(example example.cpp)

target_link_libraries(example cpptest)

