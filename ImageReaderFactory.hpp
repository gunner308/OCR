#ifndef IMAGEREADERFACTORY_HPP
#define IMAGEREADERFACTORY_HPP
#include "ImageReader.hpp"
class ImageReaderFactory{
    public:
        virtual ImageReader* createReader() = 0;
};
#endif
