cmake_minimum_required(VERSION 3.0.0)
project(mclient_tra_preprocessor)
set(CMAKE_CXX_STANDARD 20)

# Debug
set(CMAKE_BUILD_TYPE Debug)

# Executables
set(mclient_tra_preprocessor "mclient_tra_preprocessor")

# Main
file(GLOB mclient_tra_preprocessor_SRC
    "src/mclient_tra_preprocessor.cc"
)
add_executable(${mclient_tra_preprocessor}
    ${mclient_tra_preprocessor_SRC}
)
target_link_libraries(${mclient_tra_preprocessor}
)

# Headers
include_directories(
    "src"
)
