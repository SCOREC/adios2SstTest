cmake -S adios2SstTest -B buildAdios2SstTest_sysAdios2 -DCMAKE_CXX_COMPILER=g++ -DCMAKE_C_COMPILER=gcc -DCMAKE_INSTALL_PREFIX=buildAdios2SstTest_sysAdios2/install

cmake --build buildAdios2SstTest_sysAdios2 -j2
