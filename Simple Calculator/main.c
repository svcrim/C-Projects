
#include <stdio.h>
#include <stdlib.h>

int process_operations(int *numbers, char *operators, int arraySize);

int main() {

    int *numbers;
    char *operators;
    int size = 2;
    int arraySize = 0;

    numbers = (int *)malloc(size * sizeof(int)); 
    operators = (char *)malloc(size * sizeof(char));
    if (numbers == NULL || operators == NULL) {
        printf("Failed to allocate memory\n");
        return 0;
    }

    while (1) {
        int num;
        char op;
        
        printf("Enter a number:    ");
        scanf("%d", &num);

        if (arraySize >= size) { // Expand memory if needed
            size *= 2;
            numbers = (int *)realloc(numbers, size * sizeof(int));
            operators = (char *)realloc(operators, size * sizeof(char));
            if (numbers == NULL || operators == NULL) {
                printf("Failed to allocate memory\n");
                return 0;
            }
        }

        numbers[arraySize] = num;

        printf("Enter an Operator: ");
        scanf(" %c", &op);

        if (op == '=') { // Stop taking input and start calculating
            break;
        }

        operators[arraySize] = op;
        arraySize++;
    }

    printf("\033[H\033[J"); // Clear the screen
    printf("Result is: %d\n", process_operations(numbers, operators, arraySize)); // Pass the arrays and their size

    free(numbers);
    free(operators);

    getchar(); 
    getchar(); // Wait for user to press Enter

    return 0;
}

int process_operations(int *numbers, char *operators, int arraySize) {
    // Multiplication and Division first
    for (int i = 0; i < arraySize; i++) {
        if (operators[i] == '*' || operators[i] == '/') {
            if (operators[i] == '*') {
                numbers[i] = numbers[i] * numbers[i + 1];
            } else {
                numbers[i] = numbers[i] / numbers[i + 1];
            }

            // Shift numbers and operators to the left
            for (int j = i + 1; j < arraySize - 1; j++) {
                numbers[j] = numbers[j + 1];
                operators[j - 1] = operators[j];
            }
            arraySize--; // Reduce array size since we merged two numbers
            i--; // Stay at the same index to check again
        }
    }

    // Addition and Subtraction
    int result = numbers[0];
    for (int i = 0; i < arraySize; i++) {
        if (operators[i] == '+') {
            result += numbers[i + 1];
        } else if (operators[i] == '-') {
            result -= numbers[i + 1];
        }
    }

    return result;
}
