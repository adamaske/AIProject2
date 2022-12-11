#include "pch.h"
#include "Layer.h"

Layer::Layer() : mNodes(0), mConnections(0)
{
}

Layer::Layer(int nodes, int connections) : mNodes(nodes), mConnections(connections)
{

}

std::vector<float> Layer::Output(std::vector<float> input) 
{
	//A vector for the activations
	std::vector<float> mActivations;
	mActivations.reserve(mNodes);

	//Go through every node
	for (int node = 0; node < mNodes; node++) {
		//How much does this node activate?
		float activationSum = 0;
		//Every node has a mConnections of connections, finding the right one = (x * y) + y
		for (int connection = 0; connection < mConnections; connection++) {
			//We want to add the a(1) = w0,0 + a(0)0... wN,N 0 a(n)n - b(N) 
			//input[node] is the activation
			float weightActivation = input[node] * mWeights[(node * mConnections) + connection];
			activationSum += weightActivation;
		}
		//Subtract the bias for the node
		activationSum -= mBiases[node];
		//Add the weighted sum of this node's activation
		mActivations[node] = WeightedSum(activationSum);
	}

	mOutputs = mActivations;
	//All the outputs has now been calculated
	return mActivations;
}
//Fill weights and biases with random stuff
void Layer::PopulateRandom()
{
	//Fills both with random numbers
	mBiases.clear();
	mBiases.reserve(mNodes);
	for (auto i = 0; i < mNodes; i++)
	{
		mBiases[i] = rand() % 20;
	}
	mWeights.clear();
	mWeights.reserve(mNodes * mConnections);

	for (auto i = 0; i < mNodes * mConnections; i++)
	{
		mWeights[i] = rand() % 20;
	}

}

float Layer::WeightedSum(float sum)
{
	return tanh(sum);
}
