#include "MNISTReaderFactory.hpp"
#include "UCIReaderFactory.hpp"
#include "FeatureExtractor.hpp"
#include "MachineLearning.hpp"
int main()
{
    // Load the data from data.csv (hard-coded).  Use CLI for simple command-line
    // parameter handling.
    /*
    arma::mat data;
    data::Load("data.csv", data, true);
    // Use templates to specify that we want a NeighborSearch object which uses
    // the Manhattan distance.
    NeighborSearch<NearestNeighborSort, ManhattanDistance> nn(data);
    // Create the object we will store the nearest neighbors in.
    arma::Mat<size_t> neighbors;
    arma::mat distances; // We need to store the distance too.
    // Compute the neighbors.
    nn.Search(1, neighbors, distances);
    // Write each neighbor and distance using Log.
    for (size_t i = 0; i < neighbors.n_elem; ++i)
    {
    Log::Info << "Nearest neighbor of point " << i << " is point "
        << neighbors[i] << " and the distance is " << distances[i] << ".\n";
    }
    */
    ImageReaderFactory* aMNISTFactory = new MNISTReaderFactory();
    ImageReaderFactory* aUCIFactory = new UCIReaderFactory();
    ImageReader* readerMNIST = aMNISTFactory->createReader();
    ImageReader* readerUCI = aUCIFactory->createReader();
    ifstream inputUCI ("TrainingData/optdigits-orig.tra", ifstream::in);
    ifstream inputMNISTImgs("TrainingData/train-images.idx3-ubyte", ifstream::in);
    ifstream inputMNISTLabls("TrainingData/train-labels.idx1-ubyte", ifstream::in);
    ifstream dummy;
    readerUCI->readData(inputUCI, dummy);
    readerMNIST->readData(inputMNISTImgs, inputMNISTLabls);
    inputMNISTImgs.close();
    inputMNISTLabls.close();
    inputUCI.close();
    cout << readerMNIST->getImages().size() << endl;
    cout << readerUCI->getImages().size() << endl;
    FeatureExtractor featureExtractor;
    //ofstream outputFeatures("trainingFeatures", ofstream::app);
    std::cout << "Doing training feature extraction UCI" << std::endl;
    featureExtractor.createFeatureTrainingSet(readerUCI, true);
    std::cout << "Doing training feature extraction MNIST" << std::endl;
    featureExtractor.createFeatureTrainingSet(readerMNIST, true);
    std::cout << "Training feature extraction done. Reading testing data" << std::endl;
    //outputFeatures.close();
    //ifstream inputTestImage("TestingData/t10k-images.idx3-ubyte", ifstream::in);
    //ifstream inputTestLabel("TestingData/t10k-labels.idx1-ubyte", ifstream::in);
    //ImageReader* readerMNISTTesting = aMNISTFactory->createReader();
    ifstream inputTestUCI("TestingData/optdigits-orig.windep", ifstream::in);
    ImageReader* readerUCITesting = aUCIFactory->createReader();
    //readerMNISTTesting->readData(inputTestImage, inputTestLabel);
    readerUCITesting->readData(inputTestUCI, dummy);
    MachineLearning ml(featureExtractor);
    //ml.recognise(readerMNISTTesting);
    ml.recognise(readerUCITesting);
    int nCorrect = 0;
    //int nTests = readerMNISTTesting->getImages().size();
    int nTests = readerUCITesting->getImages().size();
    //vector<int> referenceResults = readerMNISTTesting->getLabels();
    vector<int> referenceResults = readerUCITesting->getLabels();
    for(int i=0; i < nTests; ++i){
    //    std::cout << ml.getResults()[i] << "  " << referenceResults[i] << std::endl;
        if (ml.getResults()[i] == referenceResults[i]) ++nCorrect;
    }
    cout << "Accuracy:" << (double)nCorrect/nTests * 100 <<"%" << endl;
    return 0;
}
