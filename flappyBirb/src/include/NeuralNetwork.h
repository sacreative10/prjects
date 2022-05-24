#pragma once
// this file holds the declaration of the NeuralNetwork class
#include <eigen3/Eigen/Eigen>
#include <vector>

// typedefs to make the code more readable
typedef float Scalar;
typedef Eigen::MatrixXf Matrix;
typedef Eigen::RowVectorXf RowVector;
typedef Eigen::VectorXf ColVector;


class NeuralNetwork{
    public:
        NeuralNetwork(std::vector<uint> topology, Scalar learningRate = Scalar(0.005));
        void propogateForward(const RowVector &input);
        void backPropogate(const RowVector &output);
        void calcError(const RowVector &output);
        void updateWeights();
        RowVector train(std::vector<RowVector *> &inputs, std::vector<RowVector *> &outputs);
        std::vector<uint> topology;
        std::vector<RowVector*> neuronLayers;
        std::vector<RowVector*> cacheLayers;
        std::vector<RowVector*> deltaLayers;
        std::vector<Matrix*> weightLayers;
        Scalar learningRate;
};
