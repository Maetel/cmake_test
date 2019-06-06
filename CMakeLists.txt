cmake_minimum_required(VERSION 3.0.0)

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(BIN_DIR "${CMAKE_CURRENT_BINARY_DIR}")
set(SRCS "srcs")

message("Source directory : ${SRC_DIR}")
message("Binary directory : ${BIN_DIR}")

####################################################################
#3rd party
set(3RD_PARTY "${SRC_DIR}/3rdparty")

#Eigen
set(EIGEN_VERSION "3.3.7")
set(EIGEN_SRC "${3RD_PARTY}/eigen/${EIGEN_VERSION}")

####################################################################
#macros

macro(set_as_project)

    #set project
    get_filename_component(ProjectId ${CMAKE_CURRENT_LIST_DIR} NAME)
    string(REPLACE " " "_" ProjectId ${ProjectId})
    project(${ProjectId})

    #add files
    FILE(GLOB CPP_FILES "*.cpp")
    FILE(GLOB HEADER_FILES "*.h" "*.hpp")
    add_executable(${ProjectId} "${CPP_FILES}" "${HEADER_FILES}")

    message("Project : ${ProjectId} added")
endmacro()

macro(link_eigen)
    include_directories("${EIGEN_SRC}")
endmacro()

macro(subdirlist subdirs curdir)
    FILE(GLOB dirs RELATIVE ${curdir} ${curdir}/*)
    SET(dirlist "")
    FOREACH(dir ${dirs})
        IF(IS_DIRECTORY ${curdir}/${dir})
            LIST(APPEND dirlist ${dir})
        ENDIF()
    ENDFOREACH()
    SET(subdirs ${dirlist})
endmacro()

macro(set_base_proj)
    get_filename_component(ProjectId ${CMAKE_CURRENT_LIST_DIR} NAME)
    project(${ProjectId})
endmacro()

macro(add_sub_dirs)
    set(curdir "${CMAKE_CURRENT_LIST_DIR}")
    subdirlist(subdirs ${curdir})
    FOREACH(dir ${subdirs})
        add_subdirectory(${dir})
    ENDFOREACH()
endmacro()

set_base_proj()
add_subdirectory(${SRCS})