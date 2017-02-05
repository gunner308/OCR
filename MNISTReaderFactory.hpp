#include "ImageReaderFactory.hpp"
class MNISTReaderFactory:public ImageReaderFactory{
    public:
        ImageReader* createReader() override;
};
