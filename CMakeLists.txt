cmake_minimum_required(VERSION 3.0.0)
project(monetdb-tra-preprocessor)
set(CMAKE_CXX_STANDARD 20)

# Debug
set(CMAKE_BUILD_TYPE Debug)

# Executables
set(monetdb-tra-preprocessor "monetdb-tra-preprocessor")

# Main
file(GLOB monetdb-tra-preprocessor_SRC
    "src/monetdb-tra-preprocessor.cc"
)
add_executable(${monetdb-tra-preprocessor}
    ${monetdb-tra-preprocessor_SRC}
)
target_link_libraries(${monetdb-tra-preprocessor}
)

# Headers
include_directories(
    "src"
)
