// Complete this main to benchmark the search algorithms outlined in
// the project specification
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "search.h"

int main(int argc, char *argv[]){
  if (argc < 4) { //wrong input
    printf("usage: ./search_benchmark <minpow> <maxpow> <repeats> [alg1 alg2 ...]\n");
    printf(" with alg1 alg2 as a combination of:\n");
    printf("  la : Linear Array Search\n");
    printf("  ll : Linked List Search\n");
    printf("  ba : Binary Array Search\n");
    printf("  bt : Binary Tree Search\n");
    printf("  (default all)\n");
    exit(1);
  }

  int run_linear_array = 1;
  int run_linked_list = 1;
  int run_binary_array = 1;
  int run_binary_tree = 1;

  if (argc > 4) { //checks what "settings" the user wanted for the table
    run_linear_array = 0;
    run_linked_list = 0;
    run_binary_array = 0;
    run_binary_tree = 0;
    for (int i = 4; i < argc; i++) {
      if (strcmp(argv[i], "la") == 0) {
        run_linear_array = 1;
      }
      if (strcmp(argv[i], "ll") == 0) {
        run_linked_list = 1;
      }
      if (strcmp(argv[i], "ba") == 0) {
        run_binary_array = 1;
      }
      if (strcmp(argv[i], "bt") == 0) {
        run_binary_tree = 1;
      }
    }
  }

  int minpow = atoi(argv[1]);
  int maxpow = atoi(argv[2]);
  int repeats = atoi(argv[3]);
  int min = 1;
  clock_t begin, end;
  double cpu_time;
  for (int i = 0; i < minpow; i++) {
    min *= 2;
  }

  char *top[] = {"LENGTH","SEARCHES","array","list","binary","tree"}; //for printing into a table format
  printf("%6s %8s", top[0],top[1]);
  //check which titles to put at the top of the table
  if (run_linear_array) {
    printf(" %10s", top[2]);
  }
  if (run_linked_list) {
    printf(" %10s", top[3]);
  }
  if (run_binary_array) {
    printf(" %10s", top[4]);
  }
  if (run_binary_tree) {
    printf(" %10s", top[5]);
  }
  printf("\n");
  //the loop that runs the function, times the functions, and puts them into a table
  for (int i = 0; i <= maxpow - minpow; i++) {
    printf("%6d %8d", min, min*2);
    if (run_linear_array) { //timing for the array
      int *linear_array = make_evens_array(min);
      begin = clock();

      for (int j = 0; j < repeats; j++) {
        for (int k = 0; k < (2*min)-1; k++) {
          linear_array_search(linear_array, min, k);
        }
      }

      end = clock();
      cpu_time = ((double) (end - begin)) / CLOCKS_PER_SEC;
      printf(" %10.4e", cpu_time);
      free(linear_array);
    }
    if (run_linked_list) { //timing for the linked list
      list_t *list = make_evens_list(min);
      begin = clock();
      for (int j = 0; j < repeats; j++) {
        for (int k = 0; k < (2*min)-1; k++) {
          linkedlist_search(list, min, k);
        }
      }
      end = clock();
      cpu_time = ((double) (end - begin)) / CLOCKS_PER_SEC;
      printf(" %10.4e", cpu_time);
      list_free(list);
    }
    if (run_binary_array) { //timing for the binary search on the array
      int *linear_array = make_evens_array(min);
      begin = clock();

      for (int j = 0; j < repeats; j++) {
        for (int k = 0; k < (2*min)-1; k++) {
          binary_array_search(linear_array, min, k);
        }
      }

      end = clock();
      cpu_time = ((double) (end - begin)) / CLOCKS_PER_SEC;
      printf(" %10.4e", cpu_time);
      free(linear_array);
    }
    if (run_binary_tree) { //timing for the binary search tree
      bst_t *tree = make_evens_tree(min);
      begin = clock();

      for (int j = 0; j < repeats; j++) {
        for (int k = 0; k < (2*min)-1; k++) {
          binary_tree_search(tree, min, k);
        }
      }

      end = clock();
      cpu_time = ((double) (end - begin)) / CLOCKS_PER_SEC;
      printf(" %10.4e", cpu_time);
      bst_free(tree);
    }
    printf("\n");
    min *= 2;
  }

  return 0;
}
