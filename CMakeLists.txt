cmake_minimum_required(VERSION 3.12)

set(PROJECT Image_Processing)
set(UNIT_TEST_RUNNER UnitTestRunner)

project(${PROJECT})

#Add OpenCV
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

# Create a variable to hold the path to the "Images" folder
set(IMAGES_DIR ${CMAKE_SOURCE_DIR}/Images)

# Get a list of all image files in the "Images" folder with a .jpg extension
# Get a list of all image files in the "Images" folder with a .jpg extension
file(GLOB IMAGE_FILES ${IMAGES_DIR}/*.jpg)

# Copy all image files from the "Images" folder to the build directory
foreach(IMAGE_FILE ${IMAGE_FILES})
    get_filename_component(FILE_NAME ${IMAGE_FILE} NAME)
    configure_file(${IMAGE_FILE} ${CMAKE_BINARY_DIR}/${PROJECT}/${FILE_NAME} COPYONLY)
endforeach()

#
# Manually specifying all the source files.
#
set(HEADER_FILES
    ImageProcessing.hpp
    )

set(SOURCE_FILES
    ImageProcessing.cpp
    main.cpp
    )

set(UNIT_TEST_FILES
    test.cpp)

#
# This is the main target
#
add_executable(${PROJECT} ${HEADER_FILES} ${SOURCE_FILES}  main.cpp)
add_executable(${UNIT_TEST_RUNNER} ${HEADER_FILES} ${UNIT_TEST_FILES})

#
# We want the C++ 20 standard for our project
#
set_property(TARGET ${PROJECT} PROPERTY CXX_STANDARD 20)
set_property(TARGET ${UNIT_TEST_RUNNER} PROPERTY CXX_STANDARD 20)

#
# Enable a lot of warnings for both compilers, forcing the developer to write better code
#
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    target_compile_options(${PROJECT} PRIVATE /W4 /permissive-)
    target_compile_options(${UNIT_TEST_RUNNER} PRIVATE /W4 /permissive-)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    target_compile_options(${PROJECT} PRIVATE -O3 -Wall -Wextra -pedantic) # -Wconversion -Wsign-conversion
    target_compile_options(${UNIT_TEST_RUNNER} PRIVATE -O3 -Wall -Wextra -pedantic)
endif()

# -------------------------------------------------------------------
#
# Add GoogleTest
#
# -------------------------------------------------------------------
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY    https://github.com/google/googletest.git
    GIT_TAG           release-1.11.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googleTest)

target_link_libraries(${UNIT_TEST_RUNNER} gtest_main)

target_link_libraries(${PROJECT} ${OpenCV_LIBS})
target_link_libraries(${UNIT_TEST_RUNNER} ${OpenCV_LIBS} gtest_main)
#
# Prepare a pre-build step to run clang-format over all the [ch]pp source files.
# Start by finding the location of the clang-format executable.
#
find_program(CLANG_FORMAT "clang-format")
if (CLANG_FORMAT)
    message("Clang-Format found at: " ${CLANG_FORMAT})

    #
    # Need to take the simple source file locations used for the project and get their full
    # file system locations for use in putting together the clang-format command line
    #
    unset(SOURCE_FILES_PATHS)
    foreach(SOURCE_FILE ${HEADER_FILES} ${SOURCE_FILES} ${UNIT_TEST_FILES} main.cpp)
        get_source_file_property(WHERE ${SOURCE_FILE} LOCATION)
        set(SOURCE_FILES_PATHS ${SOURCE_FILES_PATHS} ${WHERE})
    endforeach()

    #
    # This creates the clang-format target/command
    #
    add_custom_target(
        ClangFormat
        COMMAND ${CLANG_FORMAT}
        -i
        -style=file
        ${SOURCE_FILES_PATHS}
    )
    #
    # This makes the clang-format target a dependency of the main ${PROJECT} project
    #
    add_dependencies(${PROJECT} ClangFormat)
    add_dependencies(${UNIT_TEST_RUNNER} ClangFormat)
else()
    message("Unable to find clang-format")
endif()
