project(lab1 LANGUAGES CXX)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PRIVATE
    src/main.cpp
    PRIVATE FILE_SET CXX_MODULES
    TYPE CXX_MODULES
    FILES
    utils/lu.cppm
    utils/matrix.cppm
)

