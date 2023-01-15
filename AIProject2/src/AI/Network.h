#pragma once
class Layer;
class Network {
public:
	Network();

	void SetupNetwork(std::vector<Layer*> layers);
	void SetupNetwork(std::vector<float> layerSizes);

	std::vector<float> Output(std::vector<float> input);
	std::vector<float> Output(std::vector<float> input, std::vector<float> correctOutput);

	void PrintNetwork();
private:
	std::vector<Layer*> mLayers;
};

