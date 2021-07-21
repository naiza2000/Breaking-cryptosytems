#include <bits/stdc++.h>
using namespace std;
void process_keyword(string s){
    transform(s.begin(), s.end(), s.begin(), ::toupper);
    for(int i=0;i<s.length();i++){
        if(s[i]=='J')s[i]='I';
    }
}
string get_order(string s){
    string alphabets = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
    string order;
    order.push_back(s[0]);
    for(int i =0;i<s.length();i++){
        if(order.find(s[i])==string :: npos)order.push_back(s[i]);
    }
    for(int i=0;i<order.length();i++){
        alphabets.erase(remove(alphabets.begin(), alphabets.end(), order[i]), alphabets.end());
    }
    order+=alphabets;
    return order;

}
void form_matrix(char matrix[5][5], string s){
    int k =0;
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            matrix[i][j] = s[k];
            k++;
        }
    }
}
int main(){
    string keyword;
    cin>>keyword;
    process_keyword(keyword);
    string order = get_order(keyword);
    char matrix[5][5];
    form_matrix(matrix,order);
    int k = 0;
    map <char,int> m;
    for(int i =1;i<=5;i++){
        for(int j = 1;j<=5;j++){
            m[order[k]] = i*10+j*1;
            k++;
        }
    }
    

    string ciphertext;
    cin>>ciphertext;
    string plaintext;
    for(int i =0; i<ciphertext.length();i=i+2){
        map<char, int>::iterator it1; 
        map<char, int>::iterator it2; 
        it1 = m.find(ciphertext[i]);
        it2 = m.find(ciphertext[i+1]);
        int x1,x2,y1,y2;
        int m1,m2;

        m1 = it1 -> second;
        m2 = it2 -> second;
        
        x1 = m1/10;
        x2 = m2/10;
        y1 = m1%10;
        y2 = m2%10;
        if(x1==x2){
            y1--;
            y2--;
            if(y1==0) y1=5;
            if(y2==0) y2=5;
            
        }
        else if(y1==y2){
            x1--;
            x2--;
            if(x1==0) x1=5;
            if(x2==0) x2=5;
           
        }
        else{
            int m;
            m = y1;
            y1 = y2;
            y2 = m;
           
        }
        plaintext.push_back(matrix[x1-1][y1-1]);
        plaintext.push_back(matrix[x2-1][y2-1]);
     

    }
    cout << plaintext;
    return 0;

}