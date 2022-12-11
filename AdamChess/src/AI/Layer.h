#pragma once
class Layer {
	friend class Network;
public:
	//A layer only wants a weight and a sum
	Layer();
	Layer(int nodes, int connections);

	std::vector<float> Output(std::vector<float> input);

	void PopulateRandom();

	float WeightedSum(float sum);
private:
	std::vector<float> mWeights;
	std::vector<float> mBiases;

	int mNodes;
	int mConnections;
	//The last outputs that happend
	std::vector<float> mOutputs;
};