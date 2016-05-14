project(example)

include(VicCopyVersion)
vic_copy_version(${PROJECT_NAME} GLOBAL)
message(STATUS "${PROJECT_NAME} version: ${${PROJECT_NAME}_VERSION}")
message(STATUS "${PROJECT_NAME} binary dir: ${${PROJECT_NAME}_BINARY_DIR}")
message(STATUS "${PROJECT_NAME} source dir: ${${PROJECT_NAME}_SOURCE_DIR}")
message(STATUS "Project binary dir: ${PROJECT_BINARY_DIR}")
message(STATUS "Project source dir: ${PROJECT_SOURCE_DIR}")

#Find all source files in a directory.
aux_source_directory(./ ${PROJECT_NAME}_src_list)
message(STATUS ${${PROJECT_NAME}_src_list})

if (BUILD_STATIC_LIBRARY)
    message(STATUS "STATIC ${PROJECT_NAME}")
    set(${PROJECT_NAME}_link_lib
        god-fiber_a
        god-context_a
        god-base_a
    )
    set(${PROJECT_NAME}_dependencies
        god-base_a
        god-context_a
        god-fiber_a
    )
else()
    message(STATUS "SHARED ${PROJECT_NAME}")
    set(${PROJECT_NAME}_link_lib
        god-fiber_so
        god-context_so
        god-base_so
    )
    set(${PROJECT_NAME}_dependencies
        god-base_so
        god-context_so
        god-fiber_so
    )
endif()

#if(LIBUNWIND)
#    list(APPEND ${PROJECT_NAME}_link_lib ${LIBUNWIND})
#endif()
#if(LIBLZMA)
#    list(APPEND ${PROJECT_NAME}_link_lib ${LIBLZMA})
#endif()
#if(LIBRT)
#    list(APPEND ${PROJECT_NAME}_link_lib ${LIBRT})
#endif()

if(NOT ${PROJECT_NAME}_src_list)
    return()
endif()

foreach(${PROJECT_NAME}_src ${${PROJECT_NAME}_src_list})
    get_filename_component(${PROJECT_NAME}_name ${${PROJECT_NAME}_src} NAME_WE)
    add_executable(${${PROJECT_NAME}_name} ${${PROJECT_NAME}_src})
    if(${PROJECT_NAME}_link_lib)
        target_link_libraries(${${PROJECT_NAME}_name} ${${PROJECT_NAME}_link_lib})
    endif()
    if(${PROJECT_NAME}_dependencies)
        add_dependencies(${${PROJECT_NAME}_name} ${${PROJECT_NAME}_dependencies})
    endif()
endforeach()

