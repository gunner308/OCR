#include <mlpack/core.hpp>
#include <mlpack/methods/neighbor_search/neighbor_search.hpp>
#include <vector>
#include "FeatureExtractor.hpp"
using namespace mlpack;
using namespace mlpack::neighbor; // NeighborSearch and NearestNeighborSort
using namespace mlpack::metric; // ManhattanDistance
using namespace mlpack::util;
class MachineLearning{
    private:
        FeatureExtractor featureExtractor;
        vector<int> results;
        const int NTHREADS = 8;
    public:
        void addTrainingData(ImageReader* input);
        void addTestingData(ImageReader* input);
        void recognise();
        void selfValidate();
};
