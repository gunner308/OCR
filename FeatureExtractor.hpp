#ifndef FEATUREEXTRACTOR_HPP
#define FEATUREEXTRACTOR_HPP
#include <fstream>
#include <vector>
#include "ImageReader.hpp"
#include <mlpack/core.hpp>
using namespace std;
class FeatureExtractor{
    private:
        void thinImage();
        const static int STANDARD_SIZE = 32;
        vector<vector<int>> featureTrainingSet;
        vector<vector<int>> featureTestingSet;
        vector<int> labelTrainingSet;
        vector<vector<int>> scaledImage;
        vector<vector<int>> firstImage;
        void scaleImageToStandard(vector<vector<int>>& orginalImage);
        vector<int> countOnes();
        int countZeroIslands();
        int findIslands(vector<vector<int>>& isChecked, int rowRoller, int colRoller);
        void padImage();
        int countOne(int row, int col);
        int countTurn(int row, int col);
    public:
        FeatureExtractor();
        void createFeatureTrainingSet(ImageReader* reader, bool isTraining);
        vector<vector<int>>& getFeatureTrainingSet();
        vector<vector<int>>& getFeatureTestingSet();
        vector<int>& getLabelTrainingSet();
};
#endif
