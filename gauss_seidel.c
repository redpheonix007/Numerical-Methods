#include <stdio.h>
#include <math.h>
int main()
{
	int i,j,n;
	printf("Enter the number of euations");
	scanf("%i",&n);
	float A[n+1][n+1],c[n];
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
	float x_old[n],x_new[n],tol=pow(10,-5),s=0.0,l=0.0;
	for(i=0;i<n;i++)
	{
		x_old[i]=0.0;
	}
	while(l<tol)
	{
		l=0.0;
	for(i=0;i<n;i++)
	{
		s=c[i];
		for(j=0;j<n;j++)
		{
			if(j!=i){
			
			s=s-(A[i][j]*x_old[j]);
		}}
		l=l+(fabs(s/A[i][i]-x_old[i]));
		x_new[i]=s/A[i][i];
	}
		for(i=0;i<n;i++)
		{
			x_old[i]=x_new[i];
		}
			printf("The Value of the Equation\n");
	for (i = 0; i <n; i++) {
        printf("%15.6g",x_new[i]);
        printf("\n");
    }
	}

	return 0;
}
