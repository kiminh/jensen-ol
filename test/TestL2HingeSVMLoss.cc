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
	L2HingeSVMLoss<SparseFeature> ll(m, features, y, 1);

	Vector x(m, 0);
	double f;
	Vector g;
	cout<<"*******************************************************************\n";
	cout<<"Testing Gradient Descent with L2 Hinge SVM Loss, press enter to continue...\n";
	#ifndef DEBUG
	cin.get();
	#endif
	x = gd(ll, Vector(m, 0), 1e-8, numEpochs);

	cout<<"*******************************************************************\n";
	cout<<"Testing Gradient Descent with Line Search for L2 Hinge SVM Loss, press enter to continue...\n";
	#ifndef DEBUG
	cin.get();
	#endif
	x = gdLineSearch(ll, Vector(m, 0), 1, 1e-4, numEpochs);

	cout<<"*******************************************************************\n";
	cout<<"Testing Gradient Descent with Barzilia-Borwein Step Length for L2 Hinge SVM Loss, press enter to continue...\n";
	#ifndef DEBUG
	cin.get();
	#endif
	x = gdBarzilaiBorwein(ll, Vector(m, 0), 1, 1e-4, numEpochs);

	cout<<"*******************************************************************\n";
	cout<<"Testing Nesterov's Method for L2 Hinge SVM Loss, press enter to continue...\n";
	#ifndef DEBUG
	cin.get();
	#endif
	x = gdNesterov(ll, Vector(m, 0), 1, 1e-4, numEpochs);

	cout<<"*******************************************************************\n";
	cout<<"Testing Conjugate Gradient for L2 Hinge SVM Loss, press enter to continue...\n";
	#ifndef DEBUG
	cin.get();
	#endif
	x = cg(ll, Vector(m, 0), 1, 1e-4, numEpochs);

	cout<<"*******************************************************************\n";
	cout<<"L-BFGS for L2 Hinge SVM Loss, press enter to continue...\n";
	#ifndef DEBUG
	cin.get();
	#endif
	x = lbfgsMin(ll, Vector(m, 0), 1, 1e-4, numEpochs);

	cout<<"*******************************************************************\n";
	cout<<"Dual Coordinate Descent with L2 Hinge SVM Loss, press enter to continue...\n";
	cout<<"Note: This method does not check norm(gradient) < tol to determine convergence\n";
	#ifndef DEBUG
	cin.get();
	#endif
	x = SVCDual(features, y, 1, 1, 1e-3, numEpochs);

	cout<<"*******************************************************************\n";
	cout<<"Stochastic Gradient Descent for L2 Hinge SVM Loss, press enter to continue...\n";
	#ifndef DEBUG
	cin.get();
	#endif
	x = sgd(ll, Vector(m, 0), n, 1e-4, 100, 1e-4, numEpochs);

	cout<<"*******************************************************************\n";
	cout<<"Stochastic Gradient Descent with Decaying Learning Rate for L2 Hinge SVM Loss, press enter to continue...\n";
	#ifndef DEBUG
	cin.get();
	#endif
	x = sgdDecayingLearningRate(ll, Vector(m, 0), n, 0.5*1e-1, 200, 1e-4, numEpochs, 0.6);

	cout<<"*******************************************************************\n";
	cout<<"Stochastic Gradient Descent with AdaGrad for L2 Hinge SVM Loss, press enter to continue...\n";
	#ifndef DEBUG
	cin.get();
	#endif
	x = sgdAdagrad(ll, Vector(m, 0), n, 1e-2, 200, 1e-4, numEpochs);
}
