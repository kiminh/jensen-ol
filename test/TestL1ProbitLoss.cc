// Copyright (C) Rishabh Iyer, John T. Halloran, and Kai Wei
// Licensed under the Open Software License version 3.0
// See COPYING or http://opensource.org/licenses/OSL-3.0
/*
        Author: Rishabh Iyer
 *
 */

#include <iostream>
#include "../src/jensen.h"
using namespace jensen;
using namespace std;

int main(int argc, char** argv){
	char* featureFile = "../data/20newsgroup.feat";
	char* labelFile = "../data/20newsgroup.label";
	int n; // number of data items
	int m; // numFeatures
	vector<struct SparseFeature> features = readFeatureVectorSparse(featureFile, n, m);
	Vector y = readVector(labelFile, n) - 1;
	int numEpochs = 50;
	L1ProbitLoss<SparseFeature> ll(m, features, y, 1);

	Vector x(m, 0);
	double f;
	Vector g;
	cout<<"*******************************************************************\n";
	cout<<"Testing Gradient Descent with L1-Probit Loss, press enter to continue...\n";
	#ifndef DEBUG
	cin.get();
	#endif
	gd(ll, x, 1e-4, numEpochs);

	cout<<"*******************************************************************\n";
	cout<<"Testing Gradient Descent with Line Search for L1-Probit Loss, press enter to continue...\n";
	#ifndef DEBUG
	cin.get();
	#endif
	gdLineSearch(ll, x, 1, 1e-4, numEpochs);

	cout<<"*******************************************************************\n";
	cout<<"Testing Gradient Descent with Barzilia-Borwein Step Length for L1-Probit Loss, press enter to continue...\n";
	#ifndef DEBUG
	cin.get();
	#endif
	gdBarzilaiBorwein(ll, x, 1, 1e-4, numEpochs);

	cout<<"*******************************************************************\n";
	cout<<"Testing Nesterov's Method for L1-Probit Loss, press enter to continue...\n";
	#ifndef DEBUG
	cin.get();
	#endif
	gdNesterov(ll, x, 1, 1e-4, numEpochs);

	cout<<"*******************************************************************\n";
	cout<<"Testing Conjugate Gradient for L1-Probit Loss, press enter to continue...\n";
	#ifndef DEBUG
	cin.get();
	#endif
	cg(ll, x, 1, 1e-4, numEpochs);

	cout<<"*******************************************************************\n";
	cout<<"L-BFGS for L1-Probit Loss, press enter to continue...\n";
	#ifndef DEBUG
	cin.get();
	#endif
	lbfgsMin(ll, x, 1, 1e-4, numEpochs);

	cout<<"*******************************************************************\n";
	cout<<"L-BFGS-Owl for L1-Probit Loss, press enter to continue...\n";
	#ifndef DEBUG
	cin.get();
	#endif
	lbfgsMinOwl(ll, x, 1, 1e-4, numEpochs);

	cout<<"*******************************************************************\n";
	cout<<"Stochastic Gradient Descent for L1-Probit Loss, press enter to continue...\n";
	#ifndef DEBUG
	cin.get();
	#endif
	sgd(ll, x, n, 1e-4, 100, 1e-4, numEpochs);

	cout<<"*******************************************************************\n";
	cout<<"Stochastic Gradient Descent with Decaying Learning Rate for L1-Probit Loss, press enter to continue...\n";
	#ifndef DEBUG
	cin.get();
	#endif
	sgdDecayingLearningRate(ll, x, n, 0.5*1e-1, 200, 1e-4, numEpochs, 0.6);

	cout<<"*******************************************************************\n";
	cout<<"Stochastic Gradient Descent with AdaGrad for L1-Probit Loss, press enter to continue...\n";
	#ifndef DEBUG
	cin.get();
	#endif
	sgdAdagrad(ll, x, n, 1e-2, 200, 1e-4, numEpochs);
}
