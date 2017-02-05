#include "ImageReader.hpp"
class ImageReaderMNIST : public ImageReader{
    public:
        //ImageReaderMNIST();
        virtual void readData(ifstream& inputImagesFile, ifstream& inputLabelsFile) override;
        virtual vector<vector<vector<int>>>& getImages() override;
        virtual vector<int>& getLabels() override;
    private:
        int reverseInt (int i);
        void readImages (ifstream& inputImagesFile);
        void readLabels (ifstream& inputLabelsFile);
        vector<vector<vector<int>>> images;
        vector<int> labels;
};
