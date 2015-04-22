import java.lang.*;
import java.io.*;
import java.net.*;

class Client {
   public static void main(String args[]) {
      try {
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
	