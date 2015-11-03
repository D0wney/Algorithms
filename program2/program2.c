#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//ulimit -s unlimited

static int COMPCOUNT;


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

// Creates Random Int
void init_random_array_reasonable(int arr[], int n)
{
  	//srand(12);	//seed		
  	int i;
 	 for (i=0; i<n; i++) 
  	{
  	  arr[i] = random_int(0, 500);
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
// ========== Insertion Sort ============
// ======================================

int insertion_sort(int arr[], int n, int k)
{
	int i,j;
	for(i=1; i<n; i++)
	{
		for(j=i; j>0 && arr[j] < arr[j-1]; j--)
		{
			SWAP(arr, j, j-1);
		}
	}
	//printf("INSERTION SORT K VAL: %d\n", arr[k]);
	return arr[k];
}

void insertion_sort_3(int arr[], int s, int n)
{
	int i,j;
	for(i=s; i<n; i++)
	{
		for(j=i; j>s && arr[j] < arr[j-1]; j--)
		{
			SWAP(arr, j, j-1);
		}
	}
}

// ======================================
// ============ QuickSort ===============
// ======================================


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
		while((COMPARE(l, r)!=0) && (COMPARE(arr[l],V)!=0))  //(l<=r && arr[l]<=V)
		{
			l++;
		}
		while((COMPARE(l, r)!=0) && (COMPARE(arr[r],V)!=2))  //(l<=r && arr[r]>=V)
		{
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





// =================================
// ========== SELECT1 ==============
// =================================

int SELECT1(int arr[], int n, int k)
{
	quicksort(arr, 0, n-1);
	return arr[k];
}



// =================================
// ========== SELECT2 ==============
// =================================

int SELECT2(int arr[], int n, int k)
{
	if(n<25)
	{
		return insertion_sort(arr, n, k);
	}

	int V = arr[random_int(0,n)];

	int *L = malloc(n * sizeof(*L));
	int *E = malloc(n * sizeof(*E));
	int *G = malloc(n * sizeof(*G));

	int i=0, l=0, e=0, g=0;

	while(i<n)
	{
		if(COMPARE(arr[i],V) == 2) //(arr[i]<V)
		{
			L[l] = arr[i];
			l++;
		}
		else if(COMPARE(arr[i], V) == 1) //(arr[i]==V)
		{
			E[e] = arr[i];
			e++;
		}
		else
		{
			G[g] = arr[i];
			g++;
		}
		i++;
	}

	if(k<=l)
	{
		SELECT2(L, l, k);
	}
	else if(k<=l+e)
	{
		return(V);
	}
	else
	{
		SELECT2(G, g, k - l - e);
	}
	
	


}


// =================================
// =========== SELECT3 =============
// =================================



int SELECT3(int arr[], int n, int k)
{
	if(n<25)
	{
		return insertion_sort(arr, n, k);
	}
/*
	int *one = malloc(n/5 * sizeof (*one));
	int *two = malloc(n/5 * sizeof (*two));
	int *three = malloc(n/5 * sizeof (*three));
	int *four = malloc(n/5 * sizeof (*four));
	int *five = malloc(n/5 * sizeof (*five));
*/
	int m = (n)/5;
	int i=0;
	for(i=0; i<m; i++)
	{
		int five = i*5;
		if(COMPARE(n-five, 4) == 0)
		{
			insertion_sort_3(arr, five, 5);
			SWAP(arr, i, five + 5/2);
		}
		else
		{
			insertion_sort_3(arr, five, n-five);
			SWAP(arr, i, five + (n-five)/2);
		}
	}

	int V = SELECT3(arr, n/5, (n/5)/2);

	int *L = malloc(n * sizeof(*L));
	int *E = malloc(n * sizeof(*E));
	int *G = malloc(n * sizeof(*G));

	int l=0, e=0, g=0;
	i=0;
	while(COMPARE(i,n)==2)
	{
		if(COMPARE(arr[i],V) == 2)
		{
			L[l] = arr[i];
			l++;
		}
		else if(COMPARE(arr[i],V) == 1)
		{
			E[e] = arr[i];
			e++;
		}
		else
		{
			G[g] = arr[i];
			g++;
		}
		i++;
	}

	if(k<=l)
	{
		SELECT3(L, l, k);
	}
	else if(k<=l+e)
	{
		return(V);
	}
	else
	{
		SELECT3(G, g, k - l - e);
	}



}


int main()
{

	int reverse_array[] ={31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,
		16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0, 44, 33, 22, 555, 66, 22, 11, 66, 34,
		24, 52, 65, 75};

	int test_array[] = { 1, 3, 5, 4, 2, 7, 6};

	int *random_array_10= malloc(10000 * sizeof(*random_array_10));
	init_random_array(random_array_10, 10000);
	int *random_array_100= malloc(100000 * sizeof(*random_array_100));
	init_random_array(random_array_100, 100000);
	int *random_array_1000= malloc(1000000 * sizeof(*random_array_1000));
	init_random_array(random_array_1000, 1000000);


	int *temp_10 = malloc(10000 * sizeof(*temp_10)); 
	int *temp_100 = malloc(100000 * sizeof(*temp_100)); 
	int *temp_1000 = malloc(1000000 * sizeof(*temp_1000));


	clock_t start,end;
	double t;
	int arrk, n;


	printf("--------------------\n");



	printf("\n");
	printf("-------------SELECT1------------\n");


	memcpy(&temp_10, &random_array_10, sizeof(random_array_10));
	memcpy(&temp_100, &random_array_100, sizeof(random_array_100));
	memcpy(&temp_1000, &random_array_1000, sizeof(random_array_1000));

	//memcpy(&temp_1, &random_array_1, sizeof(random_array_1));


	//print_array(temp_1, 100);
	//printf("yo: %d\n", SELECT1(temp_1, 100, 1));
	//print_array(temp_1, 100);
	
	printf("--- 10,000 ---\n");
	n = 10000;
	COMPCOUNT = 0; 
	start=clock();
	//quicksort(temp_10, 0, 10000-1);
	arrk = SELECT1(temp_10, n, n/2);
	end=clock();
	t= (end - start)/(double)CLOCKS_PER_SEC;
	//free(temp_10);
	//print_array(temp_sorted, n);
	printf("Time: %f\n", t);
	printf("COMPCOUNT: %d\n", COMPCOUNT);
	printf("|Select 1| n:%d k:%d Arr[k]:%d COMPCOUNT:%d\n", n, n/2, arrk, COMPCOUNT);
	printf("--------------------\n");

	printf("--- 100,000 ---\n");
	n = 100000;
	COMPCOUNT = 0; 
	start=clock();
	//quicksort(temp_10, 0, 10000-1);
	arrk = SELECT1(temp_100, n, n/2);
	end=clock();
	t= (end - start)/(double)CLOCKS_PER_SEC;
	//free(temp_10);
	//print_array(temp_sorted, n);
	printf("Time: %f\n", t);
	printf("COMPCOUNT: %d\n", COMPCOUNT);
	printf("|Select 1| n:%d k:%d Arr[k]:%d COMPCOUNT:%d\n", n, n/2, arrk, COMPCOUNT);
	printf("--------------------\n");

	printf("--- 1,000,000 ---\n");
	n = 1000000;
	COMPCOUNT = 0; 
	start=clock();
	//quicksort(temp_10, 0, 10000-1);
	arrk = SELECT1(temp_1000, n, n/2);
	end=clock();
	t= (end - start)/(double)CLOCKS_PER_SEC;
	//free(temp_10);
	//print_array(temp_sorted, n);
	printf("Time: %f\n", t);
	printf("COMPCOUNT: %d\n", COMPCOUNT);
	printf("|Select 1| n:%d k:%d Arr[k]:%d COMPCOUNT:%d\n", n, n/2, arrk, COMPCOUNT);
	printf("--------------------\n");

	printf("\n");
	printf("\n");

	printf("-------------SELECT2------------\n");


	memcpy(&temp_10, &random_array_10, sizeof(random_array_10));
	memcpy(&temp_100, &random_array_100, sizeof(random_array_100));
	memcpy(&temp_1000, &random_array_1000, sizeof(random_array_1000));

	//memcpy(&temp_1, &random_array_1, sizeof(random_array_1));


	//print_array(temp_1, 100);
	//printf("yo: %d\n", SELECT1(temp_1, 100, 1));
	//print_array(temp_1, 100);
	
	printf("--- 10,000 ---\n");
	n = 10000;
	COMPCOUNT = 0; 
	start=clock();
	//quicksort(temp_10, 0, 10000-1);
	arrk = SELECT2(temp_10, n, n/2);
	end=clock();
	t= (end - start)/(double)CLOCKS_PER_SEC;
	//free(temp_10);
	//print_array(temp_sorted, n);
	printf("Time: %f\n", t);
	printf("COMPCOUNT: %d\n", COMPCOUNT);
	printf("|Select 2| n:%d k:%d Arr[k]:%d COMPCOUNT:%d\n", n, n/2, arrk, COMPCOUNT);
	printf("--------------------\n");

	printf("--- 100,000 ---\n");
	n = 100000;
	COMPCOUNT = 0; 
	start=clock();
	//quicksort(temp_10, 0, 10000-1);
	arrk = SELECT2(temp_100, n, n/2);
	end=clock();
	t= (end - start)/(double)CLOCKS_PER_SEC;
	//free(temp_10);
	//print_array(temp_sorted, n);
	printf("Time: %f\n", t);
	printf("COMPCOUNT: %d\n", COMPCOUNT);
	printf("|Select 2| n:%d k:%d Arr[k]:%d COMPCOUNT:%d\n", n, n/2, arrk, COMPCOUNT);
	printf("--------------------\n");

	printf("--- 1,000,000 ---\n");
	n = 1000000;
	COMPCOUNT = 0; 
	start=clock();
	//quicksort(temp_10, 0, 10000-1);
	arrk = SELECT2(temp_1000, n, n/2);
	end=clock();
	t= (end - start)/(double)CLOCKS_PER_SEC;
	//free(temp_10);
	//print_array(temp_sorted, n);
	printf("Time: %f\n", t);
	printf("COMPCOUNT: %d\n", COMPCOUNT);
	printf("|Select 2| n:%d k:%d Arr[k]:%d COMPCOUNT:%d\n", n, n/2, arrk, COMPCOUNT);
	printf("--------------------\n");

	printf("\n");
	printf("\n");


	printf("-------------SELECT3------------\n");


	memcpy(&temp_10, &random_array_10, sizeof(random_array_10));
	memcpy(&temp_100, &random_array_100, sizeof(random_array_100));
	memcpy(&temp_1000, &random_array_1000, sizeof(random_array_1000));

	//memcpy(&temp_1, &random_array_1, sizeof(random_array_1));


	//print_array(temp_1, 100);
	//printf("yo: %d\n", SELECT1(temp_1, 100, 1));
	//print_array(temp_1, 100);
	
	printf("--- 10,000 ---\n");
	n = 10000;
	COMPCOUNT = 0; 
	start=clock();
	//quicksort(temp_10, 0, 10000-1);
	arrk = SELECT3(temp_10, n, n/2);
	end=clock();
	t= (end - start)/(double)CLOCKS_PER_SEC;
	//free(temp_10);
	//print_array(temp_sorted, n);
	printf("Time: %f\n", t);
	printf("COMPCOUNT: %d\n", COMPCOUNT);
	printf("|Select 3| n:%d k:%d Arr[k]:%d COMPCOUNT:%d\n", n, n/2, arrk, COMPCOUNT);
	printf("--------------------\n");

	printf("--- 100,000 ---\n");
	n = 100000;
	COMPCOUNT = 0; 
	start=clock();
	//quicksort(temp_10, 0, 10000-1);
	arrk = SELECT3(temp_100, n, n/2);
	end=clock();
	t= (end - start)/(double)CLOCKS_PER_SEC;
	//free(temp_10);
	//print_array(temp_sorted, n);
	printf("Time: %f\n", t);
	printf("COMPCOUNT: %d\n", COMPCOUNT);
	printf("|Select 3| n:%d k:%d Arr[k]:%d COMPCOUNT:%d\n", n, n/2, arrk, COMPCOUNT);
	printf("--------------------\n");

	printf("--- 1,000,000 ---\n");
	n = 1000000;
	COMPCOUNT = 0; 
	start=clock();
	//quicksort(temp_10, 0, 10000-1);
	arrk = SELECT3(temp_1000, n, n/2);
	end=clock();
	t= (end - start)/(double)CLOCKS_PER_SEC;
	//free(temp_10);
	//print_array(temp_sorted, n);
	printf("Time: %f\n", t);
	printf("COMPCOUNT: %d\n", COMPCOUNT);
	printf("|Select 3| n:%d k:%d Arr[k]:%d COMPCOUNT:%d\n", n, n/2, arrk, COMPCOUNT);
	printf("--------------------\n");

	printf("\n");
	printf("\n");



	free(random_array_10);
	free(random_array_100);
	free(random_array_1000);

}