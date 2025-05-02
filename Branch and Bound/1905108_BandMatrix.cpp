#include<bits/stdc++.h>

using namespace std;

vector<vector<char> > arr;
vector<vector<char> > demo;
vector<char> d;
vector<long long> vals(4);
long long len;
pair<vector<vector<char> >, vector<long long> > pp;


long long bound(long long col, long long row){
    long long free, c, r;
    long long count;

    ///unfixed area
    //row wise
    free=0;
    for(long long i=row; i<len; i++){
        count=0;
        for(long long j=col; j<len; j++){
                if(demo[i][j]=='X' || demo[i][j]=='x'){
                    count++;
                }
        }
        count=floor((count+1)/2);
        if(count>free)
            free=count;
    }

    //col wise
    for(long long i=col; i<len; i++){
        count=0;
        for(long long j=row; j<len; j++){
                if(demo[j][i]=='X' || demo[j][i]=='x'){
                    count++;
                }
        }
        count=floor((count+1)/2);
        if(count>free)
            free=count;
    }
    //cout<<"unfixed band: "<<free<<endl;


    long long go,flag;

    ///fixed area
    //col
    c=0;
    for(long long i=0; i<col; i++){
        //upper section
        go=0;
        flag=0;
        count=0;
        for(long long j=i; j>=0; j--){
            go++;
            if(demo[j][i]=='x' || demo[j][i]=='X')
                flag=1;
            if(demo[j][i]=='0')
                flag=0;
            if(flag==1)
                count=go;
        }
        if(count>c)
            c=count;

        //lower section

        go=0;
        flag=0;
        count=0;
        for(long long j=i; j<len; j++){
            go++;
            if(j>=row && demo[j][i]=='0')
                go--;
            if(demo[j][i]=='x' || demo[j][i]=='X')
                flag=1;
            if(demo[j][i]=='0')
                flag=0;
            if(flag==1)
                count=go;
        }
        //cout<<"col:"<<count<<endl;
        if(count>c)
            c=count;
    }
    //cout<<"col band: "<<c<<endl;

    //row
    r=0;
    for(long long i=0; i<row; i++){
        //left section
        go=0;
        flag=0;
        count=0;
        for(long long j=i; j>=0; j--){
            go++;
            if(demo[i][j]=='x' || demo[i][j]=='X')
                flag=1;
            if(demo[i][j]=='0')
                flag=0;
            if(flag==1)
                count=go;
        }
        if(count>r)
            r=count;

        //right section
        go=0;
        flag=0;
        count=0;
        for(long long j=i; j<len; j++){
            go++;
            if(j>=col && demo[i][j]=='0')
                go--;
            if(demo[i][j]=='x' || demo[i][j]=='X')
                flag=1;
            if(demo[i][j]=='0')
                flag=0;
            if(flag==1)
                count=go;
        }
        //cout<<"row:"<<count<<endl;
        if(count>r)
            r=count;
    }
    //cout<<"row band: "<<r<<endl;

    free=max(free,c);
    free=max(free,r);
    return free;
}

void printD(){
    for(long long i=0; i<len; i++){
        for(long long j=0; j<len; j++){
            cout<<demo[i][j];
        }
        cout<<endl;
    }
    cout<<endl;
}

void printA(){
    for(long long i=0; i<len; i++){
        for(long long j=0; j<len; j++){
            cout<<arr[i][j];
        }
        cout<<endl;
    }
    cout<<endl;
}

void swapCol(long long fixedCol, long long exchanged){
    //fill exchanged col into demo's fixedCol
    for(long long m=0; m<len; m++)
        demo[m][fixedCol]=arr[m][exchanged];
    //fill other cols in strict order
    long long p=fixedCol;
    for(long long n=fixedCol+1; n<len; n++){
        if(p==exchanged)
            p++;
        for(long long m=0; m<len; m++){
            demo[m][n]=arr[m][p];
        }
        p++;
    }
}

void swapRow(long long fixedRow, long long exchanged){
    for(long long m=0; m<len; m++)
        demo[fixedRow][m]=arr[exchanged][m];

    long long p=fixedRow;
    for(long long n=fixedRow+1; n<len; n++){
        if(p==exchanged)
            p++;
        for(long long m=0; m<len; m++){
            demo[n][m]=arr[p][m];
        }
        p++;
    }
}

class findMin{
public:
    bool operator() (pair<vector<vector<char> >, vector<long long> > p1, pair<vector<vector<char> >, vector<long long> > p2){
        if(p1.second[3]!=p2.second[3]){
            return (p1.second[3]>p2.second[3]);
        }
        else if(p1.second[3]==p2.second[3]){
            if((p1.second[1]+p1.second[2])==(p2.second[1]+p2.second[2])){
                return (p1.second[0] < p2.second[0]);
            }
            else{
                return ((p1.second[1]+p1.second[2]) < (p2.second[1]+p2.second[2]));
            }
        }
    }
};

priority_queue<pair<vector<vector<char> >, vector<long long> > ,vector<pair<vector<vector<char> >, vector<long long> > >, findMin> pq;


long long branch(){
    long long fixedCol=0, fixedRow=0;
    long long curr, exchanged, finBound;
    demo=arr;
    finBound=bound(0,0);
    vals[0]=-1; //exchanged
    vals[1]=0;  //fixedCol
    vals[2]=0;  //fixedRow
    vals[3]=finBound;   //bound
    pp=make_pair(demo,vals);
    pq.push(pp);

    while(!pq.empty()){
        vals.clear();
        demo.clear();
        demo=pq.top().first;
        arr=demo;
        vals=pq.top().second;
        finBound=vals[3];
        fixedCol=vals[1];
        fixedRow=vals[2];

        //cout<<"------------------"<<finBound<<" "<<fixedCol<<" "<<fixedRow<<endl;
        pq.pop();
        if(fixedCol==len-1 && fixedRow==len-1){
            arr=demo;
            finBound=bound(len-1,len-1);
            while(!pq.empty()){pq.pop();}

            return finBound;
        }

        if(fixedCol==fixedRow){
            for(long long i=fixedCol; i<len; i++){
                swapCol(fixedCol, i);
                //finding bound
                finBound=bound(fixedCol+1, fixedRow);
                //vals.clear();
                vals[0]=i;
                vals[1]=fixedCol+1;
                vals[2]=fixedRow;
                vals[3]=finBound;
                pp=make_pair(demo,vals);
                pq.push(pp);
            }

        }
        else if(fixedCol=fixedRow+1){
            for(long long i=fixedRow; i<len; i++){
                swapRow(fixedRow, i);
                //finding bound
                finBound=bound(fixedCol, fixedRow+1);
                //vals.clear();
                vals[0]=i;
                vals[1]=fixedCol;
                vals[2]=fixedRow+1;
                vals[3]=finBound;
                pp=make_pair(demo,vals);
                pq.push(pp);
            }

        }
    }
}

int main(){
    char v;
    len=0;
    while(len!=-1){
    arr.clear();
    cin>>len;
    for(long long i=0; i<len; i++){
        for(long long j=0; j<len; j++){
            cin>>v;
            d.push_back(v);
        }
        arr.push_back(d);
        d.clear();
    }
    long long finBound;
    finBound=branch();
    cout<<finBound<<endl;
    printA();
    arr.clear();
    }
}


