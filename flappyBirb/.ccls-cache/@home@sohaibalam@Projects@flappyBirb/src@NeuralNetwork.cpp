#include "include/NeuralNetwork.h"

Scalar activationFunction(Scalar x)
{
    return tanf(x);
}
Scalar activationFunctionDerivative(Scalar x)
{
    return 1 - tanhf(x) * tanhf(x);
}

NeuralNetwork::NeuralNetwork(std::vector<uint> topologies, Scalar learningRate)
{
    this->topology = topologies;
    this->learningRate = learningRate;
    for (uint i = 0; i < topology.size(); i++)
    {
        if (i == topology.size() - 1)
        {
            this->neuronLayers.push_back(new RowVector(topology[i]));
        }
        else
        {
            this->neuronLayers.push_back(new RowVector(topology[i] + 1));
        }
        cacheLayers.push_back(new RowVector(neuronLayers.size()));
        deltaLayers.push_back(new RowVector(neuronLayers.size()));

        if (i != topology.size() - 1)
        {
            neuronLayers.back()->coeffRef(this->topology[i]) = 1;
            cacheLayers.back()->coeffRef(this->topology[i]) = 1;
        }

        // initialise the weights
        if (i > 0)
        {
            if (i != this->topology.size() - 1)
            {
                weightLayers.push_back(new Matrix(this->topology[i - 1] + 1, this->topology[i] + 1));
                weightLayers.back()->setRandom();
                weightLayers.back()->col(this->topology[i]).setZero();
                weightLayers.back()->coeffRef(topology[i - 1], topology[i]) = 1;
            }
            else
            {
                weightLayers.push_back(new Matrix(this->topology[i - 1] + 1, this->topology[i]));
                weightLayers.back()->setRandom();
            }
        }
    }
}

void NeuralNetwork::NeuralNetwork::propogateForward(const RowVector &input)
{
    neuronLayers.front()->block(0, 0, 1, neuronLayers.front()->size() - 1) = input;
    for (uint i = 1; i < topology.size(); i++)
    {
        (*neuronLayers[i]) = (*neuronLayers[i - 1]) * (*weightLayers[i - 1]);
        neuronLayers[i]->block(0, 0, 1, topology[i]).unaryExpr(std::ptr_fun(activationFunction));
    }
}

void NeuralNetwork::NeuralNetwork::backPropogate(const RowVector &output)
{
    calcError(output);
    updateWeights();
}

void NeuralNetwork::NeuralNetwork::calcError(const RowVector &output)
{
    (*deltaLayers.back()) = output - (*neuronLayers.back());
    for (uint i = topology.size() - 2; i > 0; i--)
    {
        (*deltaLayers[i]) = (*deltaLayers[i + 1]) * (weightLayers[i]->transpose());
    }
}

void NeuralNetwork::NeuralNetwork::updateWeights()
{
    for (uint i = 0; i < topology.size() - 1; i++)
    {
        if (i != topology.size() - 2)
        {
            for (uint c = 0; c < weightLayers[i]->cols() - 1; c++)
            {
                for (uint r = 0; r < weightLayers[i]->rows(); r++)
                {
                    weightLayers[i]->coeffRef(r, c) += learningRate * deltaLayers[i + 1]->coeffRef(c) *
                                                       activationFunctionDerivative(cacheLayers[i + 1]->coeffRef(c)) *
                                                       neuronLayers[i]->coeffRef(r);
                }
            }
        }
        else
        {
            for (uint c = 0; c < weightLayers[i]->cols() - 1; c++)
            {
                for (uint r = 0; r < weightLayers[i]->rows(); r++)
                {
                    weightLayers[i]->coeffRef(r, c) += learningRate * deltaLayers[i + 1]->coeffRef(c) *
                                                       activationFunctionDerivative(cacheLayers[i + 1]->coeffRef(c)) *
                                                       neuronLayers[i]->coeffRef(r);
                }
            }
        }
    }
}

RowVector NeuralNetwork::NeuralNetwork::train(std::vector<RowVector *> &inputs, std::vector<RowVector *> &outputs)
{
    for (uint i = 0; i < inputs.size(); i++)
    {
        propogateForward(*inputs[i]);
    }
    return *neuronLayers.back();
}