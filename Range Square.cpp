#include "bits/stdc++.h"
using namespace std;

struct Node
{
    int val;
    Node* next;
};

class Linklist
{
    public:
    Node *first,*last;
    Linklist()
    {
        first=0;
    }
    void append(int x)
    {
        Node* newlink=new Node();
        newlink->val=x;
        newlink->next=0;

        if(first==0)
        {
            first=newlink;
            last=newlink;
        }
        else
        {
            last->next=newlink;
            last=newlink;
        }
    }
    bool findPerfectSquareInRange(int a, int b, set<int> &st)
    {
        int idx=1;
        Node* temp=first;
        
        while(temp)
        {
            // if(a<=idx && idx<=b)
            // {
                // int root=sqrt(temp->val);
                if(st.count(temp->val))
                {
                    return 1;
                }
            // }

            ++idx;
            temp=temp->next;
        }

        return 0;
    }
};

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */ 
    int a,b;
    cin>>a>>b;
    set<int> st;
    for(int i=a;i<=b;++i)
    {
        st.insert(i*i);
    }

    Linklist l;
    int n;
    cin>>n;
    for(int i=0;i<n;++i)
    {
        int x;
        cin>>x;
        l.append(x);
    }  
    cout<<(l.findPerfectSquareInRange(a,b,st)?1:0);
    return 0;
}
