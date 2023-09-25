#include "Vector/vector.hpp"
#include <vector>

int main()
{
    ft::vector<int> ft_madani;

    for (int i = 0; i < 10; ++i)
        ft_madani.push_back(i);

    ft_madani.insert(ft_madani.begin() + 1, ft_madani.begin() + 3, ft_madani.end() - 2);
    std::vector<int> std_madani;

    for (int i = 0; i < 10; ++i)
        std_madani.push_back(i);

    std_madani.insert(std_madani.begin() + 1, std_madani.begin() + 3, std_madani.end() - 2);

    for (int i = 0; i < std_madani.size(); ++i)
    {
        std::cerr << "i : " << i<< " the value of std : " << std_madani[i] << " and the value of ft: " << ft_madani[i] << std::endl;
        if (ft_madani[i] != std_madani[i])
        {
            std::cerr << "not equal " << i <<  std::endl;
            exit(0);
        }
    }
    std::cerr << "all good" << std::endl;
}