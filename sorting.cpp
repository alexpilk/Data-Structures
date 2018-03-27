#include <iostream>
#include <vector>

using namespace std;

//void quickSort(int arr[], int left, int right) {
//    int i = left, j = right;
//    int tmp;
//    int pivot = arr[(left + right) / 2];
//
//    /* partition */
//    while (i <= j) {
//        while (arr[i] < pivot)
//            i++;
//        while (arr[j] > pivot)
//            j--;
//        if (i <= j) {
//            tmp = arr[i];
//            arr[i] = arr[j];
//            arr[j] = tmp;
//            i++;
//            j--;
//        }
//    };
//
//    /* recursion */
//    if (left < j)
//        quickSort(arr, left, j);
//    if (i < right)
//        quickSort(arr, i, right);
//}

void print_array(double* arr, int size){
    cout << '[';
    for (int i = 0; i < size-1; i++) {
        cout << arr[i] << ", ";
    }
    cout << arr[size-1] << ']' << endl;
}

void quickSort(double arr[], int left, int right) {
    double tmp;
    int i = left;
    int j = right;
    int pivot_index = (left + right) / 2;
    double pivot_element = arr[pivot_index];
    cout << "pivot index: " << pivot_index <<  " pivot value " << pivot_element << endl;
    while (true){
        while(arr[i]<pivot_element)
            i++;
        while(arr[j]>pivot_element)
            j--;
        print_array(arr, 10);
        if (i>=j)
            break;
        tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
        i++; j--;
    }
    cout << "i: " << i <<  " j: " << j << endl;
    if(left < j) {
        cout << "going left " << endl;
        quickSort(arr, left, j);
    }
    if(i < right) {
        cout << "going right " << endl;
        quickSort(arr, i, right);
    }
}

void insertion_sort(double* arr, int size){
    if(size > 1) {  // 1-element list is sorted already
        for (int i = 1; i < size; i++) {
            if(arr[i] < arr[i-1]){
                double element_to_insert = arr[i];
                int insert_index = 0;  // if no index will be found - insert at the beginning
                for (int j = i-1; j > 0 ; j--) {  // find insert index
                    if(arr[j-1] < element_to_insert){
                        insert_index = j;
                        break;
                    }
                }
                for (int k = i; k > insert_index; k--) {  // move affected elements forward
                    arr[k] = arr[k-1];
                }
                arr[insert_index] = element_to_insert;  // insert element
            }
        }
    }
}

void bucket_sort(double* arr, int size){
    vector<vector<double>> buckets(size);
    for (int i = 0; i < size; i++) {
        buckets[int(arr[i]*size)].push_back(arr[i]);
    }
    for (int i = 0; i < size; i++) {
        insertion_sort(&buckets[i][0], buckets[i].size());
    }

    int i = 0;
    for (int bucket_index = 0; bucket_index < size; bucket_index++) {
        for (int j = 0; j < buckets[bucket_index].size(); j++) {
            arr[i] = buckets[bucket_index][j];
            i++;
        }
    }
}
int main() {
    int array_length = 10;
//    double arr[] = {4,5,63,4,5,6,7,3,5,4};
//    quickSort(arr, 0, 9);
//    insertion_sort(arr, array_length);
    double arr[] = {0.2, 0.34, 0.63, 0.4, 0.5, 0.6, 0.7, 0.3, 0.53, 0.43};
    bucket_sort(arr, array_length);
    print_array(arr, array_length);
    return 0;
}
