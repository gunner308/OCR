#include "MachineLearning.hpp"
MachineLearning::MachineLearning(FeatureExtractor ft){
    featureExtractor = ft;
}
void MachineLearning::recognise(ImageReader* reader){
    std::cout << "Extracting tests features" << std::endl;
    featureExtractor.createFeatureTrainingSet(reader, false);
    vector<vector<int>> trainingFeatures = featureExtractor.getFeatureTrainingSet();
    vector<int> trainingLabels = featureExtractor.getLabelTrainingSet();
    vector<vector<int>> testingFeature = featureExtractor.getFeatureTestingSet();
    int nColsTraining = trainingFeatures.size();
    int nRows = trainingFeatures[0].size();
    int nColsTesting = testingFeature.size();
    /*for (unsigned int i=5; i < 10; ++i){
        std::cout << trainingLabels[i] << std::endl;
        std::cout << trainingFeatures[i][64] << std::endl;
    }*/
    arma::mat featureTrainingSet(nRows, nColsTraining);
    arma::mat featureTestingSet(nRows, nColsTesting);
    std::cout << "Converting vectors to Armadillo matrices" << std::endl;
    for (int i=0; i < nRows; ++i){
        for (int j=0; j < nColsTraining; ++j)
            featureTrainingSet(i, j) = trainingFeatures[j][i];
        for (int j=0; j < nColsTesting; ++j)
            featureTestingSet(i, j) = testingFeature[j][i];
    }
    NeighborSearch<NearestNeighborSort, metric::SquaredEuclideanDistance> a(featureTrainingSet);
    // The matrices we will store output in.
    arma::Mat<size_t> resultingNeighbors;
    arma::mat resultingDistances;
    std::cout << "Searching neighbours" << std::endl;
    a.Search(featureTestingSet, 1, resultingNeighbors, resultingDistances);
    /*for (unsigned int i=0; i < resultingNeighbors.n_rows; ++i){
        for (unsigned int j=0; j < resultingNeighbors.n_cols; ++j){
            std::cout << resultingNeighbors(i, j) <<  " ";
        }
        std::cout << std::endl;
    }*/
    std::cout << "Finish searching, putting results in place" << std::endl;
    for (unsigned int i=0; i < resultingNeighbors.n_cols; ++i){
        results.push_back(trainingLabels[resultingNeighbors(0,i)]);
    }
    std::cout << "Recognition done. Returning..." << std::endl;
}
vector<int>& MachineLearning::getResults(){
    return results;
}
