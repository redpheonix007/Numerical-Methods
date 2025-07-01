#include <stdio.h>
#include <math.h>

#define MAX_N 100 // Define a maximum size for simplicity

int main() {
    int i, j, k, n, m;
    FILE *fin;

    printf("Enter the number of observations: \n");
    scanf("%d", &n);
    if (n > MAX_N) {
        printf("Number of observations exceeds the maximum allowed (%d).\n", MAX_N);
        return 1;
    }

    printf("Enter the order of the polynomial: \n");
    scanf("%d", &m);

    if (m >= n) {
        printf("Polynomial order must be less than the number of observations\n");
        return 1;
    }

    float x[n], y[n], A[n][m + 1], ATA[m + 1][m + 1], ATy[m + 1], x1[m + 1], y_pred[n];
    fin = fopen("values.txt", "r");
    if (fin == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    printf("Reading values of x and y from the file...\n");
    for (i = 0; i < n; i++) {
        if (fscanf(fin, "%f %f", &x[i], &y[i]) != 2) {
            printf("Error reading data from file\n");
            fclose(fin);
            return 1;
        }
    }
    fclose(fin);

    // Normalize x values
    float max = x[0], min = x[0];
    for (i = 1; i < n; i++) {
        if (x[i] > max) max = x[i];
        if (x[i] < min) min = x[i];
    }
    float alpha = -min / (max - min);
    float beta = 1 / (max - min);
    for (i = 0; i < n; i++) {
        x[i] = alpha + beta * x[i];
    }

    // Construct matrix A and vectors ATA and ATy
    for (i = 0; i < n; i++) {
        for (j = 0; j <= m; j++) {
            A[i][j] = pow(x[i], j);
        }
    }

    for (i = 0; i <= m; i++) {
        for (j = 0; j <= m; j++) {
            ATA[i][j] = 0.0;
        }
        ATy[i] = 0.0;
        x1[i] = 0.0;
    }

    // Calculate ATA = A^T * A and ATy = A^T * y
    for (i = 0; i <= m; i++) {
        for (j = 0; j <= m; j++) {
            for (k = 0; k < n; k++) {
                ATA[i][j] += A[k][i] * A[k][j];
            }
        }
    }

    for (i = 0; i <= m; i++) {
        for (k = 0; k < n; k++) {
            ATy[i] += A[k][i] * y[k];
        }
    }

    // Solve ATA * x1 = ATy using Gaussian elimination (without partial pivoting)
    for (i = 0; i <= m; i++) {
        for (j = 0; j <= m; j++) {
            if (i != j) {
                float s = ATA[j][i] / ATA[i][i];
                for (k = 0; k <= m; k++) {
                    ATA[j][k] -= s * ATA[i][k];
                }
                ATy[j] -= s * ATy[i];
            }
        }
    }

    for (i = 0; i <= m; i++) {
        x1[i] = ATy[i] / ATA[i][i];
    }

    // Calculate predictions and R^2
    float mean_y = 0.0;
    for (i = 0; i < n; i++) {
        mean_y += y[i];
    }
    mean_y /= n;

    float SST = 0.0;
    for (i = 0; i < n; i++) {
        SST += pow(y[i] - mean_y, 2);
    }

    float SSE = 0.0;
    for (i = 0; i < n; i++) {
        y_pred[i] = 0.0;
        for (j = 0; j <= m; j++) {
            y_pred[i] += x1[j] * pow(x[i], j);
        }
        SSE += pow(y[i] - y_pred[i], 2);
    }

    float R2 = 1.0 - (SSE / SST);

    // Output results
    printf("Polynomial coefficients:\n");
    for (i = 0; i <= m; i++) {
        printf("x1[%d] = %12.5g\n", i, x1[i]);
    }
    printf("R^2 = %12.5g\n", R2);

    return 0;
}

