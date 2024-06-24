#ifndef __HELPER_H__
#define __HELPER_H__

#include <stdio.h>
#include <stdlib.h>

#define SUCCESS_EXIT_CODE 0
#define FAILURE_EXIT_CODE 1

/**
 * Reads the data from a file and returns it as a string.
 * 
 * \param[in] fileName The name of the file to read from.
 * \param[out] fileSize The size of the file that was read.
 * \return The data read from the file.
 */
const char * readDataFromFile(const char *fileName, size_t *fileSize) {
    FILE *fp;
    char *data;
    size_t i = 0;

    fp = fopen(fileName, "r");

    if (fp == NULL) {
        fprintf(stderr, "Failed to open the file %s for reading\n", fileName);
        return NULL;
    }

    /* Find the size of the file: */
    fseek(fp, 0, SEEK_END);
    *fileSize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    /* Create a buffer to store the file data: */
    data = (char *)malloc(*fileSize);
    if (data == NULL) {
        fprintf(stderr, "Failed to allocate %lu bytes of memory\n", *fileSize);
        fclose(fp);
        return NULL;
    }

    /* Clean the buffer: */
    for (i = 0; i < *fileSize; i++) {
        *(data+i) = 0;
    }

    /* Read the data from the file: */
    fread((void *)data, *fileSize, 1, fp);
    
    /* Close the file and return the data: */
    fclose(fp);
    return (const char*) data;
}

#endif