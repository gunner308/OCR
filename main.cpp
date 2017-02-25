#include "MNISTReaderFactory.hpp"
#include "UCIReaderFactory.hpp"
#include "FeatureExtractor.hpp"
#include "MachineLearning.hpp"

void trainingModeHandler(MachineLearning& ml){
    vector<string> uciFilenames;
    vector<pair<string, string>> mnistFilenames;
    string trainDirectory = "TrainingData/";
    while(true){
        int dataFormat = -1;
        cout << "Data format: 1. UCI  2. MNIST  0. Start training" << endl;
        cin >> dataFormat;
        if (dataFormat == 0) break;
        else if (dataFormat == 1){
            string temp;
            cout << "Filename: ";
            cin >> temp;
            uciFilenames.push_back(trainDirectory+temp);
        }
        else if (dataFormat == 2){
            string temp1, temp2;
            cout << "Image filename: ";
            cin >> temp1;
            cout << "Label filename: ";
            cin >> temp2;
            mnistFilenames.push_back(pair<string, string>(trainDirectory+temp1, trainDirectory+temp2));
        }
    }
    for(string s: uciFilenames){
        ImageReaderFactory* aUCIFactory = new UCIReaderFactory();
        ImageReader* readerUCI = aUCIFactory->createReader();
        ifstream inputUCI (s, ifstream::in);
        ifstream dummy;
        readerUCI->readData(inputUCI, dummy);
        ml.addTrainingData(readerUCI);
    }
    for(auto p: mnistFilenames){
        ImageReaderFactory* aMNISTFactory = new MNISTReaderFactory();
        ImageReader* readerMNIST = aMNISTFactory->createReader();
        ifstream inputMNISTImages (p.first, ifstream::binary);
        ifstream inputMNISTLabels (p.second, ifstream::binary);
        readerMNIST->readData(inputMNISTImages, inputMNISTLabels);
        ml.addTrainingData(readerMNIST);
    }
}
void validationModeHandler(MachineLearning& ml){
    vector<string> uciFilenames;
    vector<pair<string, string>> mnistFilenames;
    string testDirectory = "TestingData/";
    while(true){
        int dataFormat = -1;
        cout << "Data format: 1. UCI  2. MNIST  0. Start validating" << endl;
        cin >> dataFormat;
        if (dataFormat == 0) break;
        else if (dataFormat == 1){
            string temp;
            cout << "Filename: ";
            cin >> temp;
            uciFilenames.push_back(testDirectory+temp);
        }
        else if (dataFormat == 2){
            string temp1, temp2;
            cout << "Image filename: ";
            cin >> temp1;
            cout << "Label filename: ";
            cin >> temp2;
            mnistFilenames.push_back(make_pair(testDirectory+temp1, testDirectory+temp2));
        }
    }
    for(string s: uciFilenames){
        ImageReaderFactory* aUCIFactory = new UCIReaderFactory();
        ImageReader* readerUCI = aUCIFactory->createReader();
        ifstream inputUCI (s, ifstream::in);
        ifstream dummy;
        readerUCI->readData(inputUCI, dummy);
        ml.addTestingData(readerUCI);
    }
    for(auto p: mnistFilenames){
        ImageReaderFactory* aMNISTFactory = new MNISTReaderFactory();
        ImageReader* readerMNIST = aMNISTFactory->createReader();
        ifstream inputMNISTImgs(p.first, ifstream::binary);
        ifstream inputMNISTLabls(p.second, ifstream::binary);
        readerMNIST->readData(inputMNISTImgs, inputMNISTLabls);
        ml.addTestingData(readerMNIST);
    }
    ml.recognise();
    ml.selfValidate();
}
int main()
{
    /*ImageReaderFactory* aMNISTFactory = new MNISTReaderFactory();
    ImageReaderFactory* aUCIFactory = new UCIReaderFactory();
    ImageReader* readerMNIST = aMNISTFactory->createReader();
    ImageReader* readerUCI = aUCIFactory->createReader();
    ifstream inputUCI ("TrainingData/optdigits-orig.tra", ifstream::in);
    ifstream inputMNISTImgs("TrainingData/train-images.idx3-ubyte", ifstream::binary);
    ifstream inputMNISTLabls("TrainingData/train-labels.idx1-ubyte", ifstream::binary;
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
        if (ml.getResults()[i] == referenceResults[i]) ++nCorrect;
    }
    cout << "Accuracy:" << (double)nCorrect/nTests * 100 <<"%" << endl;
    return 0;*/
    MachineLearning ml;
    while(true){
        int mode;
        cout << "1. Training mode    2. Validation mode    3. Exit" << endl;
        cout << "Please choose mode: ";
        cin >> mode;
        switch(mode){
            case 1:
                trainingModeHandler(ml);
                break;
            case 2:
                validationModeHandler(ml);
                break;
            case 3:
                return 0;
        }
    }
    return 0;
}
