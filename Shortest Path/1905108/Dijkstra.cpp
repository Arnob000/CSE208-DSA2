#include<bits/stdc++.h>
#define INF 100000007

using namespace std;

class Graph{
    int vertex;
    int edge;
    vector<pair<int, double> > adj[50];
    int visited[50];
    int parent[50];
    double d[50];
    bool neg;
    vector<int> ans;

public:
    Graph(){
        vertex=0;
        edge=0;
        memset(visited, -1, sizeof visited);
        memset(parent, -1, sizeof parent);
        neg=false;
    }
    Graph(int a, int b){
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


    void printGraph(){
        for(int i=0; i<vertex; i++){
            for(int j=0; j<adj[i].size(); j++)
                cout<<i<<"-"<<adj[i][j].first<<" : "<<adj[i][j].second<<endl;
        }
    }


    void addEdge(int a, int b, double w){
        adj[a].push_back(make_pair((int)b,(double)w));
        //adj[b].push_back(make_pair((int)a,(double)w));
        if(w<0)
            neg=true;
    }

    void dijkstra(int s){       //O(V+ElogV)
        if(neg)
            return;
        //init
        int u,v;
        double w;
        for(int i=0; i<vertex; i++){        //O(V)
            d[i]=INF;
            parent[i]=-1;
        }
        d[s]=0;
        priority_queue<pair<double,int> ,vector<pair<double, int> >, greater<pair<double, int> > > pq;

        pq.push({d[s],s});
        while(!pq.empty()){     //v times
            u=pq.top().second;      //O(1)
            pq.pop();
            if(visited[u]==1)
                continue;
            ans.push_back(u);   //for all shortest path from u
            visited[u]=1;
            for(int i=0; i<adj[u].size(); i++){     //total E times
                v= adj[u][i].first;
                w= adj[u][i].second;
                relax(u, v, w);
                pq.push({d[v],v});      //O(logV)
            }
        }
    }

    void relax(int u, int v, double w){
        if(d[v]> d[u]+w){
            d[v]=d[u]+w;
            parent[v]=u;
        }
    }

    void printSSP(int src, int des){
        int dst=des;
         if(neg){
            cout<<"Negative weighted edges";
            return;
        }

        cout<<"Shortest path cost: "<<d[des]<<endl;

        stack<int> sp;

        while(parent[des]!=src){
            sp.push(parent[des]);
            des=parent[des];
        }
        sp.push(src);

        while(!sp.empty()){
            cout<<sp.top()<<" -> ";
            sp.pop();
        }
        cout<<dst<<endl;
    }
};

int main(){
    freopen("ssp.in", "r", stdin);

    int v,e,a,b;
    int src, des;
    double w;
    Graph g;
    cin>>v>>e;
    g.addNumOfVE(v,e);
    for(int i=0; i<e; i++){
        cin>>a>>b>>w;
        g.addEdge(a,b,w);
    }
    cin>>src>>des;

    g.dijkstra(src);
    g.printSSP(src, des);
}
