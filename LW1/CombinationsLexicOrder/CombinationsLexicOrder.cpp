#include <iostream>
#include <vector>
#include <boost/timer.hpp>

int main()
{
    int n;
    std::cout << "Enter N: ";
    std::cin >> n;
    int k;
    std::cout << "Enter k: ";
    std::cin >> k;
    std::vector<int> v(k + 1);

    boost::timer t;
    t.restart();

    for (int i = 1; i <= k; ++i)
    {
        v[i] = i;
    }
    v[0] = -1;
    int m = 1;

    while (m != 0)
    {
        for (int i = 1; i <= k; ++i)
        {
            std::cout << v[i] << " ";
        }
        std::cout << std::endl;
        m = k;
        while (v[m] == n - k + m)
        {
            m -= 1;
        }
        v[m] = v[m] + 1;
        for (int i = m + 1; i <= k; ++i)
        {
            v[i] = v[i - 1] + 1;
        }
    }
    double duration = t.elapsed();
    std::cout << "For N = " << n
        << "\nand k = " << k
        << "\nTime = " << duration << " seconds \n";
}

// k = 5

// N = 10 => t = 0.211s
// N = 20 => t = 11.221s
// N = 25 => t = 32.159s
// N = 50 => t = 1311.77s
// N = 100 => t = 46612.2s