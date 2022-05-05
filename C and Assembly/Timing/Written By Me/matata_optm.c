// optimized versions of matrix A^T*A operation
#include "matvec.h"
#include <string.h>

int matata_VER1(matrix_t mat, matrix_t ans) {
  //removed transpose
  //instead the for loops below access the "transpose" element when they need to (tij)
  memset(ans.data, 0, mat.rows*mat.cols*sizeof(int)); //Initialize ans so all entries are 0
  int k;
  int length = mat.rows; //Length for loop unfolding
  int limit = length - 1; //limit for loop unfolding

  for (int i = 0; i < mat.rows; i++) {
    for (int j = 0; j < mat.rows; j++) {
      int tij = MGET(mat, j, i); //calling this here instead of in the k for loop greatly increases speed
      for (k = 0; k < limit; k+=2) { //loop unfolded for loop
        int mjk = MGET(mat, j, k);   //changed it so these MGET calls go through each column in the row before moving onto the next row
        int mjk2 = MGET(mat, j, k+1);
        int cur = MGET(ans, i, k);
        int cur2 = MGET(ans, i, k+1);
        int acc = tij*mjk;
        int acc2 = tij*mjk2;
        int new = cur + acc;
        int new2 = cur2 + acc2;
        MSET(ans, i, k, new);
        MSET(ans,i,k+1,new2);
      }
      for (; k < length; k++) { //for the extra cases where the loop unfolding doesnt do enough iterations
        int tij = MGET(mat, j, i);
        int mjk = MGET(mat, j, k);
        int cur = MGET(ans, i, k);
        int acc = tij*mjk;
        int new = cur + acc;
        MSET(ans, i, k, new);
      }
    }
  }

  return 0;
}

// ADDITIONAL VERSIONS HERE

int matata_OPTM(matrix_t mat, matrix_t ans) {
  if(mat.rows != mat.cols ||                    // must be a square matrix for A^T*A
     mat.rows != ans.rows ||
     mat.cols != ans.cols)
  {
    printf("matata_OPTM: dimension mismatch\n");
    return 1;
  }

  // Call to some version of optimized code
  return matata_VER1(mat, ans);
  // return matata_VER2(mat, ans);
}
