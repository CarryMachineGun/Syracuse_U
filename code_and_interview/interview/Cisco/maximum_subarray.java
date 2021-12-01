package interview.Cisco;

import java.io.*;

class MaximumSubarray{
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int count = Integer.valueOf(br.readLine());
        String in[] = br.readLine().split(" ");        
        int nums[] = new int[in.length];

        for(int i = 0; i < in.length; i++) nums[i] = Integer.valueOf(in[i]);

        int max = nums[0], sum = 0;

        for(int i : nums){
            if(sum < 0) sum = i;
            else sum += i;

            if(sum > max) max = sum;
            // System.out.println(i);
        }

        System.out.println(max);

        return;
    }
}