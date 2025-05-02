#include<bits/stdc++.h>
#include<ctime>
#include "BinaryHeap.cpp"
#include "FibHeapPQNew.cpp"
#define INF 100000007
#define NODE 50000
#define ADJ 500
using namespace std;


class Graph
{
public:
    int vertex;
    int edge;
    bool neg;
    vector<pair<int, double> > adj[ADJ];

    Graph()
    {
        vertex=0;
        edge=0;
        neg=false;
    }
    Graph(int a, int b)
    {
        vertex=a;
        edge=b;
        neg=false;
    }

    void addNumOfVE(int a,int b)
    {
        vertex=a;
        edge=b;
    }

    void printGraph()
    {
        for(int i=0; i<vertex; i++)
        {
            for(int j=0; j<adj[i].size(); j++)
                cout<<i<<"-"<<adj[i][j].first<<" : "<<adj[i][j].second<<endl;
        }
    }

    void addEdge(int a, int b, double w)
    {
        adj[a].push_back(make_pair((int)b,(double)w));
        adj[b].push_back(make_pair((int)a,(double)w));
        if(w<0)
            neg=true;
    }

};

vector<int> parent;
vector<double> d;
bool neg;
//time
clock_t timeOfFib, timeOfBin;
float tFib, tBin;

 bool relax(int u, int v, double w){
        if(d[v]> d[u]+w){
            d[v]=d[u]+w;
            parent[v]=u;
            return true;
        }
        return false;
    }

//Dijkstra with binary heap
void dijkstraBinaryHeap(Graph g, int s)        //O(VlgV+ElogV)
{
    vector<int> visited;
    visited.assign(NODE,-1);

    if(g.neg)
    {
        neg=g.neg;
        return;
    }
    //init
    int u,v;
    double w;
    for(int i=0; i<g.vertex; i++)         //O(V)
    {
        d[i]=INF;
        parent[i]=-1;
    }
    d[s]=0;
    //priority_queue<pair<double,int> ,vector<pair<double, int> >, greater<pair<double, int> > > pq;
    Heap pq;
    pq.push({d[s],s});
    while(!pq.isEmpty())      //v times
    {
        u=pq.minimum().second;      //O(1)
        pq.extractMin();            //O(logV)

        if(visited[u]==1)
            continue;
        visited[u]=1;

        for(int i=0; i<g.adj[u].size(); i++)      //total E times
        {
            v= g.adj[u][i].first;
            w= g.adj[u][i].second;
            if(relax(u,v,w))
                pq.push({d[v],v});      //O(logV)
        }
    }
}

//Dijkstra with Fibonacci heap
void dijkstraFibHeap(Graph g, int s)        //O(E+VlogV)
{
    vector<int> visited;
    visited.assign(NODE,-1);
    if(g.neg)
    {
        neg=g.neg;
        return;
    }
//init
    int u,v;
    double w;
    for(int i=0; i<g.vertex; i++)         //O(V)
    {
        d[i]=INF;
        parent[i]=-1;
    }

    d[s]=0;
    fibHeap<double, int> pq;
    pq.insert(d[s],s);
    while(!pq.isEmpty())      //v times
    {
        u=pq.minimum();      //O(1)
        pq.extractMin();            //O(logV)

        if(visited[u]==1)
            continue;
        visited[u]=1;

        for(int i=0; i<g.adj[u].size(); i++)      //total E times
        {
            v= g.adj[u][i].first;
            w= g.adj[u][i].second;
            if(relax(u, v, w))
                pq.insert(d[v],v);      //O(1)
            //pq.findRoots();
        }
    }
}


int pSSP(int src, int des)
{
    int dst=des;
    int len=0;
    if(neg)
    {
        cout<<"Negative weighted edges";
        return 0;
    }

    stack<int> sp;
    if(parent[des]==-1)
        return 0;

    while(parent[des]!=src)
    {
        sp.push(parent[des]);
        des=parent[des];
    }
    sp.push(src);

    while(!sp.empty())
    {
        //cout<<sp.top()<<" -> ";
        len++;
        sp.pop();
    }
    //cout<<dst<<endl;
    return len;
}

int main()
{
    clock_t ace=clock();
    int v,e,a,b;
    int src, des;
    double w;
    Graph g;
    float bCost,fCost;
    int bLen, fLen;
    parent.assign(NODE,0);
    d.assign(NODE,0);

    ifstream myfile("input1.txt");
    if(myfile.is_open()){
        while(!myfile.eof()){
            myfile>>v>>e;
            g.addNumOfVE(v,e);
            for(int i=0; i<e; i++){
                myfile>>a>>b>>w;
                g.addEdge(a,b,w);
            }
        }
        myfile.close();
    }

    int test;
    myfile.open("input2.txt");
    ofstream outfile("output.txt");

    if(myfile.is_open()){
        if(!myfile.eof())
            myfile>>test;

            while(test>0){
                test--;
                if(!myfile.eof())
                    myfile>>src>>des;

                parent.assign(NODE,0);
                d.assign(NODE,0);
                timeOfBin=clock();
                dijkstraBinaryHeap(g, src);
                tBin=float(clock()-timeOfBin)/CLOCKS_PER_SEC;
                bLen=pSSP(src, des);
                bCost=d[des];

                parent.assign(NODE,0);
                d.assign(NODE,0);
                timeOfFib=clock();
                dijkstraFibHeap(g, src);
                tFib=float(clock()-timeOfFib)/CLOCKS_PER_SEC;
                fLen=pSSP(src, des);
                fCost=d[des];

                if(bCost==fCost){
                    outfile<<bLen<<" "<<bCost<<" "<<tBin<<" "<<tFib<<endl;
                }
            }

        myfile.close();
        outfile.close();
    }
}

