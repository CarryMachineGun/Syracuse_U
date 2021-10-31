package algorithms;
import java.io.*;

class main{
    public static void quickSort(int[] arr, int start, int end){
        if(start >= end){
            return;
        }

        int povit = arr[end], l_end = start, l = start, r = end;

        while(l < r){
            if(arr[l] < povit){
                int temp = arr[l];
                arr[l] = arr[l_end];
                arr[l_end] = temp;
                l_end++;
            }

            l++;
        }
           
        arr[r] = arr[l_end];
        arr[l_end] = povit;
        
        quickSort(arr, start, l_end -1);
        quickSort(arr, l_end+1, end);

        return;
    }   
    
    public static void main(String[] args) throws Exception{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String in[] = br.readLine().split(",");
        int arr[] = new int[in.length];

        for(int i = 0; i < in.length; i++){
            arr[i] = Integer.valueOf(in[i]);
        }

        quickSort(arr, 0, arr.length -1);

        for(int i : arr){
            System.out.print(i + ", ");
        }


        return;
    }
}
