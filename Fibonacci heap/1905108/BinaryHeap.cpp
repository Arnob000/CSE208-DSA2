#include<bits/stdc++.h>

using namespace std;
//min
class Heap{
    vector<pair<double, int> > arr;
    int len;

public:
    Heap(){             //constructor
        arr.assign(1, {0,0});
        len=1;
    }

    ~Heap(){
        arr.clear();
    }

    int leftchild(int i){
        return 2*i;
    }

    int rightchild(int i){
        return (2*i)+1;
    }

    bool isEmpty(){
        if(len<=1)
            return true;
        else
            return false;
    }

    void push(pair<double, int> n){
        arr.push_back(n);
        int  pos=len;
        pair<double, int> t;
        while(pos/2 > 0){
            if(arr[pos/2].first > arr[pos].first){
                t=arr[pos/2];
                arr[pos/2]=arr[pos];
                arr[pos]=t;
                pos=pos/2;
            }
            else
                break;
        }
        len++;
    }

    pair<double, int> minimum(){
        if(len>1)
            return arr[1];
        else{
            cout<<"Heap is empty\n";
            return {-1,-1};
        }
    }

    int size(){
        return len-1;
    }

    void extractMin(){
        if(len<=1){
            cout<<"Heap is empty\n";
            return;
        }

        arr[1]=arr[--len];
        arr.pop_back();
        int i=1, l, r, smallest;
        pair<double, int> t;

        while(i<len){
            l=leftchild(i);
            r=rightchild(i);

            if(l<len && arr[l]<arr[i])
                smallest=l;
            else
                smallest=i;

            if(r<len && arr[r]<arr[smallest])
                smallest=r;

            if(smallest!=i){
                t=arr[i];
                arr[i]=arr[smallest];
                arr[smallest]=t;
                i=smallest;
            }
            else
                break;
        }
    }

};

