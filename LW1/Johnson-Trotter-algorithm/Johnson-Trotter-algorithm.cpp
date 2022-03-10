#include <iostream>
#include <algorithm>
#include <vector>
#include <boost/timer.hpp>

int main()
{
    int n;
    std::cout << "Enter n: ";
    std::cin >> n;
    std::vector<int> v(n + 2);
    std::vector<int> p(n + 1);
    std::vector<int> d(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        v[i] = p[i] = i;
        d[i] = -1;
    }
    d[1] = 0;
    int m = v[0] = v[n + 1] = n + 1;

    boost::timer t;
    t.restart();

    while (m != 1)
    {
        //copy(v.begin() + 1, v.end() - 1, std::ostream_iterator<int>(std::cout, ""));
        //std::cout << std::endl;
        m = n;
        while (v[p[m] + d[m]] > m)
        {
            d[m] = -d[m];
            m = m - 1;
        }
        std::swap(v[p[m]], v[p[m] + d[m]]);
        std::swap(p[v[p[m]]], p[m]);

    }

    double duration = t.elapsed();
    std::cout << "Time = " << duration << " seconds" << std::endl;
    return 0;
}