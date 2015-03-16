# hdf-missing-frames

Small test application to reproduce an issue when appending frames to an extending dataset


## Build log (Debug build)

    make: Entering directory `/home/up45/workspaces/luna/hdf-missing-frames/Debug'
    Building file: ../missingframes.c
    Invoking: GCC C Compiler
    /dls_sw/prod/tools/RHEL6-x86_64/hdf5/1-8-11/prefix/bin/h5cc -I/dls_sw/prod/tools/RHEL6-x86_64/hdf5/1-8-11/prefix/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"missingframes.d" -MT"missingframes.d" -o "missingframes.o" "../missingframes.c"
    Finished building: ../missingframes.c
     
    Building target: hdf-missing-frames
    Invoking: GCC C Linker
    /dls_sw/prod/tools/RHEL6-x86_64/hdf5/1-8-11/prefix/bin/h5cc  -o "hdf-missing-frames"  ./missingframes.o   
    Finished building target: hdf-missing-frames
     
    make: Leaving directory `/home/up45/workspaces/luna/hdf-missing-frames/Debug'


Example output files are in the data directory.


