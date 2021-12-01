package interview.Cisco;

import java.io.*;

class MaximumSubarray_2 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int count = Integer.valueOf(br.readLine());
        int nums[] = new int[count];

        for (int i = 0; i < count; i++)
            nums[i] = Integer.valueOf(br.readLine());

        int max = nums[0], sum = 0;

        for (int i : nums) {
            if (sum < 0)
                sum = i;
            else
                sum += i;

            if (sum > max)
                max = sum;
            // System.out.println(i);
        }

        System.out.println(max);

        return;
    }
}