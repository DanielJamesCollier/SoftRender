cmake_minimum_required(VERSION 3.0)

project(SoftRender)

add_subdirectory(./src)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")

add_executable(${PROJECT_NAME} ${SOURCEFILES})

add_custom_target(
    Resources ALL
    ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/res ./res
    SOURCES ${Resources}
)

if(APPLE)

target_link_libraries(${PROJECT_NAME}
    "-framework SDL2"
)

endif(APPLE)
