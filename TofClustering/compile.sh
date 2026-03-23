cmake -S . -B build -DCMAKE_INSTALL_PREFIX="${PREFIX}"
cmake --build build -j16
cmake --install build