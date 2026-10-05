find_package(Python3 REQUIRED COMPONENTS Interpreter)
set(aquagram_overlay_dir ${CMAKE_CURRENT_BINARY_DIR}/aquagram)
set(aquagram_toolkit_dir ${CMAKE_CURRENT_SOURCE_DIR}/lib_ui)
execute_process(
    COMMAND ${Python3_EXECUTABLE}
        ${CMAKE_CURRENT_SOURCE_DIR}/cmake/aquagram_overlay.py
        ${aquagram_toolkit_dir} ${aquagram_overlay_dir}
    RESULT_VARIABLE aquagram_overlay_result
    ERROR_VARIABLE aquagram_overlay_error
)
if (NOT aquagram_overlay_result EQUAL 0)
    message(FATAL_ERROR "AquaGram toolkit overlay failed: ${aquagram_overlay_error}")
endif()
get_target_property(aquagram_sources lib_ui SOURCES)
foreach (file
    ui/style/style_core.cpp
    ui/widgets/buttons.cpp
    ui/widgets/fields/input_field.cpp
    ui/widgets/fields/masked_input_field.cpp)
    set(original ${aquagram_toolkit_dir}/${file})
    if (NOT original IN_LIST aquagram_sources)
        message(FATAL_ERROR "AquaGram toolkit source missing: ${original}")
    endif()
    list(REMOVE_ITEM aquagram_sources ${original})
    list(APPEND aquagram_sources ${aquagram_overlay_dir}/${file})
    set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS ${original})
endforeach()
set_property(TARGET lib_ui PROPERTY SOURCES ${aquagram_sources})
target_include_directories(lib_ui PRIVATE ${src_loc})
set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/aquagram_overlay.py)

add_library(aquagram_styles INTERFACE)
generate_styles(aquagram_styles ${src_loc}
    "ui/aquagram/aquagram.style"
    "${dependent_style_files}")
add_dependencies(lib_ui aquagram_styles_styles)
add_dependencies(td_ui_styles aquagram_styles_styles)
target_link_libraries(lib_ui PUBLIC aquagram_styles)
target_sources(lib_ui PRIVATE
    ${src_loc}/ui/aquagram/aquagram.cpp
    ${src_loc}/ui/aquagram/aquagram.h
    ${CMAKE_CURRENT_BINARY_DIR}/gen/styles/style_aquagram.cpp)
