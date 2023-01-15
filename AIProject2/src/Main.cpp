#include "pch.h"

#include "Chess/Chess.h"
#include "AI/Network.h"
#include "AI/Layer.h"

int main() {
	srand(time(0));
	std::vector<Layer*> layers;
	layers.push_back(new Layer(5, 5));
	//layers.push_back(new Layer(5, 5));
	//layers.push_back(new Layer(5, 5));
	//layers.push_back(new Layer(5, 5));
	//layers.push_back(new Layer(5, 5));
	layers.push_back(new Layer(2, 2));

	Network* network = new Network();
	
	network->SetupNetwork(layers);
	network->PrintNetwork();

	std::vector<std::vector<float>> results;
	for (int i = 0; i < 300; i++) {
		auto r = network->Output({(rand() % 10) / 10.f, (rand() % 10) / 10.f , (rand() % 10) / 10.f, (rand() % 10) / 10.f , (rand() % 10) / 10.f }, {0.2, 0.3});
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