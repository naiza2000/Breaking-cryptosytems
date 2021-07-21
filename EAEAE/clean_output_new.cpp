#include <iostream>
#include <fstream>

using namespace std;

int main(){
    ofstream out;
    ifstream in;
    for(int i = 1; i < 9; i++){
        for(int j=1;j<=i;j++)
        {
            in.open("./raw_output/" + to_string(i) +"/" + to_string(j) + ".txt");
            out.open("./output/" + to_string(i) +"/" + to_string(j) + ".txt");

            string temp;
            while(getline(in, temp)){
                // cout << temp << ":::::" << temp.length() << endl;
                if(temp.length() == 19){
                    out << temp.substr(2, 19) << endl;
                }
            }
            in.close();
            out.close();
        }
        
    }
    return 0;
}