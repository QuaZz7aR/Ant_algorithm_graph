#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<pair<int, pair<int, int>>> fillCoefs(int amountOfCoefs)
{
	vector<pair<int, pair<int, int>>> coefs;
	for (int i = 0; i < amountOfCoefs; i++)
	{
		pair<int, pair<int, int>> x;
		cout << "Enter the " << i + 1 << " edge and the " << i + 1 << " pair :" << endl;
		cin >> x.first >> x.second.first >> x.second.second;
		coefs.push_back(x);
	}
	return coefs;
}

string stringDivisor(vector<pair<int, pair<int, int>>>& coefs, int startPoint, vector<int> edges)
{
	string a = "";
	for (unsigned int i = 0; i < coefs.size(); i++)
	{
		for (unsigned int j = 0; j < edges.size(); j++)
		{
			if (coefs[i].first / 10 == startPoint && coefs[i].first % 10 == edges[j] ||
				coefs[i].first % 10 == startPoint && coefs[i].first / 10 == edges[j])
				a += to_string(coefs[i].second.second) + "/"
				+ to_string(coefs[i].second.first) + "+";
		}
	}
	a.pop_back();
	return a;
}

void displayPEquation(vector<pair<int, pair<int, int>>>& coefs, vector<float> p1, vector<int>& edges, int startPoint)
{
	string a = stringDivisor(coefs, startPoint, edges);

	for (unsigned int i = 0; i < coefs.size(); i++)
	{
		for (unsigned int j = 0; j < edges.size(); j++)
		{
			if (coefs[i].first / 10 == startPoint && coefs[i].first % 10 == edges[j])
			{
				cout << "P" << coefs[i].first << " = "
					<< coefs[i].second.second << "/" << coefs[i].second.first
					<< " / " << a << " = " << p1[j] << endl;
			}
			else if (coefs[i].first % 10 == startPoint && coefs[i].first / 10 == edges[j])
			{
				cout << "P" << coefs[i].first % 10 << coefs[i].first / 10 << " = "
					<< coefs[i].second.second << "/" << coefs[i].second.first
					<< " / " << a << " = " << p1[j] << endl;
			}
		}
	}
	cout << endl;
}

void eraseNum(vector<int>& vec, int num)
{
	vec.erase(remove(begin(vec), end(vec), num), end(vec));
}

vector<float> ComputeP(vector<pair<int, pair<int, int>>>& coefs, int startPoint, vector<int>& edges)
{
	eraseNum(edges, startPoint); // erase passed vertex

	float div = 0; // divisor for computing the probability of transition 
	for (unsigned int i = 0; i < coefs.size(); i++)
	{
		for (unsigned int j = 0; j < edges.size(); j++)
		{
			if (coefs[i].first / 10 == startPoint && coefs[i].first % 10 == edges[j] ||
				coefs[i].first % 10 == startPoint && coefs[i].first / 10 == edges[j]) {
				div += ((float)coefs[i].second.second / (float)coefs[i].second.first);
			}
		}
	}

	vector<float> p; // Probability of transition to the next vertex
	for (unsigned int i = 0; i < coefs.size(); i++)
	{
		for (unsigned int j = 0; j < edges.size(); j++)
		{
			if (coefs[i].first / 10 == startPoint && coefs[i].first % 10 == edges[j] ||
				coefs[i].first % 10 == startPoint && coefs[i].first / 10 == edges[j]) {
				float p1 = (100 * ((float)coefs[i].second.second / (float)coefs[i].second.first / div));
				p.push_back(p1);
			}
		}
	}

	return p;
}

vector<float> computePsums(vector<float> p)
{
	float sum = 0;
	vector<float> sums{ 0 };
	for (float x : p) {
		sum += x;
		sums.push_back(sum);
	}
	return sums;
}

void displaySums(vector<float> sums)
{
	cout << "[0, ";
	for (unsigned int i = 1; i < sums.size() - 1; i++)
	{
		cout << sums[i] << "], [" << sums[i] << ", ";
	}
	cout << "100]" << endl << endl;
}

int computeTheWay(vector<float> sums, int num, vector<int> edges)
{
	for (unsigned int i = 0; i < sums.size() - 1; i++)
	{
		if (num >= sums[i] && num < sums[i + 1])
		{
			cout << sums[i] << " < " << num << " < " << sums[i + 1]
				<< ", the next top is : " << edges[i] << endl << endl;
			return edges[i];
		}
	}
}

int enterRandNum()
{
	int randomNum = 0;
	cout << "Enter random number between 0 and 100 : ";
	cin >> randomNum;
	cout << endl;
	return randomNum;
}

void displayAllWay(vector<int> theWay, vector<pair<int, pair<int, int>>> const& coefs)
{
	string resultWay = "";
	for (int x : theWay) resultWay += to_string(x) + "-";
	resultWay.pop_back();
	cout << resultWay << endl;
	resultWay.clear();

	int sum = 0;
	for (unsigned int i = 0; i < coefs.size(); i++)
	{
		for (unsigned int j = 0; j < theWay.size() - 1; j++)
		{
			if (coefs[i].first / 10 == theWay[j] && coefs[i].first % 10 == theWay[j + 1] ||
				coefs[i].first % 10 == theWay[j] && coefs[i].first / 10 == theWay[j + 1]) {
				sum += coefs[i].second.first;
				resultWay += to_string(coefs[i].second.first) + "+";
			}
		}
	}
	resultWay.pop_back();
	resultWay += " = " + to_string(sum);
	cout << "L1 = " << resultWay << endl << endl;
}

void ant_algorithm()
{
	cout << "lab4 part 2 :" << endl << endl;
	int amountOfCoefs = 0;
	/*cout << "Enter the amount coefficients : ";
	cin >> amountOfCoefs;
	vector<pair<int, pair<int, int>>> valuesOfEdges = fillCoefs(amountOfCoefs);*/
	vector<pair<int, pair<int, int>>> valuesOfEdges;

	valuesOfEdges.push_back(make_pair(12, make_pair(54, 2)));
	valuesOfEdges.push_back(make_pair(13, make_pair(83, 1)));
	valuesOfEdges.push_back(make_pair(14, make_pair(74, 2)));
	valuesOfEdges.push_back(make_pair(15, make_pair(59, 2)));
	valuesOfEdges.push_back(make_pair(23, make_pair(38, 2)));
	valuesOfEdges.push_back(make_pair(24, make_pair(62, 3)));
	valuesOfEdges.push_back(make_pair(25, make_pair(83, 3)));
	valuesOfEdges.push_back(make_pair(34, make_pair(47, 2)));
	valuesOfEdges.push_back(make_pair(35, make_pair(87, 2)));
	valuesOfEdges.push_back(make_pair(45, make_pair(47, 2)));

	vector<int> edges{ 1,2,3,4,5 };
	vector<int> theWay{ 1 };
	int startPoint = 1;

	for (unsigned int i = 0; i < edges.size() + 2; i++)
	{
		vector<float> firstWays = ComputeP(valuesOfEdges, startPoint, edges);
		displayPEquation(valuesOfEdges, firstWays, edges, startPoint);

		vector<float> sums = computePsums(firstWays);
		displaySums(sums);

		int randomNum = enterRandNum();
		startPoint = computeTheWay(sums, randomNum, edges);
		theWay.push_back(startPoint);
	}
	theWay.push_back(1);
	displayAllWay(theWay, valuesOfEdges);
}

int main()
{
	srand((unsigned int)time(0));
	ant_algorithm();

	return 0;
}