#include <iostream>
#include <algorithm>
#include <vector>
#include <boost/timer.hpp>

int main()
{
    std::vector<size_t> v = { 0, 7, 6, 5, 4, 3, 2, 1, 9, 8 };
    boost::timer t;
    t.restart();
    std::sort(v.begin(), v.end());
    do
    {
        //copy(v.begin(), v.end(), std::ostream_iterator<size_t>(std::cout, " "));
        //std::cout << std::endl;
    } while (std::next_permutation(v.begin(), v.end()));
    double duration = t.elapsed();
    std::cout << "Time = " << duration << " seconds" << std::endl;
}

//N = 10 => t = 3.244s
//N = 15 => t = 1 081 080s
//N = 20 => t = 2 011 327 718 400s
//N = 50 => t = 1 280 348 958 031 347 712h
//N = 100 => t = 15 266 076 836 879 138 816y