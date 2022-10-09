require "clion"

workspace "CmdSweeper"
   configurations { "Debug", "Release" }

project "CmdSweeper"
   includedirs { "libs/fmt-9.1.0/include" }
   kind "ConsoleApp"
   language "C++"
   targetdir "bin/%{cfg.buildcfg}"

   files { "src/**.h", "src/**.cpp" }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"