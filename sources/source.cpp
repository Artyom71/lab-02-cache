// Copyright 2018 Your Name <your_email>

#include <header.hpp>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;


void straight (int mas[], int n)
{
    for (int i = 0; i < n; i++)
    {
        mas[i] = mas[i] + 17;
    }
}
void back (int mas[], int n)
{
    for (int i = n; i > 0; i--)
    {
        mas[i] = mas[i] + 17;
    }
}
void random (int mas[], int n)
{
    random_shuffle(mas, mas+n);

    for (int i = 0; i < n; i++)
    {
        mas[i] = mas[i] + 17;
    }
}

int output1( int mas[], int n)
{
    straight(mas, n);  // прогревание кэша
    unsigned int start_time = clock();
    for (int j = 0; j < 1000; j++)
    {
        straight(mas, n);
    }
    unsigned int end_time = clock();
    unsigned int search_time = end_time-start_time;
    return search_time;
}
int output2(int mas[], int n)
{
    back(mas, n);  // прогревание кэша
    unsigned int start_time = clock();
    for (int j = 0; j < 1000; j++)
    {
        straight(mas, n);
    }
    unsigned int end_time = clock();
    unsigned int search_time = end_time - start_time;
    return search_time;
}
int output3(int mas[], int n)
{
    random(mas, n);  // прогревание кэша

    unsigned int start_time = clock();
    for (int j = 0; j < 1000; j++)
    {
        straight(mas, n);
    }
    unsigned int end_time = clock();
    unsigned int search_time = end_time - start_time;
    return search_time;
}

int main()
{  // 1 int = 4 байт, 1kb = 1024 b
    int mas[7];   //массив размерности в байтах
    int r1 = 128; // 128 kb = 131072 b (1/2 от первого уровня)
    // 9216 kb = 9437184 b (3/2 третьего уровня)

    vector <int> random_walk;
    vector <int> back_walk;
    vector <int> straight_walk;

    for (int i = 1; i < 8; i++)
    {
        mas[i - 1] = (r1 * i * 1024) / 4;
    }

    srand(time(0));

    for (int j = 0; j < 7; j++)
    {
        int *array = new int[mas[j]];  //создание массива

        for (int i = 0; i < mas[j]; i++)  //заполнение массива рандомными числами
        {
            array[i] = rand() % 20;
        }

        random_walk.push_back(output3(array, mas[j]));  //случайный обход
        back_walk.push_back(output2(array, mas[j]));   //обратный обход
        straight_walk.push_back(output1(array, mas[j])); //прямой обход

        delete[] array;
    }

    cout << "investigation:" << endl;
    cout << "  travel_variant: straight " << endl;
    cout << "  experiments:" << endl;
    for (int i = 0; i < 7; i++)
    {
        cout << "  - experiment:" << endl;
        cout << "      number: " << i+1 << endl;
        cout << "      input_data:" << endl;
        cout << "        buffer_size: '" << r1 << "' kb" << endl;
        cout << "      results:" << endl;
        cout << "        duration: " << straight_walk[i] << " ms" << endl;
        r1 = r1 * 2;
    }
    cout << endl;
    cout << "investigation:" << endl;
    cout << "  travel_variant: back " << endl;
    cout << "  experiments:" << endl;
    r1 = 128;
    for (int i = 0; i < 7; i++)
    {
        cout << "  - experiment:" << endl;
        cout << "      number: " << i + 1 << endl;
        cout << "      input_data:" << endl;
        cout << "        buffer_size: '" << r1 << "' kb" << endl;
        cout << "      results:" << endl;
        cout << "        duration: " << back_walk[i] << " ms" << endl;
        r1 = r1 * 2;
    }
    cout << endl;
    cout << "investigation:" << endl;
    cout << "  travel_variant: random " << endl;
    cout << "  experiments:" << endl;
    r1 = 128;
    for (int i = 0; i < 7; i++)
    {
        cout << "  - experiment:" << endl;
        cout << "      number: " << i + 1 << endl;
        cout << "      input_data:" << endl;
        cout << "        buffer_size: '" << r1 << "' kb" << endl;
        cout << "      results:" << endl;
        cout << "        duration: " << random_walk[i] << " ms" << endl;
        r1 = r1 * 2;
    }
    return 0;
}