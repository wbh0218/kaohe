#include<iostream>
#include<string>
using namespace std;
int i=0;
string maxword[100];
struct Result{
    int wordnumber;
    int maxn;
    string word[100];
    string wordset[100];
};
Result countword(const string&sentence){
    struct Result res;
    res.wordnumber=0;
    int wordsize[100];
    int i=1;
    res.maxn=0;
    string space;
    int setting=0;
    for(char w:sentence){
        if(w!=' '){
            wordsize[i]++;
            maxword[i]+=w;
        }
        else if(w==' '){
            res.wordnumber++;
            i++;}
    }
    res.wordnumber++;
    for(int t=0;t<=i;t++){
        res.maxn=max(wordsize[t],res.maxn);
    }
    for(int t1=0;t1<=i;t1++){
        if(wordsize[t1]==res.maxn){
            res.word[t1]=maxword[t1];
        }
    }
    for(int t2=0;t2<i;t2++){
        for(int t3=0;t3<i-t2;t3++){
            if(wordsize[t3]<wordsize[t3+1]){
                setting=wordsize[t3+1];
                wordsize[t3+1]=wordsize[t3];
                wordsize[t3]=setting;
                space=maxword[t3];
                maxword[t3]=maxword[t3+1];
                maxword[t3+1]=space;
            }
        }
    }
    for(int t4=0;t4<=i;t4++){
        res.wordset[t4]=maxword[t4];
    }
    return res;
}
int main(){
    string sentence; 
    cout<<"请输入英语句子"<<endl;
    getline(cin,sentence);
    struct Result res=countword(sentence);
    cout<<"单词数量为："<<res.wordnumber<<endl<<'\n';
    cout<<"最长单词长度为："<<res.maxn<<endl<<'\n';
    cout<<"最长单词为：";
    for(int i=0;i<=res.wordnumber;i++){
        cout<<res.word[i]<<' ';
    }
    cout<<'\n'<<"排序后为：";
    for(int i1=0;i1<=res.wordnumber;i1++){
        cout<<res.wordset[i1]<<' ';
    }
    return 0;
    }