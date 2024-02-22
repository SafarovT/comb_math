#include <iostream>
#include <fstream>
#include <sstream>
#include "quadraticAssignmentProblem.h"
#include <string>
#include <optional>
#define BOOST_TIMER_ENABLE_DEPRECATED
#include <boost/timer.hpp>

namespace
{
    using namespace std;
    
    struct GivenMatrixes
    {
        Matrix facilities, locations;
    };


    optional<string> ParseArgs(int argc, char* argv[])
    {
        if (argc != 2)
        {
            cout << "Invalid argument count\n"
                << "Usage: program.exe <MatrixFile.txt>\n";
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

    optional<Matrix> ReadMatrix(ifstream& matrixFile)
    {
        Matrix matrix;
        MatrixElement readedValue;
        string str;
        size_t i = 0;
        while (getline(matrixFile, str))
        {
            if (str == "")
            {
                break;
            }
            matrix.push_back({});
            size_t j = 0;
            stringstream ss(str);
            string temp;
            while (!ss.eof())
            {
                ss >> temp;
                if (stringstream(temp) >> readedValue)
                {
                    matrix[i].push_back(readedValue);
                    j++;
                }
                else
                {
                    cout << "Please, enter a correct matrix with numbers" << endl;
                    cout << temp << " <- [Error]";
                    return nullopt;
                }
                temp = "";
            }
            i++;
        }

        return matrix;
    }

    optional<GivenMatrixes> ReadMatrixes(string& inputFilePath)
    {
        ifstream inputFile;
        if (!OpenFile(inputFile, inputFilePath))
        {
            return nullopt;
        }

        auto facilities = ReadMatrix(inputFile);
        auto locations = ReadMatrix(inputFile);

        if (!facilities || !locations)
        {
            cout << "Corrupted matrix data in file " << inputFilePath << endl;
            return nullopt;
        }

        if (inputFile.bad())
        {
            cout << "Failed to read data from file " << inputFilePath << endl;
            return nullopt;
        }

        return optional<GivenMatrixes>({ *facilities, *locations });
    }

    void WriteMatrix(const Matrix& matrix)
    {
        for (int i = 0; i < matrix.size(); ++i)
        {
            for (int j = 0; j < matrix[i].size(); ++j)
            {
                MatrixElement numberToPrint = round(matrix[i][j] * 1000) / 1000;
                cout << numberToPrint << " ";
            }
            cout << endl;
        }
    }
}

int main(int argc, char* argv[])
{
    auto args = ParseArgs(argc, argv);
    if (!args) return EXIT_FAILURE;

    auto matrixes = ReadMatrixes(*args);
    if (!matrixes) return EXIT_FAILURE;

    boost::timer t;
    t.restart();
    ResultAssigment result = SolveQuadraticAssignmentProblem(matrixes->facilities, matrixes->locations);
    double duration = t.elapsed();

    for (int i = 0; i < matrixes->facilities.size(); i++)
    {
        cout << "F: " << (result.assignment[i] + 1) << " -> L: " << (i + 1) << endl;
    }
    cout << endl;
    cout << "Total cost: " << result.totalCost << endl << endl;
    cout << "Time = " << duration << " seconds" << endl;
    
    return EXIT_SUCCESS;
}