#include <stdio.h>
#include <stdlib.h>

int count = 0;

void sort(int *arr, int first, int last){

    if(first < last && last > 0){
        count++;
        if(arr[first] > arr[first+1]){
            int temp = arr[first];
            arr[first] = arr[first+1];
            arr[first+1] = temp;
        }
        printf("calling first \n");
        sort(arr, first+1, last);
        sort(arr, first, last-1);
    }
    else
        return;
}
int main(void) {

    int data [] = { 3, 5 , 6, 2, 1, 10, 4};
    int len = sizeof(data)/sizeof(int);
    int i = 0;
    sort(data,0,len-1);
    for(i=0;i<len;i++)
        printf("%d ",data[i]);

    printf("\n");
    printf("COMP COUNT: %d\n", count);

    return EXIT_SUCCESS;
}