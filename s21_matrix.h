#pragma once

#include <inttypes.h>
#include <math.h>
#include <omp.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum ERROR_CODES { OK, INCORRECT_MATRIX, CALCULATION_ERROR };

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

#include "include/arithmetic.h"
#include "include/base.h"
#include "include/helpers.h"
#include "include/operation.h"
