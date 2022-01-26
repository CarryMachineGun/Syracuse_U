#include <iostream>


void printArray(int arr[], int size){
    int i; 
    for (i = 0; i < size; i++) 
        std::cout << arr[i] << " "; 
    std::cout << std::endl; 

    return;
}

void bubbleSort(int arr[], int size){

    int dummy = 0;

    for(int i = size - 1 ; i >=0; i--){
        for(int j = 0; j < i; j++){
            if(arr[j] > arr[j+1]){
                dummy = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = dummy;
    printArray(arr, size);
            }
        }
    }

    return;

}


int main(){
    int arr[] = {3,60,35,2,45,320,5};
    int size = sizeof(arr)/sizeof(arr[0]);

    std::cout << "array size = " << sizeof(arr) << " and " << sizeof(arr[0]) << std::endl;

    bubbleSort(arr, size);

    // printArray(arr, size);

    return 0;

}