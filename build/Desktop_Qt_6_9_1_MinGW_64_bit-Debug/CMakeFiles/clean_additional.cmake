# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\QLDSV_TC_GUI_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\QLDSV_TC_GUI_autogen.dir\\ParseCache.txt"
  "QLDSV_TC_GUI_autogen"
  )
endif()
