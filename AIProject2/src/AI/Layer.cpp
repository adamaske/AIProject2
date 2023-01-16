#include "pch.h"
#include "Layer.h"

Layer::Layer() : mNodes(0), mConnections(0)
{
}

Layer::Layer(int nodes, int connections) : mNodes(nodes), mConnections(connections)
{
	for (int i = 0; i < nodes; i++)
	{
		mProps.push_back(0);
	}
}

std::vector<float> Layer::Output(std::vector<float> input) 
{
	std::cout << "Layer got input : ";
	for (int i = 0; i < input.size(); i++) {
		std::cout << input[i] << ", ";
	}

	//Connections and input should correspond
	mActivations.clear();
	//A vector for the activations
	std::vector<float> activations;
	//Go through every node
	for (int node = 0; node < mNodes; node++) {
		//How much does this node activate?
		float activationSum = 0;
		//Every node has a mConnections of connections, finding the right one = (x * y) + y
		for (int connection = 0; connection < mConnections; connection++) {
			//We want to add the a(1) = w0,0 + a(0)0... wN,N 0 a(n)n - b(N) 
			//input[node] is the activation
			float weightActivation = input[connection] * mWeights[(node * connection) + connection];
			activationSum += weightActivation;
		}
		//Subtract the bias for the node
		activationSum -= mBiases[node];
		//Save it to get activation before weighted sum later
		mActivations.push_back(activationSum);
		//std::cout << "Activation : " << mActivations[node] << "\n";
		//Add the weighted sum of this node's activation
		activations.push_back(Sigmoid(activationSum));
		//std::cout << "Sigmoid Activation : " << activations[node] << "\n";
		}
	
	mOutputs = activations;
	
	std::cout << "\nLayer sent Output : " << mOutputs.size();
	for (int i = 0; i < mOutputs.size(); i++) {
		std::cout << mOutputs[i] << ", ";
	}
	std::cout << "\n";
	//All the outputs has now been calculated
	return mOutputs;
}
//Fill weights and biases with random stuff
void Layer::PopulateRandom()
{
	//Fills both with random numbers
	mBiases.clear();
	for (auto i = 0; i < mNodes; i++)
	{
		mBiases.push_back(rand() % 10);
	}
	mWeights.clear();
	
	for (auto i = 0; i < mNodes * mConnections; i++)
	{
		mWeights.push_back((rand() % 100) / 100.f);
	}
	//std::cout << "Weights size : " << mWeights.size() << "\nBiases size : " << mBiases.size() << "\n";
}

float Layer::Sigmoid(float sum)
{
	return 1 / (1 + exp(-sum));
}

float Layer::SigmoidDerivative(float sum)
{
	return sum * ( 1 - sum);
}

void Layer::PrintLayer()
{
	std::cout << "Layer\nNodes : " << mNodes << " Connections : " << mConnections<< "\n";

	for (int i = 0; i < mNodes ; i++) {
		for (int j = 0; j < mConnections; j++)
		{
			std::cout << "W : " << mWeights[(i * j) + j] << ", ";
		}
		std::cout << "Bias : " << mBiases[i];
		std::cout << "\n";

	}
	std::cout << "\n";
}
