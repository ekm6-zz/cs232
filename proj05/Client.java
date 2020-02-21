/* Client.java defines the Client class
 * Purpose: send string to server and echo output
 * Usage: <hostName> <portNumber> 
 * Input: user string
 * Output: caeser chipher of user string
 * 
 * Name: Enoch Mwesigwa
 * Date: 5/6/19
 *  */
import java.io.*;
import java.net.*;
import java.util.Scanner;
 
public class Client {
    public static void main(String[] args) throws IOException {
        
        //makes sure commandline input is valid
        if (args.length != 2) {
            System.err.println(
                "Usage: java Client <host name> <port number>");
            System.exit(1);
        }
 
        String hostName = args[0];
        int portNumber = Integer.parseInt(args[1]);
        
        //creates I/0 objects for socket
		try 
		(   
            Socket mySocket = new Socket(hostName, portNumber);
            PrintWriter out =
                new PrintWriter(mySocket.getOutputStream(), true);
            BufferedReader in =
                new BufferedReader(
                    new InputStreamReader(mySocket.getInputStream()));
            BufferedReader stdIn =
                new BufferedReader(
                    new InputStreamReader(System.in))
		) 
		{	
			System.out.println("Welcome to the the Ceaser Cipher v1.0");
			System.out.println("Enter the rotation number:");
            String userInput;
            
            //loop runs until user enters "quit"
            while ( !(userInput = stdIn.readLine()).equals("quit") ) {
				out.println(userInput);
                System.out.println( "Ciphered: " + in.readLine());
                out.flush();
            }
		} 
		catch (UnknownHostException e) {
            System.err.println(hostName + " at port number " + portNumber + " was unfound");
            System.exit(1); } 
		catch (IOException e) {
            System.err.println("Invalid entry for to " +
                hostName);
            System.exit(1); } 
    }
}