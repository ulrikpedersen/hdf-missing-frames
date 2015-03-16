/*
 * missingframes.c
 *
 *  Created on: 16 Mar 2015
 *      Author: Ulrik Kofoed Pedersen
 */


/**********************************************************************
 *
 * Configure the TESTs by commenting/un-commenting the relevant
 * setup in the #defines below here...
 *
 * Note that we write very small 'frames' of 4x6 32bit integers in this example.
 * Increasing the size of the frames - or changing the datatype does not
 * influence the issue.
 *
 * After some experimentation, two things seems to make a difference:
 *
 *  1) decrease the number of chunks in the dataset.
 *  2) decrease the istorek parameter.
 *
 */

/* TEST1: Reproducing the problem */
/*
#define FILENAME    "/scratch/repro_test1.h5"
#define NUM_FRAMES 65540
#define FRAME_DIMS {1, 4, 6}
#define CHUNK_DIMS {1, 4, 6}
#define ISTOREK 32770
#define CACHE_SIZE 192
#define CACHE_SLOTS 3
*/


/* TEST2: decrease the number of chunks by increasing the chunk sizes and
 * problem goes away */
/*
#define FILENAME    "/scratch/repro_test2.h5"
#define NUM_FRAMES 65540
#define FRAME_DIMS {1, 4, 6}
#define CHUNK_DIMS {2, 4, 6}
#define ISTOREK 32770
#define CACHE_SIZE 192
#define CACHE_SLOTS 3
*/


/* TEST3:  */
#define FILENAME    "/scratch/repro_test3.h5"
#define NUM_FRAMES 65540
#define FRAME_DIMS {1, 4, 6}
#define CHUNK_DIMS {1, 4, 6}
#define ISTOREK 123
#define CACHE_SIZE 192
#define CACHE_SLOTS 3


/* End of configuration
 *
 **********************************************************************/

#include <assert.h>
#include "hdf5.h"

#define DATASETNAME "ExtendibleArray"
#define RANK         3


int main (int argc, char* argv[])
{
    hid_t        file=-1;                          /* handles */
    hid_t        dataspace=-1, dataset=-1;
    hid_t        filespace=-1, memspace=-1;
    hid_t        prop=-1; // property list
    hid_t        access_plist=-1, create_plist=-1;
    hid_t        dset_access_plist = -1;


    herr_t       status;
    hsize_t      dims[3]  = FRAME_DIMS;           /* dataset dimensions at creation time */
    hsize_t      maxdims[3] = FRAME_DIMS;
                 maxdims[0] = H5S_UNLIMITED;
    hsize_t      chunk_dims[3] = CHUNK_DIMS;
    int          fillvalue = 0;
    hsize_t      data_dims[3] = FRAME_DIMS;
    int          data[4][6] = { {11, 12, 13, 14, 15, 16},    /* data to write */
                                {21, 22, 23, 24, 25, 26},
                                {31, 32, 33, 34, 35, 36},
                                {41, 42, 43, 44, 45, 46} };

    /* Variables used in extending and writing to the extended portion of dataset */
    //hsize_t      size[3];
    hsize_t      offset[3] = {0, 0, 0};

    hsize_t      i=0;

    access_plist = H5Pcreate(H5P_FILE_ACCESS);
    H5Pset_fclose_degree(access_plist, H5F_CLOSE_STRONG);

    create_plist = H5Pcreate(H5P_FILE_CREATE);
    status = H5Pset_istore_k(create_plist, ISTOREK);

    /* Create a new file. If file exists its contents will be overwritten. */
    file = H5Fcreate (FILENAME, H5F_ACC_TRUNC, create_plist, access_plist);

    /* Modify dataset creation properties, i.e. enable chunking  */
    prop = H5Pcreate (H5P_DATASET_CREATE);
    status = H5Pset_chunk (prop, RANK, chunk_dims);
    status = H5Pset_fill_value(prop, H5T_NATIVE_INT, (void*)&fillvalue );

    /* Create the data space with unlimited dimensions. */
    dataspace = H5Screate_simple (RANK, dims, maxdims);

    dset_access_plist = H5Pcreate(H5P_DATASET_ACCESS);
    status = H5Pset_chunk_cache( dset_access_plist, CACHE_SLOTS, CACHE_SIZE, 1.0);

    /* Create a new dataset within the file using chunk
       creation properties.  */
    dataset = H5Dcreate2 (file, DATASETNAME, H5T_NATIVE_INT, dataspace,
                         H5P_DEFAULT, prop, dset_access_plist);

    /* Define memory space */
    memspace = H5Screate_simple (RANK, data_dims, maxdims);

    dims[0] = 0;
    for (i=0; i < NUM_FRAMES; i++) {
        /* Extend the dataset.  */
        dims[0]++;
        status = H5Dset_extent (dataset, dims);

        /* Select a hyperslab in extended portion of dataset  */
        filespace = H5Dget_space (dataset);

        status = H5Sselect_hyperslab (filespace, H5S_SELECT_SET, offset, NULL,
                                      data_dims, NULL);
        offset[0]++;

        /* Write the data to the extended portion of dataset  */
        status = H5Dwrite (dataset, H5T_NATIVE_INT, memspace, filespace,
                           H5P_DEFAULT, data);

        status = H5Sclose (filespace);
    }


    /* Close resources */
    status = H5Dclose (dataset);
    status = H5Pclose (prop);
    status = H5Sclose (dataspace);
    status = H5Sclose (memspace);
    status = H5Fclose (file);
    return 0;
}
