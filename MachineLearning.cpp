#include "MachineLearning.hpp"
#include <thread>
void MachineLearning::addTrainingData(ImageReader* input){
    size_t previousSize = featureExtractor.getFeatureTrainingSet().size();
    size_t inputNImages = input->getImages().size();
    featureExtractor.getFeatureTrainingSet().resize(previousSize + inputNImages);
    featureExtractor.getLabelTrainingSet().resize(previousSize + inputNImages);
    vector<thread> workerThreads;
    int first, last;
    int nImagesForAThread = input->getImages().size()/NTHREADS;
    for (int i=0; i < NTHREADS; ++i){
        first = nImagesForAThread * i;
        if (i < NTHREADS-1) last = first + nImagesForAThread - 1;
        else last = inputNImages - 1;
        workerThreads.push_back(thread(&FeatureExtractor::createFeatureTrainingSet, &featureExtractor, input, true, first, last, previousSize));
    }
    for (int i=0; i < NTHREADS; ++i){
        workerThreads[i].join();
    }
}
void MachineLearning::addTestingData(ImageReader* input){
    size_t previousSize = featureExtractor.getFeatureTestingSet().size();
    size_t inputNImages = input->getImages().size();
    featureExtractor.getFeatureTestingSet().resize(previousSize + inputNImages);
    featureExtractor.getLabelTestingSet().resize(previousSize + inputNImages);
    vector<thread> workerThreads;
    int first, last;
    int nImagesForAThread = input->getImages().size()/NTHREADS;
    for (int i=0; i < NTHREADS; ++i){
        first = nImagesForAThread * i;
        if (i < NTHREADS-1) last = first + nImagesForAThread - 1;
        else last = inputNImages - 1;
        workerThreads.push_back(thread(&FeatureExtractor::createFeatureTrainingSet, &featureExtractor, input, false, first, last, previousSize));
    }
    for (int i=0; i < NTHREADS; ++i){
        workerThreads[i].join();
    }
}
void MachineLearning::recognise(){
    vector<vector<int>> trainingFeatures = featureExtractor.getFeatureTrainingSet();
    vector<int> trainingLabels = featureExtractor.getLabelTrainingSet();
    vector<vector<int>> testingFeature = featureExtractor.getFeatureTestingSet();
    int nColsTraining = trainingFeatures.size();
    int nRows = trainingFeatures[0].size();
    int nColsTesting = testingFeature.size();
    arma::mat featureTrainingSet(nRows, nColsTraining);
    arma::mat featureTestingSet(nRows, nColsTesting);
    std::cout << "Converting vectors to Armadillo matrices" << std::endl;
    for (int i=0; i < nRows; ++i){
        for (int j=0; j < nColsTraining; ++j)
            featureTrainingSet(i, j) = trainingFeatures[j][i];
        for (int j=0; j < nColsTesting; ++j)
            featureTestingSet(i, j) = testingFeature[j][i];
    }
    NeighborSearch<NearestNeighborSort, metric::EuclideanDistance> a(featureTrainingSet);
    // The matrices we will store output in.
    arma::Mat<size_t> resultingNeighbors;
    arma::mat resultingDistances;
    std::cout << "Searching neighbours" << std::endl;
    a.Search(featureTestingSet, 1, resultingNeighbors, resultingDistances);
    std::cout << "Finish searching, putting results in place" << std::endl;
    for (unsigned int i=0; i < resultingNeighbors.n_cols; ++i){
        results.push_back(trainingLabels[resultingNeighbors(0,i)]);
    }
    std::cout << "Recognition done. Returning..." << std::endl;
}
void MachineLearning::selfValidate(){
    vector<int> referenceResults = featureExtractor.getLabelTestingSet();
    int nTests = referenceResults.size();
    int nCorrect = 0;
    for(int i=0; i < nTests; ++i){
        if (results[i] == referenceResults[i]) ++nCorrect;
    }
    cout << "Accuracy:" << (double)nCorrect/nTests * 100 <<"%" << endl;
}
