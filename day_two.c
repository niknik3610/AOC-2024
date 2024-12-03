#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUM_COUNT 8
#define MAX 999

int diff(int val_one, int val_two) {
    return abs(val_one - val_two);
}

// to_edit will contain [to_edit_size][to_edit_size - 1] vals
void calc_different_arrays(int to_edit[MAX_NUM_COUNT][MAX_NUM_COUNT-1], int to_edit_size, int numbers[]) {
    int arr[MAX_NUM_COUNT][MAX_NUM_COUNT-1];
    for (int i = 0; i< to_edit_size; i++) {
        int found = 0;
        for (int j = 0; j < to_edit_size; j++) {
            if (j < i) {
                arr[i][j] = numbers[j]; 
            }
            else if (j > i) {
                arr[i][j-1] = numbers[j]; 
            }
        }
    }

    memcpy(to_edit, arr, sizeof(arr));
}

int check_pass_fail(int input[MAX_NUM_COUNT], int size) {
    int pass = 1;
    int condition_number = 0;
    // printf("%d ", input[0]);
    for (int i = 1; i < size; i++) { 
        // printf("%d ", input[i]);
        int condition_one = input[i - 1] > input[i];
        int condition_two = input[i - 1] < input[i];

        if (condition_number == 0) {
            if (condition_one) {
                condition_number = 1;
            } else if (condition_two) {
                condition_number = -1;
            }
        } else {
            if (condition_number == 1) {
                condition_two = 0;
            } else {
                condition_one = 0;
            }
        }

        int num_diff = diff(input[i - 1], input[i]);
        int condition_three = num_diff < 4 && num_diff > 0 ;
        if (!((condition_one || condition_two) && condition_three)) {
            pass = 0;
            break;
        }
    }
    return pass;
}

int part_two() {
    FILE *input = fopen("./day_two_input.txt", "r");
    if (input == NULL) {
        printf("Error opening file");
        exit(-1); 
    }

    char buf[MAX];
    int safe_count = 0;
    int numbers[MAX_NUM_COUNT];


    while (fgets(buf, MAX, input)) {
        int count = sscanf(buf, "%d %d %d %d %d %d %d %d", &numbers[0], &numbers[1], &numbers[2], &numbers[3], &numbers[4], &numbers[5], &numbers[6], &numbers[7]);  
        
        int prev_bad = 0;
        int pass = 0;
        int input[MAX_NUM_COUNT][MAX_NUM_COUNT - 1] = {};
        calc_different_arrays(input, count, numbers);

        for (int i = 0; i < count; i++) {
            for (int j = 0; j < count - 1; j++) {
                printf("%d ", input[i][j]);
            }
            printf("\n");
            pass = check_pass_fail(input[i], count - 1);
            if (pass) {
                safe_count++;
                break;
            }
        }
        
    }

    free(input);
    return safe_count;
}

int part_one() {
    FILE *input = fopen("./day_two_input.txt", "r");
    if (input == NULL) {
        printf("Error opening file");
        exit(-1); 
    }

    char buf[MAX];
    int safe_count = 0;
    int numbers[MAX_NUM_COUNT];
    int line_num = 0;
    while (fgets(buf, MAX, input)) {
        int count = sscanf(buf, "%d %d %d %d %d %d %d %d", &numbers[0], &numbers[1], &numbers[2], &numbers[3], &numbers[4], &numbers[5], &numbers[6], &numbers[7]);  
        int pass = 1;
        int condition_number = 0;
        for (int i = 1; i < count; i++) { 
            int condition_one = numbers[i - 1] > numbers[i];
            int condition_two = numbers[i - 1] < numbers[i];

            if (condition_number == 0) {
                if (condition_one) {
                    condition_number = 1;
                } else if (condition_two) {
                    condition_number = -1;
                }
            } else {
                if (condition_number == 1) {
                    condition_two = 0;
                } else {
                    condition_one = 0;
                }
            }

            int num_diff = diff(numbers[i - 1], numbers[i]);
            int condition_three = num_diff < 4 && num_diff > 0 ;
            if (!((condition_one || condition_two) && condition_three)) {
                pass = 0;
                break;
            }
        }
        if (pass) {
            safe_count++;
        }
        line_num++;
    }
    free(input);
    return safe_count;
}


int main() {
    int result;
    // result = part_one();
    result = part_two();
    printf("%d\n", result);
}
