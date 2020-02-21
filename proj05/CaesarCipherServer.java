/* CaesarCipher.java defines the CaesarCipherServer class
 *
 * usage: <portNumber>
 * Input: user string
 * Output: caeser chipher of user string
 * 
 * Name: Enoch Mwesigwa
 * Date: 5/6/19
 *  */
import java.awt.SystemTray;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;

import java.net.ServerSocket;
import java.net.Socket;
import java.text.SimpleDateFormat;
import java.util.Calendar;
 
public class CaesarCipherServer {
   ServerSocket myServerSocket;
   boolean ServerOn = true;

   public CaesarCipherServer(int portNumber) { 
      
      //creates a parent socket
      try {
         myServerSocket = new ServerSocket(portNumber);
         System.out.println("Sever connected to port " + portNumber + " successfully\n");
      } catch(IOException ioe) { 
         System.out.println("Error: unable create server socket on port" + portNumber + " exiting...");
         System.exit(-1);
      } 
		
      
      
      while(ServerOn) { 
         try 
         { 
            System.out.println("Searching...");
            Socket clientSocket = myServerSocket.accept();              //accepts client connection
            System.out.println("Found a client...");
            CipherThread cliThread = new CipherThread(clientSocket);    //creates child socket
            cliThread.start(); 
         } 
         catch(IOException ioe) {    
            System.out.println("Error: exception found on accept. Ignoring. Stack Trace :"); 
            ioe.printStackTrace(); 
         }  
      } 

      try { 
         myServerSocket.close(); 
         System.out.println("Server Stopped"); 
      } catch(Exception ioe) { 
         System.out.println("Error: unable to stop server socket"); 
         System.exit(-1); 
      } 
   }
	
   public static void main (String[] args) {
      System.out.println("CaesarCipherServer v.1 started...\n");
      int portNumber = Integer.parseInt(args[0]); 
      new CaesarCipherServer(portNumber);        
   } 
   
   //defines children class of socket
   class CipherThread extends Thread { 
      Socket myClientSocket;
      boolean ThreadRuning = true; 
      public CipherThread() { 
         super(); 
      } 
		
      CipherThread(Socket s) { 
         myClientSocket = s; 
      } 
      
      /* run() recieves a number from the client,
       * if its valid, it sends it back and calls
       * encrypt() to encode futher input from the client
       * if not valid, terminates thread
       * preconditon: thread is created
       * postcondition: 
      */
      public void run() {
         
         //displays time
         Calendar now = Calendar.getInstance();
         SimpleDateFormat formatter = new SimpleDateFormat( "E yyyy.MM.dd 'at' hh:mm:ss a zzz" );
         System.out.println("Time is : " + formatter.format(now.getTime()));

         BufferedReader in = null; 
         PrintWriter out = null; 
         int rotNum = 3;
         System.out.println( "Accepted Client Address - " + myClientSocket.getInetAddress().getHostName() );
         try 
         { 
            //initialize varibales to be used in loop
            in = new BufferedReader( new InputStreamReader(myClientSocket.getInputStream()) );
            out = new PrintWriter( new OutputStreamWriter(myClientSocket.getOutputStream()) );
            boolean rotNumNotSet = true;
            String clientInput= "*****";
            while(ThreadRuning) { 
               
               //checks if the rotation number is valid
               if( rotNumNotSet)
               {
                  clientInput = in.readLine(); 
                  System.out.println( "Recieved input: " + clientInput);

                  if ( clientInput.matches("-?\\d+(\\.\\d+)?") ) {
                     rotNum = Integer.parseInt(clientInput);

                     System.out.print("Input is an integer...\n");
   
                     if (rotNum < 27 && rotNum > 0 ) {  
                        System.out.println("Input is within 1 and 26...\n");
                        out.println(clientInput);                                   //sends it back to client
                        rotNumNotSet = false;                                       // signifies that the rotation number is set
                        out.flush();                                                          // if statement won't run on future loops
                     }
                     else {  
                        System.out.println("Value is not within 1-26.\nClosing thread.");
                        out.println("Value is not within 1-26. Closing thread....");
                        out.flush();
                        ThreadRuning = false;                                            //terminates thread
                     }
                  } 
                  else
                  {  
                     System.out.println("Value is not an integer. \nClosing thread");
                     out.println("Value is not an integer. Closing thread...");
                     out.flush();
                     ThreadRuning = false;                                             //terminates thread
                  }
               }

 
               
               System.out.println( "*******");
               clientInput = in.readLine(); 

              //terminates if clent sends "quit"
              if(clientInput.equalsIgnoreCase("quit")) {                          
               ThreadRuning = false;
               System.out.print("Stopping client thread for client : ");
            }
            
               System.out.println( "Recieved input: " + clientInput);
               System.out.println("encrypting...\n");

               StringBuffer text;
               text = encrypt(clientInput, rotNum);
               
               System.out.println("sending...\n");
               
               out.println(text);
               out.flush();
               
               System.out.println("Completed...\n ");
               System.out.println( "*******");

            } 
            
         } 
         catch(Exception e) { 
            e.printStackTrace(); 
         } 
         finally { 
            try { 
               in.close(); 
               out.close(); 
               myClientSocket.close(); 
               System.out.println("...Stopped"); 
            } catch(IOException ioe) { 
               ioe.printStackTrace(); 
            } 
         } 
      }

   /* encrypt() is a method that encripts a string into a caesar cipher
    * Recieve: String- message, int- num 
    * Return: encrypted stringBuffer "result"
   **************************************************************/
      public StringBuffer encrypt (String message, int num){
         
         StringBuffer result= new StringBuffer(); 
  
         for (int i=0; i<message.length(); i++) 
         { 
             if (Character.isUpperCase(message.charAt(i))) 
             { 
                 char ch = (char)(((int)message.charAt(i) + 
                                  num- 65) % 26 + 65); 
                 result.append(ch); 
             } 
             else
             { 
                 char ch = (char)(((int)message.charAt(i) + 
                                  num- 97) % 26 + 97); 
                 result.append(ch); 
             } 
         } 
         return result; 
         } 
   } 
}