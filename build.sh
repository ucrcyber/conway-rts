# if [ -d /vcpkg ]
#   echo run ./vcpkg-setup.sh first
#   exit 1
# fi

cmake -B ./build -S .
cmake --build ./build
