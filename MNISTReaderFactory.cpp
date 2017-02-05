#include "MNISTReaderFactory.hpp"
#include "ImageReaderMNIST.hpp"
ImageReader* MNISTReaderFactory::createReader(){
    ImageReaderMNIST* readerMNISTPtr = new ImageReaderMNIST();
    return readerMNISTPtr;
}
