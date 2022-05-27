#include "LevelConverter.h"

#include <fstream>
#include <sstream>

#define offset 15

LevelConverter::LevelConverter()
{
    this->gridSize = 0;
    this->amountOfFullStates = 0;
    this->truthTable = NULL;

    this->maxAmountOfNumbersInRows = 0;
    this->maxAmountOfNumbersInColumns = 0;
  
}

void LevelConverter::initializeFromImageAndTxt(Image* image,std::string imageName, std::string fileName)
{
    getImageInformationFromTxt(fileName);
    getTilesInformationFromImage(image,imageName);
    this->initializeTruthTable();
    this->initializeRowsNumbers();
    this->initializeColumnsNumbers();
   
}

void LevelConverter::calculateFullStates()
{
    for (int i = 0; i < gridSize; i++)
    {
        for (int j = 0; j < gridSize; j++)
        {
            if (truthTable[i][j])
               this->amountOfFullStates++;
        }
    }
}

void LevelConverter::calculateMaxAmountOfNumbersInRows()
{
    for (int row = 0; row < gridSize; row++)
    {
        if (rowsNumbers[row].size() > maxAmountOfNumbersInRows)
            maxAmountOfNumbersInRows = rowsNumbers[row].size();
    }
}

void LevelConverter::calculateMaxAmountOfNumbersInColumns()
{
    for (int column = 0; column < gridSize; column++)
    {
        if (columnsNumbers[column].size() > maxAmountOfNumbersInColumns)
            maxAmountOfNumbersInColumns = columnsNumbers[column].size();
    }

}

void LevelConverter::calculateMaxAmountOfNumbersGeneral()
{
    this->calculateMaxAmountOfNumbersInColumns();
    this->calculateMaxAmountOfNumbersInRows(); 

    maxAmountOfNumbersGeneral = std::max(maxAmountOfNumbersInColumns, maxAmountOfNumbersInRows);

}

 ImageInformation* LevelConverter::getImageInformation(std::string imageName)
{
     imageName = imageName.substr(0, imageName.size() - 4);

     return imagesInformation.find(imageName)->second;
}


void LevelConverter::initializeTruthTable()
{
    truthTable = new bool* [tilesInformation.size()];
    this-> gridSize = sqrt(tilesInformation.size());

    for (int i = 0; i < gridSize; i++)
        truthTable[i] = new bool[gridSize]; 

    for (int i = 0; i < gridSize; i++)
    {
        for (int j = 0; j < gridSize; j++)
        {
            truthTable[i][j] = (tilesInformation)[i *gridSize + j]->isFilledInEndState;
        }
    }
}

void LevelConverter::initializeColumnsNumbers()
{
    for (int column = 0; column < gridSize; column++)
    {
        int counter = 0;
        std::vector<int> numbers;
        bool sequence = false;
        for (int row = 0; row < gridSize; row++)
        {
            if (truthTable[row][column] and !sequence)
            {
                sequence = true;
                counter++;
            }
            else if (truthTable[row][column] and sequence)
            {
                counter++;
            }
            else if (!truthTable[row][column] and sequence)
            {
                sequence = false;
                numbers.push_back(counter);
                counter = 0;
            }
            if (truthTable[row][column] and sequence and row == gridSize - 1)
            {
                numbers.push_back(counter);
            }
        }
        columnsNumbers.push_back(numbers);
    }


}

void LevelConverter::initializeRowsNumbers()
{
    for (int row = 0; row < gridSize; row++)
    {
        int counter = 0;
        std::vector<int>numbers;
        bool sequence = false;
        for (int j = 0; j < gridSize; j++)
        {
            if (truthTable[row][j] and !sequence)
            {
                sequence = true;
                counter++;
            }
            else if (truthTable[row][j] and sequence)
            {
                counter++;
            }
            else if (!truthTable[row][j] and sequence)
            {  sequence = false; 
            numbers.push_back(counter);
                counter = 0;
            }
            if (truthTable[row][j] and sequence and  j == gridSize - 1)
            {
                numbers.push_back(counter);
            }
        }
        rowsNumbers.push_back(numbers);
    }
}

void LevelConverter::getImageInformationFromTxt(std::string fileName)
{
    std::ifstream file(fileName);
    std::string line;
    while (std::getline(file, line))
    {
        std::stringstream ss;
        ss<< line;

        std::string name;
        int tileSize = 0;
        int r_color = 0 , g_color = 0, b_color = 0;
        std::vector<int> numbersOfTileWithCross ;

        ss >>  name;
        ss >> tileSize;
        ss >> b_color;
        ss >> g_color;
        ss >> r_color;
        
        int sizeOfVector = 0;;
        ss >> sizeOfVector;
        for (int i = 0; i < sizeOfVector; i++)
        {
            int temp = 0;
            ss >> temp;
            numbersOfTileWithCross.push_back(temp);
        }

        ImageInformation* temp = new ImageInformation();
        temp->tileSize = tileSize;
        temp->r_color = r_color;
        temp->g_color = g_color;
        temp->b_color = b_color;
        temp->numbersOfTileWithCross = numbersOfTileWithCross;

        imagesInformation[name] = temp;
    }

}

void LevelConverter::getTilesInformationFromImage(Image* image, std::string imageName)
{
    imageInformation = getImageInformation(imageName);

    backgroundColor[0] = imageInformation->r_color;
    backgroundColor[1] = imageInformation->g_color;
    backgroundColor[2] = imageInformation->b_color;

    
    std::vector<int> vecCrossState = imageInformation->numbersOfTileWithCross;


    int** tilesTable;
   
    int widthint = (int)(image->width);
    int heightint = (int)image->height;
    
    int tabSize = (widthint / imageInformation->tileSize);
    tilesTable = new int* [tabSize * tabSize]; 
    int amounOfInformationAboutTIles = 5;

    for (int i = 0; i < tabSize * tabSize; i++)
        tilesTable[i] = new int[amounOfInformationAboutTIles]; 

    for (int i = (imageInformation->tileSize / 2) * 3, k = 0; i < widthint * 3; i += imageInformation->tileSize * 3)
    {
        for (int j = (imageInformation->tileSize / 2) * 3; j < heightint * 3; j += 3 * imageInformation->tileSize)
        {
            bool isPicturePixel = false;
            TileInformation* tileInfo = new TileInformation();
            for (int p = 2; p >= 0; p--)
            {
                if (backgroundColor[p] != (int)image->pixels[i * widthint + j + p])
                    isPicturePixel = true;
                tileInfo->rgb[2 - p] = (int)image->pixels[i * widthint + j + p];
            }

            tileInfo->isFilledInEndState = (int)isPicturePixel;
            tileInfo->isCrossState =
                std::find(vecCrossState.begin(), vecCrossState.end(), k + 1) != vecCrossState.end();

            tilesInformation.push_back(tileInfo);
            k++;
        }
    }
   
}

void LevelConverter::saveToFile(const std::string & fileResultsName)
{
    printTruthTable();

    std::fstream file(fileResultsName);
    if (file.is_open())
    {
      


        file << gridSize << "\n";

        for (int i = 0; i < tilesInformation.size(); i++)
        {
            file << tilesInformation[i]->rgb[0] << " " << tilesInformation[i]->rgb[1]
                    << " " << tilesInformation[i]->rgb[2]
                    << " " << tilesInformation[i]->isFilledInEndState
                    << " " << tilesInformation[i]->isCrossState;
            
            file << "\n";
        }

        this->calculateFullStates();
        file << amountOfFullStates << " \n";
       
        this->calculateMaxAmountOfNumbersGeneral();
      
        file << maxAmountOfNumbersGeneral << "\n\n";
       
        for (int i = 0; i < rowsNumbers.size(); i++)
        {
            for (int j = 0; j < maxAmountOfNumbersGeneral - rowsNumbers[i].size(); j++)
            {
                file << 0 << " ";
            }
            for (int k = 0; k < rowsNumbers[i].size(); k++)
            {
                file << rowsNumbers[i][k] << " ";
            }
            file << "\n";
        }

        for (int i = 0; i < columnsNumbers.size(); i++)
        {
            for (int j = 0; j < maxAmountOfNumbersGeneral - columnsNumbers[i].size(); j++)
            {
                file << 0 << " ";
            }
            for (int k = 0; k < columnsNumbers[i].size(); k++)
            {
                file << columnsNumbers[i][k] << " ";
            }
            file << "\n";
        }

        file << "\n";

        file.close();
    }
    else std::cout << "Unable to open file";
}