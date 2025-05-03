using System;
using System.Threading;

class Helloworld
{
    static void Main()
    {
     
        Thread even = new Thread(PrintEvenNumbers);
        Thread odd = new Thread(PrintOddNumbers);

      
        even.Start();
        odd.Start();

        
        even.Join();
        odd.Join();
        
         
        Console.WriteLine("The code is  successfully Run");
    }

    static void PrintEvenNumbers()
    {
        Console.WriteLine("Question is:Write a program that creates two threads: one prints even numbers from 2 to 10 and the other prints odd numbers from 1 to 9. Use Thread.Sleep() to simulate delay.\n");
        
        
        for (int i = 2; i <= 10; i += 2)
        {
          
            Console.WriteLine($"Even number is: {i}");
            Thread.Sleep(500); 
        }
    }

    static void PrintOddNumbers()
    {
        for (int i = 1; i <= 9; i += 2)
        {
            Console.WriteLine($"Odd number is: {i}");
            Thread.Sleep(500); 
        }
    }
}
