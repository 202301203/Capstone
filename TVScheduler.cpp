#include<iostream>
#include<vector>
#include<cstring>
#define M 15
#define N 15
using namespace std;

class TVSeries{
    public:
        string name;
};

class Member{
    public:
        string name;
        vector<int> FreeSlots; //1 for free slot , 0 for busy
        vector<string> FavoriteSeries;
    public:
        Member(string s) : name(s) {
            int k;
            string a;
            cout << "Enter Free Slots of Member " << s << "(1 for free, 0 otherwise) :- ";
            for(int i=0 ; i<M ; i++)
            {
                cin >> k;
                FreeSlots.push_back(k);
            }
            cout << "Enter Member " << s << "'s Favorite Series :- ";
            for(int i=0 ; i<N ; i++)
            {
                cin >> a;
                FavoriteSeries.push_back(a);
            }
        } 
};

class ScheduleSlot{
    public:
        string Member;
        string Tvseries;
};

//Function will asign if member have free slot on premire of sereis
void scheduleTVSeries(vector<Member>& family, vector<TVSeries>& series, vector<ScheduleSlot>& slots ,vector<string>& record){
    for(int i = 0 ; i<M ; i++)
    {
        int f = 0;
        for(int j=0 ; j<N ; j++)
        {
            for(int k=0 ; k < family[i].FavoriteSeries.size() ; k++)
            {
                if(family[i].FavoriteSeries[k] == series[j].name)
                {
                    if(family[i].FreeSlots[k] == 1)
                    {
                        f = 1;
                        slots[k] = {family[i].name , series[j].name} ;
                        break;
                    }
                    else
                    {
                        record.push_back(series[j].name);
                    }
                }
            }
            if(f==1)
                break;
        }
    }
}


int main(){
    return 0;
}