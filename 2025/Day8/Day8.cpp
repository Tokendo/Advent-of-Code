#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <chrono>

struct  ElectricBox
{
	long circuitID = 0;
	long long positionX = 0;
	long long positionY = 0;
	long long positionZ = 0;
	std::vector<int>vConnections;
};


const int  inputHeight = 1100;
static std::vector<std::string> vInputStr;
static std::vector<ElectricBox> vElectricBox;
static std::vector<int> vCircuitBoxCount;
static  std::vector< std::vector<long long>> distances;
int boxCount = 0, shortestDistBox1ID = 0, shortestDistBox2ID = 0, mergeCount = 1, shortestIndex = 0;;
long circuitCount = 0;

void readFile(std::string inputFileName)
{
	std::ifstream inputFile(inputFileName.c_str());
	std::string line = "";

	while (std::getline(inputFile, line)) {
		vInputStr.push_back(line);
		boxCount++;
	}
	inputFile.close();
}

void setupElectricBoxes()
{
	long long posX = 0, posY = 0, posZ = 0;
	int length = 0, comaCount = 0;

	for (size_t i = 0; i < boxCount; i++)
	{
		length = vInputStr[i].length();
		comaCount = 0;
		std::string numStr = "";
		for (size_t j = 0; j < length; j++)
		{
			if (vInputStr[i][j] == ',')
			{
				if (comaCount == 0)
					posX = std::stoll(numStr);
				else if (comaCount == 1)
					posY = std::stoll(numStr);
				comaCount++;
				numStr = "";
			}
			else if (int(vInputStr[i][j]) >= 48 && int(vInputStr[i][j]) <= 57)
			{
				numStr += vInputStr[i][j];
			}
			else
			{
				break;
			}

		}
		posZ = std::stoll(numStr);
		vElectricBox.push_back(ElectricBox());
		vElectricBox[i].circuitID = i;
		vCircuitBoxCount.push_back(1);
		vElectricBox[i].positionX = posX;
		vElectricBox[i].positionY = posY;
		vElectricBox[i].positionZ = posZ;
		circuitCount++;
	}
}

long long calculateDistanceBetweenBoxes(int box1ID, int box2ID)
{
	long long distance = 0;
	long long posX1 = vElectricBox[box1ID].positionX;
	long long posY1 = vElectricBox[box1ID].positionY;
	long long posZ1 = vElectricBox[box1ID].positionZ;
	long long posX2 = vElectricBox[box2ID].positionX;
	long long posY2 = vElectricBox[box2ID].positionY;
	long long posZ2 = vElectricBox[box2ID].positionZ;
	long long dX2 = (posX1 - posX2) * (posX1 - posX2);
	long long dY2 = (posY1 - posY2) * (posY1 - posY2);
	long long dZ2 = (posZ1 - posZ2) * (posZ1 - posZ2);
	

	distance = std::round(1000*std::sqrt(dX2  + dY2 + dZ2));

	if (distance < 0)
	{
		printf("overflow");
	}
	return distance;
}

void calculateAllDistances()
{
	int index = 0;
	std::string outstr = "";
	for (size_t i = 0; i < boxCount-1; i++)
	{
		for (size_t j = i+1; j < boxCount; j++)
		{
			if (i != j)
			{
				distances.push_back(std::vector<long long>(3, 0));
				distances[index][0] = i;
				distances[index][1] = j;
				distances[index][2] = calculateDistanceBetweenBoxes(i, j);
				index++;
			}
		}
		if (i % 100 == 0)
		{
			outstr = "Calculated distances for box ";
			outstr += std::to_string(i);
			outstr += "\n";
			printf(outstr.c_str());
			outstr = "";
		}
	}
	outstr = "Finished calculating distances\n";
	printf(outstr.c_str());
	
}

void heapSort()
{
	auto startChrono = std::chrono::high_resolution_clock::now();
	printf("Starting heap sort\n");
	long start = distances.size() / 2 -1;
	long end = distances.size() - 1;
	long iteration = 0;
	while (end > 1)
	{
		if (start > 0) //heap construction
		{
			start--;
		}
		else //heap extraction
		{
			end--;
			std::swap(distances[0], distances[end]);
		}
		//sift down
		long root = start;
		while (root * 2 + 1 < end)
		{
			long child = root * 2 + 1;

			if (child+1<end && distances[child][2]< distances[child+1][2])
			{
				child++;
			}
			if (distances[root][2] < distances[child][2])
			{
				std::swap(distances[root], distances[child]);
				root = child;
			}
			else
			{
				break;
			}
		}
		iteration++;
		
	}

	auto elapsedChrono = std::chrono::high_resolution_clock::now() - startChrono;
	printf("\nHeap sort finished\n");
	printf("Elapsed time (ms): ");
	printf(std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(elapsedChrono).count()).c_str());
	printf("\n");
	printf("\n");
}

bool checkAlreadyConnected(int box1ID, int box2ID)
{
	int length = vElectricBox[box1ID].vConnections.size();
	bool good = true;
	if (length == 0)
	{
		return good;
	}
	for (size_t i = 0; i < length; i++)
	{
		if (vElectricBox[box1ID].vConnections[i] == box2ID)
		{
			good = false;
			break;
		}
	}
	return good;
}

void refreshShortestDistanceID()
{
	int length = distances.size();
	long long shortestDistance = LLONG_MAX;
	for (size_t i = 0; i < length; i++)
	{
		if (distances[i][2]< shortestDistance)
		{
			if (checkAlreadyConnected(distances[i][0], distances[i][1]))
			{

				shortestDistance = distances[i][2];
				shortestDistBox1ID = distances[i][0];
				shortestDistBox2ID = distances[i][1];
			}
		}
	}
	//printf("refreshed!\n");
}
void refreshShortestDistanceIDSorted()
{
	shortestDistBox1ID = distances[shortestIndex][0];
	shortestDistBox2ID = distances[shortestIndex][1];
	shortestIndex++;
}

void mergeCircuits(int box1ID, int box2ID)
{
	int circuitIDToChange = vElectricBox[box2ID].circuitID;
	int circuitIDToKeep = vElectricBox[box1ID].circuitID;
	std::string outstr = "Cable:";
	
	vElectricBox[box1ID].vConnections.push_back(box2ID);
	mergeCount++;
	if (vElectricBox[box1ID].circuitID == vElectricBox[box2ID].circuitID)
	{
		return;
	}
	for (size_t i = 0; i < boxCount; i++)
	{
		if (vElectricBox[i].circuitID == circuitIDToChange)
		{
			vElectricBox[i].circuitID = circuitIDToKeep;
		}
	}
	vCircuitBoxCount[circuitIDToKeep] += vCircuitBoxCount[circuitIDToChange];
	vCircuitBoxCount[circuitIDToChange] = 0;
	circuitCount--;
	if (circuitCount == 1)
	{
		int debug = 1;
		printf("All boxes connected! \n");
		printf("Box1 coord X: ");
		printf(std::to_string(vElectricBox[box1ID].positionX).c_str());
		printf("\n Box2 coord X: ");
		printf(std::to_string(vElectricBox[box2ID].positionX).c_str());
		printf("\n Result= ");
		printf(std::to_string(vElectricBox[box1ID].positionX*vElectricBox[box2ID].positionX).c_str());
		printf("\n");

	}
	outstr = "Box par circuit:\n";
	int length = vCircuitBoxCount.size();
	for (size_t i = 0; i < length; i++)
	{
		outstr += "Circuit no ";
		outstr += std::to_string(i);
		outstr += " : ";
		outstr += std::to_string(vCircuitBoxCount[i]);
		outstr += "\n";

	}
	//printf(outstr.c_str());
}

void optimizeCircuits(int cableQty)
{
	for (size_t i = 0; i < cableQty; i++)
	{
		refreshShortestDistanceIDSorted();
		
		mergeCircuits(shortestDistBox1ID, shortestDistBox2ID);
	}
}

std::string getGreatestCircuits()
{
	int big1ID = 0, big2ID = 0, big3ID = 0;
	int big1Count = 0, big2Count = 0, big3Count = 0;
	int length = vCircuitBoxCount.size();
	long long result = 0;
	std::string outputStr = "";
	for (size_t i = 0; i < length; i++)
	{
		if (vCircuitBoxCount[i] >= big1Count)
		{
			big3ID = big2ID;
			big3Count = big2Count;
			big2ID = big1ID;
			big2Count = big1Count;
			big1ID = i;
			big1Count = vCircuitBoxCount[i];
		}
		else if (vCircuitBoxCount[i] >= big2Count)
		{
			big3ID = big2ID;
			big3Count = big2Count;
			big2ID = i;
			big2Count = vCircuitBoxCount[i];
		}
		else if (vCircuitBoxCount[i] >= big3Count)
		{
			big3ID = i;
			big3Count = vCircuitBoxCount[i];
		}
	}
	result = big1Count * big2Count * big3Count;
	outputStr += "Big 1 ID: " + std::to_string(big1ID) + " Count: " + std::to_string(big1Count) + "\n";
	outputStr += "Big 2 ID: " + std::to_string(big2ID) + " Count: " + std::to_string(big2Count) + "\n";
	outputStr += "Big 3 ID: " + std::to_string(big3ID) + " Count: " + std::to_string(big3Count) + "\n";
	outputStr += "Result: " + std::to_string(result) + "\n";
	return outputStr;

}

int main()
{
	//std::string inputFileName = "inputTest.txt";
	//std::string inputFileName = "inputSmall.txt";
	std::string inputFileName = "input.txt";
	std::string outputStr = "";

	readFile(inputFileName);
	setupElectricBoxes();
	calculateAllDistances();
	heapSort();
	optimizeCircuits(100000);

	outputStr = getGreatestCircuits();
	printf(outputStr.c_str());

	std::ofstream outputFile("output.txt");
	outputFile << outputStr;
	outputFile.close();

}