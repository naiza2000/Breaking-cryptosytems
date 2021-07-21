#include <bits/stdc++.h>
using namespace std;

int main()
{
    std::ifstream input_random("text/outputs.txt");
    std::ofstream output_bin;
    output_bin.open("text/outputs_bin.txt");
    string line;
    if (input_random.is_open())
    {
        while (std::getline(input_random, line))
        {
            for (int i = 0; i < 16; i++)
            {
                char c = line[i];
                output_bin << bitset<4>(c - 102).to_string();
            }
            output_bin << "\n";
        }
    }
}