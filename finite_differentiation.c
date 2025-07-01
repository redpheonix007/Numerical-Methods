#include <stdio.h>
#include <math.h>
int main()
{
	int i, j, n;
	printf("reading values from the file values.txt for the data");
	printf("\n");
	float x[20],y[20],fd[20],bd[20],fd1[20],bd1[20],fd2[20],bd2[20];
	printf("enter the number of data points");
	printf("\n");
	scanf("%i",&n);
	printf("1.Central Difference\n");
	printf("2.Forward Difference\n");
	printf("3.BackwardDifference\n");
	scanf("%i",&j);
	FILE *fid;
	fid=fopen("values.txt","r");
	for(i=0;i<n;i++) fscanf(fid, "%f %f", &x[i], &y[i]);
	fclose(fid);
	float h=1;
	for(i=1;i<n-1;i++)
	fd[i]=((y[i+1]-y[i-1])/(2*h));
	for(i=1;i<n-1;i++)
	bd[i]=((y[i+1]+y[i-1]-y[i]-y[i])/(h*h));
	for(i=0;i<n-1;i++)
	fd1[i]=((y[i+1]-y[i])/(h));
	for(i=0;i<n-2;i++)
	bd1[i]=((y[i+2]+y[i]-(2*y[i+1]))/(h*h));
	for(i=1;i<n;i++)
	fd2[i]=((y[i]-y[i-1])/(h));
	for(i=2;i<n;i++)
	bd2[i]=((y[i-2]+y[i]-(2*y[i-1]))/(h*h));
	printf("%15s%15s%15s%15s","x","y","dy/dx","d2y/dx2");
	printf("\n");printf("\n");
	for (i=0;i<n;i++)
	{
	 	printf("%15.6g",x[i]);
		printf("%15.6g",y[i]);
		if(j==1){if(i!=0)
		{if(i!=(n-1)){printf("%15.5g",fd[i]);
		printf("%15.5g",bd[i]);
		}}}
		if(j==2){if(i!=(n-1)){
		printf("%15.5g",fd1[i]);
		if(i!=(n-2)){printf("%15.5g",bd1[i]);
		}}}
		if(j==3){if(i!=0){
		printf("%15.5g",fd2[i]);
		if(i!=(1)){printf("%15.5g",bd2[i]);
		}}}
		printf("\n");
	}
}
