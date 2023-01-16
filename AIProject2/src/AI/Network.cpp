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
		std::cout << "Filling layer with random\n";
		layer->PopulateRandom();
	}
}
void Network::SetupNetwork(std::vector<float> layerSizes)
{
	for (int i = 0; i < layerSizes.size(); i++)
	{
		//3, 3, 3 
		// First layer 3 nodes
		// Second 3 nodes
		// 
		//The first layer size is not treated as a node, only a connectino
		Layer* layer = new Layer(layerSizes[i+1], layerSizes[i]);
	}
}


std::vector<float> Network::Output(std::vector<float> input)
{
	std::vector<float> output = input;

	for (int i = 0; i < mLayers.size(); i++) {
		auto r = mLayers[i]->Output(output);
		for (auto p : r) {
			std::wcout << p << ", ";
		}
		std::cout << "\n";
		output = r;
	}
	return output;
}

std::vector<float> Network::Output(std::vector<float> input, std::vector<float> correctOutput)
{
	//Gets the output
	
	std::vector<float> output = Output(input);

	//Vector to store the costs
	std::vector<float> costs;
	float totalCost = 0;
	std::cout << "Output : " << output.size() << "\n";
	for (int i = 0; i < output.size(); i++) {

		std::cout << "Output : " << output[i] << " : ";
		//Find costs
		costs.push_back(2*  pow(output[i] - correctOutput[i], 2.f));
		totalCost += costs[i];
		std::cout << " Cost : " << costs[i] << "\n";
	}
	float learn = 0.1f;
	//GO backwards through each layer
	for (int layer = mLayers.size()-2; layer > 0; layer--) {
		//every node in the layer
		for (int node = 0; node < mLayers[layer]->mNodes; node++) {
			//every weight in the layer
			for (int con = 0; con < mLayers[layer]->mConnections; con++) {
				//weight index
				float weight = (node * con) + con;
				//this is how sensitive the cost is to this weight
				//Chain rule: dC / dw_j_k = z / w * a/z * c/a
				auto wgradient = mLayers[layer - 1]->mActivations[con] * 
					mLayers[layer]->SigmoidDerivative(mLayers[layer]->mActivations[node]) * 
					mLayers[layer + 1]->mProps[con];
			
				mLayers[layer]->mWeights[weight] -= learn * wgradient;
				
				//Every node behind this layer is represented in mLayers[layer-1]
				//To obtain the sensitivty 
				//a(0), the weight effects the z by the activation of the previous node	
					 //sigmoid'(z(-1)) * 2(a(-1) - Y)	
					 // *2(a(l) - Y)
				//This is how sensitive the cost function to the activation of the previous lay
				// c/a(l-1) =	w(l-1) *	sigmoid'(z(l)) *  2(a(l) - Y)/ c / a(l-1)
				//the previous layer should inheret this
				//each node in this layer, has one connection to each node in layer behind
				//if we are on the first node in this layer, go thorugh 0-4 con in the props 
				//c / a(l-1) = z / a(l-1) * a/z * c/ a 
				mLayers[layer-1]->mProps[con] += mLayers[layer]->mWeights[weight] * 
					mLayers[layer]->SigmoidDerivative(mLayers[layer]->mActivations[node]) * 
					mLayers[layer]->mProps[node];
			}
			// I want a sum of all the wrong firings of for these nodes


			auto bgradient = mLayers[layer]->SigmoidDerivative(mLayers[layer]->mActivations[node]) * mLayers[layer]->mProps[node];
			mLayers[layer]->mBiases[node] -= learn * bgradient;
		}
		//apply gradients
	}

	//try again
	return output;
}

void Network::PrintNetwork()
{
	Logger::Log("Network Starting Print");
	int i = 0;
	for (auto layer : mLayers) {
		layer->PrintLayer();
	}
}
