//HAMMING CODE SENDER
#include<stdio.h>
#include<math.h>

void adddatatoarray(int *array,int length, int indexpos);
void encodedata(int *data, int datalength, int codelength);
int calculatecodelength(int datalength);
void calculatevalueofredundantbits(int *data, int codelength, int totaldatalength);
int returnparityofbits(int *array, int redundantbitposition, int length);

int main()
{
	int data[20]={0};
	int datalength, codelength, i, totaldatalength;
	
	printf("Enter length of data");
	scanf("%d",&datalength);	
	
	

	printf("\n\nEnter data (ENTER DATA FROM LSB TO MSB)\n");

	//accept binary numbers from user	
	for(int i = 0 ; i< datalength ; i++)
	{
		scanf("%d",&data[i]);
	}

	codelength = calculatecodelength(datalength);
	
	printf("\n\ncodelength : %d \n\n",codelength);	
	
	totaldatalength = datalength+codelength;

	encodedata(data,datalength,codelength);	//it will generate data whih will contain redundant / extra bits

	
	calculatevalueofredundantbits(data, codelength, totaldatalength);
	
	for(int i=totaldatalength-1 ; i>=0 ; i--)
	{
		printf("%d ",data[i]);
	}
	

	return 0;

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

void encodedata(int *data, int datalength, int codelength)
{
	for(int  i = 0 ; i<codelength ;i++)
	{
		adddatatoarray(data,datalength,pow(2,i)-1);		//we are writing pow(2,i)-1 because 1st bit is locatd at 0th position
		++datalength;
	}
	

}

void adddatatoarray(int *array,int length, int indexpos)
{
	int i;
	for(i = length-1 ; i>= indexpos ; i--)
	{
		array[i+1] = array[i];
	}
	array[i+1] = 2 ;

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
		{
			++sum;
		}
		++flag;	
	}
	if(sum % 2 == 0) return 0;
	
	return 1;
}
void calculatevalueofredundantbits(int *data, int codelength, int totaldatalength)
{

	
	for(int r = 0 ; r < codelength ; r++)
		data[(int)pow(2,r)-1] = returnparityofbit(data, pow(2,r)-1, totaldatalength);
	
}


