#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_INPUT_LEN 32
#define BUF_SIZE 65536

typedef struct Tuple_t {
    int first;
    int second;
} Tuple;

Tuple* get_numbers_from_line(char *line) {
    int number_one;
    int number_two;
    {
        char *to_parse = malloc(MAX_INPUT_LEN * sizeof(char));
        char *to_parse_ptr = to_parse;
        while (*line != ' ' && *line != '\0') {
            *to_parse_ptr = *line;
            to_parse_ptr++;
            line++;
        }
        *to_parse_ptr = '\0';
        number_one = strtoll(to_parse, NULL, 0);
        free(to_parse);
    }
    
    while (*line == ' ' && *line != '\0') {
        line++;
    }

    {
        char *to_parse = malloc(MAX_INPUT_LEN * sizeof(char));
        char *to_parse_ptr = to_parse;
        while (*line != ' ' && *line != '\0') {
            *to_parse_ptr = *line;
            to_parse_ptr++;
            line++;
        }
        *to_parse_ptr = '\0';
        number_two = strtoll(to_parse, NULL, 0);
        free(to_parse);
    }
    Tuple *tuple = malloc(sizeof(Tuple));
    tuple->first = number_one;
    tuple->second = number_two;
    return tuple;
}

void sort_arr(int arr[], size_t arr_size) {
    if (arr_size == 0) {
        return;
    }

    int current_smallest_val = INT_MAX;
    int *current_smallest_ptr = arr;

    int new_arr[arr_size]; 
    for (size_t i = 0; i < arr_size; i++) {
        for (size_t j = 0; j < arr_size; j++) {
            if (arr[j] != -1 && arr[j] <= current_smallest_val) {
                current_smallest_val = arr[j];
                current_smallest_ptr = &arr[j];
            }
        }
        new_arr[i] = current_smallest_val;
        *current_smallest_ptr = -1;
        current_smallest_val = INT_MAX;
    }

    memcpy(arr, new_arr, sizeof(new_arr));
}

int count_lines(FILE* file) {
    char buf[BUF_SIZE];
    int counter = 0;
    for(;;)
    {
        size_t res = fread(buf, 1, BUF_SIZE, file);
        if (ferror(file))
            return -1;

        int i;
        for(i = 0; i < res; i++)
            if (buf[i] == '\n')
                counter++;

        if (feof(file))
            break;
    }

    return counter;
}

int part_one() {
    FILE *input = fopen("./day_one_input.txt", "r");
    if (input == NULL) {
        printf("Error opening file");
        exit(-1); 
    }

    char *line = NULL;
    size_t line_len = 0;
    ssize_t read = 0;
    size_t current_pair_nmbr = 0;

    size_t file_size = count_lines(input);
    fseek(input, 0, SEEK_SET);
    int numbers_one[file_size];
    int numbers_two[file_size];

    while ((read = getline(&line, &line_len, input)) != -1) {
        Tuple *tuple = get_numbers_from_line(line);
        numbers_one[current_pair_nmbr] = tuple->first;
        numbers_two[current_pair_nmbr] = tuple->second;
        current_pair_nmbr++;
    }

    int sum = 0;
    sort_arr(numbers_one, file_size);
    sort_arr(numbers_two, file_size);
    
    for (int i = 0; i < current_pair_nmbr; i++) {
        if (numbers_one[i] >= numbers_two[i]) {
            sum += numbers_one[i] - numbers_two[i];
        } else {
            sum += numbers_two[i] - numbers_one[i];
        }
    }

    // printf("sum: %d\n", sum);
    fclose(input);
    return sum;
}

int part_two() {
    FILE *input = fopen("./day_one_input.txt", "r");
    if (input == NULL) {
        printf("Error opening file");
        exit(-1); 
    }

    char *line = NULL;
    size_t line_len = 0;
    ssize_t read = 0;
    size_t current_pair_nmbr = 0;

    size_t file_size = count_lines(input);
    fseek(input, 0, SEEK_SET);
    int numbers_one[file_size];
    int numbers_two[file_size];

    while ((read = getline(&line, &line_len, input)) != -1) {
        Tuple *tuple = get_numbers_from_line(line);
        numbers_one[current_pair_nmbr] = tuple->first;
        numbers_two[current_pair_nmbr] = tuple->second;
        current_pair_nmbr++;
    }

    int sum = 0;
    sort_arr(numbers_one, file_size);
    sort_arr(numbers_two, file_size);
   
    int sym_score = 0;
    for (int i = 0; i < current_pair_nmbr; i++) {
        int current_nbr_counter = 0;
        for (int j = 0; j < current_pair_nmbr; j++) {
            if (numbers_two[j] < numbers_one[i]) {
                continue;
            } else if (numbers_two[j] == numbers_one[i]) {
                current_nbr_counter++;
            }
            else {
                break;
            }
        }
        sym_score += numbers_one[i] * current_nbr_counter;
    }


    fclose(input);
    return sym_score;
}

int main() {
    // int result = part_one();
    int result = part_two();
    printf("%d\n", result);
}
