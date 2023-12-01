add_library(day STATIC
    src/Day.cpp
)
target_include_directories(day BEFORE
    PUBLIC include
)

target_compile_definitions(day PRIVATE DIRROOT=\"${PROJECT_SOURCE_DIR}/\")