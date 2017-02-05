#ifndef IMAGEREADER_HPP
#define IMAGEREADER_HPP
#include <fstream>
#include <vector>
using namespace std;
class ImageReader{
    public:
        //ImageReader();
        virtual void readData(ifstream& inputImageFile, ifstream& inputLabelFile) = 0;
        virtual vector<vector<vector<int>>>& getImages() = 0;
        virtual vector<int>& getLabels() = 0;
    private:
        vector<vector<vector<int>>> images;
        vector<int> labels;
};
#endif
