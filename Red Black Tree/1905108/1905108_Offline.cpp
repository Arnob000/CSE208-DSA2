#include<iostream>
#include<fstream>
#include "RedBlackTree.cpp"

using namespace std;

int main(){
    int n, e, x;
    RedBlackTree<int> a;
    ifstream myfile("input.txt");
    ofstream outfile("output.txt");
    if(myfile.is_open()){
        myfile>>n;
        outfile<<n<<endl;
        while(n>0){
            n--;
            myfile>>e>>x;
            switch(e){
            case 0:
                outfile<<e<<" "<<x<<" "<<a.Delete(x)<<endl;
                break;
            case 1:
                outfile<<e<<" "<<x<<" "<<a.insert(x)<<endl;
                break;
            case 2:
                outfile<<e<<" "<<x<<" "<<a.Found(x)<<endl;
                break;
            case 3:
                outfile<<e<<" "<<x<<" "<<a.printNumOfProgLessThan(x)<<endl;
                break;
            }
        }
    }
    myfile.close();
    outfile.close();

}
