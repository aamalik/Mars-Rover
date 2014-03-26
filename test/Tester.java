import java.net.Socket;
import java.io.*;
import java.util.*;
import java.net.UnknownHostException;

public class Tester {
	private static String host;
	private static int port;
	private static BufferedReader in;
	private static PrintWriter out;
	private static Socket client_socket;

	private static void initialize_socket() {
		try {
			client_socket = new Socket(host, port);
			in = new BufferedReader(
					new InputStreamReader(client_socket.getInputStream()));
			out = new PrintWriter(new BufferedWriter(
					new OutputStreamWriter(client_socket.getOutputStream())),true);
		} catch (UnknownHostException e) { 
			System.out.println("Unknown host! " + e.getMessage());
		} catch (IOException exc) {
			System.out.println("Socket connection failed!\n");
		}
	}
	public static void main(String args[]) {
		Scanner input = new Scanner(System.in);
		System.out.println("Enter host: ");
		if (input.hasNext()) {
			host = input.nextLine();
		}
		System.out.println("\nEnter port: ");
		if (input.hasNext()) {
			String port_field = input.nextLine();
			try {
					port = Integer.parseInt(port_field.trim());
				} catch (NumberFormatException exc) {
					System.out.println("Invalid port!\n");
			}
		}
		initialize_socket();
		//We are now connected to the server through host and port 
		//Enter commands
		System.out.println("You are now connected...\n");
		System.out.println("You can give commands to the rover...\n");

		while (true) {
			if (input.hasNext()) {
				String command = input.nextLine();	
				if (command.equals("exit")) {
					break;
				}
				out.print(command);
				out.flush();
			}
		}
	}
}
