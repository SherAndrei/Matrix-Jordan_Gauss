/*
Метод Жордана решения системы линейных уравнений
*/
#include "matrix.h"
#include "error.h"
#include "print.h"
#include "fill.h"
#include "solve.h"
#include <stdlib.h>
#include <time.h>

int main(int argc, const char* argv[])
{
    if(argc < 4 || argc > 5)
        return INPUT_ERROR(argc);
    else {
        int error_code = 0;
        double* matrix;
        double *right_part, *answer;
        int dim          = atoi(argv[1]);
        if (dim < 0)
            return INPUT_ERROR(dim);

        int print_value = atoi(argv[2]);
        if (print_value > dim || print_value < 0)
            return INPUT_ERROR(print_value);

        if((matrix = alloc_matrix(dim, dim)) == NULL) {
            return FUNC_ERROR("malloc matrix");
        }
        int formula_name = atoi(argv[3]);
        if(formula_name == 0) {
            const char* filename = argv[4];
            if((error_code = fill_from_file(matrix, dim, filename)) != 1)
                return error_code;
        } else if(formula_name > 0 || formula_name < 5 ) {
            fill_with_formula(matrix, dim, formula_name);
        } else
            return INPUT_ERROR(formula_name);

        if((right_part = alloc_matrix(1, dim)) == NULL) {
            return FUNC_ERROR("malloc right part");
        }
        fill_right_part(matrix, right_part, dim);

        if((answer = alloc_matrix(1, dim)) == NULL) {
            return FUNC_ERROR("malloc right part");
        }
        fill_answer(right_part, answer,  dim);

        print_matrix(matrix, dim ,dim , print_value);
        print_matrix(right_part, 1, dim, print_value);
        time_t start, end;
        start = clock();
        if(solve(dim, matrix, answer) < 0)
            return FUNC_ERROR("Matrix is degenerate!");
        end = clock();
        
        print_all(matrix, answer, dim,
                  residual(dim, matrix, right_part, answer),
                  print_value, ((float)(end - start))/CLOCKS_PER_SEC                
                  );
        free(matrix);
        free(right_part);
        free(answer);
    }

}