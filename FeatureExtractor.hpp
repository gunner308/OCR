#ifndef FEATUREEXTRACTOR_HPP
#define FEATUREEXTRACTOR_HPP
#include <fstream>
#include <vector>
#include "ImageReader.hpp"
#include <mlpack/core.hpp>
using namespace std;
class FeatureExtractor{
    private:
        //void thinImage();
        const static int STANDARD_SIZE = 32;
        vector<vector<int>> featureTrainingSet;
        vector<vector<int>> featureTestingSet;
        vector<int> labelTrainingSet;
        vector<int> labelTestingSet;
        void scaleImageToStandard(vector<vector<int>>& orginalImage, vector<vector<int>>& scaledImage);
        vector<int> countOnes(vector<vector<int>>& scaledImage);
        int countZeroIslands(vector<vector<int>>& firstImage);
        int findIslands(vector<vector<int>>& isChecked, int rowRoller, int colRoller, vector<vector<int>>& firstImage);
        void padImage(vector<vector<int>>& firstImage);
        //int countOne(int row, int col);
        //int countTurn(int row, int col);
    public:
        void createFeatureTrainingSet(ImageReader* reader, bool isTraining, int first, int last, size_t previousSize);
        vector<vector<int>>& getFeatureTrainingSet();
        vector<vector<int>>& getFeatureTestingSet();
        vector<int>& getLabelTrainingSet();
        vector<int>& getLabelTestingSet();
};
#endif
