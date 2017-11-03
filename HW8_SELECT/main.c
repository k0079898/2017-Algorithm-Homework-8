#include <stdio.h>
#include <stdlib.h>

void swap(int arr[], int i, int j);
int select(int arr[], int start, int end, int k);
void insertionSort(int arr[], int start, int end);
int partition(int arr[], int start, int end);

int main(void) {
    FILE *input, *output;
    char s[20];
    int size, target, num;
    int *arr;

    input = fopen("input.txt", "r");
    fgets(s, 20, input);
    size = atoi(s);
    arr = (int*) calloc(size, sizeof(int));
    for(int i=0;i<size;i++) {
        if(i == size-1) {
            fgets(s, 20, input);
            arr[i] = atoi(s);
        }else {
            fscanf(input, "%s", s);
            arr[i] = atoi(s);
        }
    }
    fgets(s, 20, input);
    target = atoi(s);
    fclose(input);

    num = select(arr, 0,size-1,target-1);

    output = fopen("output.txt", "w");
    fprintf(output, "%d\n", num);
    fclose(output);

    free(arr);

    return 0;
}

void swap(int arr[], int i, int j) {
    int temp;
    temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

int select(int arr[], int start, int end, int k)
{
    if(end-start<=4) {
        insertionSort(arr, start, end);
        return arr[k];
    }else {
        int i, m, x, index, median;
        m = (end-start+5)/5;
        index = 0;
        for(i=0;i<m;i++) {
            if(i==m-1 && start+i*5+4 > end) {
                insertionSort(arr, start+i*5, end);
                if(start+i*5+2<=end) {
                    swap(arr, start+index, start+i*5+2);
                    index++;
                }
            }else {
                insertionSort(arr, start+i*5, start+i*5+4);
                swap(arr, start+index, start+i*5+2);
                index++;
            }
        }
        m = start + ((index-1)/2);
        median = select(arr, start, start+index-1, m);
        for(i=start;i<=start+index-1;i++) {
            if(arr[i]==median) {
                swap(arr, i, end);
                break;
            }
        }
        x = partition(arr, start, end);
        if(x==k) return arr[k];
        else if(x>k) return select(arr, start, x-1, k);
        else return select(arr, x+1, end, k);
    }
}

void insertionSort(int arr[], int start, int end)
{
    int key, i, j;
    for(i=start+1;i<=end;i++) {
        key = arr[i];
        j = i - 1;
        while(j >= start && arr[j] > key) {
            arr[j+1] = arr[j];
            j = j - 1;
        }
        arr[j+1] = key;
    }
}

int partition(int arr[], int start, int end)
{
    int i, j, x;
    x = arr[end];
    i = start - 1;
    for(j=start;j<=end-1;j++) {
        if(arr[j]<=x) {
            i++;
            swap(arr, i, j);
        }
    }
    swap(arr, i+1, end);
    return i+1;
}
