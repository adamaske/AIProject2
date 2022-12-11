#include "pch.h"
#include "Network.h"
#include "Layer.h"
Network::Network()
{
	Logger::Log("Network created");
}

void Network::SetupNetwork(std::vector<Layer*> layers)
{
	mLayers = layers;

	for (auto layer : mLayers) {
		//
		layer->PopulateRandom();
	}
}
void Network::SetupNetwork(std::vector<float> layerSizes)
{
	for (int i = 0; i < layerSizes.size(); i++)
	{
		//The first layer size is not treated as a node, only a connectino
		Layer* layer = new Layer(layerSizes[i+1], layerSizes[i]);
	}
}


std::vector<float> Network::Output(std::vector<float> input)
{
	std::vector<float> output;

	for (int i = 0; i < mLayers.size(); i++) {
		output = mLayers[i]->Output(input);
	}
}

std::vector<float> Network::Output(std::vector<float> input, std::vector<float> correctOutput)
{
	//Gets the output
	auto output = Output(input);

	//Vector to store the costs
	std::vector<float> costs;
	costs.reserve(output.size());

	//We want the correctOutput(n) - output(n)
	for (int i = 0; i < output.size(); i++) {
		costs[i] = output[i] - correctOutput[i];
	}

	std::vector<float> slopes;
	slopes.reserve(costs.size());
	for (int i = 0; i < costs.size(); i++) {
		//Derivative of the activation function Activation =( Activation - Cost )^2
		slopes[i] = 2 * (output[i] - correctOutput[i]);
	};
	//we now have a bunch of differences between the output and the desired output, We can now find the gradient of the decent

	return costs;
}

void Network::PrintNetwork()
{
	Logger::Log("Network Starting Print");
	int i = 0;
	for (auto layer : mLayers) {
		std::cout << "Layer : " << i << "\n";
		int w = 0;
		for (auto weight : layer->mWeights) {
			std::cout << "w" << w << "( " << weight << " ), ";
			w++;
		}
		std::cout << "\n";
		int b = 0;
		for (auto bias : layer->mBiases) {
			std::cout << "b" << b << "( " << bias << "), ";
			b++;
		}
		std::cout << "\n";
		i++;
	}
}
