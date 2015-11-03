#include<stdio.h>

int main()
{
	char* hi = "hello";
	printf("%c\n", hi[3]);
	printf("hello \n");
	int min;
	int max;
	int a[] = {2, 3, 1, 22, 331, 10, 5, 1111, 33};
	//test(&min, &max);
	minMax(a, 0, 9, &min, &max);
	printf("min: %d    max: %d \n", min, max);

}

minMax(int a[], int start, int n, int *min, int *max)
{
	if (n==1)
	{
		*max = a[start];
		*min = a[start];
	}
	else if (n==2)
	{
		if(a[start] > a[start+1])
		{
			*max = a[start];
			*min = a[start+1];
		}
		else
		{
			*max = a[start+1];
			*min = a[start];
		}
	}
	else
	{
		int min1 = *min, min2= *min, max1= *max, max2= *max;
		minMax(a, start, n/2, &min1, &max1);
		minMax(a, start+n/2, n-n/2, &min2, &max2);
		if (min1 > min2)
			*min = min2;
		else
			*min = min1;
		if (max1>max2)
			*max = max1;
		else
			*max =max2;
	}
}

void test(int* a, int b)
{
	*a = 5;
	b = 5;
}