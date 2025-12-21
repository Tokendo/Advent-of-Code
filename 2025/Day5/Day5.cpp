
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>

int main()
{
	std::ifstream inputFile("input.txt");
	std::string line = "";
	
	printf("Reading file line by line:\n");
	while (std::getline(inputFile, line)) {
		;
	}
	
	inputFile.close();

	auto start = std::chrono::high_resolution_clock::now();

	auto elapsed = std::chrono::high_resolution_clock::now() - start;

	std::ofstream outputFile("output.txt");
	outputFile << "output";
	outputFile.close();
	printf("Finished processing.\n");


}
