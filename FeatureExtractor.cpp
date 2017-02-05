#include "FeatureExtractor.hpp"
#include <iostream>
using namespace std;
FeatureExtractor::FeatureExtractor(){
}
void FeatureExtractor::createFeatureTrainingSet(ImageReader* reader, bool isTraining){
    vector<vector<vector<int>>> images = reader->getImages();
    vector<int> labels = reader->getLabels();
    size_t oldSizeTrainingFeature = featureTrainingSet.size();
    size_t oldSizeTestingFeature = featureTestingSet.size();
    int nImages = images.size();
    if (isTraining){
        featureTrainingSet.resize(oldSizeTrainingFeature + nImages);
    }
    else featureTestingSet.resize(oldSizeTestingFeature + nImages);
    for (int i=0; i < nImages; ++i){
        if (scaledImage.size()){
            scaledImage.clear();
        }
        if (firstImage.size()){
            firstImage.clear();
        }
        firstImage = images[i];
        scaleImageToStandard(images[i]);
        vector<int> nOnes = countOnes();
        for (unsigned int j=0; j < nOnes.size(); ++j){
            if(isTraining) featureTrainingSet[oldSizeTrainingFeature + i].push_back(nOnes[j]);
            else featureTestingSet[oldSizeTestingFeature + i].push_back(nOnes[j]);
        }
        padImage();
        //thinImage();
        /*if (i==8 || i == 9 || i == 7){
            for (unsigned int i=0; i < firstImage.size(); ++i){
                for (unsigned int j=0; j < firstImage.size(); ++j)
                    cout << (firstImage[i][j]!=0)? 1 : 0;
                cout << endl;
            }
            cout << endl;
        }*/
        if(isTraining) featureTrainingSet[oldSizeTrainingFeature + i].push_back(countZeroIslands());
        else featureTestingSet[oldSizeTestingFeature + i].push_back(countZeroIslands());
        if (isTraining)
            labelTrainingSet.push_back(labels[i]);
    }
}
int FeatureExtractor::countZeroIslands(){
    vector<vector<int>> isChecked;
    size_t imageSize = firstImage.size();
    int nIslands = 0;
    for (unsigned int i=0; i<imageSize; ++i)
        isChecked.push_back(vector<int>(imageSize, 0));

    for (unsigned int i=0; i < imageSize; ++i){
		for (unsigned int j=0; j < imageSize; ++j){
			if (isChecked[i][j] == 0 && firstImage[i][j] == 0){
				++nIslands;
           		findIslands(isChecked, i, j);
			}
		}
	}
	return nIslands;
}

vector<int> FeatureExtractor::countOnes(){
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
void FeatureExtractor::scaleImageToStandard(vector<vector<int>>& originalImage){
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
int FeatureExtractor::findIslands(vector<vector<int>>& isChecked, int i, int j){
    size_t imageSize = firstImage.size();
    if (i-1 >= 0 && firstImage[i-1][j] == firstImage[i][j] && isChecked[i-1][j] == 0){
      	isChecked[i-1][j] = 1;
      	findIslands(isChecked, i-1, j);
   	}

   	if (j+1 < imageSize && firstImage[i][j+1] == firstImage[i][j] && isChecked[i][j+1] == 0){
      	isChecked[i][j+1] = 1;
      	findIslands(isChecked, i, j+1);
   	}

   	if (i+1 < imageSize && firstImage[i+1][j] == firstImage[i][j] && isChecked[i+1][j] == 0){
    	isChecked[i+1][j] = 1;
      	findIslands(isChecked, i+1, j);
   	}

   	if (j-1 >= 0 && firstImage[i][j-1] == firstImage[i][j] && isChecked[i][j-1] == 0){
      	isChecked[i][j-1] = 1;
      	findIslands(isChecked, i, j-1);
   	}

   	if (i-1 >= 0 && j-1 >= 0 && firstImage[i-1][j-1] == firstImage[i][j] && isChecked[i-1][j-1] == 0){
      	isChecked[i-1][j-1] = 1;
      	findIslands(isChecked, i-1, j-1);
   	}

   	if (j+1 < imageSize && i-1 >= 0 && firstImage[i-1][j+1] == firstImage[i][j] && isChecked[i-1][j+1] == 0){
      	isChecked[i-1][j+1] = 1;
      	findIslands(isChecked, i-1, j+1);
   	}

   	if (i+1 < imageSize && j+1 < imageSize && firstImage[i+1][j+1] == firstImage[i][j] && isChecked[i+1][j+1] == 0){
    	isChecked[i+1][j+1] = 1;
      	findIslands(isChecked, i+1, j+1);
   	}

   	if (j-1 >= 0 && i+1 < imageSize && firstImage[i+1][j-1] == firstImage[i][j] && isChecked[i+1][j-1] == 0){
      	isChecked[i+1][j-1] = 1;
      	findIslands(isChecked, i+1, j-1);
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
void FeatureExtractor::padImage(){
    vector<int> zeros(firstImage.size(), 0);
    firstImage.emplace(firstImage.begin(), zeros);
    firstImage.push_back(zeros);
    for (unsigned int i=0; i < firstImage.size(); ++i){
        firstImage[i].emplace(firstImage[i].begin(), 0);
        firstImage[i].push_back(0);
    }
}
int FeatureExtractor::countTurn(int i, int j)
{
	int q[8]={ firstImage[i-1][j], firstImage[i-1][j+1],firstImage[i][j+1], firstImage[i+1][j+1],
		       firstImage[i+1][j], firstImage[i+1][j-1],firstImage[i][j-1], firstImage[i-1][j-1]};

	int turn=0;

	for( int t=0; t < 8; t++){
	    if (t<7) {
            if( q[t] == 0 && q[t+1] != 0){
                turn++;
            }
	    }
		else {
            if(( q[7] == 0 && q[0] != 0)){
                turn++;
            }
        }
	}
	return turn;
}
int FeatureExtractor::countOne(int i, int j){
	int count1=0;
	if( firstImage[i][j+1] != 0)		count1++;
	if( firstImage[i+1][j+1] != 0)	    count1++;
	if( firstImage[i+1][j] != 0)		count1++;
	if( firstImage[i+1][j-1] != 0)	    count1++;
	if( firstImage[i][j-1] != 0)		count1++;
	if( firstImage[i-1][j-1] != 0)	    count1++;
	if( firstImage[i-1][j] != 0)		count1++;
	if( firstImage[i-1][j+1] != 0)	    count1++;
	return count1;
}

void FeatureExtractor::thinImage(){
    bool isChanged= true;
    vector<vector<bool>> isMarked;
    size_t imageSize = firstImage.size();
	for(unsigned int i=0; i < imageSize; i++)
		isMarked.push_back(vector<bool>(imageSize, false));

	while( isChanged == true)
	{
		isChanged = false;
		for(unsigned int i=1; i < imageSize-1; i++){
			for(unsigned int j=1; j < imageSize-1; j++){
				if( ( firstImage[i][j] != 0
					&& (1 < countOne(i, j) && countOne(i, j) < 7)
					&& countTurn(i, j)==1)
					&& (firstImage[i-1][j] *  firstImage[i][j+1] * firstImage[i+1][j] == 0)
					&& (firstImage[i][j+1] * firstImage[i+1][j] * firstImage[i][j-1] == 0)){

					isMarked[i][j] = true;
					isChanged = true;
				}
			}
		}

		for(unsigned int i=0; i < imageSize; i++){
			for(unsigned int j=0; j < imageSize; j++){
				if( isMarked[i][j]){
					firstImage[i][j] = 0;
					isMarked[i][j] = false;
				}
			}
		}

		for( int i=imageSize-2; i >= 1; i--){
			for( int j=imageSize-2; j >= 1; j--){
				if( firstImage[i][j] == 1
					&& (1 < countOne(i, j) && countOne(i, j) < 7)
					&& countTurn(i, j) != 0
					&& (firstImage[i-1][j] * firstImage[i][j+1] * firstImage[i][j-1] == 0)
					&& (firstImage[i-1][j] * firstImage[i+1][j] * firstImage[i][j-1] == 0)){

						isMarked[i][j] = true;
						isChanged = true;
				}
			}
		}

		for( int i=imageSize-1; i >= 0; i--){
			for( int j=imageSize-1; j >= 0; j--){
				if( isMarked[i][j]){
					firstImage[i][j] = 0;
					isMarked[i][j] = false;
				}
			}
		}
	}
}
