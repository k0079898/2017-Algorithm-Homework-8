#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int arr[], int i, int j);
int select5(int arr[], int start, int end, int k);
int select7(int arr[], int start, int end, int k);
int select9(int arr[], int start, int end, int k);
void insertionSort(int arr[], int start, int end);
int partition(int arr[], int start, int end);
void HeapSort(int arr[], int size);
void maxHeapify(int arr[], int i, int size);

int main()
{
    clock_t start, stop;
    double time_S5[10], time_S7[10], time_S9[10], time_HS[10];
    char ss[20];
    int i, j, k, TS[10000], arr[10000], target[10], num;

    for(i=0;i<10000;i++) {
        scanf("%s", ss);
        TS[i] = atoi(ss);
    }

    target[0]=876;
    target[1]=1234;
    target[2]=21;
    target[3]=2000;
    target[4]=1357;
    target[5]=3500;
    target[6]=1;
    target[7]=6666;
    target[8]=123;
    target[9]=9999;
    i=0;
    for(int j=1000;j<=10000;j=j+1000) {
        printf("Find %04d-th smallest number with %d elements\n", target[i], j);
        printf("================================================\n");
        for(k=0;k<j;k++) arr[k] = TS[k];
        start = clock();
        num = select5(arr, 0, j-1, target[i]);
        stop = clock();
        time_S5[i] = ((double) (stop - start)) / CLOCKS_PER_SEC;
        printf("1.SELECT algorithm(groups of 5): %d\n", num);

        for(k=0;k<j;k++) arr[k] = TS[k];
        start = clock();
        num = select7(arr, 0, j-1, target[i]);
        stop = clock();
        time_S7[i] = ((double) (stop - start)) / CLOCKS_PER_SEC;
        printf("2.SELECT algorithm(groups of 7): %d\n", num);

        for(k=0;k<j;k++) arr[k] = TS[k];
        start = clock();
        num = select9(arr, 0, j-1, target[i]);
        stop = clock();
        time_S9[i] = ((double) (stop - start)) / CLOCKS_PER_SEC;
        printf("3.SELECT algorithm(groups of 9): %d\n", num);

        for(k=0;k<j;k++) arr[k] = TS[k];
        start = clock();
        HeapSort(arr, j);
        stop = clock();
        time_HS[i] = ((double) (stop - start)) / CLOCKS_PER_SEC;
        printf("3.Heapsort: %d\n", arr[target[i]]);
        printf("================================================\n\n");
        i++;
    }

    printf("==================Running time==================\n");
    printf("================================================\n");
    printf("||   Tn   |   S5   |   S7   |   S9   |   HS   ||\n");
    printf("================================================\n");
    i=1000;
    for(j=0;j<10;j++) {
        printf("||%6d: %.6lf %.6lf %.6lf %.6f ||\n", i, time_S5[j], time_S7[j], time_S9[j], time_HS[j]);
        i=i+1000;
    }
    printf("================================================\n");

    return 0;
}

void swap(int arr[], int i, int j) {
    int temp;
    temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

int select5(int arr[], int start, int end, int k)
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
        median = select5(arr, start, start+index-1, m);
        for(i=start;i<=start+index-1;i++) {
            if(arr[i]==median) {
                swap(arr, i, end);
                break;
            }
        }
        x = partition(arr, start, end);
        if(x==k) return arr[k];
        else if(x>k) return select5(arr, start, x-1, k);
        else return select5(arr, x+1, end, k);
    }
}

int select7(int arr[], int start, int end, int k)
{
    if(end-start<=6) {
        insertionSort(arr, start, end);
        return arr[k];
    }else {
        int i, m, x, index, median;
        m = (end-start+7)/7;
        index = 0;
        for(i=0;i<m;i++) {
            if(i==m-1 && start+i*7+6 > end) {
                insertionSort(arr, start+i*7, end);
                if(start+i*7+3<=end) {
                    swap(arr, start+index, start+i*7+3);
                    index++;
                }
            }else {
                insertionSort(arr, start+i*7, start+i*7+6);
                swap(arr, start+index, start+i*7+3);
                index++;
            }
        }
        m = start + ((index-1)/2);
        median = select7(arr, start, start+index-1, m);
        for(i=start;i<=start+index-1;i++) {
            if(arr[i]==median) {
                swap(arr, i, end);
                break;
            }
        }
        x = partition(arr, start, end);
        if(x==k) return arr[k];
        else if(x>k) return select7(arr, start, x-1, k);
        else return select7(arr, x+1, end, k);
    }
}

int select9(int arr[], int start, int end, int k)
{
    if(end-start<=8) {
        insertionSort(arr, start, end);
        return arr[k];
    }else {
        int i, m, x, index, median;
        m = (end-start+9)/9;
        index = 0;
        for(i=0;i<m;i++) {
            if(i==m-1 && start+i*9+8 > end) {
                insertionSort(arr, start+i*9, end);
                if(start+i*9+4<=end) {
                    swap(arr, start+index, start+i*9+4);
                    index++;
                }
            }else {
                insertionSort(arr, start+i*9, start+i*9+8);
                swap(arr, start+index, start+i*9+4);
                index++;
            }
        }
        m = start + ((index-1)/2);
        median = select9(arr, start, start+index-1, m);
        for(i=start;i<=start+index-1;i++) {
            if(arr[i]==median) {
                swap(arr, i, end);
                break;
            }
        }
        x = partition(arr, start, end);
        if(x==k) return arr[k];
        else if(x>k) return select9(arr, start, x-1, k);
        else return select9(arr, x+1, end, k);
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

void HeapSort(int arr[], int size) {
    for(int i = size/2-1;i>=0;i--) maxHeapify(arr, i, size);
    for(int j = size-1;j>0;j--) {
        int temp = arr[0];
        arr[0] = arr[j];
        arr[j] = temp;
        maxHeapify(arr, 0, j);
    }
}

void maxHeapify(int arr[], int i, int size) {
    int l, r, largest;

    if(i*2+1 < size) {
        l = i*2+1;
        if(i*2+2 < size) r = i*2+2;
        else r = -1;
        if(arr[l] > arr[i]) largest = l;
        else largest = i;
        if(r != -1 && (arr[r] > arr[largest]) ) largest = r;
        if(largest != i) {
            int temp = arr[i];
            arr[i] = arr[largest];
            arr[largest] = temp;
            maxHeapify(arr, largest, size);
        }
    }
}
