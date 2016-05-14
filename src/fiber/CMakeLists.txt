project(god-fiber)

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

if(NOT ${PROJECT_NAME}_src_list)
    return()
endif()

#Static library
if(BUILD_STATIC_LIBRARY)
    message(STATUS "STATIC ${PROJECT_NAME}")
    add_library(${PROJECT_NAME}_a STATIC ${${PROJECT_NAME}_src_list})
    set_target_properties(${PROJECT_NAME}_a PROPERTIES OUTPUT_NAME "${PROJECT_NAME}")
    install(TARGETS ${PROJECT_NAME}_a DESTINATION lib)
endif()

#Shared library
if(BUILD_SHARED_LIBRARY)
    message(STATUS "SHARED ${PROJECT_NAME}")
    add_library(${PROJECT_NAME}_so SHARED ${${PROJECT_NAME}_src_list})
    set_target_properties(${PROJECT_NAME}_so PROPERTIES OUTPUT_NAME "${PROJECT_NAME}")
    set_target_properties(${PROJECT_NAME}_so PROPERTIES VERSION ${${PROJECT_NAME}_VERSION} SOVERSION ${${PROJECT_NAME}_VERSION_MAJOR})
    install(TARGETS ${PROJECT_NAME}_so DESTINATION lib)
endif()

