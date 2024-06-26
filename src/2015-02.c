#include "../include/helper.h"

typedef struct {
    unsigned int width;
    unsigned int length;
    unsigned int height;
} Present;

unsigned int calculateWrappingPaper(const Present* present) {
    unsigned int side1 = present->width * present->length;
    unsigned int side2 = present->length * present->height;
    unsigned int side3 = present->height * present->width;
    unsigned int smallestSide = side1;

    if (side2 < smallestSide) {
        smallestSide = side2;
    }

    if (side3 < smallestSide) {
        smallestSide = side3;
    }

    return 2 * side1 + 
           2 * side2 + 
           2 * side3 +
           smallestSide;
}

unsigned int calculateWrappingRibbon(const Present* present) {
    unsigned int sides[3];
    int i, j;
    
    sides[0] = present->width;
    sides[1] = present->length;
    sides[2] = present->height;

    for (i = 0; i < 3; i++) {
        for (j = i + 1; j < 3; j++) {
            if (sides[i] > sides[j]) {
                unsigned int t = sides[i];
                sides[i] = sides[j];
                sides[j] = t;
            }
        }
    }

    return 2 * sides[0] +
           2 * sides[1] + 
           present->width * present->length * present->height;    
}

int main(int argc, char** argv) {
    size_t fileSize;
    const char* data;
    unsigned int totalWrappingPaper = 0;
    unsigned int totalWrappingRibbon = 0;

    if (argc < 2) {
        printf("Usage: %s <input file>\n", argv[0]);
        return FAILURE_EXIT_CODE;
    }

    data = readDataFromFile(argv[1], &fileSize);

    if (data == NULL) {
        return FAILURE_EXIT_CODE;
    }

    while(*data != '\0') {
        Present present;
        int result = sscanf(data, "%ux%ux%u\n", &present.width, &present.length, &present.height);

        if (result != 3) {
            fprintf(stderr, "Failed to parse the present dimensions\n");
            return FAILURE_EXIT_CODE;
        }

        totalWrappingPaper += calculateWrappingPaper(&present);
        totalWrappingRibbon += calculateWrappingRibbon(&present);

        do {
            data++;
        } while(*data != '\n' && *data != '\0');
    }

    printf("=== Part 1 ===\n");
    printf("The elves need %u sqft of wrapping paper!\n", totalWrappingPaper);
    printf("=== Part 2 ===\n");
    printf("The elves also need %u ft of ribbon!\n", totalWrappingRibbon);

    return SUCCESS_EXIT_CODE;
}