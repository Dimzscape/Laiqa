class Solution {
    public int balancedString(String s) {
      int n = s.length();
      int character = n/4;
      int[] count = new int[128];
      for(char c : s.toCharArray()){
        count[c]++;
      }  
      //s.toCharArray() converts the String s into a char[] array. For example, "QQQW".toCharArray() becomes ['Q', 'Q', 'Q', 'W'].
      if(count['Q']<=character && count['W']<=character && count['E']<=character && count['R']<=character){
        return 0;
      }
      int left=0;
      int result = n;
      int right;

      for(right=0; right < n; right++){
        count[s.charAt(right)]--;

        while(left<=right && count['Q'] <=character && count['W']<=character && count['E']<=character && count['R']<=character){
            result = Math.min(result, right-left+1);
            //right - left + 1 is the length of the current valid window. We compare this new valid window's length to our best answer so far (result), and keep whichever is smaller.

            //Math.min ensures we never accidentally replace a good (small) answer with a worse (bigger) one — we only keep improving, never regressing.

            count[s.charAt(left)]++;
            left++;
        }
      }
      return result;

    }
}