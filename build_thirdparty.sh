mkdir thirdparty
cd thirdparty
git clone  https://github.com/ceres-solver/ceres-solver.git
# 创建安装目录
mkdir ceres
cd ceres
ceres_lib=$(pwd)
echo ${ceres_lib}

# 编译安装ceres
cd ..
cd ceres-solver
git checkout -b 2.0.0
mkdir build
cd build && rm -rf *
cmake .. -DCMAKE_INSTALL_PREFIX=${ceres_lib}
make -j6
make install

# 删除源代码
cd ../..
rm -rf ceres-solver

