# Building
1. Install CMake
2. Install clang (may be part of installing LLVM toolchain on Windows)
3. Run
```bash
mkdir build
cd build
cmake ..
cmake --build .
```
## Having libraries
I will update the CMake file to use the libaries provided in `nest-libs`, right
now it just finds the package on your system so you need it installed somewhere
there.