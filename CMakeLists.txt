cmake_minimum_required(VERSION 3.15.3)
project(go)

include_directories(/usr/local/opt/curl/include/)
include_directories(/Users/afrankel02/cpp/cli/include/)

set(CMAKE_CXX_STANDARD 17)

set(CURL_LIBRARY "-lcurl")
find_package(CURL REQUIRED)

add_executable(tree tree.cpp )
add_executable(go main.cpp )
add_executable(o scratch.cpp )


include_directories(${CURL_INCLUDE_DIR})
target_link_libraries(go ${CURL_LIBRARIES})
