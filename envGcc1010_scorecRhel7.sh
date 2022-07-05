# Set Environment for Rhel-7 systems, gcc 10
module unuse /opt/scorec/spack/lmod/linux-rhel7-x86_64/Core 
module use /opt/scorec/spack/v0154_2/lmod/linux-rhel7-x86_64/Core 
module load \
gcc/10.1.0 \
mpich \
cmake/3.20.0 \
gdb \

export CMAKE_PREFIX_PATH=$CMAKE_PREFIX_PATH:/space/cwsmith/wdmCpl/buildAdios2/install
