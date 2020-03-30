

/**
 * Hello
 */
public class Project1 {

    public static String padLeftZeros(String str, int n) {
        return String.format("%1$" + n + "s", str).replace(' ', '0');
    }

    public static void main(String[] args) {
        long startTime = System.currentTimeMillis();
        char[] arr = new char[] { '1', '2', 'a', 'b', '5', 'd', 'c', '4' }; //32 bit long message
        char[] arr_rep = new char[arr.length];  //used for shuffling
        char[] arr_rep2 = new char[arr.length]; //used for shuffling
        String plaintext = new String(arr);
        String hex = "1111";//"12a24b21";   //key
        hex = padLeftZeros(hex, 8);
        System.out.println("Key: "+hex);
        char[] key = hex.toCharArray();
        for (int i = 0; i < arr.length; i++) {
            String s = String.valueOf(arr[i]);
            String s1 = String.valueOf(key[i]);
            // System.out.println(s+" "+s1);
            String temp = Integer.toHexString((Integer.parseInt(s, 16) + Integer.parseInt(s1, 16)) % 16);
            arr[i] = temp.charAt(0);

        }
        
        arr_rep[0] = arr[2];
        arr_rep[1] = arr[3];
        arr_rep[2] = arr[1];
        arr_rep[3] = arr[7];
        arr_rep[4] = arr[6];
        arr_rep[5] = arr[5];
        arr_rep[6] = arr[4];
        arr_rep[7] = arr[0];

        arr_rep2[0] = arr_rep[7];
        arr_rep2[1] = arr_rep[2];
        arr_rep2[2] = arr_rep[3];
        arr_rep2[3] = arr_rep[5];
        arr_rep2[4] = arr_rep[1];
        arr_rep2[5] = arr_rep[6];
        arr_rep2[6] = arr_rep[0];
        arr_rep2[7] = arr_rep[4];

        arr_rep[0] = arr_rep2[5];
        arr_rep[1] = arr_rep2[4];
        arr_rep[2] = arr_rep2[6];
        arr_rep[3] = arr_rep2[0];
        arr_rep[4] = arr_rep2[2];
        arr_rep[5] = arr_rep2[3];
        arr_rep[6] = arr_rep2[7];
        arr_rep[7] = arr_rep2[1];

        long endTime = System.currentTimeMillis();
        System.out.print("Encrytion Time (in ms):");
        System.out.println(endTime - startTime);

        /// decryption
        startTime = System.currentTimeMillis();
        arr_rep2[0] = arr_rep[3];
        arr_rep2[1] = arr_rep[7];
        arr_rep2[2] = arr_rep[4];
        arr_rep2[3] = arr_rep[5];
        arr_rep2[4] = arr_rep[1];
        arr_rep2[5] = arr_rep[0];
        arr_rep2[6] = arr_rep[2];
        arr_rep2[7] = arr_rep[6];

        arr_rep[1] = arr_rep2[4];
        arr_rep[0] = arr_rep2[6];
        arr_rep[2] = arr_rep2[1];
        arr_rep[3] = arr_rep2[2];
        arr_rep[4] = arr_rep2[7];
        arr_rep[5] = arr_rep2[3];
        arr_rep[6] = arr_rep2[5];
        arr_rep[7] = arr_rep2[0];

        arr[0] = arr_rep[7];
        arr[1] = arr_rep[2];
        arr[2] = arr_rep[0];
        arr[3] = arr_rep[1];
        arr[4] = arr_rep[6];
        arr[5] = arr_rep[5];
        arr[6] = arr_rep[4];
        arr[7] = arr_rep[3];

        String n = "";
        int count = 0;
        char[] arr3 = new char[arr.length];
        
        while (!n.equals(plaintext)) {
            String hex_try = Integer.toHexString(count);
            hex_try = padLeftZeros(hex_try, 8);
            key = hex_try.toCharArray();
            for (int i = 0; i < arr.length; i++) {
                String s = String.valueOf(arr[i]);
                String s1 = String.valueOf(key[i]);

                String temp = "";
                if ((Integer.parseInt(s, 16) - Integer.parseInt(s1, 16)) < 0) {
                    temp = Integer.toHexString((Integer.parseInt(s, 16) - Integer.parseInt(s1, 16)) + 16);
                } else {
                    temp = Integer.toHexString((Integer.parseInt(s, 16) - Integer.parseInt(s1, 16)) % 16);
                }
                arr3[i] = temp.charAt(0);
            }
            n = new String(arr3);
            count++;

            // System.out.println(n);
        }
        endTime = System.currentTimeMillis();
        System.out.print("Brute Force(in ms):");
        System.out.println(endTime - startTime);

        
    }
}
