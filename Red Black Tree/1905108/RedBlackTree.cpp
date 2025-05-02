#include<iostream>
#include<fstream>

using namespace std;

#define red 0
#define black 1

template <typename E>
class Node{

public:
    E key;
    int color;
    int leftSubTreeSize;
    int rightSubTreeSize;
    Node<E>* leftChild;
    Node<E>* rightChild;
    Node<E>* parent;

    Node(){
        leftChild=NULL;
        rightChild=NULL;
        parent=NULL;
        key=0;
        color=red;
        leftSubTreeSize=0;
        rightSubTreeSize=0;
    }

    Node(E ele, Node<E>* l=NULL, Node<E>* r=NULL, Node<E>* p=NULL){
        key=ele;
        leftChild=l;
        rightChild=r;
        parent=p;
        color=red;
        leftSubTreeSize=0;
        rightSubTreeSize=0;
    }

    ~Node(){}

};

template <typename E>
class RedBlackTree{
    Node<E>* root;
    Node<E>* nil;
    int nodeCount;

    void clearhelp(Node<E>* root);
    Node<E>* findhelp(Node<E>* rt, const E& e);
    Node<E>* getmin(Node<E>* rt);
    Node<E>* getmax(Node<E>* rt);
    void printhelp(Node<E>* rt);
    void pre(Node<E>* rt);
    void post(Node<E>* rt);
    void in(Node<E>* rt);


public:
    RedBlackTree(){
        nil=new Node<E>();
        nil->color=black;
        root=nil;
        nodeCount=0;
    }
    ~RedBlackTree(){
        clearhelp(root);
    }

    void clear(){
        clearhelp(root);
        root=nil;
        nodeCount=0;
    }

    void fixSize(Node<E>* a){
        while(a!=nil){
            if(a->leftChild!=nil)
                a->leftSubTreeSize=1+((a->leftChild)->leftSubTreeSize)+((a->leftChild)->rightSubTreeSize);
            else
                a->leftSubTreeSize=0;
            if(a->rightChild!=nil)
                a->rightSubTreeSize=1+((a->rightChild)->leftSubTreeSize)+((a->rightChild)->rightSubTreeSize);
            else
                a->rightSubTreeSize=0;
            a=a->parent;
        }
    }

    void leftRotate(Node<E>* x){
        Node<E>* y =x->rightChild;
        x->rightChild=y->leftChild;
        x->rightSubTreeSize=1+((y->leftChild)->leftSubTreeSize)+((y->leftChild)->rightSubTreeSize);

        if(y->leftChild!=nil)
            (y->leftChild)->parent=x;

        y->parent=x->parent;
        y->leftChild=x;
        y->leftSubTreeSize=1+(x->leftSubTreeSize)+(x->rightSubTreeSize);

        if(x->parent==nil)
            root=y;
        else if (x==x->parent->leftChild){
            x->parent->leftChild=y;
            x->parent->leftSubTreeSize=1+(y->leftSubTreeSize)+(y->rightSubTreeSize);
        }
        else{
            x->parent->rightChild=y;
            x->parent->rightSubTreeSize=1+(y->leftSubTreeSize)+(y->rightSubTreeSize);
        }
        x->parent=y;
        Node<E>* a=x->parent->parent;
        fixSize(a);
    }

    void rightRotate(Node<E>* x){
        Node<E>* y =x->leftChild;
        x->leftChild=y->rightChild;
        x->leftSubTreeSize=1+((y->rightChild)->leftSubTreeSize)+((y->rightChild)->rightSubTreeSize);

        if(y->rightChild!=nil)
            (y->rightChild)->parent=x;

        y->parent=x->parent;
        y->rightChild=x;
        y->rightSubTreeSize=1+(x->leftSubTreeSize)+(x->rightSubTreeSize);

        if(x->parent==nil)
            root=y;
        else if (x==x->parent->rightChild){
            x->parent->rightChild=y;
            x->parent->rightSubTreeSize=1+(y->leftSubTreeSize)+(y->rightSubTreeSize);
        }
        else{
            x->parent->leftChild=y;
            x->parent->leftSubTreeSize=1+(y->leftSubTreeSize)+(y->rightSubTreeSize);
        }
        x->parent=y;
        Node<E>* a=x->parent->parent;
        fixSize(a);
    }

    int fixSubTreeSize(Node<E>* rt){
        if(rt==nil)
            return 0;
        else{
             rt->leftSubTreeSize=fixSubTreeSize(rt->leftChild);
             rt->rightSubTreeSize=fixSubTreeSize(rt->rightChild);
             return (1+(rt->leftSubTreeSize)+(rt->rightSubTreeSize));
        }
    }

    void insertFixUp(Node<E>* z){
        Node<E>* y= NULL;
        while((z->parent)->color==red){
            if(z->parent == ((z->parent)->parent)->leftChild){
                y=((z->parent)->parent)->rightChild;
                if(y->color == red){
                    (z->parent)->color=black;
                    y->color=black;
                    ((z->parent)->parent)->color=red;
                    z=(z->parent)->parent;
                }
                else{
                    if(z==(z->parent)->rightChild){
                        z=z->parent;
                        leftRotate(z);
                    }
                    (z->parent)->color=black;
                    ((z->parent)->parent)->color=red;
                    rightRotate((z->parent)->parent);
                }
            }
            else{
                y=((z->parent)->parent)->leftChild;
                if(y->color == red){
                    (z->parent)->color=black;
                    y->color=black;
                    ((z->parent)->parent)->color=red;
                    z=(z->parent)->parent;
                }
                else {
                    if(z==(z->parent)->leftChild){
                        z=z->parent;
                        rightRotate(z);
                    }
                    (z->parent)->color=black;
                    ((z->parent)->parent)->color=red;
                    leftRotate((z->parent)->parent);
                }
            }
        }
        root->color=black;
    }

    int insert(const E& e){
        Node<E>* z = new Node<E>(e);
        Node<E>* x=root;
        Node<E>* y=NULL;
        Node<E>* test;
        test=findhelp(root, e);
        if(test!=nil)
            return 0;

        if(root==nil){
            root=z;
            z->color=black;
            z->parent=nil;
            z->leftChild=nil;
            z->rightChild=nil;
        }
        else{
            while(x!=nil){
                y=x;
                if(z->key < x->key)
                    x=x->leftChild;
                else
                    x=x->rightChild;
            }
            z->parent=y;
            z->leftChild=nil;
            z->rightChild=nil;

            if(z->key < y->key){
                y->leftChild=z;
                y->leftSubTreeSize=1+(z->leftSubTreeSize)+(z->rightSubTreeSize);
            }
            else if(z->key > y->key){
                y->rightChild=z;
                y->rightSubTreeSize=1+(z->leftSubTreeSize)+(z->rightSubTreeSize);;
            }

            insertFixUp(z);
            fixSubTreeSize(root);
        }
        nodeCount++;
        return 1;
    }

    Node<E>* successor(Node<E>* x){
        Node<E>* temp=nil;
        if(x->rightChild != nil){
            temp=getmin(x->rightChild);
        }
        return temp;
    }

    void deleteFixUp(Node<E>* x){
        Node<E>* w=NULL;
        while(x->color==black && x!=root){
            if(x==((x->parent)->leftChild)){
                w=(x->parent)->rightChild;
                if(w->color==red){
                    w->color=black;
                    (x->parent)->color=red;
                    leftRotate(x->parent);
                    w=(x->parent)->rightChild;
                }
                if((w->leftChild)->color == black && (w->rightChild)->color==black){
                    w->color=red;
                    x=x->parent;
                }
                else{
                    if((w->rightChild)->color==black){
                        (w->leftChild)->color=black;
                        w->color=red;
                        rightRotate(w);
                        w=(x->parent)->rightChild;
                    }
                    w->color=(x->parent)->color;
                    (x->parent)->color=black;
                    (w->rightChild)->color=black;
                    leftRotate(x->parent);
                    x=root;
                }
            }
            else{
                if(x==((x->parent)->rightChild)){
                    w=(x->parent)->leftChild;
                    if(w->color==red){
                        w->color=black;
                        (x->parent)->color=red;
                        rightRotate(x->parent);
                        w=(x->parent)->leftChild;
                    }
                    if((w->rightChild)->color == black && (w->leftChild)->color==black){
                        w->color=red;
                        x=x->parent;
                    }
                    else{
                        if((w->leftChild)->color==black){
                            (w->rightChild)->color=black;
                            w->color=red;
                            leftRotate(w);
                            w=(x->parent)->leftChild;
                        }
                        w->color=(x->parent)->color;
                        (x->parent)->color=black;
                        (w->leftChild)->color=black;
                        rightRotate(x->parent);
                        x=root;
                    }
                }
            }
        }
        x->color=black;
    }

    int Delete(const E& e){
        Node<E>* x=NULL;
        Node<E>* y=NULL;
        Node<E>* z=NULL;
        z=findhelp(root,e);
        if(z==nil)
            return 0;
        else{
            if(z->leftChild==nil || z->rightChild==nil)
                y=z;
            else
                y=successor(z);

            if(y->leftChild!=nil)
                x=y->leftChild;
            else
                x=y->rightChild;

            x->parent=y->parent;
            if(y->parent==nil)
                root=x;
            else if (y==(y->parent)->leftChild){
                (y->parent)->leftChild=x;
                (y->parent)->leftSubTreeSize=1+(x->leftSubTreeSize)+(x->rightSubTreeSize);
            }
            else{
                (y->parent)->rightChild=x;
                (y->parent)->rightSubTreeSize=1+(x->leftSubTreeSize)+(x->rightSubTreeSize);
            }

            if(y!=z){
                z->key=y->key;
            }
            if(y->color==black)
                deleteFixUp(x);
            fixSubTreeSize(root);
            nodeCount--;
            return 1;
        }
    }

    E removeRoot(){
        if(root != nil){
            E temp = root->key;
            if(Delete(temp))
                return temp;
        }
        return NULL;
    }

    E removeMin(){
        if(root != nil){
            Node<E>* temp = getmin(root);
            if(Delete(temp->key))
                return temp->key;
        }
        return NULL;
    }

     E removeMax(){
        if(root != nil){
            Node<E>* temp = getmax(root);
            if(Delete(temp->key))
                return temp->key;
        }
        return NULL;
    }

    E Search(const E& e){
        Node<E>* temp=NULL;
        temp=findhelp(root,e);
        if(temp==nil)
            return NULL;
        else
            return temp->key;
    }

    int Found(const E& e){
        Node<E>* temp=NULL;
        temp=findhelp(root,e);
        if(temp==nil)
            return 0;
        else
            return 1;
    }

    int length(){
        return nodeCount;
    }

    void print(){
        if(root != nil){
            printhelp(root);
            cout<<endl;
        }
        else
            cout<<"Red-Black Tree is empty.\n";
    }

    //Traversal
    void preOrder(){
        pre(root);
        cout<<endl;
    }

    void postOrder(){
        post(root);
        cout<<endl;
    }

    void inOrder(){
        in(root);
        cout<<endl;
    }

    int printNumOfProgLessThan(E val){
        int count=0;
        if (root == nil)
            return 0;
        if(getmax(root)->key < val)
            return nodeCount;
        count=ProgLess(root,val);
        return count;
    }

   int ProgLess(Node<E>* rt, E val){
        int count=0;
        if (rt == nil)
            return 0;
        if(getmin(rt)->key > val)
            return 0;
        if(rt->key > val)
            count=ProgLess(rt->leftChild, val);
        else if(rt->key<val){
            count=1+rt->leftSubTreeSize;
            count+=ProgLess(rt->rightChild, val);
        }
        else if(rt->key = val)
            count=rt->leftSubTreeSize;

        return count;
    }

};

//find
template <typename E>
Node<E>* RedBlackTree<E> :: findhelp(Node<E>* rt, const E& e){
    if(rt == nil)
        return nil;

    if(e < rt->key)
        return findhelp(rt->leftChild, e);
    else if (e > rt->key)
        return findhelp(rt->rightChild, e);
    else
        return rt;
}

//get min
template <typename E>
Node<E>* RedBlackTree<E>:: getmin(Node<E>* rt) {
    if (rt->leftChild == nil)
        return rt;
    else
        return getmin(rt->leftChild);
}

//get max
template <typename E>
Node<E>* RedBlackTree<E>:: getmax(Node<E>* rt) {
    if (rt->rightChild == nil)
        return rt;
    else
        return getmax(rt->rightChild);
}

//clear
template <typename E>
void RedBlackTree<E>:: clearhelp(Node<E>* rt){
    if(rt == nil)
        return;
    clearhelp(rt->leftChild);
    clearhelp(rt->rightChild);
    delete rt;
}

//print
template <typename E>
void RedBlackTree<E>:: printhelp(Node<E>* rt){
    if (rt == nil)
        return;
    int a=1;
    if(rt->leftChild == nil && rt->rightChild == nil)
        a=-1;
    cout<<rt->key;
    if(a==1)
        cout<<"(";
    printhelp(rt->leftChild);
    if(a==1)
        cout<<")(";
    printhelp(rt->rightChild);
    if(a==1)
        cout<<")";
}

//preOrder traversal
template <typename E>
void RedBlackTree<E>:: pre(Node<E>* rt){
    if(rt == nil)
        return;

    cout<<rt->key<<" ";
    pre(rt->leftChild);
    pre(rt->rightChild);
}

//postOrder traversal
template <typename E>
void RedBlackTree<E>:: post(Node<E>* rt){
    if(rt == nil)
        return;

    post(rt->leftChild);
    post(rt->rightChild);
    cout<<rt->key<<" ";
}

//inOrder traversal
template <typename E>
void RedBlackTree<E>:: in(Node<E>* rt){
    if(rt == nil)
        return;

    in(rt->leftChild);
    cout<<rt->key<<" ";
    in(rt->rightChild);
}




