// C# program to illustrate the creation 
// of thread using static method 
using System;
using System.Threading;

public class ExThread
{
    // Static method for thread a 
    public static void thread1()
    {
            Console.WriteLine("Hello World");   
    }

}

// Driver Class 
public class GFG
{

    // Main method 
    public static void Main()
    {
        // Creating and initializing threads 
        Thread a = new Thread(ExThread.thread1);
        a.Start();

        a.Join();
        Console.WriteLine("Joined");
        System.Threading.Thread.Sleep(5000);
    }
}