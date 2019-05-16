using System;
using System.Net;
using System.Net.Sockets;
using System.IO;
using System.Text;

namespace ServerECHOTCP
{
    public class TcpEchoServer
    {
        public static void Main()
        {
            Console.WriteLine("Starting echo server...");

            int port = 0;
            Console.Write("Port: ");
            port = Convert.ToInt32(Console.ReadLine()); ;
            TcpListener listener = new TcpListener(IPAddress.Any, port);
            listener.Start();

            TcpClient client = listener.AcceptTcpClient();
            NetworkStream stream = client.GetStream();
            StreamWriter writer = new StreamWriter(stream, Encoding.ASCII) { AutoFlush = true };
            StreamReader reader = new StreamReader(stream, Encoding.ASCII);
            var clientPort = ((IPEndPoint)client.Client.RemoteEndPoint).Port;
            while (true)
            {
                Console.WriteLine("Client connected with IP {0} on port {1}", ((IPEndPoint)client.Client.RemoteEndPoint).Address, port);
                string inputLine = "";
                while (inputLine != null)
                {
                    inputLine = reader.ReadLine();
                    if (inputLine == "end") { break; }
                    writer.WriteLine("Echoing string: " + inputLine);
                    Console.WriteLine("Echoing string: " + inputLine);
                }
                if (inputLine == "end") { break; }
            }
            Console.WriteLine("Server saw disconnect from client.");
            listener.Stop();
            stream.Close();
            stream.Dispose();
        }
    }
}
