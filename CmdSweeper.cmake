add_executable("CmdSweeper"
"src/cmdSweeper.cpp"
"src/cmdSweeper.h"
"src/consoleSetup.cpp"
"src/consoleSetup.h"
"src/main.cpp"
)
if(CMAKE_BUILD_TYPE STREQUAL Debug)
  set_target_properties("CmdSweeper" PROPERTIES
    OUTPUT_NAME "CmdSweeper"
    ARCHIVE_OUTPUT_DIRECTORY "bin/Debug"
    LIBRARY_OUTPUT_DIRECTORY "bin/Debug"
    RUNTIME_OUTPUT_DIRECTORY "bin/Debug"
  )
endif()
target_include_directories("CmdSweeper" PRIVATE
  $<$<CONFIG:Debug>:C:/Users/gwch3/CLionProjects/CmdSweeper/libs/fmt-9.1.0/include>
)
target_compile_definitions("CmdSweeper" PRIVATE
  $<$<CONFIG:Debug>:DEBUG>
)
target_compile_options("CmdSweeper" PRIVATE
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:C>>:-g>
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:CXX>>:-g>
)
if(CMAKE_BUILD_TYPE STREQUAL Release)
  set_target_properties("CmdSweeper" PROPERTIES
    OUTPUT_NAME "CmdSweeper"
    ARCHIVE_OUTPUT_DIRECTORY "bin/Release"
    LIBRARY_OUTPUT_DIRECTORY "bin/Release"
    RUNTIME_OUTPUT_DIRECTORY "bin/Release"
  )
endif()
target_include_directories("CmdSweeper" PRIVATE
  $<$<CONFIG:Release>:C:/Users/gwch3/CLionProjects/CmdSweeper/libs/fmt-9.1.0/include>
)
target_compile_definitions("CmdSweeper" PRIVATE
  $<$<CONFIG:Release>:NDEBUG>
)
target_compile_options("CmdSweeper" PRIVATE
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:C>>:-O2>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:CXX>>:-O2>
)