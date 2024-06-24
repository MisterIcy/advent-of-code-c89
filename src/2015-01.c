#include "../include/helper.h"

int main(int argc, char** argv) {
    size_t fileSize;
    const char* data;
    int currentFloor = 0;

    if (argc < 2) {
        printf("Usage: %s <input file>\n", argv[0]);
        return FAILURE_EXIT_CODE;
    }

    data = readDataFromFile(argv[1], &fileSize);
    
    if (data == NULL) {
        return FAILURE_EXIT_CODE;
    }

    while(*data != '\0') {
        if (*data == '(') {
            currentFloor++;
        } else if (*data == ')') {
            currentFloor--;
        }
        data++;
    }

    printf("=== Part 1 ===\n");
    printf("Santa is on floor %d\n", currentFloor);

    return SUCCESS_EXIT_CODE;
}