cmake -S adios2SstTest -B buildAdios2SstTest -DCMAKE_CXX_COMPILER=g++ -DCMAKE_C_COMPILER=gcc -DCMAKE_INSTALL_PREFIX=buildAdios2SstTest/install

cmake --build buildAdios2SstTest -j2
