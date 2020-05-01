VCPKG_DIR=~/Workspace/vcpkg
BUILD_DIR=./build

if [ ! -d "${BUILD_DIR}" ]; then
    mkdir ${BUILD_DIR}
fi

cmake . -B${BUILD_DIR} -DCMAKE_TOOLCHAIN_FILE=${VCPKG_DIR}/scripts/buildsystems/vcpkg.cmake
cd ${BUILD_DIR}
make
