cmake_minimum_required( VERSION 3.13.2 )

file(
    GLOB_RECURSE
    source_list
    RELATIVE
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "Iris/Include/*"
    "Iris/Source/*"
)

add_executable( Iris ${source_list} )
set_target_properties( Iris PROPERTIES CMAKE_AUTOMOC ON )
target_compile_definitions(Iris PUBLIC UNICODE)

find_package(
    Qt5
    REQUIRED COMPONENTS
    Core
    Widgets
    Gui
    WinExtras
)

target_link_libraries(
    Iris
    PUBLIC
    Qt5::Core
    Qt5::Widgets
    Qt5::Gui
    Qt5::WinExtras
    optimized   ${IRIS_RIVET_RELEASE_LIB_PATH}
    optimized   ${IRIS_ULIS_RELEASE_LIB_PATH}
    optimized   ${IRIS_BOKU_RELEASE_LIB_PATH}
    optimized   ${IRIS_LCMS2_RELEASE_LIB_PATH}
    debug       ${IRIS_RIVET_DEBUG_LIB_PATH}
    debug       ${IRIS_ULIS_DEBUG_LIB_PATH}
    debug       ${IRIS_BOKU_DEBUG_LIB_PATH}
    debug       ${IRIS_LCMS2_DEBUG_LIB_PATH}
)

target_include_directories(
    Iris
    PUBLIC
    "Iris/Include/"
    "Iris/Source/"
    "Iris/Source/Window/"
    "Iris/Source/Utils/"
    ${IRIS_RIVET_INCLUDE_PATH}
    ${IRIS_ULIS_INCLUDE_PATH}
    ${IRIS_BOKU_INCLUDE_PATH}
    ${IRIS_BOOST_INCLUDE_PATH}
    ${IRIS_COAL_INCLUDE_PATH}
    ${IRIS_GLM_INCLUDE_PATH}
    ${IRIS_LCMS2_INCLUDE_PATH}
)

# For MSVC parse pretty filter names
foreach(source IN LISTS source_list)
    get_filename_component(source_path "${source}" PATH)
    string(REPLACE "/" "\\" source_path_msvc "${source_path}")
    source_group("${source_path_msvc}" FILES "${source}")
endforeach()
