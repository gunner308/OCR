#include "UCIReaderFactory.hpp"
#include "ImageReaderUCI.hpp"
ImageReader* UCIReaderFactory::createReader(){
    ImageReaderUCI* readerUCIPtr = new ImageReaderUCI();
    return readerUCIPtr;
}
