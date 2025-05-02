#include<bits/stdc++.h>
#include<string>

using namespace std;

#define INF 10000007
vector<int> rVertex;
vector<int> oVertex;
int team,flag;
string name[50];
int win[50];
int loss[50];
int lef[50];
int g[50][50];

class Edge{
    int first;
    int last;
    double capacity;
    int flow;
public:
    Edge(){}
    Edge(int a,int b, double w){
        first=a;
        last=b;
        capacity=w;
        flow=0;
    }
    int edgeU(){
        return first;
    }
    int edgeV(){
        return last;
    }

    void loadFlow(int f){
        flow=f;
    }

    int showFlow(){
        return flow;
    }

    double edgeCapacity(){
        return capacity;
    }
    void print(){
        cout<<first<<"-"<<last<<" : "<<capacity<<":"<<flow<<endl;
    }
};


class Graph{
    int vertex;
    int edge;
    int V[50];
    int count;
    vector<pair<int, double> > adj[100];
    double resMat[100][100];
    int parent[100];
    int visited[100];
    vector<Edge> edges;

public:
    Graph(){
        vertex=0;
        edge=0;
        count=0;
        memset(resMat, 0, sizeof resMat);
    }
    Graph(int a, int b){
        vertex=a;
        edge=b;
        count=0;
        memset(resMat, 0, sizeof resMat);
    }

    void clear(){
        memset(resMat,0,sizeof resMat);
        for(int i=0; i<vertex; i++){
            adj[i].clear();
        }
        edges.clear();
    }

    void addNumOfVE(int a,int b){
        vertex=a;
        edge=b;
    }

    void printGraph(){
        for(int i=0; i<vertex; i++){
            for(int j=0; j<adj[i].size(); j++)
                cout<<V[i]<<"-"<<V[adj[i][j].first]<<" : "<<adj[i][j].second<<endl;
        }
        cout<<endl;
    }

    void addEdge(int a, int b, double w){
        int one=-1, two=-1;
        for(int i=0; i<count; i++){
            if(V[i]==a)
                one=i;
            if(V[i]==b)
                two=i;
        }

        if(one==-1){
            one=count++;
            V[one]=a;
        }
        if(two==-1){
            two=count++;
            V[two]=b;
        }

        adj[one].push_back(make_pair((int)two,(double)w));
        resMat[one][two]=w;
        Edge e(one,two,w);
        edges.push_back(e);
    }

    bool bfs(int u, int des){
        int a;
        queue<int> q;
        memset(visited,0,sizeof visited);
        memset(parent, -1, sizeof parent);

        visited[u]=1;
        q.push(u);

        while(!q.empty()){
            a=q.front();
            q.pop();
            for(int ver=0; ver<vertex; ver++){
                if(a!=ver && visited[ver]!=1 && resMat[a][ver]>0){
                    visited[ver]=1;
                    q.push(ver);
                    parent[ver]=a;
                    if(ver==des)
                        return true;
                }
            }
        }
        return false;
    }

    int edmonKarp(int s, int t){       //O(VE*numOfPath) //for bfs O(VE^2)    //INCLUDING EXTRA O((VE)^2+VE^3)
        bool findPath;
        int node;
        double minflow, maxflow=0;

        for(int i=0; i<vertex; i++){
            if(V[i]==s)
                s=i;
            if(V[i]==t)
                t=i;
        }
        //for every path
        //augment the flow
        while(true){                 //ORIGINAL O(V^2E+VE^2)=O(VE^2) //INCLUDING EXTRA O((VE)^2+VE^3)
            findPath=bfs(s,t);      //SINGLE O(V+E) //TOTAL O(VE+E^2)
            node=t;
            if(findPath){
                minflow=INF;
                //find minflow in a path
                while(node!=s){          //O(V)
                    if(minflow>resMat[parent[node]][node])
                        minflow=resMat[parent[node]][node];
                    node=parent[node];
                }
                maxflow+=minflow;
                //update graph
                node=t;
                while(node!=s){          //V TIMES
                    resMat[parent[node]][node]-=minflow;
                    resMat[node][parent[node]]+=minflow;
                    for(int i=0; i<edge; i++){          //O(E)  //EXTRA
                        if(edges[i].edgeU()==parent[node] && edges[i].edgeV()==node){
                                edges[i].loadFlow(edges[i].showFlow()+minflow);
                        }
                        else if(edges[i].edgeU()==node && edges[i].edgeV()==parent[node]){
                                edges[i].loadFlow(edges[i].showFlow()-minflow);
                        }
                    }
                    node=parent[node];
                }
            }
            else
                break;
        }
        return maxflow;
    }

    void show(){
        for(int i=0; i<vertex; i++){
            cout<<"vertex:"<<i<<":"<<V[i]<<endl;
        }
        cout<<endl;
    }

    void showEdges(){
        for(int i=0; i<edges.size();i++){
            edges[i].print();
        }
    }

    void dfs(int s){
        memset(visited,0,sizeof visited);

        for(int i=0; i<vertex; i++){
            if(V[i]==s)
                s=i;
        }

       /* for(int i=0; i<vertex; i++){
            if(visited[i]!=1)
                dfsUtil(i);
        }*/
        dfsUtil(s);
        visited[s]=1;

        for(int i=0; i<vertex; i++){
            if(visited[i]==1){
                rVertex.push_back(V[i]);
            }
        }
    }

    void dfsUtil(int u){
        for(int i=0; i<edges.size(); i++){
            if(edges[i].edgeU()==u && (edges[i].edgeCapacity()-edges[i].showFlow())>0){
                visited[edges[i].edgeV()]=1;
                dfsUtil(edges[i].edgeV());
            }
        }
    }

};

void printBonus(int ele){
        int w=0,count=0,eachOther=0;

        cout<<name[ele]<<" is eliminated\n";
        cout<<"They can win at most "<<win[ele]<<" + "<<lef[ele]<<" = "<<win[ele]+lef[ele]<<" games.\n";

        for(int j=0; j<oVertex.size(); j++){
            count++;

            if(j==oVertex.size()-1)
                cout<<name[oVertex[j]]<<" ";
            else
                cout<<name[oVertex[j]]<<", ";
            w+=win[oVertex[j]];
        }
        for(int i=0; i<oVertex.size(); i++){
            for(int j=i+1; j<oVertex.size(); j++){
                eachOther+=g[oVertex[i]][oVertex[j]];
            }
        }
        float f=1.0*(w+eachOther)/count;
        cout<<" has won a total of "<<w<<" games.\n";
        cout<<"They play each other "<<eachOther<<" times.\n";
        cout<<"So on average, each of the teams in this group wins "<<w+eachOther<<"/"<<count<<" = "<<f<<" games.\n";
        cout<<endl;
}

int main(){
   // freopen("baseball.in", "r", stdin);
    int t;
    cin>>t;
    int person,v,e;
    int src, des;
    int node=0;
    int man1[50];
    int man2[50];
    int manNode[50];
    int tNode[6];
    int tshirt;
    string tsize,tsize2;
    int t1,t2;
    int n=1;
    while(n<=t){
        n++;
        cin>>tshirt>>person;

        for(int i=0; i<person; i++){
                cin>>tsize>>tsize2;
                if(tsize=="XXL")
                    t1=0;
                else if(tsize=="XL")
                    t1=1;
                else if(tsize=="L")
                    t1=2;
                else if(tsize=="M")
                    t1=3;
                else if(tsize=="S")
                    t1=4;
                else if(tsize=="XS")
                    t1=5;

                if(tsize2=="XXL")
                    t2=0;
                else if(tsize2=="XL")
                    t2=1;
                else if(tsize2=="L")
                    t2=2;
                else if(tsize2=="M")
                    t2=3;
                else if(tsize2=="S")
                    t2=4;
                else if(tsize2=="XS")
                    t2=5;


            man1[i]=t1;
            man2[i]=t2;
        }
        src=0;
        node=0;
        for(int j=0; j<person; j++){
            manNode[j]=++node;
        }
        for(int j=0; j<6; j++){
            tNode[j]=++node;
        }
        des=++node;


        //
        Graph graph;

        v=person+6+2;
        e=person+6+(person*6);

        graph.addNumOfVE(v,e);

        //graph

        for(int j=0; j<person; j++){
                graph.addEdge(src,manNode[j],1);
        }
        for(int j=0; j<person; j++){
            for(int k=0; k<6; k++){
                    if(man1[j]==k)
                        graph.addEdge(manNode[j], tNode[k], 1);
                    if(man2[j]==k)
                        graph.addEdge(manNode[j],tNode[k], 1);
                    else
                        graph.addEdge(manNode[j],tNode[k], 0);
            }
        }
        for(int j=0; j<6; j++){
                graph.addEdge(tNode[j],des,3);
        }


        int maxflow=graph.edmonKarp(src,des);
        if(maxflow==person)
            cout<<"Case "<<t<<": YES"<<endl;
        else
           cout<<"Case "<<t<<": NO"<<endl;
        graph.clear();

    }



}
