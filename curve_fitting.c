#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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

void least_squares(int n, double *x, double *y, double *a, double *b, double *r) {
    double sum_x = 0, sum_y = 0, sum_xy = 0, sum_x2 = 0, sum_y2 = 0;
    int i;
    for (i = 0; i < n; i++) {
        sum_x += x[i];
        sum_y += y[i];
        sum_xy += x[i] * y[i];
        sum_x2 += x[i] * x[i];
        sum_y2 += y[i] * y[i];
    }
    *a = (n * sum_xy - sum_x * sum_y) / (n * sum_x2 - sum_x * sum_x);
    *b = (sum_y - (*a) * sum_x) / n;

    double numerator = (n * sum_xy - sum_x * sum_y);
    double denominator = sqrt((n * sum_x2 - sum_x * sum_x) * (n * sum_y2 - sum_y * sum_y));
    *r = numerator / denominator;
}


void exponential_fit(int n, double *x, double *y, double *a, double *b, double *r) {
    double sum_x = 0, sum_y = 0, sum_xlogy = 0, sum_x2 = 0, sum_logy2 = 0;
    int i;
    for (i = 0; i < n; i++) {
        if (y[i] <= 0) {
            fprintf(stderr, "Non-positive y value for exponential fit.\n");
            exit(EXIT_FAILURE);
        }
        double log_y = log(y[i]);
        sum_x += x[i];
        sum_y += log_y;
        sum_xlogy += x[i] * log_y;
        sum_x2 += x[i] * x[i];
        sum_logy2 += log_y * log_y;
    }
    *b = (n * sum_xlogy - sum_x * sum_y) / (n * sum_x2 - sum_x * sum_x);
    *a = exp((sum_y - *b * sum_x) / n);

    double numerator = (n * sum_xlogy - sum_x * sum_y);
    double denominator = sqrt((n * sum_x2 - sum_x * sum_x) * (n * sum_logy2 - sum_y * sum_y));
    *r = (numerator / denominator);
}


void power_law_fit(int n, double *x, double *y, double *a, double *b, double *r) {
    double sum_logx = 0, sum_logy = 0, sum_logxlogy = 0, sum_logx2 = 0;
    int i;
    for (i = 0; i < n; i++) {
        double log_x = log(x[i]);
        double log_y = log(y[i]);
        sum_logx += log_x;
        sum_logy += log_y;
        sum_logxlogy += log_x * log_y;
        sum_logx2 += log_x * log_x;
    }
    *b = (n * sum_logxlogy - sum_logx * sum_logy) / (n * sum_logx2 - sum_logx * sum_logx);
    *a = exp((sum_logy - *b * sum_logx) / n);

    double numerator = (n * sum_logxlogy - sum_logx * sum_logy);
    double denominator = sqrt((n * sum_logx2 - sum_logx * sum_logx) * (n * sum_logy * sum_logy - sum_logy * sum_logy));
    *r = (numerator / denominator);
}


void logarithmic_fit(int n, double *x, double *y, double *a, double *b, double *r) {
    double sum_logx = 0, sum_y = 0, sum_logx_y = 0, sum_logx2 = 0;
    int i;
    for (i = 0; i < n; i++) {
        double log_x = log(x[i]);
        sum_logx += log_x;
        sum_y += y[i];
        sum_logx_y += log_x * y[i];
        sum_logx2 += log_x * log_x;
    }
    *b = (n * sum_logx_y - sum_logx * sum_y) / (n * sum_logx2 - sum_logx * sum_logx);
    *a = (sum_y - *b * sum_logx) / n;

    double sum_y2 = 0;
    for (i = 0; i < n; i++) {
        double log_x = log(x[i]);
        sum_y2 += y[i] * y[i];
    }
    
    double numerator = (n * sum_logx_y - sum_logx * sum_y);
    double denominator = sqrt((n * sum_logx2 - sum_logx * sum_logx) * (n * sum_y2 - sum_y * sum_y));
    *r = (numerator / denominator);
}

int main() {
    const char *filename = "values.txt";
    int n = 0;
    double x[100], y[100];

    read_data(filename, x, y, &n);

    int choice;
    printf("Choose the type of fit:\n");
    printf("1. Linear Fit\n");
    printf("2. Exponential Fit\n");
    printf("3. Power-Law Fit\n");
    printf("4. Logarithmic Fit\n");
    printf("Enter your choice (1-4): ");
    scanf("%d", &choice);

    double a, b, c, r;

    switch (choice) {
        case 1:
            least_squares(n, x, y, &a, &b, &r);
            printf("Linear Fit: y = %fx + %f\n", a, b);
            printf("Correlation Coefficient: %f\n", r);
            break;
        case 2:
            exponential_fit(n, x, y, &a, &b, &r);
            printf("Exponential Fit: y = %fe^(%fx)\n", a, b);
            printf("Correlation Coefficient: %f\n", r);
            break;
        case 3:
            power_law_fit(n, x, y, &a, &b, &r);
            printf("Power Law Fit: y = %fX^(%f)\n", a, b);
            printf("Correlation Coefficient: %f\n", r);
            break;
        case 4:
            logarithmic_fit(n, x, y, &a, &b, &r);
            printf("Logarithmic Fit: y = %flog(x) + %f\n", a, b);
            printf("Correlation Coefficient: %f\n", r);
            break;
        default:
            fprintf(stderr, "Invalid choice.\n");
            exit(EXIT_FAILURE);
    }

    return 0;
}

