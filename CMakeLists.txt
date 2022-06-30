cmake_minimum_required(VERSION 3.15.0...3.21.0)
project(adios2SstTest VERSION 1.0.0 LANGUAGES C CXX) #C is required to find MPI_C
find_package(MPI REQUIRED)
#adios2 adds C and Fortran depending on how it was built
find_package(ADIOS2 CONFIG 2.7.1 REQUIRED)
add_executable(setupComms setupComms.cpp)
target_compile_features(setupComms PUBLIC cxx_std_17)
target_link_libraries(setupComms PUBLIC adios2::cxx11_mpi MPI::MPI_C)
