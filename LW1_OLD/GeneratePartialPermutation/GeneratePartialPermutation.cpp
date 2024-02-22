#include <iostream>
#include <algorithm>
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
        do
        {
            copy(v.begin() + 1, v.end(), std::ostream_iterator<size_t>(std::cout, " "));
            std::cout << std::endl;
        } while (std::next_permutation(v.begin() + 1, v.end()));
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
    std::cout << "Time = " << duration << " seconds" << std::endl;
}

// 10 * 9 * 8 * 7 * 6 = 30 240

//k = 5

//N = 10 => t = 16.25s.
//N = 20 => t = 1000s.
//N = 50 => t = 136 659s.
//N = 100 => t = 4 856 006s.