using System;
using System.Net;
using System.Net.Sockets;
using System.Text;

namespace Server
{

	class Program
	{
		// Main Method 
		static void Main(string[] args)
		{
			ExecuteServer();
		}

		public static void ExecuteServer()
		{
			// Establish the local endpoint 
			// for the socket. Dns.GetHostName 
			// returns the name of the host 
			// running the application. 

			IPEndPoint localEndPoint = new IPEndPoint(IPAddress.Parse("192.168.100.9"), 1337);

			// Creation TCP/IP Socket using 
			// Socket Class Costructor 
			Socket listener = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

			try
			{

				// Using Bind() method we associate a 
				// network address to the Server Socket 
				// All client that will connect to this 
				// Server Socket must know this network 
				// Address 
				listener.Bind(localEndPoint);

				// Using Listen() method we create 
				// the Client list that will want 
				// to connect to Server 
				listener.Listen(1);

				while (true)
				{

					//Console.WriteLine("Waiting connection ... ");

					// Suspend while waiting for 
					// incoming connection Using 
					// Accept() method the server 
					// will accept connection of client 
					Socket clientSocket = listener.Accept();
					//Console.WriteLine("Connection Accepted");

					// Data buffer 
					byte[] bytes = new Byte[10];
					string data = null;

					int numByte = clientSocket.Receive(bytes);

					data = Encoding.Default.GetString(bytes, 0, numByte);

					string action;
					if (Int32.Parse(data) < 30)
					{
						action = "On";
					}
					else
					{
						action = "Off";
					}

					
					byte[] message = Encoding.Default.GetBytes(action);

					// Send a message to Client 
					// using Send() method 
					clientSocket.Send(message);
					Console.WriteLine($"Information received: {data}");
					// Close client Socket using the 
					// Close() method. After closing, 
					// we can use the closed Socket 
					// for a new Client Connection 
					//clientSocket.Shutdown(SocketShutdown.Both);
					clientSocket.Close();
				}
			}

			catch (Exception ex)
			{
				Console.WriteLine(ex.ToString());
			}
		}
	}
}