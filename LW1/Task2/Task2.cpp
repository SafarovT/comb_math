#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <optional>
#define BOOST_TIMER_ENABLE_DEPRECATED
#include <boost/timer.hpp>
#include "solveKnapsack.h"

namespace
{
    using namespace std;

    optional<string> ParseArgs(int argc, char* argv[])
    {
        if (argc != 2)
        {
            cout << "Invalid argument count\n"
                << "Usage: program.exe <DataFile.txt>\n";
            return nullopt;
        }

        return argv[1];
    }

    bool OpenFile(ifstream& inputFile, string filePath)
    {
        inputFile.open(filePath);

        if (!inputFile.is_open()) {
            cout << "Failed to open file for reading \n";

            return false;
        }

        return true;
    }

    optional<GivenData> ReadData(ifstream& inputFile)
    {
        GivenData data;
        string str;
        if (!(inputFile >> data.maxWeight))
        {
            cout << "Error max weight data" << endl;
            return nullopt;
        }
        while (getline(inputFile, str))
        {
            if (str == "")
            {
                break;
            }
            stringstream ss(str);
            int weight, price;
            if (ss >> weight && ss >> price)
            {
                data.weights.push_back(weight);
                data.prices.push_back(price);
            }
            else
            {
                cout << "Please, enter a correct data" << endl;
                cout << str << " <- [Error]";
                return nullopt;
            }
        }
        data.itemsCount = data.weights.size();

        return data;
    }

    optional<GivenData> ReadData(string& inputFilePath)
    {
        ifstream inputFile;
        if (!OpenFile(inputFile, inputFilePath))
        {
            return nullopt;
        }

        auto data = ReadData(inputFile);

        if (!data)
        {
            cout << "Corrupted data in file " << inputFilePath << endl;
            return nullopt;
        }

        if (inputFile.bad())
        {
            cout << "Failed to read data from file " << inputFilePath << endl;
            return nullopt;
        }

        return data;
    }
}

int main(int argc, char* argv[])
{
    auto args = ParseArgs(argc, argv);
    if (!args)
    {
        return EXIT_FAILURE;
    }

    auto data = ReadData(*args);
    if (!data)
    {
        return EXIT_FAILURE;
    }

    boost::timer t;
    t.restart();
    auto answer = SolveKnapsack(*data);
    double duration = t.elapsed();

    for (auto& item : answer)
    {
        cout << item << " ";
    }
    cout << endl << "Time = " << duration << " seconds" << endl;

    return EXIT_SUCCESS;
}
