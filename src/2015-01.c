#include "../include/helper.h"

int main(int argc, char** argv) {
    size_t fileSize;
    const char* data;
    char *currentChar;
    int currentFloor = 0;
    unsigned int firstBasementPosition = 0;

    if (argc < 2) {
        printf("Usage: %s <input file>\n", argv[0]);
        return FAILURE_EXIT_CODE;
    }

    data = readDataFromFile(argv[1], &fileSize);
    
    if (data == NULL) {
        return FAILURE_EXIT_CODE;
    }

    currentChar = (char *)data;

    while(*currentChar != '\0') {
        if (*currentChar == '(') {
            currentFloor++;
        } else if (*currentChar == ')') {
            currentFloor--;
        }

        if (currentFloor == -1 && firstBasementPosition == 0) {
            firstBasementPosition = (currentChar - data) + 1;
        }

        currentChar++;
    }

    printf("=== Part 1 ===\n");
    printf("Santa is on floor %d\n", currentFloor);
    printf("=== Part 2 ===\n");
    printf("Santa entered the basement at position %d\n", firstBasementPosition);

    return SUCCESS_EXIT_CODE;
}