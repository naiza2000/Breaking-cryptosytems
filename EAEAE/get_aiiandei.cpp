#include<bits/stdc++.h>
#include<fstream>

using namespace std;



int two_letters_to_number(string s)
{
    int a=s[0]-'f';
    int b=s[1]-'f';
    int i=0,i1=0;
    int ans=0;
    while(i<8)
    {
        if(i<4&&((1<<i)&b))
        {
            ans+= 1<<i;
        }
        if(i>=4&&((1<<(i-4))&a))
        {
            ans+= 1<<i;
        }
        i++;
    }
    return ans;
}

int multiply_bin(int n, int m)
{
    int ans = 0;
	for(int i=0;i<8;i++)
    {
        if(n & (1<<i))
            ans= ans^(m<<i);
    }
    for(int i=13;i>6;i--)
    {
        if(ans & (1<<i))
        {
            ans^= 1<<i;
            ans^= 1<<(i-6);
            ans^= 1<<(i-7);
        }
    }
    return ans;
}


int main()
{
    ofstream out;
    ifstream output_random;
    ifstream input_random;
    out.open("pairs.txt");
    for(int k1=1;k1<=8;k1++)
    {
        vector<pair<int,int>> a_e;
        for(int a=0;a<128;a++)
        {
            for(int e=1;e<127;e++)
            {
                a_e.push_back({a,e});
            }
        }
        input_random.open("input"+to_string(k1)+".txt");
        output_random.open("outputs"+to_string(k1)+".txt");
        string input1,output1;
        if(input_random.is_open()&& output_random.is_open())
        {
            while(getline(input_random, input1)) //loop for different outputs
            {
                
                getline(output_random, output1);
                int s1 = two_letters_to_number(input1.substr(2*(k1-1),2));
                int s1_out = two_letters_to_number(output1.substr(2*(k1-1),2));
                // auto it=a_e.begin();
                vector<pair<int,int>> a_e_temp;
                for(auto it=a_e.begin();it!=a_e.end();it++)
                {
                    int a1=(*it).first;
                    int atemp=a1;
                    int stemp=s1;
                    int etemp=(*it).second;
                    int etemp_2 = (((etemp*etemp)%127)*etemp)%127;
                    int etemp_1 = (((etemp*etemp)%127)+etemp)%127;
                    for(int pow=1;pow<etemp_1;pow++)
                    {
                        atemp = multiply_bin(atemp,a1);
                    }
                    for(int pow=1;pow<etemp_2;pow++)
                    {
                        stemp = multiply_bin(stemp,s1);
                    }
                    // cout<<atemp<<" "<<stemp<<endl;
                    if(multiply_bin(atemp,stemp)==s1_out)
                    {
                        a_e_temp.push_back(*it);
                    }
                    
                }
                a_e.clear();
                a_e = a_e_temp;
                a_e_temp.clear();
            }
        }
        input_random.close();
        output_random.close();

        if(a_e.size()!=0)
        for(int i=0;i<a_e.size();i++)
        {
            out<<a_e[i].second<<" "<<a_e[i].first<<"\t";
        }
        out<<endl;
    }
    out.close();
    

    
    return 0;
}

