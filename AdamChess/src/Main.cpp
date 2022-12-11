#include "pch.h"

#include "Chess/Chess.h"
#include "AI/Network.h"
#include "AI/Layer.h"

int main() {
	Logger::Log("Started program");

	Chess* chess = new Chess();
	chess->SetupGame();
	
	Layer* layer = new Layer();
	std::vector<Layer*> layers;
	layers.push_back(new Layer());
	for (auto layer : layers) {
		//Maybe do something to the layer
	}

	std::vector<float> layerSizes = { 64, 3, 3, 64 };
	Network* network = new Network();
	
	network->SetupNetwork(layers);

	return 0;
}