-------------------------------------------------------------------------------
-- CDS Build Configuration
-------------------------------------------------------------------------------
solution "C Data Structures"
configurations { "Release" }
targetdir "build"

-------------------------------------------------------------------------------
-- CDS - A library of common data structures written in C
-------------------------------------------------------------------------------
project "cds"
    kind "SharedLib"
    language "C"
    location "build"
    files { "source/**.*" }

project "tests"
    kind "ConsoleApp"
    language "C++"
    location "build"
    links { "UnitTest++", "cds" }
    includedirs { "source/**", "tools/UnitTest++/**" }
    files { "tests/**.c*" }
    postbuildcommands { "./tests.exe" }

project "doxygen"
    postbuildcommands { "doxygen" }

-------------------------------------------------------------------------------
-- UnitTest++ - A C++ unit testing library
-------------------------------------------------------------------------------
project "UnitTest++"
    kind "SharedLib"
    language "C++"
    location "build"
    files {
        "tools/UnitTest++/src/*.*",
    }
    if os.is "windows" then
        files { "tools/UnitTest++/src/Win32/**.*" }
    else
        files { "tools/UnitTest++/src/Posix/**.*" }
    end

