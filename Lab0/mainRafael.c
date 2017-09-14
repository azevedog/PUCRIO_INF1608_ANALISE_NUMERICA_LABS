#include <stdio.h>

#include "matriz.h"

void vec_print(double* A, int m, char* name) {
    int i;
    printf("%s:\n", name);
    printf("[");
    for (i = 0; i < m; i++) {
        printf("%f", A[i]);
        if (i != m - 1) {
            printf(", \t");
        }
    }
    printf("]\n\n");
}

void mat_print(double** A, int m, int n, char* name) {
    int i, j;
    printf("%s:\n", name);
    for (i = 0; i < m; i++) {
        printf("[");
        for (j = 0; j < n; j++) {
            printf("%f", A[i][j]);
            if (j != n - 1) {
                printf(", \t");
            }
        }
        printf("]\n");
    }
    printf("\n");
}

int main(void) {
    double** A = mat_cria(3, 2);
    double** TA = mat_cria(2, 3);

    double** B = mat_cria(2, 3);
    double** TB = mat_cria(3, 2);

    double** C = mat_cria(2, 4);
    double** TC = mat_cria(4, 2);

    double** AB = mat_cria(3, 3);
    double** AC = mat_cria(3, 4);
    double** TCC = mat_cria(4, 4);

    double v[2] = {1, 2};
    double w[3];

    A[0][0] = 1; A[0][1] = 4;
    A[1][0] = 2; A[1][1] = 5;
    A[2][0] = 3; A[2][1] = 6;

    B[0][0] = 1; B[0][1] = 2; B[0][2] = 3;
    B[1][0] = 4; B[1][1] = 5; B[1][2] = 6;

    C[0][0] = 9; C[0][1] = 8; C[0][2] = 7; C[0][3] = 6;
    C[1][0] = 2; C[1][1] = 3; C[1][2] = 4; C[1][3] = 5;

    mat_transposta(3, 2, A, TA);
    mat_transposta(2, 3, B, TB);
    mat_transposta(2, 4, C, TC);
    mat_multv(3, 2, A, v, w);
    mat_multm(3, 2, 3, A, B, AB);
    mat_multm(3, 2, 4, A, C, AC);
    mat_multm(4, 2, 4, TC, C, TCC);

    mat_print(A, 3, 2, "A");
    mat_print(B, 2, 3, "B");
    mat_print(C, 2, 4, "C");
    vec_print(v, 2, "v");
    mat_print(TA, 2, 3, "TA");
    mat_print(TB, 3, 2, "TB");
    mat_print(TC, 4, 2, "TC");
    vec_print(w, 3, "A * v");
    mat_print(AB, 3, 3, "A * B");
    mat_print(AC, 3, 4, "A * C");
    mat_print(TCC, 4, 4, "TC * C");

    mat_libera(3, A);
    mat_libera(2, TA);
    mat_libera(2, B);
    mat_libera(3, TB);
    mat_libera(2, C);
    mat_libera(4, TC);
    mat_libera(3, AB);
    mat_libera(3, AC);
    mat_libera(4, TCC);

    return 0;
}