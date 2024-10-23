We will use `CMake`, and `clang` as the compiler on all platforms. We'll have consistent
compilations and better error messages

Experimenting with using `vcpkg` for package management so we can use libraries as we
go easier.

# How to Build
1. Install build tools

Install [CMake](https://cmake.org/download/) and
[Clang](https://releases.llvm.org/download.html) however you do on your OS. On
Mac using `brew` (Homebrew) might be easiest? And Windows however you do there,
probably through Visual Studio, might be called LLVM tools/clang.

2. Setup `vcpkg`
```bash
git submodule update --init --recursive
cd vcpkg
git pull
.\bootstrap-vcpkg.bat # on Windows
./bootstrap-vcpkg.sh # on Linux/Mac
```

3. Build
```bash
# change directory back to hookline/
cd ..
# make build directory and build
mkdir build
cd build
cmake ..
cmake --build . -j 10
```

4. More builds - just rerun the build command
```bash
# cmake .. # if you add new source files
cmake --build . -j 10
```

Alternatively if you use CMakeTools in VS Code or you use Visual Studio it will
detect the CMake project automatically and can build for you.

# Problems

The first build will take a while since `vcpkg` might compile a lot of things
from source at first. After that it's fast.

If you have problems during the build (probably missing libraries or OpenGL)
try to read the build output and see what missing library there is and download
them so you can build. Visual Studio might do this on Windows for you.
