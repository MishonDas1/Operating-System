using System;
using System.Threading;

class ProducerConsumer
{
    private static readonly int BufferSize = 5;
    private static int[] buffer = new int[BufferSize];
    private static int inIndex = 0;
    private static int outIndex = 0;

    // Semaphores
    private static Semaphore empty = new Semaphore(BufferSize, BufferSize); // initially all slots empty
    private static Semaphore full = new Semaphore(0, BufferSize);           // initially no full slots
    private static Mutex mutex = new Mutex();                               // for mutual exclusion

    // Producer thread method
    public static void Producer()
    {
        Random rand = new Random();
        while (true)
        {
            int item = rand.Next(100); // Produce a random item

            empty.WaitOne();          // Wait for an empty slot
            mutex.WaitOne();          // Enter critical section

            buffer[inIndex] = item;
            Console.WriteLine($"Produced: {item} at {inIndex}");
            inIndex = (inIndex + 1) % BufferSize;

            mutex.ReleaseMutex();     // Exit critical section
            full.Release();           // Signal that a new item is available

            Thread.Sleep(500);        // Simulate work
        }
    }

    // Consumer thread method
    public static void Consumer()
    {
        while (true)
        {
            full.WaitOne();           // Wait for an available item
            mutex.WaitOne();          // Enter critical section

            int item = buffer[outIndex];
            Console.WriteLine($"\tConsumed: {item} from {outIndex}");
            outIndex = (outIndex + 1) % BufferSize;

            mutex.ReleaseMutex();     // Exit critical section
            empty.Release();          // Signal that a slot is free

            Thread.Sleep(800);        // Simulate work
        }
    }

    static void Main()
    {
        Thread producerThread = new Thread(Producer);
        Thread consumerThread = new Thread(Consumer);

        producerThread.Start();
        consumerThread.Start();

        producerThread.Join();
        consumerThread.Join();
    }
}
