#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declarations of the two functions you will implement
// Feel free to declare any helper functions or global variables
void printPuzzle(char** arr);
void searchPuzzle(char** arr, char* word);
int bSize;

// Main function, DO NOT MODIFY 	
int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <puzzle file name>\n", argv[0]);
        return 2;
    }
    int i, j;
    FILE *fptr;

    // Open file for reading puzzle
    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        printf("Cannot Open Puzzle File!\n");
        return 0;
    }

    // Read the size of the puzzle block
    fscanf(fptr, "%d\n", &bSize);
    
    // Allocate space for the puzzle block and the word to be searched
    char **block = (char**)malloc(bSize * sizeof(char*));
    char *word = (char*)malloc(20 * sizeof(char));

    // Read puzzle block into 2D arrays
    for(i = 0; i < bSize; i++) {
        *(block + i) = (char*)malloc(bSize * sizeof(char));
        for (j = 0; j < bSize - 1; ++j) {
            fscanf(fptr, "%c ", *(block + i) + j);            
        }
        fscanf(fptr, "%c \n", *(block + i) + j);
    }
    fclose(fptr);

    printf("Enter the word to search: ");
    scanf("%19s", word);
    
    // Print out original puzzle grid
    printf("\nPrinting puzzle before search:\n");
    printPuzzle(block);
    
    // Call searchPuzzle to the word in the puzzle
    searchPuzzle(block, word);
    
     // Free allocated memory
    for (i = 0; i < bSize; i++)
        free(*(block + i));
    free(block);
    free(word);

    return 0;
}

void printPuzzle(char** arr) {
	// This function will print out the complete puzzle grid (arr). 
    // It must produce the output in the SAME format as the samples 
    // in the instructions.
    // Your implementation here...
    //taken from lab_04
    for (int i = 0; i < bSize; i++){
		for(int j = 0; j < bSize; j++){
			printf("%c ", *(*(arr + i) + j));
		}
		printf("\n");

	}

}

void printPath(int** path) {
    // This function will print out the complete puzzle grid (arr). 
    // It must produce the output in the SAME format as the samples 
    // in the instructions.
    // Your implementation here...
    //taken from lab_04
    for (int i = 0; i < bSize; i++){
		for(int j = 0; j < bSize; j++){
			printf("%d ", *(*(path + i) + j));
		}
		printf("\n");

	}

}

int toUpper(char c) {
    // Convert to uppercase using ascii, since lowercase is offset by 32 bytes
    // https://www.ascii-code.com/ helped with the spacing
    if (c >= 'a' && c <= 'z'){
        c -= 32;
    }
    //printf("%c \n", c);
    return c;
}

int pathFinder(char** arr, char* word, int row, int col, int index, int** path){
    if (*(word + index) == '\0'){
        return 1;
    }

    if (row < 0|| row >= bSize || col < 0|| col >= bSize){
        return 0;
    }
    
    
    char arrayChar = toUpper(*(*(arr + row) + col));
    char wordChar = toUpper(*(word + index));


    if (arrayChar == wordChar){
        // current is 0 if unexplored
        int current = *(*(path + row) + col);

        // if current is 0, current * 10 should be 0
        // so any number previously stored in the value in path[row][col] will be affected by the * 10
        // eg if (1, 2) had a value of 2 previously, moving it up to 20 and adding 4 would change it 
        *(*(path + row) + col) = current * 10 + (index + 1);
        printf("%d \n", *(*(path + row) + col));
        
        for (int sides = -1; sides <= 1; sides++){
            for (int upDown = -1; upDown <= 1; upDown++){
                if (sides == 0 && upDown == 0) {
                    continue;
                }
                if (pathFinder(arr, word, row + sides, col + upDown, index + 1, path) == 1) {
                    return 1;
                }
            }
        }
        //reset back to unexplored if no matching words are around it
        *(*(path + row) + col) = current;
    }
    return 0; 
}

void searchPuzzle(char** arr, char* word) {
    // This function checks if arr contains the search word. If the 
    // word appears in arr, it will print out a message and the path 
    // as shown in the sample runs. If not found, it will print a 
    // different message as shown in the sample runs.
    // Your implementation here...
    int found = 0;

    //taken from lab_04
    int** path = (int**)malloc(bSize * sizeof(int*));
    for (int i = 0; i < bSize; i++){
        *(path + i) = (int*)malloc(bSize * sizeof(int));
        for (int j = 0; j < bSize; j++){
            *(*(path + i) + j) = 0;
        }
    }

    for (int i = 0; i < bSize; i++){
        for (int j = 0; j < bSize; j++){
            if(pathFinder(arr, word, i, j, 0, path) == 1){
                found = 1;
            }
        }
    }

    if (found != 0) {
        printf("\nWord found!\n");
        printf("Printing the search path:\n");
        printPath(path);
    } else {
        printf("\nWord not found!\n");
    }

    

}
