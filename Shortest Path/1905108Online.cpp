#include<bits/stdc++.h>

using namespace std;

class Graph
{
    int vertex;
    int edge;
    vector<pair<int, double> > adj[50];
    int visited[50];
    int parent[50];
    double d[50];
    bool neg;
    double precost;
    vector<int> ans;

public:
    Graph()
    {
        vertex=0;
        edge=0;
        memset(visited, -1, sizeof visited);
        memset(parent, -1, sizeof parent);
        neg=false;
    }
    Graph(int a, int b)
    {
        vertex=a;
        edge=b;
        memset(visited, -1, sizeof visited);
        memset(parent, -1, sizeof parent);
        bool neg=false;
    }

    void addNumOfVE(int a,int b)
    {
        vertex=a;
        edge=b;
    };


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
    }

    void belford(int s, int des)        //O(VE)
    {
        //init
        int u,v, flag=1;
        double w;
        for(int i=0; i<vertex; i++)         //O(V)
        {
            d[i]=INT_MIN;
            parent[i]=-1;
        }
        d[s]=1.0;
        for(int n=0; n<vertex-1; n++)         //v times
        {
            for(u=0; u<vertex; u++)
            {
                for(int i=0; i<adj[u].size(); i++)      //total E times
                {
                    v= adj[u][i].first;
                    w= adj[u][i].second;
                    relax(u, v, w);
                }
            }
        }

        precost=d[des];

        //for(int n=0; n<vertex; n++)                 //total V times
        //{
            for(u=0; u<vertex; u++)
            {
                for(int i=0; i<adj[u].size(); i++)      //total E times
                {
                    v= adj[u][i].first;
                    w= adj[u][i].second;
                    if(d[v]<d[u]*w)
                        flag=-1;
                    //relax(u, v, w);

                }
            }
        //}


        if(flag==1)
            printBelford(s, des);
        else{
            cout<<"There is an increasing cycle\n";
            //if(precost == d[des])
                //printBelford(s, des);
        }
    }

    void relax(int u, int v, double w)
    {
        if(d[v]< 1.0*d[u]*w)
        {
            d[v]=1.0*d[u]*w;
            parent[v]=u;
        }
    }

    void printBelford(int src, int des)
    {
        int dst=des;

        cout<<"Most reliable path score: "<<d[des]<<endl;

        stack<int> sp;

        while(parent[des]!=src)
        {
            sp.push(parent[des]);
            des=parent[des];
        }
        sp.push(src);

        while(!sp.empty())
        {
            cout<<sp.top()<<" -> ";
            sp.pop();
        }
        cout<<dst<<endl;
    }
};

int main()
{
    freopen("Online.in", "r", stdin);

    int v,e,a,b;
    int src, des;
    double w;
    Graph g;
    cin>>v>>e;
    g.addNumOfVE(v,e);
    for(int i=0; i<e; i++){
        cin>>a>>b;
        cin>>w;
        g.addEdge(a,b,w);
    }
    cin>>src>>des;

    g.belford(src, des);
}

