#include "ImageReaderFactory.hpp"
class UCIReaderFactory:public ImageReaderFactory{
    public:
        ImageReader* createReader() override;
};
