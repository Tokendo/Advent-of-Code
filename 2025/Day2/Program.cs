using System;
class Program
{

    static void Main()
    {
        //load input file
        StreamReader reader = new StreamReader("input.txt");
        string line;
        string[] valuesList;

        line = reader.ReadLine();
        valuesList = line.Split(',');
        long  totalInvalid = 0;
        foreach (string id in valuesList)
        {
            line = id;
            string first = "", last = "";
            bool separated = false;
            for (int i = 0; i < line.Length; i++)
            {
                if (line[i] == '-')
                {
                    separated = true;
                    continue;
                }
                if (!separated)
                    first += line[i];
                else
                    last += line[i];
            }
            long lastID = long.Parse(last);

            for (long i = long.Parse(first); i <= lastID; i++)
            {
                string currentID = i.ToString();
                if (!isIDValid(currentID))
                {
                    Console.WriteLine("ID invalide: " + currentID);
                    totalInvalid += i;
                }
            }

            Console.WriteLine("occurences de zéro:");
        }
        Console.WriteLine("fin, total="+ totalInvalid.ToString());
        static bool isIDValid(string id)
        {
            int length= id.Length;
            int mid = length / 2;
            int count = 0, particleCount=0;
            string particle = "";
            string[] particleList= new string[50];
            for (int i = 1; i <= mid; i++)
            {
                //i is the length of the particle
                if(length%i!=0)
                    continue;
                count=length/i-1;
                particle = id.Substring(0, i);
                particleList = new string[50];
                particleCount = 0;
                for (int j = i; j <= length - i; j += i)
                {
                    string nextParticle = id.Substring(j, i);
                    if (nextParticle == particle)
                    {
                        particleCount++;
                    }
                }

                if (particleCount==count)
                {
                    return false;
                }


            }

            return true;
        }
    }
}