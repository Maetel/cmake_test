cmake_minimum_required(VERSION 3.8)

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(BIN_DIR "${CMAKE_CURRENT_BINARY_DIR}")
set(SRCS "framework")

if(NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 11)
    set(CMAKE_CXX_STANDARD_REQUIRED True)
endif()

option(BUILD_SHARED_LIBS "Build shared libs" ON)
option(USE_CUDA ON)

message("Source directory : ${SRC_DIR}")
message("Binary directory : ${BIN_DIR}")

####################################################################
#3rd party
set(3RD_PARTY "${SRC_DIR}/3rdparty")

#Eigen
set(EIGEN_VERSION "3.3.7")
set(EIGEN_SRC "${3RD_PARTY}/eigen/${EIGEN_VERSION}")

#CUDA
if(USE_CUDA)
    if(NOT DEFINED CMAKE_CUDA_STANDARD)
        set(CMAKE_CUDA_STANDARD 11)
        set(CMAKE_CUDA_STANDARD REQUIRED True)
    endif()
endif()

#JPEG
set(JPEG_VERSION "9c")
set(JPEG_SRC "${3RD_PARTY}/libjpeg/jpeg-${JPEG_VERSION}")
#http://www.ijg.org/
set(JPEG_RW_VERSION "1.0.1")
set(JPEG_RW_SRC "${3RD_PARTY}/JPEGReaderWriter/JPEGReaderWriter-${JPEG_RW_VERSION}")

#OpenCL
set(OpenCL_VERSION "1.2")
set(OpenCL_INCLUDE "${3RD_PARTY}/OpenCL/OpenCL${OpenCL_VERSION}/include")
set(OpenCL_STATIC_x64 "${3RD_PARTY}/OpenCL/OpenCL${OpenCL_VERSION}/lib/x64/OpenCL.lib")
set(OpenCL_STATIC_x86 "${3RD_PARTY}/OpenCL/OpenCL${OpenCL_VERSION}/lib/Win32/OpenCL.lib")

#CImg
set(CImg_VERSION "2.6.7")
set(CImg_INCLUDE "${3RD_PARTY}/CImg/CImg-${CImg_VERSION}")

#Boost
set(BOOST_VERSION "1.71.0")
set(BOOST_VERSION_REPLACED "")
STRING(REPLACE "." "_" BOOST_VERSION_REPLACED ${BOOST_VERSION})
set(BOOST_DIR "C:/work/srcs/boost")
set(BOOST_INCLUDE "${BOOST_DIR}/boost_${BOOST_VERSION_REPLACED}")
set(BOOST_LIB_DIR "${BOOST_INCLUDE}/libs")

#Qt5
set(QT5_VERSION "5.12.5")
set(QT5_CMAKE_PATH C:/Qt/${QT5_VERSION}/msvc2017_64/lib/cmake)

####################################################################
#macros

macro(set_as_project)
    
    #set project
    get_filename_component(ProjectId ${CMAKE_CURRENT_LIST_DIR} NAME)
    string(REPLACE " " "_" ProjectId ${ProjectId})
    set(current_project ${ProjectId})
    
    if(USE_CUDA)
        project(${current_project} CUDA CXX)
    else()
        project(${current_project} CXX)
    endif()

    #add files
    #FILE(GLOB CPP_FILES "*.cpp")
    #FILE(GLOB HEADER_FILES "*.h" "*.hpp")
    #add_executable(${current_project} "${CPP_FILES}" "${HEADER_FILES}")
    FILE(GLOB current_project_srcs "*.cpp" "*.h" "*.hpp")
    add_executable(${current_project} ${current_project_srcs})

    message("Project : ${current_project} added")
endmacro()

macro(set_as_qt_project)
    
    #set project
    get_filename_component(ProjectId ${CMAKE_CURRENT_LIST_DIR} NAME)
    string(REPLACE " " "_" ProjectId ${ProjectId})
    set(current_project ${ProjectId})
    
    if(USE_CUDA)
        project(${current_project} CUDA CXX)
    else()
        project(${current_project} CXX)
    endif()

    #find files
    FILE(GLOB project_headers "*.h" "*.hpp")
    FILE(GLOB project_srcs "*.c" "*.cpp")

    #link qt here
    set(QT5_MODUL_PATH ${QT5_CMAKE_PATH})
    set(Qt5_DIR "${QT5_MODUL_PATH}/Qt5")
    #set(QT_QMAKE_EXECUTABLE "C:/Qt/5.12.5/msvc2017_64/bin/qmake.exe")
    #set(Qt5Core_DIR "${QT5_MODUL_PATH}/Qt5Core")
    #set(Qt5Widgets_DIR "${QT5_MODUL_PATH}/Qt5Widgets")
    #set(Qt5Gui_DIR "${QT5_MODUL_PATH}/Qt5Gui")

    find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui)
    #find_package(Qt5Core REQUIRED)
    #find_package(Qt5Widgets REQUIRED)
    #find_package( REQUIRED)
    #qt5_wrap_ui(project_headers_wrapped ${project_ui})
    qt5_wrap_cpp(project_sources_moc ${project_headers})

    #add to project
    add_executable(${current_project} 
        ${project_headers}
        ${project_srcs}
        ${project_sources_moc}
        )
    target_link_libraries(${current_project}
        PUBLIC
        Qt5::Core
        Qt5::Widgets
    )

    message("Qt5 Project : ${current_project} added")
endmacro()

macro(set_as_CUDA_project)
    #set project name
    get_filename_component(ProjectId ${CMAKE_CURRENT_LIST_DIR} NAME)
    string(REPLACE " " "_" ProjectId ${ProjectId})
    set(current_project ${ProjectId})

    if(USE_CUDA)
        project(${current_project} CUDA CXX)
        
        #add files
        FILE(GLOB current_project_srcs "*.cpp" "*.h" "*.hpp" "*.cu" "*.cc")
        add_executable(${current_project} ${current_project_srcs})

        message("CUDA Project : ${current_project} added")
    else()
        message("USE_CUDA is turned off. ${current_project} is not added.")
    endif()
endmacro()

macro(set_as_lib)
    
    #set project
    get_filename_component(ProjectId ${CMAKE_CURRENT_LIST_DIR} NAME)
    string(REPLACE " " "_" ProjectId ${ProjectId})
    set(current_project ${ProjectId})
    
    FILE(GLOB current_project_srcs "*.cpp" "*.h" "*.hpp")
    
    set(LIB_TYPE "")

    if(BUILD_SHARED_LIBS)
        add_library(${current_project} SHARED ${current_project_srcs})
        set(LIB_TYPE "Shared")
    else()
        add_library(${current_project} STATIC ${current_project_srcs})
        set(LIB_TYPE "Static")
    endif()
    
    message("${LIB_TYPE} Library : ${current_project} added")
endmacro()

macro(set_as_library)
    set_as_lib()
endmacro(set_as_library)

########################################################################################################
###########LINK###########

macro(link_eigen)
    include_directories("${EIGEN_SRC}")
endmacro()

#macro(link_cuda)
#    enable_language(CUDA)
#endmacro()

macro(link_jpg)
    #message("${current_project} : link_jpg is muted now")
    #FILE(GLOB jpeg_srcs "${JPEG_SRC}/*.c")
    #add_executable(${current_project} jpeg_srcs)
    #add_library(${current_project} SHARED jpeg_srcs)
    include_directories(${current_project} ${JPEG_SRC})
    include_directories(${current_project} ${JPEG_RW_SRC})
endmacro()

macro(link_jpeg)
    link_jpg()
endmacro()

macro(link_opencl)
    
    include_directories(${current_project} ${OpenCL_INCLUDE})
    target_link_libraries(${current_project} ${OpenCL_STATIC_x64})

    #find_package(OpenCL REQUIRED)
    #if(OpenCL_FOUND)
    #message("OpenCL Found")
    #    include_directories(${current_project} ${OpenCL_INCLUDE_DIRS})
    #    target_link_libraries(${current_project} ${OpenCL_LIBRARIES})
    #endif()
    #message("OpenCL_INCLUDE_DIRS ${OpenCL_INCLUDE_DIRS}")
    #message("OpenCL_LIBRARIES ${OpenCL_LIBRARIES}")

    message("OpenCL_INCLUDE ${OpenCL_INCLUDE}")
    #message("OpenCL_STATIC_x64 ${OpenCL_STATIC_x64}")
    message("${current_project} : OpenCL Linked")
endmacro()

macro(link_cimg)
    include_directories(${current_project} ${CImg_INCLUDE})
endmacro()

macro(link_boost)
    include_directories(${current_project} ${BOOST_INCLUDE})
    target_link_libraries(${current_project} STATIC ${BOOST_LIB_DIR})
endmacro()



########################################################################################################

macro(set_as_cuda_lib)
    #set project
    get_filename_component(ProjectId ${CMAKE_CURRENT_LIST_DIR} NAME)
    string(REPLACE " " "_" ProjectId ${ProjectId})
    set(current_project ${ProjectId})
    
    if(USE_CUDA)

        FILE(GLOB current_project_srcs "*.cpp" "*.h" "*.hpp" "*.cu" "*.cc")
        
        set(LIB_TYPE "")

        if(BUILD_SHARED_LIBS)
            add_library(${current_project} CUDA CXX SHARED ${current_project_srcs})
            set(LIB_TYPE "Shared")
        else()
            add_library(${current_project} CUDA CXX STATIC ${current_project_srcs})
            set(LIB_TYPE "Static")
        endif()
        
        message("${LIB_TYPE} CUDA Library : ${current_project} added")
    else()
        message("USE_CUDA is turned off. Library ${current_project} is not added.")
    endif()

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
    set(current_project ${ProjectId})
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