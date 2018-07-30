//HAMMING CODE RECEIVER

#include<stdio.h>
#include<math.h>
int calculatecodelength(int datalength);
int decodedata(int *data, int totaldatalength, int codelength,int*);
int returnparityofbit(int *array, int redundantbitposition, int length);
void correcterror(int *data,  int* arr, int codelength);

int main()
{	

	int data[20]={0}, arr[20] = {0};
	int datalength, codelength, i, totaldatalength;
	int iserror = 0;
	
	printf("Enter length of data");
	scanf("%d",&datalength);	
	
	codelength = calculatecodelength(datalength);

	printf("\n\ncodelength : %d \n\n",codelength);	

	totaldatalength = datalength+codelength;


	printf("\n\nEnter encoded data (ENTER DATA FROM LSB TO MSB)\n");

	//accept binary numbers from user	
	for(int i = 0 ; i< totaldatalength ; i++)
	{
		scanf("%d",&data[i]);
	}

	
	iserror =  decodedata(data,totaldatalength,codelength,arr);	//it will generate data whih will contain redundant / extra bits

	if(iserror == 0)
	{
		printf("\nNo Error \n");
	}
	
	else
	{
		printf("\n\nError at \n\n");
		for(int i=codelength ; i>=0 ; i--)
		{
			printf("%d ",arr[i]);
		}
		
		correcterror(data,arr,codelength);
		
		printf("\n\nCORRECTED DATA\n\n");
	
		for(int i = totaldatalength ; i>=0 ; i--)
		{
			printf("%d ",data[i]);
		}
	}
		
	

}




int calculatecodelength(int datalength)
{
	int r=0;
	while(pow(2,r)<(datalength+r+1))
	{
		++r;
	}
	return r;
	

}

int decodedata(int *data, int totaldatalength, int codelength,int * arr)
{

	int iserror = 0;

	for(int r = 0 ; r < codelength ; r++)
	{
		arr[r] = returnparityofbit(data, pow(2,r)-1, totaldatalength);
		if(arr[r] == 1)
			iserror = 1;	

	}
	return iserror;
	
}


int returnparityofbit(int *array, int redundantbitposition, int length)
{
	int sum = 0;
	int flag = 0;
	int skipcount=0, noofskips = redundantbitposition+1;//used to skip the indexes		
	for(int i = redundantbitposition ; i<length ;i++)
	{
		if(flag == noofskips && skipcount != noofskips)
		{
			++skipcount;
			continue;
		}
		if(skipcount == noofskips)
		{
			flag = skipcount = 0;
		}
		if(array[i] == 1)
			++sum;

		++flag;	
	}
	if(sum % 2 == 0) return 0;
	
	return 1;
}

void correcterror(int *data,  int* arr, int codelength)
{
	int loc = 0;
	for(int i = 0 ;i<codelength ; i++)
	{
		if(arr[i] == 1)
		{
			 loc = pow(2,(i)) + loc;
		}
	}

	if (data[loc-1] == 0)
		data[loc-1] = 1;
	else
	    	data[loc-1] = 0;
}
			 


