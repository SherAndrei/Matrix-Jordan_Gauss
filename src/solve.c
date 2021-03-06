#include <stdio.h>
#include <string.h>
#include <math.h>

#include "matrix.h"
#include "print.h"

// Поменять местами элемент lhs и rhs
void swap(double* lhs, double* rhs) {
    double temp = *lhs;
    *lhs = *rhs;
    *rhs = temp;
}

// Поменять местами строчку lhs и rhs в матрице
void swap_lines(double* matrix, const int dim, int lhs, int rhs) {
    for (int j = 0; j < dim; j++) {
        swap(&(Matrix(lhs, j)), &(Matrix(rhs, j)));
    }
}

// Найти корни и записать в answer
int solve(const int dim, double* matrix, double* answer) {
    double coef;
    // идем по столбикам
    for (int k = 0; k < dim; k++) {
        // Если элемент на диагонали равен  0, то
        if (Matrix(k, k) == 0) {
            int non_zero_row = -1;
            // ищем ненулевой элемент,
            for (int i = k; i < dim; i++) {
                if (Matrix(i, k) != 0) {
                    // Если нашли, то запомнили
                    non_zero_row = i;
                    // Поменяли
                    swap_lines(matrix, dim, k, non_zero_row);
                    swap(&(answer[k]), &(answer[non_zero_row]));
                    break;
                }
            }
            // Если не нашли, то вовзращаем код ошибки
            if (non_zero_row == -1) {
                return -1;
            }
        }

        // Так как элемент a_kk на диагонали != 0, то
        // разделим k уравнение на него
        coef = Matrix(k, k);
        answer[k] /= coef;
        for (int j = k; j < dim; j++) {
            Matrix(k, j) /= coef;
        }

        // теперь a_kk == 1
        // Зануляем в столбике все остальное
        for (int i = 0; i < dim; i++) {
            if (i != k) {
                coef = Matrix(i, k);
                answer[i] -=  coef * answer[k];
                // Применим вычетание ко всей строчке
                for (int j = k; j < dim; j++) {
                    Matrix(i, j) -= coef * (Matrix(k, j));
                }
            }
        }
    }
    return 0;
}
// Норма вектора
double  norm(const double* vector, const int length) {
    double result = 0.;
    for (int i = 0; i < length; ++i) {
            result += (vector[i] * vector[i]);
    }
    return sqrt(result);
}

// Норма невязки
double residual(const int dim, const double* matrix, const double* r_part, const double* answer) {
    double result[dim];
    // Заполняем весь массив нулями
    memset(result, 0. , dim*sizeof(double));
    // Вычисляем AX-b
    for (int i = 0; i < dim; i++) {
        // Складываем все a_ijx
        for (int j = 0; j < dim; j++) {
            result[i] = result[i] + (Matrix(i, j) * answer[j]);
        }
        // Вычитаем b_i
        result[i] -= r_part[i];
    }

    return norm(result, dim) / norm(r_part, dim);
}

// Норма разности с ответом
double difference(const int dim, double* answer) {
    for (int i = 0; i < dim; i+=2) {
        answer[i] -= 1;
    }
    return norm(answer, dim);
}

