if [ -d "build" ]; then
    rm -fr build
    mkdir build
fi

cmake -S . -B build
cd build
make
cd ..
