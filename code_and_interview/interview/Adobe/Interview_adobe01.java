package interview.Adobe;
import java.io.*;
import java.util.*;


class MyCode {
	private static String makeKey(String s){
        char arr[] = s.toCharArray();
        //I change the line below from Arrays.sort(arr, (a, b) -> (a - b));
        Arrays.sort(arr);
        
        return String.valueOf(arr);
      }
  
  public static void main (String[] args) {
		System.out.println("Hello Java");
    
    String in[] = {"god", "cat", "act", "foo", "dog", "tac"};
    
    //I change the line below from Map<LinkedList<String>> map = new HashMap<>();
    Map<String, LinkedList<String>> map = new HashMap<>();
    
    for(String i : in){
      String key = makeKey(i);
      
      if(!map.containsKey(key)){
        map.put(key, new LinkedList<>());
      }
      
      map.get(key).add(i);
    }
    
    for(LinkedList i : map.values()){

        //I change the line below from System.out.printn
        System.out.println(i);
    }
    
    return;
    
	}
}

