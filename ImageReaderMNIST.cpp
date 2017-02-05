#include "ImageReaderMNIST.hpp"
//ImageReaderMNIST::ImageReaderMNIST(){}
int ImageReaderMNIST::reverseInt(int i){
    unsigned char ch1, ch2, ch3, ch4;
    ch1=i&255;
    ch2=(i>>8)&255;
    ch3=(i>>16)&255;
    ch4=(i>>24)&255;
    return((int)ch1<<24)+((int)ch2<<16)+((int)ch3<<8)+ch4;
}
void ImageReaderMNIST::readImages(ifstream& inputFile){
    //ifstream file ("C:\\t10k-images.idx3-ubyte",ios::binary);
    if (inputFile.is_open())
    {
        int magic_number=0;
        int number_of_images=0;
        int n_rows=0;
        int n_cols=0;
        inputFile.read((char*)&magic_number,sizeof(magic_number));
        magic_number= reverseInt(magic_number);
        inputFile.read((char*)&number_of_images,sizeof(number_of_images));
        number_of_images= reverseInt(number_of_images);
        images.resize(number_of_images);
        inputFile.read((char*)&n_rows,sizeof(n_rows));
        n_rows= reverseInt(n_rows);
        inputFile.read((char*)&n_cols,sizeof(n_cols));
        n_cols= reverseInt(n_cols);
        for (int i=0; i < number_of_images; ++i){
            images[i].resize(n_rows);
            for (int j=0; j < n_rows; ++j){
                images[i][j].resize(n_cols);
            }
        }
        for(int i=0;i<number_of_images;++i)
        {
            for(int r=0;r<n_rows;++r)
            {
                for(int c=0;c<n_cols;++c)
                {
                    unsigned char temp=0;
                    inputFile.read((char*)&temp,sizeof(temp));
                    images[i][r][c]= (int)temp;
                }
            }
        }
    }
}
void ImageReaderMNIST::readLabels(ifstream& inputFile){
    //ifstream file ("C:\\t10k-images.idx3-ubyte",ios::binary);
    if (inputFile.is_open())
    {
        int magic_number=0;
        int number_of_images=0;
        inputFile.read((char*)&magic_number,sizeof(magic_number));
        magic_number= reverseInt(magic_number);
        inputFile.read((char*)&number_of_images,sizeof(number_of_images));
        number_of_images= reverseInt(number_of_images);
        labels.resize(number_of_images);
        for(int i=0;i<number_of_images;++i)
        {
            unsigned char temp=0;
            inputFile.read((char*)&temp,sizeof(temp));
            labels[i]= (int)temp;
        }
    }
}
void ImageReaderMNIST::readData(ifstream& inputImage, ifstream& inputLabel){
    readImages(inputImage);
    if (inputLabel.good())
        readLabels(inputLabel);
}

vector<vector<vector<int>>>& ImageReaderMNIST::getImages(){
    return images;
}

vector<int>& ImageReaderMNIST::getLabels(){
    return labels;
}
