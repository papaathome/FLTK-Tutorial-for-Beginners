
### Boot process ################################################################# {{{1

set(boot_srcs
    main.cpp
)

set(boot_hdrs
)

set(test_srcs
    main_test.cpp
)

set(test_hdrs
)


### Examples (resources) ######################################################### {{{1

set(gui_resources
    jolly.jpg
    jolly.png
)

foreach(gui_item IN LISTS gui_resources)
    configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/resources/${gui_item}"
        "${CMAKE_BINARY_DIR}/source/${gui_item}"
        COPYONLY
    )
endforeach()

### Examples (sources) ########################################################### {{{1

include_directories( ${CMAKE_SOURCE_DIR}/source )
set(root ${CMAKE_SOURCE_DIR}/source)
set (examples
    ${root}/example0.cpp  # empty test (not in the tutorial).
    ${root}/example1.cpp  # window
    ${root}/example2.cpp  # button
    ${root}/example3.cpp  # window class
    ${root}/example4.cpp  # callback
    ${root}/example5.cpp  # input/output
    ${root}/example6.cpp  # editor
    ${root}/example7.cpp  # brouwser
    ${root}/example8.cpp  # menu bar
    ${root}/example9.cpp  # toolbar
    ${root}/example10.cpp # dialog window, radio button
    ${root}/example11.cpp # images
    ${root}/example12.cpp # images, scrollbar
    ${root}/example13.cpp # tabs
    ${root}/example14.cpp # mouse over
    ${root}/example15.cpp # mouse events
    ${root}/example16.cpp # events
    ${root}/example17.cpp # tree
)

### Examples (building) ########################################################## {{{1

foreach(f IN LISTS examples)
    if(NOT EXISTS "${f}")
        message("-- ${f}: file not found, skipped.")
        continue()
    endif()
    get_filename_component(f_name ${f} NAME_WE)

    add_library(lib${f_name} STATIC ${f})
    set_target_properties(lib${f_name} PROPERTIES
        LINKER_LANGUAGE CXX
        POSITION_INDEPENDENT_CODE ON)
    target_include_directories(lib${f_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )
    target_link_libraries(lib${f_name} PRIVATE
        compiler_flags
        fltk::images
        fltk::fltk
    )

    add_executable(${f_name} ${boot_srcs} ${boot_hdrs} )
    set_target_properties(${f_name} PROPERTIES LINKER_LANGUAGE CXX)
    target_link_libraries(${f_name} PRIVATE compiler_flags lib${f_name})

    if (${APP_TESTING_ENABLED})
        add_test(NAME ${f_name} COMMAND ${f_name})
    endif()
endforeach()

