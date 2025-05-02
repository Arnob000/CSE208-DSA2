#include<bits/stdc++.h>

using namespace std;

#define INF 10000007

class Graph{
    int vertex;
    int edge;
    vector<pair<int, double> > adj[100];
    int parent[100][100];
    double dp[100][100];
    double w[100][100];

public:
    Graph(){
        vertex=0;
        edge=0;
        memset(parent, -1, sizeof parent);
    }
    Graph(int a, int b){
        vertex=a;
        edge=b;
        memset(parent, -1, sizeof parent);
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
        a--;
        b--;
        adj[a].push_back(make_pair((int)b,(double)w));
    }

    void floyd(){
        for(int i= 0; i<vertex; i++){
            for(int j=0; j<vertex; j++){
                if(i==j)
                    dp[i][j]=0;
                else
                    dp[i][j]=INF;

                parent[i][j]=-1;
            }
        }

        for(int i=0; i<vertex; i++){
            for(int j=0; j<adj[i].size(); j++)
                dp[i][adj[i][j].first]=adj[i][j].second;
        }

        for(int k=0; k<vertex; k++){
            for(int i=0; i<vertex; i++){
                for(int j=0; j<vertex; j++){
                   /* if(i==j)
                        continue;
                    else*/ if(dp[i][j]>dp[i][k]+dp[k][j]){
                            if(dp[i][k]+dp[k][j]>=1000000)
                                continue;
                        dp[i][j]=dp[i][k]+dp[k][j];
                        parent[i][j]=k;
                    }
                }
            }
        }

    }

    void printAPSP(){
        for(int i=0; i<vertex; i++){
            if(dp[i][i]<0)
            {
                cout<<"Negative cycle\n";
                return;
            }
        }
        for(int i=0; i<vertex; i++){
            for(int j=0; j<vertex; j++){
                if(dp[i][j]==INF || i==j)
                    continue;
                cout<<i+1<<"-"<<j+1<<" : "<<dp[i][j]<<endl;
                cout<<"Path: "<<i+1<<"->";
                path(i,j);
                cout<<j+1<<endl;
            }
        }
    }

    void path(int i, int j){
        if(parent[i][j]>-1){
            path(i,parent[i][j]);
            cout<<parent[i][j]+1<<"->";
            path(parent[i][j],j);
        }
    }

    void printMatrix(){
        cout<<"Shortest distance matrix\n";
        for(int i=0; i<vertex; i++){
            for(int j=0; j<vertex; j++){
                if(dp[i][j]>=INF)
                    cout<<"INF ";
                else
                    cout<<dp[i][j]<<" ";
            }
            cout<<endl;
        }
    }

};

int main(){
    //freopen("apsp.in", "r", stdin);

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

    g.floyd();
    g.printMatrix();
}

