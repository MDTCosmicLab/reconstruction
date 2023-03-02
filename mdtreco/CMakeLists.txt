#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 3.19 FATAL_ERROR)
project(mdtreco)

#----------------------------------------------------------------------------
# Find ROOT
#
find_package(ROOT REQUIRED)
if(ROOT_FOUND)
  message("ROOT found")
else()
  message("ROOT NOT found")
endif()

#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#
include_directories(${PROJECT_SOURCE_DIR}/include 
		    ${ROOT_INCLUDE_DIRS} )

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cxx)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.h)

set(CXX_FLAGS,-O3 -DNDEBUG -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX12.3.sdk -std=c++17)
#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(mdtreco ${sources} ${headers})
target_link_libraries(mdtreco ${ROOT_Core_LIBRARY} ${ROOT_Tree_LIBRARY} ${ROOT_Math_Library})


#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS mdtreco DESTINATION ${PROJECT_SOURCE_DIR}/../run)
