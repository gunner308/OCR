#include "ImageReaderUCI.hpp"
#include <sstream>
#include <string>
//ImageReaderUCI::ImageReaderUCI(){}
void ImageReaderUCI::readData(ifstream& inputImageFile, ifstream& inputLabelFile){
    string line;
    int tempLabel;
    int lineCounter = 0;
    int nImages = 0;
    while (getline(inputImageFile, line)){
        lineCounter ++;
        if (lineCounter < DATASTARTLINE){
            istringstream iss(line);
            if (line.find("ndigit = ") != string::npos){
                string tmp1, tmp2;
                iss >> tmp1 >> tmp2 >> nImages;
                images.resize(nImages);
            }
            continue;
        }
        if ((lineCounter - DATASTARTLINE + 1) % (SIZE+1) == 0){
            istringstream iss(line);
            iss >> tempLabel;
            labels.push_back(tempLabel);
            continue;
        }
        int imageNo = (lineCounter - DATASTARTLINE)/(SIZE + 1);
        int row = (lineCounter - DATASTARTLINE) % (SIZE+1);
        if (images[imageNo].size() == 0) images[imageNo].resize(SIZE);
        images[imageNo][row].resize(SIZE);
        for (int i=0; i < SIZE; ++i){
            images[imageNo][row][i] = ((int) line[i]) - 48;
        }
    }
}

vector<vector<vector<int>>>& ImageReaderUCI::getImages(){
    return images;
}

vector<int>& ImageReaderUCI::getLabels(){
    return labels;
}
