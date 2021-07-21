#include <bits/stdc++.h>
#include <sstream>
#include <bitset>
using namespace std;
int main()
{
    string hash = "01100001011000010110010001100000000000000000000000000000000000000001000000001110000100110000111001101000011101100110011101101000011101010111111101111111011111110110100001110110011001110110100000010100000111100001101100011111011010000111011001100111011010000000010000010000000010000001000100000000000000000000000000000000000101000001111000011011000111110110100001110110011001110110100001100101011100010110110001110001000000000000000000000000000000000110000101100001011001000110000000000000000000000000000000000000";
    string msg(128, '0');
    for (int z = 0; z < 64; z++)
    {
        for (int t = 0; t < 2; t++)
        {
            for (int n = 0; n < 2; n++)
            {
                string m(128, '0');
                if (t == 1)
                    m[z] = '1';
                if (n == 1)
                    m[z + 64] = '1';
                char hexa[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
                uint64_t b = 1600;
                uint64_t l = 512;
                uint64_t c = 1024;
                uint64_t r = 576;
                int rounds = 24;
                int i, j, k;
                uint64_t state[5][5][64], tempstate[5][5][64];
                for (i = 0; i < 5; ++i)
                    for (j = 0; j < 5; ++j)
                        for (k = 0; k < 64; ++k)
                            state[i][j][k] = 0;
                uint64_t message[r];
                k = 0;
                while (k < 128)
                {
                    message[k] = m[k] - '0';
                    k++;
                }
                while (k < r)
                {
                    message[k] = 0;
                    ++k;
                }
                for (k = 0; k < r; ++k)
                    state[k / (64 * 5)][(k / 64) % 5][k % 64] = message[k];
                uint64_t current_round = 0;
                uint64_t column_parity[5][64];
                while (current_round < rounds)
                {
                    //theta operation
                    for (i = 0; i < 5; ++i)
                    {
                        for (k = 0; k < 64; ++k)
                        {
                            column_parity[i][k] = 0;
                            for (j = 0; j < 5; ++j)
                                column_parity[i][k] ^= state[i][j][k];
                        }
                    }

                    for (i = 0; i < 5; ++i)
                    {
                        for (j = 0; j < 5; ++j)
                        {
                            for (k = 0; k < 64; ++k)
                            {
                                state[i][j][k] ^= column_parity[(i + 4) % 5][k] ^ column_parity[(i + 1) % 5][k];
                                tempstate[i][j][k] = state[i][j][k];
                            }
                        }
                    }

                    //pi operation
                    for (i = 0; i < 5; ++i)
                        for (j = 0; j < 5; ++j)
                            for (k = 0; k < 64; ++k)
                                state[j][((2 * i) + (3 * j)) % 5][k] = tempstate[i][j][k];

                    //chi operation
                    for (i = 0; i < 5; ++i)
                        for (j = 0; j < 5; ++j)
                            for (k = 0; k < 64; ++k)
                                tempstate[i][j][k] = state[i][j][k];

                    for (i = 0; i < 5; ++i)
                        for (j = 0; j < 5; ++j)
                            for (k = 0; k < 64; ++k)
                                state[i][j][k] = tempstate[i][j][k] ^ (~tempstate[i][(j + 1) % 5][k] & tempstate[i][(j + 2) % 5][k]);

                    ++current_round;
                }
                int out[4];
                for (int he = 0; he < 3; he++)
                {
                    out[he] = state[0][he][z];
                }
                int flag = 0;
                for (int p = 0; p < 3; p++)
                {
                    if (out[p] != (hash[z + 64 * p] - '0'))
                    {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0)
                {
                    msg[z] = m[z];
                    msg[z + 64] = m[z + 64];
                }
            }
        }
    }
    cout << msg;
    return 0;
}