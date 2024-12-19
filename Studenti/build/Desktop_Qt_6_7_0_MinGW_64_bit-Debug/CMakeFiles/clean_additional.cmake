# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Studenti_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Studenti_autogen.dir\\ParseCache.txt"
  "Studenti_autogen"
  )
endif()
