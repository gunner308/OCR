#include "FeatureExtractor.hpp"
#include <iostream>
using namespace std;

void FeatureExtractor::createFeatureTrainingSet(ImageReader* reader, bool isTraining, int first, int last, size_t previousSize){
    vector<vector<vector<int>>> images = reader->getImages();
    vector<int> labels = reader->getLabels();
    vector<vector<int>> scaledImage;
    vector<vector<int>> firstImage;
    for (int i=first; i <= last; ++i){
        firstImage = images[i];
        scaleImageToStandard(images[i], scaledImage);
        vector<int> nOnes = countOnes(scaledImage);
        for (unsigned int j=0; j < nOnes.size(); ++j){
            if(isTraining) featureTrainingSet[previousSize + i].push_back(nOnes[j]);
            else featureTestingSet[previousSize + i].push_back(nOnes[j]);
        }
        padImage(firstImage);
        //thinImage();
        if(isTraining) featureTrainingSet[previousSize + i].push_back(countZeroIslands(firstImage));
        else featureTestingSet[previousSize + i].push_back(countZeroIslands(firstImage));
        if (isTraining) labelTrainingSet[previousSize + i] = labels[i];
        else labelTestingSet[previousSize + i] = labels[i];
    }
}

int FeatureExtractor::countZeroIslands(vector<vector<int>>& firstImage){
    vector<vector<int>> isChecked;
    size_t imageSize = firstImage.size();
    int nIslands = 0;
    for (unsigned int i=0; i<imageSize; ++i)
        isChecked.push_back(vector<int>(imageSize, 0));

    for (unsigned int i=0; i < imageSize; ++i){
		for (unsigned int j=0; j < imageSize; ++j){
			if (isChecked[i][j] == 0 && firstImage[i][j] == 0){
				++nIslands;
           		findIslands(isChecked, i, j, firstImage);
			}
		}
	}
	return nIslands;
}

vector<int> FeatureExtractor::countOnes(vector<vector<int>>& scaledImage){
    vector<int> nOnes;
    for (int rowUpperLimit = 4; rowUpperLimit <= STANDARD_SIZE; rowUpperLimit += 4){
        for (int colUpperLimit = 4; colUpperLimit <= STANDARD_SIZE; colUpperLimit += 4){
            int nOnesInThisBlock = 0;
            for (int i = rowUpperLimit - 4; i < rowUpperLimit; ++i)
                for (int j = colUpperLimit - 4; j < colUpperLimit; ++j)
                    if (scaledImage[i][j] != 0) ++nOnesInThisBlock;
            nOnes.push_back(nOnesInThisBlock);
        }
    }
    return nOnes;
}
void FeatureExtractor::scaleImageToStandard(vector<vector<int>>& originalImage, vector<vector<int>>& scaledImage){
    double scale = (double)STANDARD_SIZE/originalImage.size();
    if (scale == 1){
        scaledImage = originalImage;
        return;
    }
    scaledImage.resize(STANDARD_SIZE);
    for (int i=0; i < STANDARD_SIZE; ++i)
        scaledImage[i].resize(STANDARD_SIZE);
    for (int i=0; i < STANDARD_SIZE; ++i){
        for (int j=0; j < STANDARD_SIZE; ++j){
            int sourceRow =  i / scale;
            int sourceCol = j/scale;
            scaledImage[i][j] =  originalImage[sourceRow][sourceCol];
        }
    }
}
int FeatureExtractor::findIslands(vector<vector<int>>& isChecked, int i, int j, vector<vector<int>>& firstImage){
    size_t imageSize = firstImage.size();
    if (i-1 >= 0 && firstImage[i-1][j] == firstImage[i][j] && isChecked[i-1][j] == 0){
      	isChecked[i-1][j] = 1;
      	findIslands(isChecked, i-1, j, firstImage);
   	}

   	if (j+1 < imageSize && firstImage[i][j+1] == firstImage[i][j] && isChecked[i][j+1] == 0){
      	isChecked[i][j+1] = 1;
      	findIslands(isChecked, i, j+1, firstImage);
   	}

   	if (i+1 < imageSize && firstImage[i+1][j] == firstImage[i][j] && isChecked[i+1][j] == 0){
    	isChecked[i+1][j] = 1;
      	findIslands(isChecked, i+1, j, firstImage);
   	}

   	if (j-1 >= 0 && firstImage[i][j-1] == firstImage[i][j] && isChecked[i][j-1] == 0){
      	isChecked[i][j-1] = 1;
      	findIslands(isChecked, i, j-1, firstImage);
   	}

   	if (i-1 >= 0 && j-1 >= 0 && firstImage[i-1][j-1] == firstImage[i][j] && isChecked[i-1][j-1] == 0){
      	isChecked[i-1][j-1] = 1;
      	findIslands(isChecked, i-1, j-1, firstImage);
   	}

   	if (j+1 < imageSize && i-1 >= 0 && firstImage[i-1][j+1] == firstImage[i][j] && isChecked[i-1][j+1] == 0){
      	isChecked[i-1][j+1] = 1;
      	findIslands(isChecked, i-1, j+1, firstImage);
   	}

   	if (i+1 < imageSize && j+1 < imageSize && firstImage[i+1][j+1] == firstImage[i][j] && isChecked[i+1][j+1] == 0){
    	isChecked[i+1][j+1] = 1;
      	findIslands(isChecked, i+1, j+1, firstImage);
   	}

   	if (j-1 >= 0 && i+1 < imageSize && firstImage[i+1][j-1] == firstImage[i][j] && isChecked[i+1][j-1] == 0){
      	isChecked[i+1][j-1] = 1;
      	findIslands(isChecked, i+1, j-1, firstImage);
   	}

	return 0;
}

vector<vector<int>>& FeatureExtractor::getFeatureTrainingSet(){
    return featureTrainingSet;
}
vector<vector<int>>& FeatureExtractor::getFeatureTestingSet(){
    return featureTestingSet;
}
vector<int>& FeatureExtractor::getLabelTrainingSet(){
    return labelTrainingSet;
}
vector<int>& FeatureExtractor::getLabelTestingSet(){
    return labelTestingSet;
}
void FeatureExtractor::padImage(vector<vector<int>>& firstImage){
    vector<int> zeros(firstImage.size(), 0);
    firstImage.emplace(firstImage.begin(), zeros);
    firstImage.push_back(zeros);
    for (unsigned int i=0; i < firstImage.size(); ++i){
        firstImage[i].emplace(firstImage[i].begin(), 0);
        firstImage[i].push_back(0);
    }
}
