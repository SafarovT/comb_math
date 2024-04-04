#include <iostream>
#include <optional>
#include "tree.h"

namespace
{
    using namespace std;

    optional<string> ParseArgs(int argc, char* argv[])
    {
        if (argc != 2)
        {
            cout << "Invalid argument count\n"
                << "Usage: program.exe <GraphFile.txt>\n";
            return nullopt;
        }

        return argv[1];
    }
}

int main(int argc, char* argv[])
{
    auto args = ParseArgs(argc, argv);
    if (!args)
    {
        return EXIT_FAILURE;
    }

    FindStrongComponents(*args);

    return EXIT_SUCCESS;
}