#include <fstream>
#include <iostream>
#include <vector>
#include <ctime>
#include <queue>
#include <unordered_set>
#include <unordered_map>

using namespace std;


class Node{
    protected:
        int g;
        int h;
        int f;//f=g+h;
        string str;
        string pat;

    public:
        int GetG()const {return g;}
        int GetH()const {return h;}
        int GetF()const {return f;}
        string GetStr()const {return str;}
        string GetPat()const {return pat;}

        void SetG(const int val){g=val;f=g+h;}
        Node(int g,string str,string pat)
            :g(g),str(str),pat(pat)
        {
            h=0;
            for(int i=0;i<str.size();i++)
            {
                if(str[i]=='0')
                    h++;
            }
            f=g+h;
        }
};
bool operator <(const Node& nod1,const Node& nod2)
{
    if(nod1.GetF()<nod2.GetF()) return false;
    if(nod1.GetF()>nod2.GetF()) return true;

    if(nod1.GetH()<nod2.GetH()) return false;
    if(nod1.GetH()>nod2.GetH()) return true;

    string str1=nod1.GetStr();
    string str2=nod2.GetStr();
    for(int i=0;i<str1.size();i++)
    {
        if(str1[i]<str2[i]) return false;
        if(str1[i]>str2[i]) return true;
    }

    return false;
}
ostream& operator<<(ostream& os,const Node& nod)
{
    cout<<nod.GetF()<<"="<<nod.GetG()<<"+"<<nod.GetH()<<"  "<<nod.GetStr();
    return os;
}
ostream& operator<<(ostream& os,const unordered_map<string,string>& parents)
{
    for(auto it=parents.begin();it!=parents.end();it++)
    {
        cout<<(*it).first<<" \'s parent is "<<(*it).second<<endl;
    }
    return os;
}

int main(int argc,char** argv)
{
    if(argc!=3) {cerr<<"there should be two parameters: start string, permitted strings file";exit(1);}
    string start=argv[1];
    ifstream in(argv[2],ios::in);
    if(!in.is_open())
    {
        cerr<<"****************************\ncan't open "<<argv[2]<<"\n****************************"<<endl;
        exit(1);
    }

    unordered_set<string> rec;
    unordered_map<string,string> parents;//record the parents realitionships
    //child , parent  many to one

    string cnt_str;
    getline(in,cnt_str);//no \n
    int cnt=atoi(cnt_str.c_str());
    while(cnt>0)
    {
        cnt--;
        string tmp;
        getline(in,tmp);//no \n
        if(rec.count(tmp)==0)
        {
            rec.insert(tmp);
        }
    }
    priority_queue<Node> open;//open list
    open.push(Node(0,start,""));//push the start point

    unordered_set<string> closed;//closed list
    int X=0;
    while(!open.empty())//open not empty,and there is no end point in the open list  SOMETHING WRONG
        //when we meet the "11111" we just break out
    {
        Node fnt=open.top();//fnt
        open.pop();
        if(closed.count(fnt.GetStr())!=0)
        {
            //cout<<"closed have "<<fnt.GetStr()<<endl;
            continue;
        }
        else
        {
            X++;
            closed.insert(fnt.GetStr());
            //cout<<"Insert "<<fnt.GetStr()<<" \'s parent is "<<fnt.GetPat()<<endl;
            parents[fnt.GetStr()]=fnt.GetPat();
        }

        //generate all the children
        string str=fnt.GetStr();
        string pat=str;
        for(int i=0;i<str.size();i++)
        {
            char ch=str[i];

            str[i]=(str[i]=='0'?'1':'0');
            if(rec.count(str)==0||closed.count(str)!=0)
            {
                //cout<<"rec count or closed "<<str<<endl;
                str[i]=ch;
                continue;
            }
            Node nod(fnt.GetG()+1,str,pat);
            //cout<<str<<" "<<pat<<endl;
            if(nod.GetPat()!=""&&nod.GetH()==0)
            {
                parents[str]=pat;//ok
                //cout<<parents<<endl;
                vector<string> res;
                while(str!=start)
                {
                    res.push_back(str);
                    //cout<<str<<"->";
                    str=parents[str];
                }
                //cout<<start<<endl;
                res.push_back(str);

                for(int i=res.size()-1;i>=0;i--)
                {
                    cout<<res[i]<<endl;
                }
                cout<<"expansions = "<<X<<endl;
                return 0;
            }
            open.push(nod);
            //cout<<"open push "<<nod.GetStr()<<endl;

            str[i]=ch;
        }
    }
    cout<<"No transformation"<<endl;
    cout<<"expansions = "<<X<<endl;
    return 0;
}
