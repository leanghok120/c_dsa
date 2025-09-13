/*
 * bubble sort algorithm in C
 */

#include <stdio.h>

void bubble_sort(int arr[], int length) {
  for (int i = 0; i < length; i++) {
    for (int j = 0; j < length - 1; j++) {
      if (arr[j] > arr[j+1]) {
        int temp = arr[j];
        arr[j] = arr[j+1];
        arr[j+1] = temp;
      }
    }
  }
}

int main() {
  int arr[] = { 5, 6, 1, 3 };
  int length = sizeof(arr) / sizeof(arr[0]);

  bubble_sort(arr, length);

  for (int i = 0; i < length; i++) {
    printf("%d\n", arr[i]);
  }

  return 0;
}
