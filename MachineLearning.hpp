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
        vector<int> results;
        FeatureExtractor featureExtractor;
    public:
        MachineLearning(FeatureExtractor ft);
        void recognise(ImageReader* inputTest);
        vector<int>& getResults();
};
