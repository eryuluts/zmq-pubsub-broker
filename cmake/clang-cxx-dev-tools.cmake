# Additional targets to perform clang-format/clang-tidy
# Get all project files
file(GLOB_RECURSE
     ALL_SOURCE_FILES
     *.cpp *.hpp *.proto
     )
list(FILTER ALL_SOURCE_FILES EXCLUDE REGEX build)

message(SOURCES: ${ALL_SOURCE_FILES})
# Adding clang-format target if executable is found
find_program(CLANG_FORMAT "clang-format")
if(CLANG_FORMAT)
  add_custom_target(
    clang-format
    COMMAND /usr/bin/clang-format
    -i
    -style=file
    ${ALL_SOURCE_FILES}
    )
endif()