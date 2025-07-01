#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main() {
    FILE *file = fopen("values.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    int m, n = 20; 
    printf("Input the order of the polynomial: ");
    scanf("%d", &m);
    float x[n], a[n][m + 1], c[m + 1], y[n], ata[m + 1][m + 1], aty[m + 1];
    int i=0,j=0,k=0;
    for (i = 0; i <= m; i++) {
        for (j = 0; j <= m; j++) {
            ata[i][j] = 0;
        }
        aty[i] = 0;
    }
    i=0;
    while (fscanf(file, "%f %f", &x[i], &y[i]) == 2 && i < n) {
        i++;
    }
    fclose(file);
    for (i = 0; i < n; i++) {
        for (j = 0; j <= m; j++) {
            a[i][j] = pow(x[i], j);
        }
    }
    for (i = 0; i <= m; i++) {
        for (j = 0; j <= m; j++) {
            for (k = 0; k < n; k++) {
                ata[i][j] += a[k][i] * a[k][j];
            }
        }
    }
    for (i = 0; i <= m; i++) {
        for (k = 0; k < n; k++) {
            aty[i] += a[k][i] * y[k];
        }
    }   
    
    
    
    printf("%-12s", "ATA=");
    for (i = 0; i <= m; i++) {
        printf("%-12s", " ");
    }
    printf("%-20s\n", "ATy=");
    for (i = 0; i <= m; i++) {
        for (j = 0; j <= m; j++) {
            printf("%12.5g", ata[i][j]);
        }
        printf("%20.5g\n", aty[i]);
    }
    		printf("\n");

     printf("%-12s\n", "A=");
     for (i = 0; i <= m; i++) {
        for (j = 0; j <= m; j++) {
            printf("%12.5g", a[i][j]);
        }
		printf("\n");
	}
    float s=0.0,xx=0.0;
    for(i=0;i<n;i++)
    {
    	for(j=0;j<n;j++)
    	{
    		if(i!=j)
    		{
    			s=(ata[j][i]/ata[i][i]);
    			ata[j][i]=0;
    			for(k=i+1;k<n;k++)
    			{
    				ata[j][k]=ata[j][k]-(s*ata[i][k]);
				}
				aty[j]=aty[j]-(s*aty[i]);
			}
		}
	}
	for(i=0;i<n;i++)
	{	
		printf(aty[i]/ata[i][i]);
	}
}

