# TIGL Library

find_package(Threads REQUIRED)
include(tiglmacros)

configure_file (
  "${CMAKE_CURRENT_SOURCE_DIR}/api/tigl_version.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/api/tigl_version.h"
)

source_group(Fuselage REGULAR_EXPRESSION "CCPACSFuselage")
source_group(Rotor REGULAR_EXPRESSION "CCPACSRotor")
source_group(Wing REGULAR_EXPRESSION "CCPACSWing")

file(GLOB_RECURSE TIGL_GENERATED_SRC generated/*)
source_group(generated FILES ${TIGL_GENERATED_SRC})

# add all subdirectories to include path
set(TIGL_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR})
subdirlist(SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR})
list(REMOVE_ITEM SUBDIRS generated)
foreach(subdir ${SUBDIRS})
  set(TIGL_INCLUDES ${TIGL_INCLUDES} ${CMAKE_CURRENT_SOURCE_DIR}/${subdir})
endforeach()

include_directories(${OpenCASCADE_INCLUDE_DIR}
                    ${TIXI_INCLUDE_DIRS}
                    ${CMAKE_CURRENT_BINARY_DIR}
                    ${CMAKE_CURRENT_BINARY_DIR}/api
                    ${TIGL_INCLUDES}
)

# boost
include_directories(${PROJECT_SOURCE_DIR}/thirdparty/boost_1_63_0)
file(GLOB_RECURSE BOOST_SRC ${PROJECT_SOURCE_DIR}/thirdparty/boost_1_63_0/libs/*)

file(GLOB_RECURSE TIGL_SRC
    "*.h"
    "*.hxx"
    "*.cpp"
    "*.cxx"
)
set(TIGL_SRC ${TIGL_SRC} ${BOOST_SRC})

if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS=1 /wd4355 -DTIGL_INTERNAL_EXPORTS)
endif(MSVC)

if(CMAKE_COMPILER_IS_GNUCC)
    # gcc 4.3.4 creates wrong code for boost::hash if compiled with optimizations
    SET_SOURCE_FILES_PROPERTIES(CTiglIntersectionCalculation.cpp PROPERTIES COMPILE_FLAGS -O0)
endif(CMAKE_COMPILER_IS_GNUCC)

# tigl dll/so library
add_library(tigl3 SHARED ${TIGL_SRC})

if(GLOG_FOUND)
  include_directories(${GLOG_INCLUDE_DIR})
  target_link_libraries (TIGL ${GLOG_LIBRARIES})
endif(GLOG_FOUND)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_definitions(-DDEBUG)
endif()

set(TIGL_LIBRARIES ${OpenCASCADE_LIBRARIES} ${TIXI_LIBRARIES} ${VLD_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  set(TIGL_LIBRARIES  ${TIGL_LIBRARIES} rt)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
if (WIN32)
  set(TIGL_LIBRARIES  ${TIGL_LIBRARIES} Shlwapi)
endif(WIN32)

target_link_libraries (tigl3 ${TIGL_LIBRARIES})
set_target_properties( tigl3 PROPERTIES VERSION ${TIGL_VERSION_MINOR}.${TIGL_VERSION_PATCH})
set_target_properties( tigl3 PROPERTIES SOVERSION "${TIGL_VERSION_MINOR}")

install (TARGETS tigl3
		 EXPORT tigl-targets
		 RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
		 LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
		 ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
		 )
		 
install (EXPORT tigl-targets DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/tigl3)
		 
install (FILES api/tigl.h ${CMAKE_CURRENT_BINARY_DIR}/api/tigl_version.h
		 DESTINATION include/tigl3
		 COMPONENT headers)

# static lib for tiglviewer 
add_library(tigl3_static ${TIGL_SRC})
# this does no actual linking but keeps track of the dependencies
target_link_libraries (tigl3_static ${TIGL_LIBRARIES})

AddToCheckstyle()
