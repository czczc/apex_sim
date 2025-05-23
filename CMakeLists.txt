# Setup the project
cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(apex_sim)

# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

# Setup Geant4 include directories and compile definitions
include(${Geant4_USE_FILE})

# Locate sources and headers for this project
include_directories(${PROJECT_SOURCE_DIR}/include
                    ${Geant4_INCLUDE_DIR})
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

# make new directory for output
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/out)
# copy mac directory
file(COPY ${PROJECT_SOURCE_DIR}/mac DESTINATION ${PROJECT_BINARY_DIR})


# Add the executable, and link it to the Geant4 libraries
add_executable(apex apex.cc ${sources} ${headers})
target_link_libraries(apex ${Geant4_LIBRARIES})

# Copy all scripts to the build directory
set(apex_SCRIPTS
    # apex.mac vis.mac gui.mac run.mac
    merge.sh
  )

foreach(_script ${apex_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()


# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
install(TARGETS apex DESTINATION bin)

