#pragma once

#include <vector>
#include "TileInformation.h"
#include "ImageInformation.h"
#include <iostream>
#include "Image.h"
#include <string>
#include <map>


class LevelConverter
{
	int gridSize; 
	std::vector<TileInformation*>  tilesInformation;
	int amountOfFullStates;
	bool** truthTable;
	std::vector<std::vector<int>> rowsNumbers; 
	std::vector<std::vector<int>> columnsNumbers;

	std::map<std::string, ImageInformation*> imagesInformation;

	int maxAmountOfNumbersInRows;
	int maxAmountOfNumbersInColumns;
	int maxAmountOfNumbersGeneral;

	ImageInformation* imageInformation;
	int backgroundColor[3];

	//init
	void initializeTruthTable();
	void initializeColumnsNumbers();
	void initializeRowsNumbers();
	void getImageInformationFromTxt(std::string fileName);
	void getTilesInformationFromImage(Image* image, std::string imageName);

    //calculate 
	void calculateFullStates();
	void calculateMaxAmountOfNumbersInRows();
	void calculateMaxAmountOfNumbersInColumns();
	void calculateMaxAmountOfNumbersGeneral();

	ImageInformation* getImageInformation(std::string imageName);


public:
	LevelConverter();
	//init
	void initializeFromImageAndTxt(Image* image, std::string fileName, std::string imageName);
	
	//save
	void saveToFile(const std::string& fileResultsName);

	//debuging
	void printColumnNumbers() {
		std::cout << "\n";

		for (int i = 0; i < columnsNumbers.size(); i++)
		{
			for (int j = 0; j < columnsNumbers[i].size(); j++)
			{
				std::cout << columnsNumbers[i][j] << " ";
			}
			std::cout << "\n";
		}
	}
	void printRowNumbers() {
		std::cout << "\n";

		for (int i = 0; i < rowsNumbers.size(); i++)
		{
			for (int j = 0; j < rowsNumbers[i].size(); j++)
			{
				std::cout << rowsNumbers[i][j] << " ";
			}
			std::cout << "\n";
		}
	}
	void printTruthTable() {
		std::cout << "\n";
		for (int i = 0; i < gridSize; i++)
		{
			for (int j = 0; j < gridSize; j++)
			{
				std::cout << truthTable[i][j] << " ";
			}
			std::cout << "\n";
		}
	}

	
};