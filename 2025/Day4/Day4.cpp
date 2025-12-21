// Day4.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>

int main()
{
	std::ifstream inputFile("input.txt");
	std::string map = "";
	std::string line = "";
	bool firstLine = true;
	int lineLength = 0;
	int y = 0;
	static bool arrIn[1000][1000] = { 0 };
	static int arrOut[1000][1000] = { 0 };
	printf("Reading file line by line:\n");
	while (std::getline(inputFile, line)) {
		if (firstLine) {
			lineLength = line.length();
			firstLine = false;
			for (size_t i = 0; i < lineLength + 2; i++)
			{

				map += ".";
				arrIn[y][i] = false;
			}
			map += "\n";
			y++;
		}
		map += "." + line + ".\n";
		arrIn[y][0] = false;
		for (size_t i = 0; i < lineLength; i++)
		{
			arrIn[y][i + 1] = line[i] == '@' ? true : false;
		}
		arrIn[y][lineLength + 2] = false;
		y++;
	}
	for (size_t i = 0; i < lineLength + 2; i++)
	{
		map += ".";
		arrIn[y][i] = 0;
	}

	inputFile.close();

	map = "";
	int nbRemoved = 0, thisPassRemoved = 0;
	auto start = std::chrono::high_resolution_clock::now();
	do
	{
		thisPassRemoved = 0;
		for (size_t i = 1; i < y; i++)
		{
			for (size_t j = 1; j < lineLength + 1; j++)
			{
				if (arrIn[i][j] == true)
				{
					int count = 0;
					if (arrIn[i - 1][j - 1]) count++;
					if (arrIn[i - 1][j]) count++;
					if (arrIn[i - 1][j + 1]) count++;
					if (arrIn[i][j - 1]) count++;
					if (arrIn[i][j + 1]) count++;
					if (arrIn[i + 1][j - 1]) count++;
					if (arrIn[i + 1][j]) count++;
					if (arrIn[i + 1][j + 1]) count++;
					if (count < 4)
					{
						arrOut[i][j] = 0;
						map += "x";
						nbRemoved++;
						thisPassRemoved++;

					}
					else
					{
						arrOut[i][j] = 1;
						map += "@";
					}
				}
				else
				{
					arrOut[i][j] = 0;
					map += ".";
				}
			}
			map += "\n";
		}
		for (size_t k = 0; k < y; k++)
		{
			for (size_t l = 0; l < lineLength + 1; l++)
			{
				arrIn[k][l] = arrOut[k][l] == 1;
			}

		}
		map += "\n";
		map += "\n";

	} while (thisPassRemoved > 0);

	auto elapsed = std::chrono::high_resolution_clock::now() - start;


	printf("Number of changes: %d\n", nbRemoved);
	map += std::to_string(nbRemoved)+"\n";
	map += "Time taken (ms): " + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count()) + "\n";

	std::ofstream outputFile("output.txt");
	outputFile << map;
	outputFile.close();
	printf("Finished processing.\n");


}

void checkNeighbour(int x, int y, int* arrptr)
{

}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
