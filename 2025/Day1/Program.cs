using System;
class Program
{

    static void Main()
    {
        //load input file
        StreamReader reader = new StreamReader("input.txt");

        //read file line by line

        int actualValue = 50, nbOfZero = 0, clics = 0;
        string line, nb = "";
        while ((line = reader.ReadLine()) != null)
        {
            nb = "";
            for (int i = 1; i < line.Length; i++)
            { nb += line[i]; }
            clics = int.Parse(nb);
            if (line[0] == 'L')
                clics = -clics;

            nbOfZero += analyseLine(clics, actualValue, out actualValue);
        }
        Console.WriteLine("occurences de zéro:" + nbOfZero.ToString());

    }
    static int analyseLine(int clics, int actualValue, out int newCounterValue)
    {
        if(actualValue==0&&clics<0)
            actualValue += 100;

        actualValue += clics;
        int zeroPass = 0;

        while (actualValue >= 100 || actualValue < 0)
        {
            if (actualValue > 100)
            {
                actualValue -= 100;
                zeroPass++;
            }
            else if (actualValue < 0)
            {
                actualValue += 100;
                zeroPass++;
            }
            else if (actualValue == 100)
            {
                actualValue = 0;
                break;
            }
        }
        if (actualValue == 0)
        {
            zeroPass++;
        }
        newCounterValue = actualValue;
        return zeroPass;
    }


}
