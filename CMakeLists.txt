cmake_minimum_required(VERSION 3.0.0)

macro(set_as_project)

    #set project
    get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
    string(REPLACE " " "_" ProjectId ${ProjectId})
    project(${ProjectId})

    #add files
    FILE(GLOB CPP_FILES "*.cpp")
    FILE(GLOB HEADER_FILES "*.h")
    FILE(GLOB HEADER_HPP_FILES "*.hpp")
    add_executable(${ProjectId} "${CPP_FILES}")

    message("Project : ${CMAKE_PROJECT_NAME} added")
endmacro()

add_subdirectory(srcs)