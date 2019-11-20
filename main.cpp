//////////////////////////
//Developer:Dyakov Nick //
//Date:     21.11.2019  //
//////////////////////////
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iterator>
#include <iomanip>
using namespace std;
static vector<double> massive_f;
static vector<double> massive_Buffer;


class Smooth_ 
{
	ifstream fin;
	int MAX;

	double get_el_of_vector()
	{
		double mass;


		//cout << "r" << endl;

		string s;
		getline(fin, s);
		stringstream ss(s);

		ss >> mass;
		cout << mass << endl;


		return mass;
	}

public:
	Smooth_(string file_, int M)
	{
		
		fin.open(file_);
		if (!fin.is_open())
		{
			cout << "File dont open, try again" << endl;
		}
		else
		{
			cout << "File open" << endl;
			MAX = M;
		}
	}

	~Smooth_()
	{
		fin.close();
	}

	void getvector( vector<double>& mass_vec)
	{
		
			
			while (!fin.eof())
			{
				mass_vec.push_back(get_el_of_vector());
				
			}

			
			
			cout << "massive_f.size()=" << mass_vec.size() << endl;
	}
};

double sum_vec(vector<double> mass)
{


	double sum_of_elems = 0;
	sum_of_elems = accumulate(mass.begin(), mass.end(), 0);

	return sum_of_elems;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
	setlocale(LC_ALL, "Russian");
	if (argc < 2)
	{
		cout << "Enter more parametrs. \nNeed 2 parametrs: \n(1)path to file - first\n(2)step of smooth - second" << endl;
		getchar();
		return 240;
	}

	const int arg2 = atoi(argv[2]);//Введена константа для удобства и сокращения времени чтения и написания кода

	Smooth_ smooth(argv[1], arg2);
	smooth.getvector(massive_f);
	cout << "massive_f.size()=" << massive_f.size() << endl;
	if ( (2*arg2+1) >= massive_f.size())
	{
		int opp = sum_vec(massive_f) / massive_f.size();
		for (int i = 0; i < massive_f.size(); i++)
		{
			massive_Buffer.push_back(opp);

		}
		cout << "Massive buffer:" << endl;
		std::copy(massive_Buffer.begin(), massive_Buffer.end(), ostream_iterator <int>(cout, "\n"));

	}
	else
	{
		int j, i;
		cout << "Massive buffer:" << endl;
		for (j = 0; j <massive_f.size(); j++)
		{
			double sum = 0;
			double sum_of = 0;
			if ((j - arg2) <= 0)
			{
				int count = 0;
				for (i = 0; i <= (j + arg2); i++)
				{
					
					sum += massive_f.at(i);
					count++;
				}			
				//cout << "Counter=" << count << endl;
				sum_of = sum / count;
			}
			else if ((j + arg2) >= massive_f.size())
			{
				int count = 0;
				for (i = (j - arg2); i <massive_f.size(); i++)
				{
				
					sum += massive_f.at(i);
					count++;
				}		
				sum_of = sum / count;
			}
			else
			{
				int count = 0;
				for (i = (j - arg2); i <= (j + arg2); i++)
				{
					
					sum += massive_f.at(i);
					count++;
				}
				sum_of = sum / count;
			}
			massive_Buffer.push_back(sum_of);
			cout << j+1 << ":";
			cout << setiosflags(ios::fixed) << setprecision(1) << massive_Buffer.at(j) << endl;
		}
	}

	/*cout << "Massive buffer:" << endl;
	std::copy(massive_Buffer.begin(), massive_Buffer.end(), ostream_iterator <int>(cout, "\n"));
	
	*/
	
	
	
	getchar();
	return 1;

}