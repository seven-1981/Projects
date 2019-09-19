cmake_minimum_required(VERSION 2.6)

# Set project path
set(PROJ_PATH "/home/pi/CPP/BPMDetector")

# Set include directories
list(APPEND includes "${PROJ_PATH}"
		     "${PROJ_PATH}/Audio"
		     "${PROJ_PATH}/Audio/Wavfiles")

include_directories(${includes})
 
# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
# Locate ALSA
find_package(ALSA REQUIRED) 
include_directories(${ALSA_INCLUDE_DIRS})  

# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests TestMain.cpp)
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread ${ALSA_LIBRARIES})                 

# Set compiler flags
list(APPEND flags "-Wall" "-std=c++11")
target_compile_options(runTests PUBLIC ${flags})
