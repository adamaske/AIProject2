#pragma once
class Layer {
	friend class Network;
public:
	//A layer only wants a weight and a sum
	Layer();
	Layer(int nodes, int connections);

	std::vector<float> Output(std::vector<float> input);

	void PopulateRandom();

	float Sigmoid(float sum);
	float SigmoidDerivative(float sum);

	void PrintLayer();
private:
	//Weights
	std::vector<float> mWeights;
	std::vector<float> mBiases;
	//Before sigmoid function a*x-b
	std::vector<float> mActivations;
	std::vector<float> mWGradients;
	std::vector<float> mBGradients;

	//The last outputs that happend
	std::vector<float> mOutputs;
	std::vector<float> mProps;
	float mProp = 0;
	int mNodes;
	int mConnections;
};