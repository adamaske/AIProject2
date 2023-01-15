#include "pch.h"

#include "Chess/Chess.h"
#include "AI/Network.h"
#include "AI/Layer.h"

int main() {

	std::vector<Layer*> layers;
	layers.push_back(new Layer(5, 3));

	layers.push_back(new Layer(5, 5));
	layers.push_back(new Layer(5, 5));

	layers.push_back(new Layer(3, 5));

	for (auto layer : layers) {
		//Maybe do something to the layer
	}

	Network* network = new Network();
	
	network->SetupNetwork(layers);
	network->PrintNetwork();

	std::vector<std::vector<float>> results;
	for (int i = 0; i < 50; i++) {
		auto r = network->Output({(rand() % 100) / 100.f,(rand() % 100) / 100.f ,(rand() % 100) / 100.f }, {1,1,1});
		results.push_back(r);
		network->PrintNetwork();
	}

	for (int i = 0; i < results.size(); i++) {
		std::cout << "Result " << i << "\n";
		for (int j = 0; j < results[i].size(); j++) {
			std::cout << results[i][j] << ", ";
		}
		std::cout << "\n";
	}

	
	return 0;
}