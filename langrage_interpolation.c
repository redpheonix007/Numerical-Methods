#include <stdio.h>
int main()
{
	int i, j, n, k;
	printf("reading values from the file values.txt for the data");
	printf("\n");
	float x[20],y[20],X[100],Y[100],h,sum=1;
	printf("enter the number of data points\n");
	scanf("%i",&n);
	printf("%-12s%-12s%-12s\n%-12s%-12s%-12s\n","S.no","X","Y","-----","-----","-----");
	FILE *fid;
	fid=fopen("values.txt","r");
	for(i=0;i<n;i++) fscanf(fid, "%f %f", &x[i], &y[i]);
	fclose(fid);
	h=(x[n-1]-x[0])/99;
	X[0]=x[0];
	for(j=1;j<99;j++) X[j]=X[j-1]+h;
	for(k=0;k<100;k++)
	{
		for(i=0;i<n;i++)
		{
		for(j=0;j<n;j++)
		{
			if(j!=i)
			sum=sum*((X[k]-x[j])/(x[i]-x[j]));
		}
			Y[k]=Y[k]+(sum*y[i]);
			sum=1;
		}
		printf("%-12i%-12.5g%-12.5g\n",k,X[k],Y[k]);
	}
}
