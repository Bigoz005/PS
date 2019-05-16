using System;
using System.IO;
using System.Net;
using System.Net.Sockets;

namespace ClientECHOTCP
{
    class TcpEchoClient
    {

        static void Main(string[] args)
        {
            Console.WriteLine("Starting echo client...");

            int port = 0;

            Console.Write("Port: ");
            port = Convert.ToInt32(Console.ReadLine());
            TcpClient client = new TcpClient("localhost", port);

            NetworkStream stream = client.GetStream();           

            StreamReader reader = new StreamReader(stream);
            StreamWriter writer = new StreamWriter(stream) { AutoFlush = true };
            Console.WriteLine("Connection established.");

            while (true)
            {
                Console.Write("Enter text to send: ");
                string lineToSend = Console.ReadLine();
                Console.WriteLine("Sending to server: " + lineToSend);
                writer.WriteLine(lineToSend);
                if(lineToSend == "end") { break; }
                string lineReceived = reader.ReadLine();
                Console.WriteLine("Received from server: " + lineReceived);
            }

            stream.Close();
            stream.Dispose();
        }
    }
}
