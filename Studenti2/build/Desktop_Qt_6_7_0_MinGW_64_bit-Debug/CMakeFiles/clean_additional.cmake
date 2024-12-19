# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Studenti2_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Studenti2_autogen.dir\\ParseCache.txt"
  "Studenti2_autogen"
  )
endif()
