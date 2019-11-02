// Copyright 2018 Your Name <your_email>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_
#include <vector>

class exsperiments
{
private:
    std::vector <int> random_walk;
    std::vector <int> back_walk;
    std::vector <int> straight_walk;
    std::vector <int> mas;
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
#endif // INCLUDE_HEADER_HPP_
