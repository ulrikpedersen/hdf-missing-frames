# hdf-missing-frames

Small test application to reproduce an issue when appending frames to an extending dataset

The use-case is as follows:

A 3D dataset is created and written as a linear series of 2D image frames. When
the number of frames to write is > 65535 then the last 65535 frames are missing
from the file. By missing means that the read-back value is 0 (may be fill value
or just 0).

Changing the data type and image dimensions do not appear to make any difference.

Two things to appear to have a positive effect (i.e. problem goes away when):

* Decreasing the number of chunks in the dataset (TEST2)
* Decreasing the istorek parameter by 1 or more (TEST3)

This test application contain 3 TEST configurations, each of which must be 
uncommented and the application rebuilt and re-run. See comments in the source
file missingframes.c

After writing the dataset in the above described fashion, the file is opened for
reading and the data is read back and compared with the original data (or a subset
thereof). A small report about missing frames is printed at the end.

Example output files can be found in the data directory.


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



