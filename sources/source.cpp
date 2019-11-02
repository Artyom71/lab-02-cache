#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <ctime>
#include <vector>

using namespace std;


void straight(vector <int> mas)
{
	for (auto iter = mas.begin(); iter != mas.end(); ++iter)
	{
		*iter = *iter + 17;
	}
	mas.clear();
}
void back(vector <int> mas)
{
	for (auto iter = mas.end() - 1; iter != mas.begin(); --iter)
	{
		*iter = *iter + 17;
	}
	mas.clear();
}

void random(vector <int> mas)
{
	for (auto iter = mas.begin(); iter != mas.end(); ++iter)
	{
		*iter = *iter + 17;
	}
	mas.clear();
}

int output1(vector <int> mas)
{
	straight(mas);  // прогревание кэша
	unsigned int start_time = clock();
	for (unsigned int j = 0; j < 1000; ++j)
	{
		for (auto iter = mas.begin(); iter != mas.end(); ++iter)
		{
			*iter = *iter + 17;
		}
	}
	unsigned int end_time = clock();
	unsigned int search_time = end_time - start_time;

	return search_time;
}
int output2(vector <int> mas)
{
	back(mas);  // прогревание кэша
	unsigned int start_time = clock();
	for (unsigned int j = 0; j < 1000; ++j)
	{
		for (auto iter = mas.end() - 1; iter != mas.begin(); --iter)
		{
			*iter = *iter + 17;
		}
	}
	unsigned int end_time = clock();
	unsigned int search_time = end_time - start_time;
	return search_time;
}
int output3(vector <int> mas)
{
	random(mas);  // прогревание кэша

	unsigned int start_time = clock();

	random_shuffle(mas.begin(), mas.end());

	for (unsigned int j = 0; j < 1000; ++j)
	{
		for (auto iter = mas.begin(); iter != mas.end(); ++iter)
		{
			*iter = *iter + 17;
		}
	}
	unsigned int end_time = clock();
	unsigned int search_time = end_time - start_time;
	return search_time;
}

class exsperiments
{
private:
	vector <int> random_walk;
	vector <int> back_walk;
	vector <int> straight_walk;
	vector <int> mas;
	void dimensionts();
	int number_of_experiments();
	void exsperiment();
	void stop();
public:
	exsperiments()
	{
		dimensionts();
		exsperiment();
		stop();
	}
};

void exsperiments::dimensionts()
{
	int j = number_of_experiments();
	mas.resize(j);
	j = 2;
	for (auto iter = mas.begin(); iter != mas.end(); ++iter)
	{
		*iter = (j * 128 * 1024) / 4;
		j = j * 2;
	}

}

int exsperiments::number_of_experiments()
{
	int n = 0;
	int i = 128;
	while (i < 9216)
	{
		n++;
		i = i * 2;
	}
	return n;
}

void exsperiments::exsperiment()
{
	vector <int> array;
	for (auto iter = mas.begin(); iter != mas.end(); ++iter)
	{
		array.resize(*iter);  //установка размера массива

		 //заполнение массива рандомными числами
		for (auto iter = array.begin(); iter != array.end(); ++iter)
		{
			*iter = rand() % 20;
		}
		straight_walk.push_back(output1(array)); //прямой обход
		back_walk.push_back(output2(array));   //обратный обход
		random_walk.push_back(output3(array));  //случайный обход

		array.clear();
	}
}

void  exsperiments::stop()
{
	unsigned int j = number_of_experiments();
	vector <string> str = { "straight",  "back",  "random" };

	for (vector<string>::iterator it = str.begin(); it != str.end(); ++it)
	{
		cout << "investigation:" << endl;
		cout << "  travel_variant: " << *it << " " << endl;
		cout << "  experiments:" << endl;
		int r1 = 128;
		for (unsigned int i = 0; i < j; i++)
		{
			cout << "  - experiment:" << endl;
			cout << "      number: " << i + 1 << endl;
			cout << "      input_data:" << endl;
			cout << "        buffer_size: '" << r1 << "' kb" << endl;
			cout << "      results:" << endl;
			if (*it == "straight")
			{
				cout << "        duration: " << straight_walk[i] << " ms" << endl;
			}
			if (*it == "back")
			{
				cout << "        duration: " << back_walk[i] << " ms" << endl;
			}
			if (*it == "random")
			{
				cout << "        duration: " << random_walk[i] << " ms" << endl;
			}
			r1 = r1 * 2;
		}


	}
}

int main()
{  // 1 int = 4 байт, 1kb = 1024 b
	//int n1 = 32768; int r1 = 128; // 128 kb = 131072 b (1/2 от первого уровня)    
	//int n = 2359296; int r5 = 9216; // 9216 kb = 9437184 b (3/2 третьего уровня)

	srand(time(0));
	exsperiments Te;
	return 0;
}
