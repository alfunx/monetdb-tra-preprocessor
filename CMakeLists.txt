cmake_minimum_required(VERSION 3.0.0)
project(mclient_tra)
set(CMAKE_CXX_STANDARD 20)

# Debug
set(CMAKE_BUILD_TYPE Debug)

# Executables
set(mclient_tra "mclient_tra")

# Main
file(GLOB mclient_tra_SRC
    "src/mclient_tra.cc"
)
add_executable(${mclient_tra}
    ${mclient_tra_SRC}
)
target_link_libraries(${mclient_tra}
)

# Headers
include_directories(
    "src"
)
