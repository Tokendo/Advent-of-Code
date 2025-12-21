using System;
class Program
{

    static void Main()
    {
        //load input file
        StreamReader reader = new StreamReader("input.txt");

        //read file line by line
        string line;
        long totalJolt = 0;
        while ((line = reader.ReadLine()) != null)
        {
            totalJolt += getMaxJolt(line);
            Console.WriteLine(line);
        }
        Console.WriteLine("Total Jolt: " + totalJolt);
    }
    static long getMaxJolt(string battery)
    {
        int max = 0, maxIndex = 0, current = 0;
        string number = "";
        
        for (int j = 0; j < 12; j++)
        {
            for (int i = maxIndex; i < battery.Length - (11 - j); i++)
            {
                current = int.Parse(battery[i].ToString());
                if (current > max)
                {
                    max = current;
                    maxIndex = i;
                    if (current == 9)
                    { break; }
                }
            }
            maxIndex += 1;
            number += max.ToString();
            max = 0;
        }
        return Convert.ToInt64(number);
    }
}