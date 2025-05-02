#include<bits/stdc++.h>

using namespace std;

vector<string> arr;
#define c1 999773
#define c2 449
//5099
//9949
//10007

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

    for(auto str : ss)
    {
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

//h2=(a*key+b)
long long h2(string key, long long m)
{
    long long res=0;
    for(long long i=0; i<key.size(); i++)
    {
        res+=(key[i]-'a'+1)*pow(39,i);
        res=res%m;
    }
    res=(9199*res+4181) % m;
    return res;
}

void checkH1(long long m)
{
    set<long long> a;
    long long count=0;
    for(long long i=0; i<arr.size(); i++)
    {
        a.insert(h1(arr[i],m));
        count++;
    }
    cout<<fixed<<"For H1: "<<(double)a.size()/(double)count*100<<"%\n";
}

void checkH2(long long m)
{
    set<long long> a;
    long long count=0;
    for(long long i=0; i<arr.size(); i++)
    {
        a.insert(h2(arr[i], m));
        count++;
    }
    cout<<fixed<<"For H2: "<<(double)a.size()/(double)count*100<<"%\n";
}

class Hash
{
    Node* hashTable[60000];
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

    void linearInsert(string key, long long value)    //some problem
    {
        Node* newNode=new Node(key, value);
        long long ind=h1(key, maxSize);

        for(long long i=0; i<maxSize; i++)
        {
            ind=(ind+i)%maxSize;
            if(hashTable[ind]==NULL)
            {
                hashTable[ind]=newNode;
                currSize++;
                return;
            }
            else if(hashTable[ind]==demo)
            {
                hashTable[ind]=newNode;
                currSize++;
                return;
            }
            else
                continue;
        }
    }

    void linearDelete(string key)
    {
        long long ind=h1(key, maxSize);
        Node* pt;
        for(long long i=0; i<maxSize; i++)
        {
            ind=(ind+i)%maxSize;
            if(hashTable[ind]==NULL)
                break;
            if(hashTable[ind]->key == key)
            {
                pt=hashTable[ind];
                hashTable[ind]=demo;
                currSize--;
                delete pt;
            }
        }
    }

    long long linearSearch(string key)
    {
        prob=0;
        long long ind=h1(key, maxSize);
        for(long long i=0; i<maxSize; i++)
        {
            prob++;
            ind=(ind+i)%maxSize;
            if(hashTable[ind]==NULL)
                return prob;
            if(hashTable[ind]->key == key)
                return prob;
            //return hashTable[ind]->key;
        }
        //cout<<"key not found\n";
        return prob;
    }

    void quadraticInsert(string key, long long value)
    {
        Node* newNode=new Node(key, value);
        long long ind=h1(key, maxSize);

        for(long long i=0; i<maxSize; i++)
        {
            ind=(ind+c1*i+c2*i*i)%maxSize;
            if(hashTable[ind]==NULL)
            {
                hashTable[ind]=newNode;
                currSize++;
                return;
            }
            else if(hashTable[ind]==demo)
            {
                hashTable[ind]=newNode;
                currSize++;
                return;
            }
            else
                continue;
        }
    }

    void quadraticDelete(string key)
    {
        long long ind=h1(key, maxSize);
        Node* pt;
        for(long long i=0; i<maxSize; i++)
        {
            ind=(ind+(c1*i)+(c2*i*i))%maxSize;
            if(hashTable[ind]==NULL)
                break;
            if(hashTable[ind]->key == key)
            {
                pt=hashTable[ind];
                hashTable[ind]=demo;
                currSize--;
                delete pt;
            }
        }
    }

    long long quadraticSearch(string key)
    {
        prob=0;
        long long ind=h1(key, maxSize);
        for(long long i=0; i<maxSize; i++)
        {
            prob++;
            ind=(ind+c1*i+c2*i*i)%maxSize;
            if(hashTable[ind]==NULL)
                return prob;
            if(hashTable[ind]->key == key)
                return prob;
//                return hashTable[ind]->key;
        }
        //cout<<"key not found\n";
        return prob;
    }

    void doubleInsert(string key, long long value)    //some problem
    {
        Node* newNode=new Node(key, value);
        long long ind1=h1(key, maxSize);
        long long ind2=h2(key, maxSize);
        long long ind=0;

        for(long long i=0; i<maxSize; i++)
        {
            ind=(ind1+i*ind2)%maxSize;
            if(hashTable[ind]==NULL)
            {
                hashTable[ind]=newNode;
                currSize++;
                return;
            }
            else if(hashTable[ind]==demo)
            {
                hashTable[ind]=newNode;
                currSize++;
                return;
            }
            else
                continue;
        }
    }

    void doubleDelete(string key)
    {
        long long ind1=h1(key, maxSize);
        long long ind2=h2(key, maxSize);
        long long ind=0;
        Node* pt;
        for(long long i=0; i<maxSize; i++)
        {
            ind=(ind1+i*ind2)%maxSize;
            if(hashTable[ind]==NULL)
                break;
            if(hashTable[ind]->key == key)
            {
                pt=hashTable[ind];
                hashTable[ind]=demo;
                currSize--;
                delete pt;
            }
        }
    }

    long long doubleSearch(string key)
    {
        prob=0;
        long long ind1=h1(key, maxSize);
        long long ind2=h2(key, maxSize);
        long long ind=0;

        for(long long i=0; i<maxSize; i++)
        {
            prob++;
            ind=(ind1+i*ind2)%maxSize;
            if(hashTable[ind]==NULL)
                return prob;
            if(hashTable[ind]->key == key)
                return prob;
//                return hashTable[ind]->key;
        }
        //cout<<"key not found\n";
        return prob;
    }

    long long length()
    {
        return currSize;
    }

    long long probing()
    {
        return prob;
    }
    void resetProb()
    {
        prob=0;
    }

};

void testHash()
{
    stringGenerator(100);
    checkH1(200);
    checkH2(200);
}


int main()
{
    long long n=0;
    testHash();
    long long test,skey;
    cin>>n;
    double loadFactor[6] = {0.4,0.5,0.6,0.7,0.8,0.9};
    vector<double> avgSearchTimeBefore(6,0);
    vector<double> avgSearchTimeAfter(6,0);
    vector<double> linAvgSearchTimeBefore(6,0);
    vector<double> linAvgSearchTimeAfter(6,0);
    vector<double> quadAvgSearchTimeBefore(6,0);
    vector<double> quadAvgSearchTimeAfter(6,0);
    vector<double> dubAvgSearchTimeBefore(6,0);
    vector<double> dubAvgSearchTimeAfter(6,0);
    vector<double> linProbBefore(6,0);
    vector<double> linProbAfter(6,0);
    vector<double> quadProbBefore(6,0);
    vector<double> quadProbAfter(6,0);
    vector<double> dubProbBefore(6,0);
    vector<double> dubProbAfter(6,0);
    vector<string> deleted;

    clock_t timepassed=clock();
    long long length=0;
    ofstream file;
    file.open("Hashing.csv");

    ///separate chain
    file<<"Table 1: Performance of separate chaining in various load factors"<<endl;
    file<<",Before Deletion, After Deletion"<<endl;
    file<<"Load factor, Avg search time, Avg search time"<<endl;
    for(long long l=0; l<6; l++)
    {
        Hash sc(n);
        stringGenerator(n*loadFactor[l]);
        test=(long long)n*loadFactor[l]*0.1;
        for(long long i=0; i<arr.size(); i++)
        {
            sc.chainInsert(arr[i],i);
        }

        //before
        srand(time(NULL));
        timepassed = clock();
        for(long long c=0; c<test; c++)
        {
            skey=rand()%arr.size();
            sc.chainSearch(arr[skey]);
        }
        avgSearchTimeBefore[l]=double(clock()-timepassed)/test;

        for(long long c=0; c<test; c++)
        {
            skey=rand()%arr.size();
            sc.chainDelete(arr[skey]);
            deleted.push_back(arr[skey]);
            arr.erase(arr.begin()+skey);
        }

        //after
        timepassed=clock();
        for(long long i=0; i<test/2; i++)
        {
            skey=rand()%deleted.size();
            sc.chainSearch(deleted[skey]);
        }
        for(long long i=0; i<test/2; i++)
        {
            skey=rand()%arr.size();
            sc.chainSearch(arr[skey]);
        }
        avgSearchTimeAfter[l]=double(clock()-timepassed)/test;

        file<<loadFactor[l]<<","<<avgSearchTimeBefore[l]<<","<<avgSearchTimeAfter[l]<<endl;
        deleted.clear();
    }

    file<<endl<<endl;


    ///linear probing
    file<<"Table 2: Performance of linear probing in various load factors"<<endl;
    file<<",Before Deletion,, After Deletion"<<endl;
    file<<"Load factor, Avg search time, Avg number of probes, Avg search time, Avg number of probes"<<endl;
    for(long long l=0; l<6; l++)
    {
        Hash lin(n);
        lin.resetProb();
        stringGenerator(n*loadFactor[l]);
        test=(long long)n*loadFactor[l]*0.1;
        for(long long i=0; i<arr.size(); i++)
        {
            lin.linearInsert(arr[i],i);
        }

        //before
        srand(time(NULL));
        timepassed = clock();
        for(long long c=0; c<test; c++)
        {
            skey=rand()%arr.size();
            linProbBefore[l]+=lin.linearSearch(arr[skey]);
        }
        linAvgSearchTimeBefore[l]=double(clock()-timepassed)/test;
        linProbBefore[l]=linProbBefore[l]/test;

        for(long long c=0; c<test; c++)
        {
            skey=rand()%arr.size();
            lin.linearDelete(arr[skey]);
            deleted.push_back(arr[skey]);
            arr.erase(arr.begin()+skey);
        }

        //after
        lin.resetProb();
        timepassed=clock();
        for(long long i=0; i<test/2; i++)
        {
            skey=rand()%deleted.size();
            linProbAfter[l]+=lin.linearSearch(deleted[skey]);
        }
        for(long long i=0; i<test/2; i++)
        {
            skey=rand()%arr.size();
            linProbAfter[l]+=lin.linearSearch(arr[skey]);
        }
        linAvgSearchTimeAfter[l]=double(clock()-timepassed)/test;
        linProbAfter[l]=linProbAfter[l]/test;

        file<<loadFactor[l]<<","<<linAvgSearchTimeBefore[l]<<","<<linProbBefore[l]<<","<<linAvgSearchTimeAfter[l]<<","<<linProbAfter[l]<<endl;
        deleted.clear();
    }

    file<<endl<<endl;

    ///quadratic probing
    file<<"Table 3: Performance of quadratic probing in various load factors"<<endl;
    file<<",Before Deletion,, After Deletion"<<endl;
    file<<"Load factor, Avg search time, Avg number of probes, Avg search time, Avg number of probes"<<endl;
    for(long long l=0; l<6; l++)
    {
        Hash quad(n);
        quad.resetProb();
        stringGenerator(n*loadFactor[l]);
        test=(long long)n*loadFactor[l]*0.1;
        for(long long i=0; i<arr.size(); i++)
        {
            quad.quadraticInsert(arr[i],i);
        }

        //before
        quad.resetProb();
        srand(time(NULL));
        timepassed = clock();
        for(long long c=0; c<test; c++)
        {
            skey=rand()%arr.size();
            quadProbBefore[l]+=quad.quadraticSearch(arr[skey]);
        }
        quadAvgSearchTimeBefore[l]=double(clock()-timepassed)/test;
        quadProbBefore[l]= quadProbBefore[l]/test;


        for(long long c=0; c<test; c++)
        {
            skey=rand()%arr.size();
            quad.quadraticDelete(arr[skey]);
            deleted.push_back(arr[skey]);
            arr.erase(arr.begin()+skey);
        }


        //after
        quad.resetProb();
        timepassed=clock();
        for(long long i=0; i<test/2; i++)
        {
            skey=rand()%deleted.size();
            quadProbAfter[l]+=quad.quadraticSearch(deleted[skey]);
        }
        for(long long i=0; i<test/2; i++)
        {
            skey=rand()%arr.size();
            quadProbAfter[l]+=quad.quadraticSearch(arr[skey]);
        }
        quadAvgSearchTimeAfter[l]=double(clock()-timepassed)/test;
        quadProbAfter[l]=quadProbAfter[l]/test;

        file<<loadFactor[l]<<","<<quadAvgSearchTimeBefore[l]<<","<<quadProbBefore[l]<<","<<quadAvgSearchTimeAfter[l]<<","<<quadProbAfter[l]<<endl;
        deleted.clear();
    }

    file<<endl<<endl;

    ///double hashing
    file<<"Table 4: Performance of double hashing in various load factors"<<endl;
    file<<",Before Deletion,, After Deletion"<<endl;
    file<<"Load factor, Avg search time, Avg number of probes, Avg search time, Avg number of probes"<<endl;
    for(long long l=0; l<6; l++)
    {
        Hash dub(n);
        dub.resetProb();
        stringGenerator(n*loadFactor[l]);
        test=(long long)n*loadFactor[l]*0.1;
        for(long long i=0; i<arr.size(); i++)
        {
            dub.doubleInsert(arr[i],i);
        }

        //before
        dub.resetProb();
        srand(time(NULL));
        timepassed = clock();
        for(long long c=0; c<test; c++)
        {
            skey=rand()%arr.size();
            dubProbBefore[l]+=dub.doubleSearch(arr[skey]);
        }
        dubAvgSearchTimeBefore[l]=double(clock()-timepassed)/test;
        dubProbBefore[l]=dubProbBefore[l]/test;

        for(long long c=0; c<test; c++)
        {
            skey=rand()%arr.size();
            dub.doubleDelete(arr[skey]);
            deleted.push_back(arr[skey]);
            arr.erase(arr.begin()+skey);
        }

        //after
        dub.resetProb();
        timepassed=clock();
        for(long long i=0; i<test/2; i++)
        {
            skey=rand()%deleted.size();
            dubProbAfter[l]+=dub.doubleSearch(deleted[skey]);
        }
        for(long long i=0; i<test/2; i++)
        {
            skey=rand()%arr.size();
            dubProbAfter[l]+=dub.doubleSearch(arr[skey]);
        }
        dubAvgSearchTimeAfter[l]=double(clock()-timepassed)/test;
        dubProbAfter[l]=dubProbAfter[l]/test;

        file<<loadFactor[l]<<","<<dubAvgSearchTimeBefore[l]<<","<<dubProbBefore[l]<<","<<dubAvgSearchTimeAfter[l]<<","<<dubProbAfter[l]<<endl;
        deleted.clear();
    }

    file<<endl<<endl;


    //performance measurement
    for(long long i=0; i<6; i++)
    {
        file<<"Table "<<(i+5)<<": Performance of various collision resolution methods in load factor "<<loadFactor[i]<<endl;
        file<<",Before Deletion,, After Deletion"<<endl;
        file<<"Method, Avg search time, Avg number of probes, Avg search time, Avg number of probes"<<endl;
        file<<"Separate Chaining,"<<avgSearchTimeBefore[i]<<",N/A,"<<avgSearchTimeAfter[i]<<",N/A"<<endl;
        file<<"Linear Probing,"<<linAvgSearchTimeBefore[i]<<","<<linProbBefore[i]<<","<<linAvgSearchTimeAfter[i]<<","<<linProbAfter[i]<<endl;
        file<<"Quadratic Probing,"<<quadAvgSearchTimeBefore[i]<<","<<quadProbBefore[i]<<","<<quadAvgSearchTimeAfter[i]<<","<<quadProbAfter[i]<<endl;
        file<<"Double Hashing,"<<dubAvgSearchTimeBefore[i]<<","<<dubProbBefore[i]<<","<<dubAvgSearchTimeAfter[i]<<","<<dubProbAfter[i]<<endl;
        file<<endl<<endl;
    }

    file.close();
}


