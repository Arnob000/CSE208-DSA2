//DFS
#include<iostream>
#include<vector>

using namespace std;

int count;
vector<int> vertex[20];
int visited[20];
int start[20];
int finish[20];

void dfsvisit(int i){
    start[i]=count;
    count++;
    cout<<i<<" ";
    visited[i]=1;

    for(int a=0; a<vertex[i].size(); a++){

        dfsvisit(vertex[i][a]);
    }

    finish[i]=count;

}

void dfs(int n){

    for(int i=1; i<=n; i++)
    {
        if(visited[i]!=1)
            dfsvisit(i);
    }

}

int findMaxFinish(int n){
    int max=0;
    for(int i=1; i<=n; i++){
        if(finish[i]>finish[max])
            max=i;
    }
    return=max;
}

int main(){
    int n, ins,f1,f2;
    cin>>n>>ins;
    count=0;
    for(int i=0; i<=n; i++)
        visited[i]=0;

    for(int i=1; i<=ins; i++){
        cin>>f1>>f2;
        vertex[f1].push_back(f2);
    }

    dfs(n);
}
