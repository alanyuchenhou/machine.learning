#include <algorithm>
#include <functional>
#include <numeric>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <iterator>
#include <assert.h>
using std::vector;
using std::array;
using std::ifstream;
using std::string;
using std::getline;
using std::stringstream;
using std::cout;
using std::endl;
using std::stoi;
using std::stod;
using std::copy;
using std::ostream_iterator;
using std::inner_product;
using std::transform;
using std::plus;
using std::minus;

template <class type>
void vectorPlus(type & result, type const & vector1, type const & vector2)
{
  transform(vector1.begin(), vector1.end(), vector2.begin(),
	    result.begin(), plus<double>());
}

template <class type>
void vectorMinus(type & result, type const & vector1, type const & vector2)
{
  transform(vector1.begin(), vector1.end(), vector2.begin(),
	    result.begin(), minus<double>());
}

template <class sample_t, class weight_t>
void getTau(string updateAlgorithm, double & tau, weight_t const & weight,
	    sample_t const & sample, int classPrediction, int classReference)
{
  if (updateAlgorithm == "passiveAgressive")
    {
      double numerator = 1 -
	(
	 inner_product(weight[classPrediction].begin(), weight[classPrediction].end(),
		       sample.begin(), 0.0) -
	 inner_product(weight[classReference].begin(), weight[classReference].end(),
		       sample.begin(), 0.0)
	 );
      double denominator = 2 *
	inner_product(sample.begin(), sample.end(), sample.begin(), 0.0);
      numerator = 1;
      tau = numerator/denominator;
    }
  else if (updateAlgorithm == "perceptron") { tau = 1; }
  else {assert(false);}
    
}

int main(int argc, char** argv)
{
  assert(argc==3);
  const int featureCount = 781;
  const int classCount = 10;
  const int trainingCount = 10;
  typedef array<double, featureCount> sample_t;
  typedef array<sample_t, classCount> weight_t;
  weight_t weight = {{}};
  printf("training.iteration  mistake.count \n");
  // learn 100 iterations on the training data
  for (int trainingIteration = 0; trainingIteration < trainingCount; trainingIteration++)
    {
      ifstream fileStream;
      fileStream.open(argv[1]);
      string line;
      int mistakeCount = 0;
      // processing the training sample in every line of the file
      // cout << "classReference classPrediction score " << endl;
      while(getline(fileStream, line))
	{
	  stringstream lineStream;
	  lineStream.str(line);
	  string cell;
	  stringstream cellStream;
	  string label;
	  string feature;
	  string value;
	  assert(getline(lineStream, label, ' '));
	  int classReference = stoi(label);
	  sample_t sample = {{}};
	  while(getline(lineStream, cell,' ')) // constructing the sample
	    {
	      cellStream.str(cell);
	      assert(getline(cellStream, feature, ':'));
	      assert(getline(cellStream, value));
	      if (stoi(feature) < featureCount)
		{
		  sample[stoi(feature)] = stod(value);
		}
	      cellStream.clear();
	    }
	  lineStream.clear();
	  int classPrediction = {};
	  int maxScore = {};
	  // predict the class of the sample
	  for (int currentClass = 0; currentClass < classCount; currentClass++)
	    {
	      int currentScore = {};
	      currentScore = inner_product(weight[currentClass].begin(),
					   weight[currentClass].end(), sample.begin(), 0.0);
	      if (currentScore > maxScore) // update best match
		{
		  classPrediction = currentClass;
		  maxScore = currentScore;
		}
	    }
	  double tau;
	  getTau(argv[2], tau, weight, sample, classPrediction, classReference);
	  // printf ("%f ", tau);
	  if (classPrediction != classReference)
	    {
	      mistakeCount++;
	      sample_t scaledSample = {{}};
	      for (int i = 0; i < featureCount; i++)
		{
		  scaledSample[i] = tau*sample[i];
		}
	      vectorPlus(weight[classReference], weight[classReference], scaledSample);
	      vectorMinus(weight[classPrediction], weight[classPrediction], scaledSample);
	    }
	  // printf("%10d %10d %10d \n", classReference, classPrediction, maxScore);
	}
      printf("%16d %16d \n", trainingIteration, mistakeCount);
      fileStream.close();
    }
  return 0;
}

// cout << "################################################################" << endl;
// cout << "classReference classPrediction score " << endl;
// cout << "sample = " << endl;
// copy (sample.begin(), sample.end(), ostream_iterator<double>(cout, ", "));
// cout << endl;
// cout << "weight = " << endl;
// for (int i = 0; i < 4; i++)
//   {
// 	copy (weight[i].begin(), weight[i].end(), ostream_iterator<double>(cout, ", "));
// 	cout << endl;
//   }	
