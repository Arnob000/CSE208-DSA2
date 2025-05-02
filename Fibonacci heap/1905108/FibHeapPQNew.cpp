#include<iostream>
#include<math.h>

using namespace std;

template <class T, class M>
class Node{

public:
    T key;
    M vertex;
    int degree;
    Node* parent;
    Node* child;
    Node* rightSibling;
    Node* leftSibling;
    bool mark;

    Node(const T &el, const M &v, Node* n=NULL, Node* p=NULL){
        key=el;
        vertex=v;
        rightSibling= n;
        leftSibling=p;
        parent=NULL;
        child=NULL;
        mark=false;
        degree=0;
    }

    Node(Node* n=NULL, Node* p=NULL){
        key=0;
        rightSibling= n;
        leftSibling=p;
        parent=NULL;
        child=NULL;
        mark=false;
        degree=0;
    }
    ~Node(){
        parent=NULL;
        child=NULL;
        rightSibling=NULL;
        leftSibling=NULL;
    }

};


template <class T, class M>
class fibHeap{
    int n;
    Node<T,M>* minNode;
public:
    fibHeap(){
        n=0;
        minNode=NULL;
    }

    void makeHeap(){
        n=0;
        minNode=NULL;
    }

    int length(){
        return n;
    }

    void insert(const T &item, const M &v){
        Node<T,M>* newNode= new Node<T,M>(item, v);
        newNode->rightSibling=newNode;
        newNode->leftSibling=newNode;

        if(n<=0)
            minNode=newNode;
        else{
            addToRootList(newNode);
            if(minNode->key > newNode->key)
                minNode=newNode;
        }
        n++;
    }

    void addToRootList(Node<T,M>* newNode){
        newNode->parent=NULL;
        newNode->leftSibling=minNode;
        newNode->rightSibling=minNode->rightSibling;
        (minNode->rightSibling)->leftSibling=newNode;
        minNode->rightSibling=newNode;
    }

    M minimum(){
        if(n>0)
            return minNode->vertex;
        else
            return (M)-1;
    }

    void fibHeapLink(Node<T,M>* y, Node<T,M>* x){
        (y->leftSibling)->rightSibling=y->rightSibling;
        (y->rightSibling)->leftSibling=y->leftSibling;
        if(x->degree==0){
            x->child=y;
            y->leftSibling=y;
            y->rightSibling=y;
        }
        else{
            y->leftSibling=x->child;
            y->rightSibling=(x->child)->rightSibling;
            ((x->child)->rightSibling)->leftSibling=y;
            (x->child)->rightSibling=y;
        }
        x->degree++;
        y->parent=x;
        y->mark=false;
    }


    void consolidate(){
        if(minNode->rightSibling==minNode  || n<2)
            return;
        int s=log2(n)+1;
        Node<T,M>* arr[s];
        for(int i=0; i<s; i++)
            arr[i]=NULL;

        Node<T,M>* x=minNode;
        Node<T,M>* temp=NULL;
        Node<T,M>* y=NULL;
        int d=0;
        do{
            x=x->rightSibling;
            d=x->degree;
            while(arr[d]!=NULL){
                y=arr[d];
                if(x->key > y->key){
                    temp=x;
                    x=y;
                    y=temp;
                }
                if(y==minNode){
                    minNode=minNode->rightSibling;
                }
                fibHeapLink(y,x);
                arr[d]=NULL;
                d++;
            }
            arr[d]=x;
        }while(x!=minNode);

        minNode=NULL;
        for(int i=0; i<s; i++){
            if(arr[i]!=NULL){
                if(minNode==NULL){
                    minNode=arr[i];
                    minNode->rightSibling=minNode;
                    minNode->leftSibling=minNode;
                }
                else{
                    addToRootList(arr[i]);
                    if(arr[i]->key < minNode->key)
                        minNode=arr[i];
                }
            }
        }

    }

    T extractMin(){
        if(n>0){
            Node<T,M>* newNode = minNode;
            Node<T,M>* temp;
            T val=minNode->key;

            if(newNode->child!=NULL){
                while((newNode->child)->rightSibling!=newNode->child){
                    temp=(newNode->child)->rightSibling;
                    (temp->rightSibling)->leftSibling=newNode->child;
                    (newNode->child)->rightSibling=temp->rightSibling;
                    addToRootList(temp);
                    newNode->degree--;
                }
                addToRootList(newNode->child);
                newNode->child=NULL;
                newNode->degree--;
            }

            if(newNode==newNode->rightSibling)
                minNode=NULL;
            else{
                minNode=minNode->rightSibling;
                (newNode->leftSibling)->rightSibling=newNode->rightSibling;
                (newNode->rightSibling)->leftSibling=newNode->leftSibling;
                consolidate();
            }
            n--;
            delete newNode;
            return val;
        }
        else
            return (T)-1;
    }

    void unionHeap(fibHeap<T,M> &H){
        Node<T,M>* r = minNode->rightSibling;
        Node<T,M>* newR= H.minNode->rightSibling;
        r->leftSibling=H.minNode;
        minNode->rightSibling=newR;
        newR->leftSibling=minNode;
        H.minNode->rightSibling=r;
        if(minNode==NULL || (H.minNode!=NULL && H.minNode->key < minNode->key))
            minNode=H.minNode;
        n+=H.length();
        H.minNode=NULL;
    }

    Node<T,M>* findNode(Node<T,M>* node, T val){
        if(node==NULL)
            return NULL;
        if(node->key==val)
            return node;
        Node<T,M>* temp=node;
        Node<T,M>* vNode=NULL;
        do{
            if(temp->child!=NULL)
                vNode=findNode(temp->child, val);
            if(vNode==NULL){
                temp=temp->rightSibling;
                if(temp->key==val)
                    vNode=temp;
            }
            if(vNode!=NULL)
                break;
        }while(temp!=node);
        return vNode;
    }

    void cut(Node<T,M>* x, Node<T,M>* y){
        if(y->degree==1){
            y->child=NULL;
            x->mark=false;
            addToRootList(x);
        }
        else{
            if(y->child==x)
                y->child=x->rightSibling;

            x->rightSibling->leftSibling=x->leftSibling;
            x->leftSibling->rightSibling=x->rightSibling;
            x->mark=false;
            addToRootList(x);
        }
        y->degree--;
    }

    void cascadingCut(Node<T,M>* y){
        Node<T,M>* z=y->parent;
        if(z!=NULL){
            if(y->mark==false)
                y->mark=true;
            else{
                cut(y,z);
                cascadingCut(z);
            }
        }
    }

    void decreaseKey(Node<T,M>* x, T k){
        if(k>x->key){
            cout<<"New key is greater than current key\n";
            return;
        }
        x->key=k;
        Node<T,M>* y=x->parent;
        if(y!=NULL && (x->key < y->key)){
            cut(x,y);
            cascadingCut(y);
        }
        if(x->key < minNode->key)
            minNode=x;
    }

    void decrease(T val, T k){
        Node<T,M>* a=findNode(minNode, val);
        if(a==NULL)
            cout<<"Element not found\n";
        else
            decreaseKey(a,k);
    }

    void deleteElement(T val){
        Node<T,M>* a=findNode(minNode, val);
        if(a==NULL)
            cout<<"Element not found\n";
        else{
            decreaseKey(a,minimum()-100);
            extractMin();
        }
    }

    void findRoots(){
        Node<T,M>* t=minNode;
        if(minNode==NULL){
            cout<<"Heap is empty\n";
            return;
        }
        cout<<"ROOTS: ";
        cout<<"("<<t->key<<","<<t->vertex<<")"<<" ";
        t=t->rightSibling;
        while(t!=minNode){
            cout<<"("<<t->key<<","<<t->vertex<<")"<<" ";
            t=t->rightSibling;
        }
        cout<<endl;
    }

    bool isEmpty(){
        if(n==0)
            return true;
        else
            return false;
    }

};

/*

int main(){
    fibHeap<int,int> a,b;

    b.insert(51,0);
    b.insert(51,0);

    b.findRoots();
    cout<<b.length()<<endl;
    cout<<b.extractMin()<<endl;
    b.findRoots();
    cout<<b.length();

}

*/
