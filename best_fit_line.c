#include <stdio.h>
#include <stdlib.h>
void read_data(const char *filename, double *x, double *y, int *n) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
*n = 0;
    while (fscanf(file, "%lf %lf", &x[*n], &y[*n]) != EOF) {
        (*n)++;
    }
    fclose(file);
}
void least_squares(int n, double *x, double *y, double *a, double *b) {
    double sum_x = 0, sum_y = 0, sum_xy = 0, sum_x2 = 0;
    int i=0;
    for (i = 0; i < n; i++) {
        sum_x += x[i];
        sum_y += y[i];
        sum_xy += x[i] * y[i];
        sum_x2 += x[i] * x[i];
    }
    *a = (n * sum_xy - sum_x * sum_y) / (n * sum_x2 - sum_x * sum_x);
    *b = (sum_y - (*a) * sum_x) / n;
}
int main() {
    const char *filename = "values.txt";
    int n = 0;
    double x[100], y[100];
    double a, b;
    read_data(filename, x, y, &n);
    least_squares(n, x, y, &a, &b);
    printf("y = %.2fX^(%.2f)", a, b);
    return 0;
}
