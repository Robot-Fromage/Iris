cmake_minimum_required(VERSION 3.11.0)

# Set Cache variables
SET( IRIS_EXPLICIT_HOST_ID          "unset"     CACHE STRING    "Explicitly set host ID from command line" )
SET( IRIS_EXPLICIT_COMPILER_ID      "unset"     CACHE STRING    "Explicitly set compiler ID from command line" )
SET( IRIS_USE_CONFIG                OFF         CACHE BOOL      "Scpecifies wether to use config files for overriding cache variables" )
SET( IRIS_QT_CMAKE_PATH             "unset"     CACHE STRING    "Indicates the path to Qt cmake package" )
SET( IRIS_RIVET_INCLUDE_PATH        "unset"     CACHE STRING    "Indicates the path to Rivet inlude dir" )
SET( IRIS_RIVET_DEBUG_LIB_PATH      "unset"     CACHE STRING    "Indicates the path to Rivet debug lib" )
SET( IRIS_RIVET_RELEASE_LIB_PATH    "unset"     CACHE STRING    "Indicates the path to Rivet release lib" )
SET( IRIS_ULIS_INCLUDE_PATH         "unset"     CACHE STRING    "Indicates the path to ULIS inlude dir" )
SET( IRIS_ULIS_DEBUG_LIB_PATH       "unset"     CACHE STRING    "Indicates the path to ULIS debug lib" )
SET( IRIS_ULIS_RELEASE_LIB_PATH     "unset"     CACHE STRING    "Indicates the path to ULIS release lib" )
SET( IRIS_BOKU_INCLUDE_PATH         "unset"     CACHE STRING    "Indicates the path to Bokuseru inlude dir" )
SET( IRIS_BOKU_DEBUG_LIB_PATH       "unset"     CACHE STRING    "Indicates the path to Bokuseru debug lib" )
SET( IRIS_BOKU_RELEASE_LIB_PATH     "unset"     CACHE STRING    "Indicates the path to Bokuseru release lib" )
SET( IRIS_BOOST_INCLUDE_PATH        "unset"     CACHE STRING    "Indicates the path to BOOST include dir" )
SET( IRIS_COAL_INCLUDE_PATH         "unset"     CACHE STRING    "Indicates the path to COAL include dir" )
SET( IRIS_GLM_INCLUDE_PATH          "unset"     CACHE STRING    "Indicates the path to GLM include dir" )
SET( IRIS_LCMS2_INCLUDE_PATH        "unset"     CACHE STRING    "Indicates the path to LCMS2 include dir" )
SET( IRIS_LCMS2_DEBUG_LIB_PATH      "unset"     CACHE STRING    "Indicates the path to LCMS2 debug lib" )
SET( IRIS_LCMS2_RELEASE_LIB_PATH    "unset"     CACHE STRING    "Indicates the path to LCMS2 release lib" )

# Display host & compiler
message( "Generating: ${IRIS_EXPLICIT_HOST_ID} ${IRIS_EXPLICIT_COMPILER_ID}")

# Generate only Debug and Release configurations for all projects
set( CMAKE_CONFIGURATION_TYPES Debug Release CACHE STRING INTERNAL FORCE )

# Generate only x64 configurations for all projects
#set( CMAKE_GENERATOR_PLATFORM x64 )

# Get rid of cmake's ZERO_CHECK for solution
set( CMAKE_SUPPRESS_REGENERATION true )

# Set Debug postfix for all projects
set( CMAKE_DEBUG_POSTFIX d )

# Set Runtime Library for all projects
#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")

# Set C++ standard options
set(CMAKE_CXX_FLAGS "-std=c++14")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Create global solution
project( IRIS CXX )

#--------------------------------------------
# Flags for Compiler / Platforms
# Flags for CLANG
if( "${IRIS_EXPLICIT_COMPILER_ID}" STREQUAL "CLANG" )
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse4.1")
    
# Flags for GCC
elseif( "${IRIS_EXPLICIT_COMPILER_ID}" STREQUAL "GCC" )
    # Specific flags for GNU GCC
    if( "${IRIS_EXPLICIT_HOST_ID}" STREQUAL "GNU" )
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse4.1 -W")
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
    # Specific flags for MinGW GCC
    elseif( "${IRIS_EXPLICIT_HOST_ID}" STREQUAL "WIN" )
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse4.1 -Wa,-mbig-obj")
    endif()

    # Support for alternat drop-in replacement of ld linker with Clang's lld, only for recent GCC ( not 7.3.0 shipped with Qt )
    #set(CMAKE_LINKER lld)
    #SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fuse-ld=lld")
    #SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -fuse-ld=lld")
    
elseif( "${IRIS_EXPLICIT_COMPILER_ID}" STREQUAL "MSVC" )
    # Flags for MSVC
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Zi -Gm- -Od -Ob0 -RTC1 -MDd")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -bigobj -EHsc")
endif()

#--------------------------------------------
# Read Preferences if needed
if( ${IRIS_USE_CONFIG} )
    #--------------------------------------------
    # Read Default Preferences
    include(${CMAKE_CURRENT_SOURCE_DIR}/../Tools/DefaultConfig.cmake)
    
    #--------------------------------------------
    # IF USING CLANG ON MAC WITH XCODE
    if( ${CMAKE_GENERATOR} STREQUAL "Xcode" )
        if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/../../Xcode_Config.cmake)
                message( "ouiouioui")
                include(${CMAKE_CURRENT_SOURCE_DIR}/../../Xcode_Config.cmake)
        endif()
    endif()
    
    #--------------------------------------------
    # IF USING CLANG ON WINDOWS WITH VISUALSTUDIO
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        # using Clang
        if( ${CMAKE_GENERATOR} STREQUAL "Visual Studio 15 2017 Win64" )
            if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/../../VisualStudio_Solution_CLANG_LLVM_Config.cmake)
                include(${CMAKE_CURRENT_SOURCE_DIR}/../../VisualStudio_Solution_CLANG_LLVM_Config.cmake)
            endif()
        endif()

    #--------------------------------------------
    # IF USING GCC
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        # Specific flags for GNU GCC
        if( "${IRIS_EXPLICIT_HOST_ID}" STREQUAL "GNU" )
            if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/../../SublimeText_Project_GNU_GCC_Config.cmake)
                include(${CMAKE_CURRENT_SOURCE_DIR}/../../SublimeText_Project_GNU_GCC_Config.cmake)
            endif()
        # Specific flags for MinGW GCC
        elseif( "${IRIS_EXPLICIT_HOST_ID}" STREQUAL "WIN" )
            if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/../../MinGW_Makefile_GCC_Config.cmake)
                include(${CMAKE_CURRENT_SOURCE_DIR}/../../MinGW_Makefile_GCC_Config.cmake)
            endif()
        endif()

    #--------------------------------------------
    # IF USING MSVC
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
        if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/../../VisualStudio_Solution_MSVC_Config.cmake)
            include(${CMAKE_CURRENT_SOURCE_DIR}/../../VisualStudio_Solution_MSVC_Config.cmake)
        endif()
    endif()
endif()

#--------------------------------------------
# Qt Options
if( NOT "${IRIS_QT_CMAKE_PATH}" STREQUAL "default")
    set (CMAKE_PREFIX_PATH ${IRIS_QT_CMAKE_PATH})
    set (CMAKE_AUTOMOC ON)
endif()

#--------------------------------------------
# Add projects
include(${CMAKE_CURRENT_SOURCE_DIR}/Iris/CMakeLists.txt)
set_property( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Iris )
