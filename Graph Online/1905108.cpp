#include<bits/stdc++.h>
#include<queue>

using namespace std;

class Graph{
    int v;
    int e;
    vector<int> adj[50];
    int visited[50];

public:
    Graph(){}
    Graph(int a){
        v=a;
        memset(visited,0,sizeof visited);
    }

    void addEdge(int a, int b){
        adj[a].push_back(b);
    }
    void printGraph(){
        for(int i=0; i<v; i++){
            //for(int j:adj[i])
            for(int j=0; j<adj[i].size(); j++)
                cout<<i<<"-"<<adj[i][j]<<endl;
        }
    }
    int checkbfs(int u, int v){
        int a,count=0;
        queue<int> q;
        visited[u]=1;
        q.push(u);

        while(!q.empty()){
            a=q.front();
            q.pop();
            for(int ver=0; ver<adj[a].size(); ver++){
                if(adj[a][ver]==v){
                    return ++count;
                }
                if(visited[adj[a][ver]]!=1){
                    visited[adj[a][ver]]=1;
                    q.push(adj[a][ver]);

                }
            }
            count++;
        }

    }

};


int main(){
    string s;
    cin>>s;
    int l=s.length();
    int count;

    char first, last;
    first=0;
    last=s.length()-1;

    Graph g(l);
    for(int i=0; i<l; i++){
            for(int j=0; j<l; j++){
                if(s[i]==s[j] && i!=j)
                    g.addEdge(i,j);

            }
            if(i+1<l)
                g.addEdge(i,i+1);
            if(i-1 >=0)
                g.addEdge(i,i-1);
    }
    cout<<g.checkbfs(first,last)<<endl;


}
