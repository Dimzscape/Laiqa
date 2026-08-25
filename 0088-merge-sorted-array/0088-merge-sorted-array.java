class Solution {
    public void merge(int[] nums1, int m, int[] nums2, int n) {
        //m is elemst from first array nums1
        //n is element from second array nums2
        //i and j stores last elements of both the arrays.
        //k points towards the last index of both merged arrays.
       int i = m-1;
       int j = n-1;
       int k = m+n-1;

       while(j>=0){
        if(i>=0 && nums1[i]>nums2[j]){
            nums1[k]=nums1[i];
            i--;
        }
        else{
            nums1[k]=nums2[j];
            j--;
        }
        k--;
       } 
    }
}