#include "ImageReader.h"
#include "LevelConverter.h"
#include <filesystem>


using namespace std;

int main()
{
    string fileName = "dataForPictures.txt";
    string imageName = "Mkarate.bmp";
    Image* image = ImageReader::loadBMPfile(imageName);

   

    LevelConverter* levelConverter = new LevelConverter();
    levelConverter->initializeFromImageAndTxt(image,imageName,fileName);
 
    string fileDestination;
    if (imageName[0]== 'E')
    {
        string pathEasy =
            "C:/Users/hania/Desktop/Hanogram2/Hanogram2/Hanogram2/Level/EASY/results.txt";
        levelConverter->saveToFile( pathEasy);
    }

    if (imageName[0] == 'M')
    {
        string pathEasy =
            "C:/Users/hania/Desktop/Hanogram2/Hanogram2/Hanogram2/Level/MEDIUM/results.txt";
        levelConverter->saveToFile(pathEasy);
    }

    if (imageName[0] == 'H')
    {
        string pathEasy =
            "C:/Users/hania/Desktop/Hanogram2/Hanogram2/Hanogram2/Level/HARD/results.txt";
        levelConverter->saveToFile(pathEasy);
  
    }


    return 0;
}