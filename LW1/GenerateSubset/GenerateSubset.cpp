#include <iostream>
#include <vector>
#include <boost/timer.hpp>

int main()
{
    int n;
    std::cout << "Enter n: ";
    std::cin >> n;

    std::vector<int> v(n);
    for (int i = 1; i < n; ++i)
    {
        v[i] = 0;
    }

    boost::timer t;
    t.restart();

    while (v[n - 1] != 1)
    {
        for (int i = 0; i < n; ++i)
        {
            if (v[i] == 1)
            {
                std::cout << i + 1 << " ";
            }
        }
        std::cout << std::endl;
        int i = 0;
        while (v[i] == 1)
        {
            v[i] = 0;
            i = i + 1;
        }
        v[i] = 1;
    }

    double duration = t.elapsed();
    std::cout << "Time = " << duration << " seconds" << std::endl;
}

//n = 10 => t = 0.639s.
//n = 20 => t = 402.764s.