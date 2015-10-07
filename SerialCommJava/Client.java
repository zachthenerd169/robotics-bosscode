import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.Socket;
import java.util.Scanner;

class Client {
	public static String paulip = "192.168.137.1";
	public static String ip = "172.17.57.104";
	
   public static void main(String args[]) {
	   
      try {
    	  Scanner type = new Scanner(System.in);
    	  System.out.print("IP: ");
    	  ip = type.nextLine();
    	  
    	  
         Socket skt = new Socket("127.0.0.1", 1234);
         BufferedReader in = new BufferedReader(new
            InputStreamReader(skt.getInputStream()));
         System.out.print("Received string: '");

         while (!in.ready()) {}
         
         while (true)
         {
        	 String input = in.readLine();
        	 System.out.println("Paul: " + input); // Read one line and output it
        	 
        	 if (input.startsWith("-exit"))
        	 {
        		 break;
        	 }
         }

         System.out.print("'\n");
         in.close();
      }
      catch(Exception e) {
         System.out.print("Whoops! It didn't work!\n");
      }
   }
}
	