#include<bits/stdc++.h>
#include<fstream>
#define INF 100000007

using namespace std;

class Edge{
    int first;
    int last;
    double weight;
public:
    Edge(){}
    Edge(int a,int b, double w){
        first=a;
        last=b;
        weight=w;
    }
    int edgeU(){
        return first;
    }
    int edgeV(){
        return last;
    }

    double edgeWeight(){
        return weight;
    }
    void print(){
        cout<<first<<"-"<<last<<" : "<<weight<<endl;
    }
};

bool cmp(Edge a, Edge b){       //comparator
    if(a.edgeWeight()<=b.edgeWeight())
        return true;
    else
        return false;
}

class Graph{
    int vertex;
    int edge;
    double mstWeight;
    double mstWeightp;
    int mstEdge;
    vector<pair<int, double> > adj[1000];
    vector<int> mstNode[1000];
    vector<Edge> edges;
    int parent[1000];
    int visited[1000];
    double key[1000];

public:
    Graph(){
        vertex=0;
        edge=0;
        mstWeight=0;
        mstWeightp=0;
        mstEdge=0;
        memset(visited, -1, sizeof visited);
        memset(parent, -1, sizeof parent);
    }
    Graph(int a, int b){
        vertex=a;
        edge=b;
        mstWeight=0;
        mstWeightp=0;
        mstEdge=0;
        memset(visited, -1, sizeof visited);
        memset(parent, -1, sizeof parent);
    }

    void addNumOfVE(int a,int b)
    {
        vertex=a;
        edge=b;
    }

    void addEdge(int a, int b, double w){
        adj[a].push_back(make_pair((int)b,(double)w));
        adj[b].push_back(make_pair((int)a,(double)w));
        Edge e(a,b,w);
        edges.push_back(e);
    }
    void printGraph(){
        for(int i=0; i<vertex; i++){
            for(int j=0; j<adj[i].size(); j++)
                cout<<i<<"-"<<adj[i][j].first<<" : "<<adj[i][j].second<<endl;
        }
    }

    void kruskal(){
        int u,v;
        memset(parent, -1, sizeof parent);
        for(int i=0; i<vertex; i++)
            parent[i]=i;

        sort(edges.begin(), edges.end(), cmp);

        for(int i=0; i<edges.size(); i++){
            u=edges[i].edgeU();
            v=edges[i].edgeV();
            if(findParent(u)!=findParent(v)){
                mstNode[u].push_back(v);
                mstWeight+=(double)edges[i].edgeWeight();
                mstEdge++;
                //each of  them have to be in the same set
                makeSet(u, v);
            }
        }
    }


    void makeSet(int u, int v){
        if(findParent(u)==findParent(v))
            return;
        if(parent[u]==u && parent[v]==v)
            parent[v]=u;
        else if(parent[u]!=u)
            parent[v]=findParent(u);
        else
            parent[u]=findParent(v);
    }

    int findParent(int u){
        int p;
        if(parent[u]==u)
            return u;
        else{
            p= findParent(parent[u]);
            return p;
        }
    }

    void prim(){
        memset(visited, -1, sizeof visited);
        memset(parent, -1, sizeof parent);
        for(int i=0; i<vertex; i++)
            key[i]=INF;
        //pair<weight, node>
        priority_queue<pair<double,int> ,vector<pair<double, int> >, greater<pair<double, int> > > pq;
        key[0]=0;
        parent[0]=-1;
        mstEdge=0;
        pq.push({0,0});
        int ind;
        while(!pq.empty()){             //O(nlogn)
            ind=pq.top().second;
            pq.pop();
            visited[ind]=1;

            for(int v=0; v<adj[ind].size(); v++){
                if(visited[adj[ind][v].first]==-1 && adj[ind][v].second<key[adj[ind][v].first]){
                    parent[adj[ind][v].first]=ind;
                    key[adj[ind][v].first]=adj[ind][v].second;
                    pq.push({adj[ind][v].second, adj[ind][v].first});
                }
            }

        }

        for(int i=0; i<vertex; i++)
        {
            if(parent[i]==-1)
                continue;
            mstWeightp+=key[i];
            mstEdge++;
        }

    }

    void printMSTk(){
        int count=1;
        cout<<"List of edges selected by Kruskal's: {";
        for(int k=0; k<vertex; k++){
            for(int j=0; j<mstNode[k].size(); j++){
                if(count==vertex-1)
                    cout<<"("<<k<<", "<<mstNode[k][j]<<")";
                else
                    cout<<"("<<k<<", "<<mstNode[k][j]<<"), ";
                count++;
            }
        }
        cout<<"}"<<endl;
    }

    void printMSTp(){
        int count=1;
        cout<<"List of edges selected by Prim's: {";
        for(int k=0; k<vertex; k++){
            if(parent[k]==-1)
                continue;
            if(count==vertex-1)
                cout<<"("<<k<<", "<<parent[k]<<")";
            else
                cout<<"("<<k<<", "<<parent[k]<<"), ";
            count++;
        }
        cout<<"}"<<endl;
    }

    void printMST(){            //O(n)
        if(mstEdge<vertex-1)
        {
            cout<<"MST is not possible\n";
            return;
        }
        else{
            cout<<"Cost of the minimum spanning tree : "<<mstWeight<<endl;
            printMSTk();
            printMSTp();
        }
    }

    double getWeightk(){
        return mstWeight;
    }

    double getWeightp(){
        return mstWeightp;
    }

};

int main(){
    int v,e,a,b;
    double w;
    Graph g;

    ifstream myfile("mst.in");       //Input from file
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

    g.kruskal();
    g.prim();

    if(g.getWeightk()!=g.getWeightp()){
        cout<<"MST is not possible\n";
        return 0;
    }
    else
        g.printMST();

}
