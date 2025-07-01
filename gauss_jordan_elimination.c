#include <stdio.h>
#include <math.h>
int main()
{
	int i,j,n;
	printf("Enter the number of euations");
	scanf("%i",&n);
	float A[n+1][n+1],c[n],x[n];
	FILE *fid;
	fid=fopen("coef.txt","r");
	for (i=0;i<n;i++)
	{
	 	for (j=0;j<=n;j++){
		 
	 	if(j<n)
			fscanf(fid,"%f",&A[i][j]);
		else
			fscanf(fid,"%f",&c[i]);
	}}
	fclose(fid);
	for (i=0;i<n;i++)
	{
	 	for (j=0;j<n;j++) 
			{
				printf("%15.6g",A[i][j]);
			}
			printf("%15.6g",c[i]);
		printf("\n");
	}
	printf("\n");
	printf("A inverse and the solution");
	printf("\n");
	float b[n][n];
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++){
		
		if(i==j) b[i][j]=1;
		else b[i][j]=0;
	}
	x[i]=0.0;
	}
	int k=0;
	float s=0.0;
	for(i=0;i<n;i++)
	{
		k=i;
		for(j=i;j<n;j++)
		{
			if(A[k][i]<A[j][i]) k=j;
		}
		if(k!=i)
		{
			for(j=0;j<n;j++)
			{
				A[i][j]=A[i][j]+A[k][j];
				b[i][j]=b[i][j]+b[k][j];
				A[k][j]=A[i][j]-A[k][j];
				b[k][j]=b[i][j]-b[k][j];
				A[i][j]=A[i][j]-A[k][j];
				b[i][j]=b[i][j]-b[k][j];
			}
			c[i]=c[i]+c[k];
			c[k]=c[i]-c[k];
			c[i]=c[i]-c[k];
		}
		for(j=0;j<n;j++)
		{
			if(j!=i)
			{
				s=A[j][i]/A[i][i];
				c[j]=c[j]-(s*c[i]);
				for(k=0;k<n;k++)
				{
					A[j][k]=A[j][k]-(s*A[i][k]);
					b[j][k]=b[j][k]-(s*b[i][k]);
				}	
			}
		}
	}
	for(i=0;i<n;i++)
	{
		x[i]=c[i]/A[i][i];
		for(j=0;j<n;j++)
		{
			b[i][j]=b[i][j]/A[i][i];
		}
	}
	for (i=0;i<n;i++)
	{
	 	for (j=0;j<n;j++) 
			{
				printf("%15.6g",b[i][j]);
			}
			printf("%15.6g",x[i]);
		printf("\n");
	}
	return 0;
}
