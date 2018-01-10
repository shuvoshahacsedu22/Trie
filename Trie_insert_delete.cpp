#include <cstdio>
#include <iostream>
#include <cmath>
#include <climits>
#include <algorithm>
#include <map>
#include <list>
#include <vector>
#include <queue>
#include <stack>
#include <cstring>
#include <set>
#include <fstream>
#include <limits>
#define ALPHABET_SIZE 10
using namespace std;
typedef long long ll;
#define REP(i,n)    for(int i=0;i<n;i++)
struct Trie
{

    Trie *children[ALPHABET_SIZE];
    int NoOfChild_prefixes;
    bool endOfWord;
    Trie()
    {
        for(int i=0; i<ALPHABET_SIZE; i++)
            children[i]=NULL;
        endOfWord=false;
        NoOfChild_prefixes=0;
    }
};

Trie *initNode(void)
{

    Trie *temp=new Trie();
    return temp;
}

void addWord(Trie *root,string str,int idx)
{

    if(str.size()==idx)
    {

        root->endOfWord=true;
        return;
    }
    root->NoOfChild_prefixes+=1;
    int k=str[idx]-'0';
    if(root->children[k]==NULL)
        root->children[k]=initNode();
        addWord(root->children[k],str,idx+1);
    }
//same as count prefixes or search word
int countPrefix(Trie *root, string str, int idx)
{

    if(str.size()==idx)
    {
        return root->NoOfChild_prefixes;
    }
int k=str[idx]-'0';
    if(root->children[k]==NULL) return 0;
    return countPrefix(root->children[k],str,idx+1);

}

int countWord(Trie *root, string str, int idx)
{

    if(str.size()==idx)
    {
        return root->endOfword;
    }

    if(root->children[idx]==NULL) return 0;
    return countWord(root->children[idx],str,idx+1);

}
bool flag=false;
bool deleteWord(Trie *root, string str, int idx)
{

    if(str.size()==idx)
    {

        if(root->endOfWord)
        {
            flag=true;//reduding  child no. for each ancestor node since a word has been deleted
            root->endOfWord=false;
            return root->NoOfChild_prefixes==0;//if there is no child of the last node then it can be deleted from memory
        }
        return false;
    }

int k=str[idx]-'0';

    if(root->children[k]==NULL) return false;

    bool to_del_child_or_not=deleteWord(root->children[k],str,idx+1);
    if(flag) root->NoOfChild_prefixes-=1;//if flag==true then the word has been deleted. so from each ancestor node 'no of child' should be decreased by 1

    if(to_del_child_or_not){
    delete root->children[k];
    root->children[k]=NULL;
    return !root->NoOfChild_prefixes && !root->endOfWord;//to delete current node or not from its parent
    }

    return false;
}


bool isNotConsistent(Trie *root){

    if(root->endOfWord==true && root->NoOfChild_prefixes) return true;

    for(int i=0;i<10;i++)
    {
    if( root->children[i]!=NULL && isNotConsistent(root->children[i]) ) return true;
    }
return false;
}

int main()
{
    //freopen("in.txt","r",stdin);
    int tc,N;
    scanf("%d",&tc);
    REP(i,tc){
        scanf("%d",&N);
        string str;
        Trie *trie=initNode();
        REP(i,N){
        cin>>str;
        addWord(trie,str,0);
        }
        if(isNotConsistent(trie)) cout<<"NO"<<endl;
        else cout<<"YES"<<endl;
        delete trie;
    }
    return 0;
}
