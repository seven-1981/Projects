cmake_minimum_required(VERSION 2.6)
 
# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
find_package(ALSA REQUIRED) 
include_directories(${ALSA_INCLUDE_DIRS})  

# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests TestMain.cpp)
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread ${ALSA_LIBRARIES})                 

# Set compiler flags
list(APPEND flags "-Wall")
target_compile_options(runTests PUBLIC ${flags})