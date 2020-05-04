BUILD_DIR=./build

if [ ! -d "${BUILD_DIR}" ]; then
    mkdir ${BUILD_DIR}
fi

cmake . -B${BUILD_DIR} 
cd ${BUILD_DIR}
make
