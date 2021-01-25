#!/bin/sh
PINPATH=/home/martin.carrasco/HSCC/zsim-nvmain/pin_kit
NVMAINPATH=/home/martin.carrasco/HSCC/zsim-nvmain/nvmain
ZSIMPATH=/home/martin.carrasco/HSCC/zsim-nvmain/
BOOST=/home/martin.carrasco/installed_libs/boost_1_59_0/
HDF5=/home/martin.carrasco/installed_libs/hdf5/
#SIMPOINT_DIR=path of simpoint
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PINPATH/intel64/lib:$PINPATH/intel64/runtime:$PINPATH/intel64/lib:$PINPATH/intel64/lib-ext:$BOOST/lib:$HDF5/lib:
INCLUDE=$INCLUDE:$HDF5/include
LIBRARY_PATH=$LIBRARY_PATH:$HDF5/lib
CPLUS_INCLUDE_PATH=$CPLUS_INCLUDE_PATH:$HDF5/include
export ZSIMPATH PINPATH NVMAINPATH LD_LIBRARY_PATH BOOST CPLUS_INCLUDE_PATH LIBRARY_PATH SIMPOINT_DIR
