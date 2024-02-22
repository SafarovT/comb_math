#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

int main()
{
    int n;
    std::cout << "Enter n: ";
    std::cin >> n;

    int k;
    std::cout << "Enter k: ";
    std::cin >> k;

    std::vector<int> v(k);
    for (int i = 1; i < k; ++i)
    {
        v[i] = 1;
    }

    for (int i = 0; i < k; ++i)
    {
        while (v[k - 1] != n - 1)
        {
            int j = 0;
            while (v[j] == n - 1)
            {
                v[j] = 1;
                ++j;
            }
            ++v[j];

            if (std::accumulate(v.begin(), v.end(), 0) == n)
            {
                for (int l = 0; l < k; ++l)
                {
                    if (v[l] != 0)
                    {
                        std::cout << v[l] << " ";
                    }
                }
                std::cout << std::endl;
            }
        }
    }
}
