#include <iostream>
#include <fstream>

using namespace std;

int main(){
    ofstream out;
    ifstream in;
    for(int i = 0; i < 8; i++){
        in.open("rawoutputs" + to_string(i+1) + ".txt");
        out.open("outputs" + to_string(i+1) + ".txt");

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
    return 0;
}