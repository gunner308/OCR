#include "ImageReader.hpp"
class ImageReaderUCI : public ImageReader{
    public:
        //ImageReaderUCI();
        virtual void readData(ifstream& inputImagesFile, ifstream& inputLabelsFile) override;
        virtual vector<vector<vector<int>>>& getImages() override;
        virtual vector<int>& getLabels() override;
    private:
        vector<vector<vector<int>>> images;
        vector<int> labels;
        const int SIZE = 32;
        const int DATASTARTLINE = 22;
};
