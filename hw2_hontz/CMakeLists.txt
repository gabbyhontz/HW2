# CMakeList.txt : CMake project for hw2_hontz, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (hw2_hontz "hw2_hontz.cpp" "hw2_hontz.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET hw2_hontz PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
