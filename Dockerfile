FROM ubuntu:18.04

RUN apt-get update
# Install dependencies for zsim
RUN apt-get install -y  build-essential g++ git scons
RUN apt-get install -y libelf-dev libhdf5-serial-dev libconfig++-dev


# Install dependencies for zsim hooks with Java and Fortran
RUN apt-get install -y gfortran openjdk-8-jdk

# Install VIM
RUN apt-get install -y vim

# Install gcc-5 required libs
RUN apt-get install -y g++-5 gcc-5 g++-4.8 gcc-4.8

# Install glog
RUN apt-get install -y libgoogle-glog-dev

# Install python-dev
RUN apt-get install -y python-dev libbz2-dev

# Select gcc-4 / g++-4 as compiler
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.8 10
RUN update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-4.8 10

ENV PINPATH=/app/zsim-nvmain/pin_kit
ENV BOOST=/app/boost_1_59_0
ENV BOOST_INCLUDE=/app/boost_1_59_0/boost
ENV BOOST_LIB=/app/boost_1_59_0/stage/lib
ENV LIBCONFIG=/usr
ENV NVMAINPATH=/app/zsim-nvmain/nvmain
ENV HDF5=/usr/lib/x86_64-linux-gnu/hdf5/serial

ENV LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PINPATH/intel64/lib:$PINPATH/intel64/runtime:$PINPATH/intel64/lib:$PINPATH/intel64/lib-ext:$BOOST_LIB
ENV INCLUDE=$INCLUDE:$HDF5/include:$LIBCONFIG:/include:$BOOST_INCLUDE
ENV LIBRARY_PATH=$LIBRARY_PATH:$HDF5/lib
ENV CPLUS_INCLUDE_PATH=$CPLUS_INCLUDE_PATH:$HDF5/include

COPY . /app


# Build BOOST
RUN cd /app/boost_1_59_0 && ./bootstrap.sh --libdir=/app/boost/lib --includedir=/app/boost/include && ./b2

# Build zsim
#RUN cd /app/zsim-nvmain && scons -j16


