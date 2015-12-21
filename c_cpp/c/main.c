#include <stdio.h>  //for printf()
#include <stdlib.h> //for rand()

/**
 * Task #1. Sort an array.
 */
#define ARRAY_LENGHT 100
void sort_array(int * array, int lenght);
void print_array(int * array, int lenght);

/**
 * Task #2. Binary search in sorted array.
 */
#define NOT_FOUND -1
int binary_search_i(int * array, int lenght, int value);

/**
 * Task #3. Transpose matrix
 */
#define M_WIDTH 4
#define M_HEIGHT 5
void print_matrix(int * matrix, int width, int height);
void transpose_matrix(int * matrix, int width, int height);

int main() {
  printf("Task 1. Sort an array:\n");

  //define array variables
  int random_order [ARRAY_LENGHT];
  int sorted [ARRAY_LENGHT];
  int inversed [ARRAY_LENGHT];

  //initialize array variables
  for (int i = 0; i < ARRAY_LENGHT; ++i) {
    random_order[i] = rand() % 100;
    sorted[i] = i;
    inversed[i] = ARRAY_LENGHT - i;
  }

  printf("Before sorting.\n"); 
  printf("Random array:\n");
  print_array(random_order, ARRAY_LENGHT);

  printf("Sorted array:\n");
  print_array(sorted, ARRAY_LENGHT);

  printf("Inversed array:\n");
  print_array(inversed, ARRAY_LENGHT);

  //sorting
  sort_array(random_order, ARRAY_LENGHT);
  sort_array(sorted, ARRAY_LENGHT);
  sort_array(inversed, ARRAY_LENGHT);

  printf("After sorting.\n"); 
  printf("Random array:\n");
  print_array(random_order, ARRAY_LENGHT);

  printf("Sorted array:\n");
  print_array(sorted, ARRAY_LENGHT);

  printf("Inversed array:\n");
  print_array(inversed, ARRAY_LENGHT);

  printf("\n\n");
  printf("Task 2. Binary search:\n");
  int niddle = rand() % 100;
  int position = binary_search_i(random_order, ARRAY_LENGHT, niddle);
  if (position == NOT_FOUND) {
    printf("There is no %d in random array.\n", niddle);
  } else {
    printf("Position of %d in random array is %d.\n", niddle, position);
  }

  printf("\n\n");
  printf("Task 3. Transpose matrix:\n");
  int matrix [M_WIDTH * M_HEIGHT];

  for (int i = 0; i < M_HEIGHT; ++i) {
    for (int j = 0; j < M_WIDTH; ++j) {
      matrix[i * M_WIDTH + j] = rand() % 100;
    }
  }

  print_matrix(matrix, M_WIDTH, M_HEIGHT);
  transpose_matrix(matrix, M_WIDTH, M_HEIGHT);
  print_matrix(matrix, M_HEIGHT, M_WIDTH);

  return 0;
}

//UTILITY
void print_array(int * array, int lenght) {
  for (int i = 0; i < lenght; ++i) {
    printf("%4d", array[i]);
  }

  printf("\n");
}

void print_matrix(int *matrix, int width, int height) {
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      printf("%4d", matrix[i * width + j]);
    }
    printf("\n");
  }

  printf("\n");
}
//END UTILITY

//Task 1 implementation
void quik_sort(int * array, int begin_pos, int end_pos);

void sort_array(int * array, int lenght) {
  if (lenght <= 0 || !array) {
    return;
  }

  quik_sort(array, 0, lenght);
}

void quik_sort(int * array, int begin_pos, int end_pos) {
  //printf("Begin pos: %d; End pos: %d\n", begin_pos, end_pos);
  if (begin_pos == end_pos || begin_pos < 0 || end_pos < 0) {
    return;
  }

  int base_index = begin_pos; //index of arbitrary element
  //swap first and last elements of subarray to use last as arbitrary
  int temp = array[end_pos - 1];
  array[end_pos - 1] = array[begin_pos];
  array[begin_pos] = temp;
  //printf("Arbitrary: %d\n", array[begin_pos]);

  for (int i = begin_pos + 1; i < end_pos; ++i) {
    //printf("%d ", array[i]);
    if (array[base_index] > array[i]) {

      if (base_index + 1 < i) {
        int temp = array[base_index + 1];
        array[base_index + 1] = array[i];
        array[i] = temp;
      }

      int temp = array[base_index];
      array[base_index] = array[base_index + 1];
      array[base_index + 1] = temp;
      ++base_index;
    }
    //printf("\n");
  }

  if (base_index != begin_pos) {
    //printf("before new iteration. Base index: %d. begin_pos: %d\n", base_index, begin_pos);
    quik_sort(array, begin_pos, base_index);
  }

  if (base_index != end_pos - 1) {
    //printf("before new iteration. Base index: %d. end_pos - 1: %d\n", base_index, end_pos - 1);
    quik_sort(array, base_index + 1, end_pos);
  }
}
//End task 1

//Task 2 implementation
int binary_search_i(int * array, int lenght, int value) {
  int begin = 0;
  int end = lenght;

  while (1) {
    if (value < array[begin] || value > array[end - 1]) {
      return NOT_FOUND;
    }

    int frame_size = end - begin;
    int middle = begin + frame_size / 2;
    if (value < array[middle]) {
      end = middle;
    } else if (value > array[middle]) {
      begin = middle;
    } else if (value == array[middle]){
      return middle;
    } else {
      //infinite loop protection
      return NOT_FOUND;
    }
  }
}
//End task 2

//Task 3 implementation
void transpose_matrix(int * matrix, int width, int height) {
  if (width <= 0 || height <= 0) {
    return;
  }

  int visited [width * height];
  for (int i = 0; i < width * height; ++i) {
    visited[i] = 0;
  }

  int current_index = 0;
  int last_index = width * height - 1;
  while (++current_index <= last_index) {
    if (visited[current_index]) {
      continue;
    }

    int a = current_index;
    do {
      if (a != last_index) {
        a = ( height * a) % last_index;
      }

      int temp = matrix[a];
      matrix[a] = matrix[current_index];
      matrix[current_index] = temp;

     visited[a] = 1;
    } while (a != current_index);
  }
}
//End task 2
