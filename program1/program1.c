// Kevin Downey
// Programming Assignment 1
// CS610
// 10/9/15

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static int COMPCOUNT;

// Prints array
void print_array(int arr[], int n)
{
	int i;
	for(i=0; i<n; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}

// Creates Random Int
void init_random_array(int arr[], int n)
{
  	srand(12);	//seed		
  	int i;
 	 for (i=0; i<n; i++) 
  	{
  	  arr[i] = rand();
  	}
}


int COMPARE(int x, int y)
{
	COMPCOUNT++;
	if(x > y)
	{
		return 0;
	}
	else if(x == y)
	{
		return 1;
	}
	else
	{
		return 2;
	}
}

//Swaps values in an Array
void SWAP(int arr[], int i1, int i2)
{
	int temp = arr[i1];
	arr[i1] = arr[i2];
	arr[i2] = temp;
}



// ======================================
// ============ MERGESORT ===============
// ======================================

void merge(int arr[], int low, int mid, int  high)
{
	int index,high_index,low_index;
	int k;
	int temp[1048576];

	low_index = low; // for first half
	high_index = mid+1; // for second half
	index = low;

	while((low_index<=mid) && (high_index<=high))
	{
		//if(arr[low_index]<= arr[high_index])
		if(COMPARE(arr[low_index],arr[high_index]) == 1 || COMPARE(arr[low_index],arr[high_index]) == 2 )
		{
			temp[index]=arr[low_index];
			low_index++;
		}
		else
		{
			temp[index]=arr[high_index];
			high_index++;
		}
		index++;
	}

	if(low_index>mid)
	{
		for(k=high_index; k<=high; k++)
		{
			temp[index] = arr[k];
			index++;
		}
	}
	else
	{
		for(k=low_index; k<=mid; k++)
		{
			temp[index] = arr[k];
			index++;
		}
	}

	for(k=low; k<=high; k++)
	{
		arr[k] = temp[k];
	}
}


void mergesort(int arr[], int low, int high)
{
	int mid;
	if(low<high)
	{
		mid = (high+low) / 2;
		mergesort(arr, low, mid);
		mergesort(arr, mid+1, high);
		merge(arr, low, mid, high);
	}
}


// ======================================
// ============ HEAPSORT ================
// ======================================




void maxHeapify(int arr[], int r, int n)
{

	int left = 2*r;
	int right = 2*r +1;

	int largest = r;


	if (left <= n && arr[left] > arr[r])
	{
		largest = left;
	}


	if (right <= n && arr[right] > arr[largest])
	{
		largest = right;
	}

	COMPCOUNT++;
	if (largest != r)
	{
		SWAP(arr, r, largest);
		maxHeapify(arr, largest, n);
	}
}


void buildMaxHeap(int arr[], int n)
{
	int i;
	for (i = (int)(n/2) ; i >= 0 ; i--)
	{
		maxHeapify(arr, i, n) ;
	}
}

void heapsort(int arr[], int n){

	int size = n;


	buildMaxHeap(arr, size);


	int i;
	for (i= size; i > 0; i--)
	{

		int temp = arr[0];
		arr[0] = arr[i];
		arr[i] = temp ;

		size--;

		maxHeapify(arr, 0, size) ;
	}
}




// ======================================
// ============ QuickSort ===============
// ======================================

// RANDOM INT FUNCTION
unsigned int random_int(unsigned int min, unsigned int max)
{
    int r;
    const unsigned int range = 1 + max - min;
    const unsigned int buckets = RAND_MAX / range;
    const unsigned int limit = buckets * range;

    do
    {
        r = rand();
    } while (r >= limit);

    return min + (r / buckets);
}

void quicksort(int arr[], int left, int right)
{
	if(left>=right)
	{
		return;
	}
	int k = random_int(left, right);
	//printf(" || %d | %d | %d || ", left, k, right);
	SWAP(arr, left, k);
	int V = arr[left]; //pivot

	int l = left+1;
	int r = right;
	while(l<=r)
	{
		while(l<=r && arr[l]<=V)
		{
			COMPCOUNT++;
			l++;
		}
		while(l<=r && arr[r]>=V)
		{
			COMPCOUNT++;
			r--;
		}
		if(COMPARE(l,r)==2) 
		{
			SWAP(arr, l, r);
			l++;
			r--;
		}
	}
	SWAP(arr, left, r); // left because pivot is there
	quicksort(arr, left, r-1);
	quicksort(arr, r+1, right);


}



int main()
{
	printf("\n");

	int sorted_array[] = {0,1,2,3,4,5,6,7,8,9,
				10,11,12,13,14,15,16,17,18,19,
		20,21,22,23,24,25,26,27,28,29,30,31};              

	int reverse_array[] ={31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,
		16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0};

	int random_array[32]; 
	init_random_array(random_array, 32);

	int n = sizeof(sorted_array)/sizeof(int); // size of array



	printf("--- Sorted array ---\n");
	print_array(sorted_array, n);
	printf("--- Reverse array ---\n");
	print_array(reverse_array, n);
	printf("--- Random array ---\n");
	print_array(random_array, n);
	printf("\n");

	int temp_sorted[32]; 
	int temp_reverse[32]; 
	int temp_random[32]; 


	
	
	printf("==================================\n");
	printf("==============PART1===============\n");
	printf("==================================\n");
	printf("\n");


	printf("-------------MERGESORT------------\n");

	memcpy(&temp_sorted, &sorted_array, sizeof(sorted_array));
	memcpy(&temp_reverse, &reverse_array, sizeof(reverse_array));
	memcpy(&temp_random, &random_array, sizeof(random_array));

	printf("--- Sorted array ---\n");
	COMPCOUNT = 0;
	mergesort(temp_sorted, 0, n-1);
	print_array(temp_sorted, n);
	printf("COMPCOUNT: %d\n", COMPCOUNT);
	printf("--------------------\n");

	printf("--- Reverse array ---\n");
	COMPCOUNT = 0;
	mergesort(temp_reverse, 0, n-1);
	print_array(temp_reverse, n);
	printf("COMPCOUNT: %d\n", COMPCOUNT);
	printf("--------------------\n");

	printf("--- Random array ---\n");
	COMPCOUNT = 0;
	mergesort(temp_random, 0, n-1);
	print_array(temp_random, n);
	printf("COMPCOUNT: %d\n", COMPCOUNT);
	printf("--------------------\n");
	printf("---------------------------------\n");


	printf("\n");
	printf("-------------HEAPSORT------------\n");

	memcpy(&temp_sorted, &sorted_array, sizeof(sorted_array));
	memcpy(&temp_reverse, &reverse_array, sizeof(reverse_array));
	memcpy(&temp_random, &random_array, sizeof(random_array));


	printf("--- Sorted array ---\n");
	COMPCOUNT = 0;
	heapsort(temp_sorted, n);
	print_array(temp_sorted, n);
	printf("COMPCOUNT: %d\n", COMPCOUNT);
	printf("--------------------\n");

	printf("--- Reverse array ---\n");
	COMPCOUNT = 0;
	heapsort(temp_reverse, n);
	print_array(temp_reverse, n);
	printf("COMPCOUNT: %d\n", COMPCOUNT);
	printf("--------------------\n");

	printf("--- Random array ---\n");
	COMPCOUNT = 0;
	heapsort(temp_random, n-1);
	print_array(temp_random, n);
	printf("COMPCOUNT: %d\n", COMPCOUNT);
	printf("--------------------\n");
	printf("---------------------------------\n");



	printf("\n");
	printf("-------------QUICKSORT------------\n");

	memcpy(&temp_sorted, &sorted_array, sizeof(sorted_array));
	memcpy(&temp_reverse, &reverse_array, sizeof(reverse_array));
	memcpy(&temp_random, &random_array, sizeof(random_array));


	printf("--- Sorted array ---\n");
	COMPCOUNT = 0;
	quicksort(temp_sorted, 0, n-1);
	print_array(temp_sorted, n);
	printf("COMPCOUNT: %d\n", COMPCOUNT);
	printf("--------------------\n");

	printf("--- Reverse array ---\n");
	COMPCOUNT = 0;
	quicksort(temp_reverse, 0, n-1);
	print_array(temp_reverse, n);
	printf("COMPCOUNT: %d\n", COMPCOUNT);
	printf("--------------------\n");

	printf("--- Random array ---\n");
	COMPCOUNT = 0;
	quicksort(temp_random, 0, n-1);
	print_array(temp_random, n);
	printf("COMPCOUNT: %d\n", COMPCOUNT);
	printf("--------------------\n");
	printf("---------------------------------\n");
	printf("\n");
	printf("\n");


	printf("==================================\n");
	printf("==============PART2===============\n");
	printf("==================================\n");
	printf("\n");

	clock_t start,end;
	double t;

	int *random_array_10= malloc(1024 * sizeof(*random_array_10));
	init_random_array(random_array_10, 1024);
	int *random_array_15= malloc(32768 * sizeof(*random_array_15));
	init_random_array(random_array_10, 32768);
	int *random_array_20= malloc(1048576 * sizeof(*random_array_20));
	init_random_array(random_array_20, 1048576);


	int *temp_10 = malloc(1024 * sizeof(*temp_10)); 
	int *temp_15 = malloc(32768 * sizeof(*temp_15)); 
	int *temp_20 = malloc(1048576 * sizeof(*temp_20));

/*
	int random_array_10[1024]; 
	init_random_array(random_array_10, 1024);
	int random_array_15[32768]; 
	init_random_array(random_array_15, 32768);
//	int random_array_20[1048576]; 
//	init_random_array(random_array_20, 1048576);

	int temp_10[1024]; // = sorted_array;
	int temp_15[32768]; // = reverse_array;
//	int temp_20[1048576]; // = random_array;
*/


	printf("-------------MERGESORT------------\n");

	memcpy(&temp_10, &random_array_10, sizeof(random_array_10));
	memcpy(&temp_15, &random_array_15, sizeof(random_array_15));
	memcpy(&temp_20, &random_array_20, sizeof(random_array_20));

	//print_array(temp_10, 1024);

	printf("--- 2^10 ---\n");
	COMPCOUNT = 0;
	start=clock();
	mergesort(temp_10, 0, 1024-1);
	end=clock();
	t= (end - start)/(double)CLOCKS_PER_SEC;
	//print_array(temp_sorted, n);
	printf("Time: %f\n", t);
	printf("COMPCOUNT: %d\n", COMPCOUNT);
	printf("--------------------\n");

	printf("--- 2^15 ---\n");
	COMPCOUNT = 0;
	start=clock();
	mergesort(temp_15, 0, 32786-1);
	end=clock();
	t= (end - start)/(double)CLOCKS_PER_SEC;
	//print_array(temp_reverse, n);
	printf("Time: %f\n", t);
	printf("COMPCOUNT: %d\n", COMPCOUNT);
	
	printf("--------------------\n");

	printf("--- 2^20 ---\n");
	COMPCOUNT = 0;
	start=clock();
	mergesort(temp_20, 0, 1048576-1);
	end=clock();
	t= (end - start)/(double)CLOCKS_PER_SEC;
	//print_array(temp_random, n);
	printf("Time: %f\n", t);
	printf("COMPCOUNT: %d\n", COMPCOUNT);
	printf("---------------------------------\n");


	printf("\n");
	printf("-------------HEAPSORT------------\n");

	memcpy(&temp_10, &random_array_10, sizeof(random_array_10));
	memcpy(&temp_15, &random_array_15, sizeof(random_array_15));
	memcpy(&temp_20, &random_array_20, sizeof(random_array_20));

	printf("--- 2^10 ---\n");
	COMPCOUNT = 0;
	start=clock();
	heapsort(temp_10, 1024-1);
	end=clock();
	t= (end - start)/(double)CLOCKS_PER_SEC;
	//print_array(temp_sorted, n);
	printf("Time: %f\n", t);
	printf("COMPCOUNT: %d\n", COMPCOUNT);
	printf("--------------------\n");

	printf("--- 2^15 ---\n");
	COMPCOUNT = 0;
	start=clock();
	heapsort(temp_15, 32786-1);
	end=clock();
	t= (end - start)/(double)CLOCKS_PER_SEC;
	//print_array(temp_reverse, n);
	printf("Time: %f\n", t);
	printf("COMPCOUNT: %d\n", COMPCOUNT);
	printf("--------------------\n");

	printf("--- 2^20 ---\n");
	COMPCOUNT = 0;
	start=clock();
	heapsort(temp_20, 1048576-1);
	end=clock();
	t= (end - start)/(double)CLOCKS_PER_SEC;
	//print_array(temp_random, n);
	printf("Time: %f\n", t);
	printf("COMPCOUNT: %d\n", COMPCOUNT);
	printf("---------------------------------\n");


	printf("\n");
	printf("-------------QUICKSORT------------\n");

	memcpy(&temp_10, &random_array_10, sizeof(random_array_10));
	memcpy(&temp_15, &random_array_15, sizeof(random_array_15));
	memcpy(&temp_20, &random_array_20, sizeof(random_array_20));

	printf("--- 2^10 ---\n");
	COMPCOUNT = 0;
	start=clock();
	quicksort(temp_10, 0, 1024-1);
	end=clock();
	t= (end - start)/(double)CLOCKS_PER_SEC;
	//print_array(temp_sorted, n);
	printf("Time: %f\n", t);
	printf("COMPCOUNT: %d\n", COMPCOUNT);
	printf("--------------------\n");

	printf("--- 2^15 ---\n");
	COMPCOUNT = 0;
	start=clock();
	quicksort(temp_15, 0, 32786-1);
	end=clock();
	t= (end - start)/(double)CLOCKS_PER_SEC;
	//print_array(temp_reverse, n);
	printf("Time: %f\n", t);
	printf("COMPCOUNT: %d\n", COMPCOUNT);
	printf("--------------------\n");

	printf("--- 2^20 ---\n");
	COMPCOUNT = 0;
	start=clock();
	quicksort(temp_20, 0, 1048576-1);
	end=clock();
	t= (end - start)/(double)CLOCKS_PER_SEC;
	//print_array(temp_random, n);
	printf("Time: %f\n", t);
	printf("COMPCOUNT: %d\n", COMPCOUNT);
	printf("---------------------------------\n");

	printf("\n");
	printf("\n");
	
}