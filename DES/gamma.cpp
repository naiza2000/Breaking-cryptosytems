#include <bits/stdc++.h>
using namespace std;

string permute(string k, int *arr, int n)
{
    string per = "";
    for (int i = 0; i < n; i++)
    {
        per += k[arr[i] - 1];
    }
    return per;
}

// Expansion D-box Table
int exp_d[48] = {32, 1, 2, 3, 4, 5, 4, 5,
                 6, 7, 8, 9, 8, 9, 10, 11,
                 12, 13, 12, 13, 14, 15, 16, 17,
                 16, 17, 18, 19, 20, 21, 20, 21,
                 22, 23, 24, 25, 24, 25, 26, 27,
                 28, 29, 28, 29, 30, 31, 32, 1};

int main()
{
    std::ifstream gamma("text/gamma.txt");
    std::ofstream gamma_exp;
    gamma_exp.open("text/gamma_exp.txt");
    string line;
    if (gamma.is_open())
    {
        while (std::getline(gamma, line))
        {
            gamma_exp << permute(line.substr(0, 32), exp_d, 48);
            gamma_exp << "\n";
        }
    }
}