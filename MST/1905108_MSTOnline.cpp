#include<bits/stdc++.h>
#include<fstream>

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
    if(a.edgeWeight()>=b.edgeWeight())
        return true;
    else
        return false;
}

class Graph{
    int vertex;
    int edge;
    double mstWeight;
    int mstEdge;
    vector<pair<int, double> > adj[10000];
    vector<int> mstNode[10000];
    vector<Edge> edges;
    int parent[10000];
    int road;

public:
    Graph(){
        vertex=0;
        edge=0;
        mstWeight=0;
        mstEdge=0;
        road=0;
    }
    Graph(int a, int b){
        vertex=a;
        edge=b;
        mstWeight=0;
        mstEdge=0;
        road=0;
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
        for(int i=1; i<=vertex; i++){
            for(int j=0; j<adj[i].size(); j++)
                cout<<i<<"-"<<adj[i][j].first<<" : "<<adj[i][j].second<<endl;
        }
    }

    int kruskal(int test){
        int u,v;
        double w;
        for(int i=0; i<vertex; i++)
            parent[i]=i;
        sort(edges.begin(), edges.end(), cmp);

        for(int i=0; i<edges.size(); i++){
            u=edges[i].edgeU();
            v=edges[i].edgeV();
            w=edges[i].edgeWeight();
            if(w=test) //for either men or women
            {

                if(findParent(u)!=findParent(v)){
                    mstNode[u].push_back(v);
                    mstWeight+=(double)edges[i].edgeWeight();
                    mstEdge++;
                    //each of  them have to be in the same set
                    makeSet(u, v);

                }
                else
                    road++;
            }
        }
       // if(mstEdge<vertex-1)
         //   return 0;
        //else{
           cout<<endl<<road<<endl;
            return road;
        //}

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

    void printMST(){
        int count=1;
        if(mstEdge<vertex-1)
        {
            cout<<"MST is not possible\n";
            return;
        }
        //cout<<"Cost of the minimum spanning tree : "<<mstWeight<<endl;
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


};

int main(){
    int v,e,a,b;
    double w;
    Graph gmen,gwo;

    ifstream myfile("mst4.txt");       //Input from file
    if(myfile.is_open()){
        while(!myfile.eof()){
            myfile>>v>>e;
            gmen.addNumOfVE(v,e);
            gwo.addNumOfVE(v,e);
            for(int i=0; i<e; i++){
                myfile>>a>>b>>w;
                gmen.addEdge(a,b,w);
                gwo.addEdge(a,b,w);
            }
        }
        myfile.close();
    }
    int men=0, women=0;
        men=gmen.kruskal(1);
        women=gwo.kruskal(2);

        if(men==0 || women==0)
            cout<<-1;
        else
            cout<<(men+women);



}
