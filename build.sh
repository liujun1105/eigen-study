if [ -d "build" ]; then
    rm -fr build
fi

mkdir build

cmake -S . -B build
cd build
make
cd ..
