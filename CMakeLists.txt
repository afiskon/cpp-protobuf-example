cmake_minimum_required(VERSION 3.1)

project(protobuf-example)

include_directories(include)
set(CMAKE_CXX_STANDARD 17) 
set(CMAKE_CXX_STANDARD_REQUIRED on)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

include(FindProtobuf)
find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIR})

# to find *.bp.h files
include_directories(${CMAKE_CURRENT_BINARY_DIR})

protobuf_generate_cpp(PROTO_SRC PROTO_HEADER src/proto/Game.proto)
add_library(proto ${PROTO_HEADER} ${PROTO_SRC})
add_executable(main src/Main.cpp)
target_link_libraries(main proto ${PROTOBUF_LIBRARY})
