#include<bits/stdc++.h>

using namespace std;

vector<string> arr;
#define c1 999773
#define c2 449

//5099
//9949
//10007




long long calPrime(int n){
    vector<int>pri(1000001,1);
    vector<int>prime;
    pri.assign(1000001,1);
    prime.clear();
    long long p;
    for(int i=2;i<=sqrt(n);i++){
        if(pri[i]==1){
            int j=2*i;
            while(j<=n){
                pri[j]=0;
                j+=i;
            }
        }
    }

    for(int i=2;i<=n;i++){
        if(pri[i]==1){
            prime.push_back(i);
        }
    }

    for(int i=0;i<prime.size();i++){
        p=prime[i];
    }
    return p;
}

class Node
{
public:
    string key;
    long long value;
    Node* next;

    Node(string k="", long long v=-1)
    {
        key=k;
        value=v;
        next=NULL;
    }
};

void stringGenerator(long long n)
{
    long long seed;
    string s="";
    arr.clear();
    unordered_set<string> ss;
    long long t=1,a=0,count=0;
    while(a<n)
    {
        while(t<8)
        {
            count++;
            seed=time(NULL)*t*(a+count);
            srand(seed);
            s+=('a'+rand()%26);
            t++;
        }
        ss.insert(s);
        s="";
        a=ss.size();
        t=1;
    }

    for(auto str : ss){
        arr.push_back(str);
    }
}
//polynomial rolling
long long h1(string key, long long m)
{
    long long res=0;
    for(long long i=0; i<key.size(); i++)
    {
        res+=(key[i]-'a'+1)*pow(31,i);
        res=res%m;
    }
    return res;
}


class Hash
{
    Node* hashTable[1000];
    Node* demo;
    long long maxSize;
    long long currSize;
    long long prob;

public:
    Hash(long long n)
    {
        maxSize=n;
        prob=0;
        currSize=0;
        demo=new Node("nil",-1);
        for(long long i=0; i<1000; i++)
        {
            hashTable[i]=NULL;
        }

    }

    void chainInsert(string key, long long value)
    {
        Node* newNode=new Node(key, value);

        long long ind=h1(key, maxSize);
        Node* pt =hashTable[ind];
        Node* temp=NULL;
        if(pt==NULL)
            hashTable[ind]=newNode;
        else
        {
            while(pt!=NULL)
            {
                temp=pt;
                pt=pt->next;
            }
            pt=newNode;
            temp->next=pt;
        }
        currSize++;
    }

    void chainDelete(string key)
    {
        long long ind=h1(key, maxSize);
        Node* pt = hashTable[ind];
        Node* temp=pt;
        if (pt!=NULL && pt->key == key)
        {
            hashTable[ind]=hashTable[ind]->next;
            delete pt;
            currSize--;
            return;
        }
        while(pt !=NULL)
        {
            if(pt->key == key)
            {
                temp->next=temp->next->next;
                delete pt;
                currSize--;
                return;
            }
            else
            {
                temp=pt;
                pt=pt->next;
            }
        }
    }

    string chainSearch(string key)
    {
        long long ind=h1(key, maxSize);
        Node* pt =hashTable[ind];
        while(pt !=NULL)
        {
            if(pt->key == key)
                return pt->key;
            else
                pt=pt->next;
        }
        //cout<<"key not found\n";
        return "";
    }

    void chainPrint()
    {
        Node* pt;
        for(long long i=0; i<maxSize; i++)
        {
            pt=hashTable[i];
            while(pt!=NULL)
            {
                cout<<"("<<pt->key<<", "<<pt->value<<") ";
                pt=pt->next;
            }
            cout<<endl;
        }
    }

    long long maxLength(){
        Node* pt;
        long long len=0;
        long long maxlen=0;
        for(long long i=0; i<maxSize; i++)
        {
            len=0;
            pt=hashTable[i];
            while(pt!=NULL)
            {
                len++;
                pt=pt->next;
            }
            if(len>maxlen)
            {
                maxlen=len;
            }
        }
        return maxlen;
    }

    void rehash(double val){
        long long s =val*maxSize;
        s=int(s+1);
        long long size = calPrime(s+1);
        Node* demo[maxSize];
        Node* pt;
        Node* pt2;
        for(long long i=0; i<maxSize; i++)
        {
            pt=hashTable[i];
            pt2=
            while(pt!=NULL)
            {
                demo[i]->key=pt->key<<", "<<pt->value<<") ";
                pt=pt->next;
            }
            cout<<endl;
        }

    }
};




int main(){
    int n, load;
    cin>>n>>load;

    Hash a(n);
    stringGenerator(10000);

    for(int i=0; i<100; i++){
        a.chainInsert(arr[i],i);
    }
    a.chainPrint();
    if(a.maxLength()>10)
        a.rehash(1.2);



}
