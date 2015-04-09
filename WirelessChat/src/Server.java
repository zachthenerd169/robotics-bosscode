import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;

class Server {
	
   public static void main(String args[]) {
      String data = "Toobie ornaught toobie";
      try {
    	  Scanner input = new Scanner(System.in);
         ServerSocket srvr = new ServerSocket(1234);
         Socket skt = srvr.accept();
         BufferedReader in = new BufferedReader(new
                 InputStreamReader(skt.getInputStream()));
         PrintWriter out = new PrintWriter(skt.getOutputStream(), true);
         
         System.out.print("Server has connected!\n");
         
         while (true)
         {
        	 System.out.print("Paul: ");
        	 data = input.nextLine();
        	 
        	 if (data.startsWith("/exit"))
        	 {
        		 break;
        	 }
        	 else
        	 {
                 out.println(data);
        	 }
        	 
//             System.out.println(in.readLine()); // Read one line and output it
         }
         
         out.close();
         skt.close();
         srvr.close();
      }
      catch(Exception e) {
         System.out.print("Whoops! It didn't work!\n");
      }
   }
}
