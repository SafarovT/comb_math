#include <iostream>
#include <vector>

std::vector<int> generateRadnomPermutation(std::vector<int> v)
{
    for (int i = 0; i < v.size(); ++i)
    {
        int newValue;
        bool isCorrect;
        do
        {
            newValue = rand() % (v.size()) + 1;
            isCorrect = true;
            for (int j = 0; j < i; ++j)
            {
                if (v[j] == newValue)
                {
                    isCorrect = false;
                }
            }
        } while (!isCorrect);
        v[i] = newValue;
    }
    return v;
}

int main()
{
    int n;
    std::cout << "Enter n: ";
    std::cin >> n;
    std::vector<int> v(n);
    char stop = 's';
    srand(time(0));
    do
    {
        v = generateRadnomPermutation(v);
        copy(v.begin(), v.end(), std::ostream_iterator<size_t>(std::cout, " "));
        std::cout << std::endl;
        std::cout << "'s' to stop, anything else for next permutation: ";
        std::cin >> stop;
    } while (stop != 's');
}