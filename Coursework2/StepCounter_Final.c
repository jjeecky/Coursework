#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FitnessDataStruct.h"
#define MAX_FILENAME_LENGTH 100
#define MAX_RECORDS 1000 
// Struct moved to header file

// Define any additional variables here
// Global variables for filename and FITNESS_DATA array


// This is your helper function. Do not change it in any way.
// Inputs: character array representing a row; the delimiter character
// Ouputs: date character array; time character array; steps character array
void tokeniseRecord(const char *input, const char *delimiter,
                    char *date, char *time, char *steps) {
    // Create a copy of the input string as strtok modifies the string
    char *inputCopy = strdup(input);
    
    // Tokenize the copied string
    char *token = strtok(inputCopy, delimiter);
    if (token != NULL) {        strcpy(date, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(time, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(steps, token);
    }
    
    // Free the duplicated string
    free(inputCopy);

                    }




// Complete the main function
int main() {
    char filename[MAX_FILENAME_LENGTH];
    FILE *file;
    FITNESS_DATA records[MAX_RECORDS];  
    int totalRecords = 0;  

    char option;

    do {
        // Print menu
        printf("A: Specify the filename\nB: Display total records\nC: Find timeslot with fewest steps\nD: Find timeslot with largest steps\nE: Find mean step count\nF: Find longest continuous period\nQ: Exit\n");

        // Get user input
        printf("Enter option: ");
        scanf(" %c", &option);

        switch(option) {
            case 'A':
                printf("Input Filename: ");
                scanf("%s", filename);

                file = fopen(filename, "r");

                if (file == NULL) {
                    printf("Error: Could not open file\n");
                    return 1;
                }

                // Reset totalRecords before reading the file
                totalRecords = 0;

                while (fscanf(file, "%[^,],%[^,],%d", records[totalRecords].date, records[totalRecords].time, &records[totalRecords].steps) == 3) {
                    totalRecords++;
                }

                fclose(file);

                
                break;

            case 'B':
                if (totalRecords == 0) {
                    printf("No records available. Please import a file first.\n");
                } else {
                    printf("Total records: %d\n", totalRecords);
                }
                break;

            case 'C':
                if (totalRecords == 0) {
                    printf("No records available. Please import a file first.\n");
                } else {
                    int minSteps = records[0].steps;
                    int minIndex = 0;

                    for (int i = 1; i < totalRecords; i++) {
                        if (records[i].steps < minSteps) {
                            minSteps = records[i].steps;
                            minIndex = i;
                        }
                    }
                    printf("Fewest steps: %s %s\n", records[minIndex].date, records[minIndex].time);
                }
                break;

            case 'D':
                if (totalRecords == 0) {
                    printf("No records available. Please import a file first.\n");
                } else {
                    int maxSteps = records[0].steps;
                    int maxIndex = 0;

                    for (int i = 1; i < totalRecords; i++) {
                        if (records[i].steps > maxSteps) {
                            maxSteps = records[i].steps;
                            maxIndex = i;
                        }
                    }
                    printf("Largest steps: %s %s\n", records[maxIndex].date, records[maxIndex].time);
                }
                break;
            
            case 'E':
                 if (totalRecords == 0) {
                    printf("No records available. Please import a file first.\n");
                } else {
                    int sumSteps = 0;

                    for (int i = 0; i < totalRecords; i++) {
                        sumSteps += records[i].steps;
                    }

                    int meanSteps = sumSteps / totalRecords;

                    printf("Mean step count: %d\n", meanSteps);
                }
                break;

            case 'F':
                if (totalRecords == 0) {
                printf("No records available. Please import a file first.\n");
                } else {
                    int currentStartIndex = 0;
                    int longestStartIndex = 0;
                    int longestLength = 0;
                    int currentLength = 0;

                    for (int i = 0; i < totalRecords; i++) {
                        if (records[i].steps > 500) {
                            currentLength++;

                            if (currentLength > longestLength) {
                                longestLength = currentLength;
                                longestStartIndex = currentStartIndex;
                            }
                        } else {
                            currentStartIndex = i + 1;
                            currentLength = 0;
                        }
                    }
                    printf("Longest period start: %s %s\n", records[longestStartIndex].date, records[longestStartIndex].time);
                    printf("Longest period end: %s %s\n", records[longestStartIndex + longestLength - 1].date, records[longestStartIndex + longestLength - 1].time);
                }
                break;

            case 'Q':
                printf("Program returns 0 & exits\n");
                break;

            default:
                printf("Invalid option. Please try again.\n");
        }
    } while (option != 'Q');

    return 0;
    } 












