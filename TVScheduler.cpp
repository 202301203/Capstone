#include<iostream>
#include<map>
#include<fstream>
#include<sstream>
#include<string>
#include<unordered_map>
#include <vector>
#include<list>
#include<cstdlib>
#define M 15
#define N 5
#define TABLE_SIZE 20
//N is series input
//S is going to be actual input

using namespace std;

int slotId(string s)
{
    map<string,int> TimeToSlot;
    TimeToSlot["6:00-7:00"] = 1;
    TimeToSlot["7:00-8:00"] = 2;
    TimeToSlot["8:00-9:00"] = 3;
    TimeToSlot["9:00-10:00"] = 4;
    TimeToSlot["10:00-11:00"] = 5;
    for(const auto& i : TimeToSlot)
    {
        if(i.first == s)
            return i.second;
    }
    return 0;
}

string idToDay(int i){
    switch(i)
    {
        case 0:
            return "Sunday";
        case 1:
            return "Monday";
        case 2:
            return "Tuesday";
        case 3:
            return "Wednesday";
        case 4:
            return "Thursday";
        case 5:
            return "Friday";
        case 6:
            return "Saturday";
        default:
            return " ";
    }
}

class record{
    public:
        string memberName;
        int seriesID;
        string Day;
        int slot;
};

class series{
    public:
        int id;
        string name;
        int showtime;
};

int sereiseID(vector<series>& abc,string s)
{
    for(const auto& i : abc)
    {
        if(i.name == s)
            return i.id;
    }
    return 0;
}

class slot{
    public:
        string name;
        string tvshowID;
        int slotid;
};

class TVShow{                                       //vector<TVShow>
    public:
        vector<slot> day;

        void output(){
            for(const auto& i : day)
            {
                cout << i.name << " -> " << i.tvshowID << " -> " << i.slotid << endl;
            }
            cout << endl;
        }
};

class Member {
    public:
        string member_id;
        string name;
        vector<string> favorite_series;
        vector<int> availability;
        vector<int> favserID;
};

class HashTable{
    public:
        unordered_map<string, list<string>> table;
        unordered_map<int,vector<int>> ShowtimeToSeriesTable;
        unordered_map<int,vector<string>> SeriesIdToMemberTable;
        unordered_map<string,vector<int>> MemberToFreeSlotTable;

        // Hash function
        size_t hash(const string& key) const {
            size_t hash = 0;
            for (char ch : key) {
                hash = ((hash << 5) + hash) + ch;
            }
            return hash % TABLE_SIZE;
        }

    public:

        void insert(const string& member,const string& series){
            table[member].push_back(series);
        }

        void insert(int showtime,int seriesID)
        {
            ShowtimeToSeriesTable[showtime].push_back(seriesID);
        }

        void insert(int sID,string Mname){
            SeriesIdToMemberTable[sID].push_back(Mname);
        }

        void insert(vector<Member>& m){
            for(const auto& i : m)
            {
                for(const auto& j : i.availability)
                MemberToFreeSlotTable[i.name].push_back(j);
            }
        }

        vector<int> getseries(int showtime){
            return ShowtimeToSeriesTable[showtime];
        }

        list<string> getseries(const string& member){
            return table[member];
        }

        void print()
        {
            for(const auto& i : table)
            {    cout << i.first << " -> " ;
                for(const auto& j : i.second)
                    cout << j << " , ";
                cout << endl;
            }      
        }

        void prints()
        {
            for(const auto& i : ShowtimeToSeriesTable)
            {    cout << i.first << " -> " ;
                for(const auto& j : i.second)
                    cout << j << " , ";
                cout << endl;
            }      
        }

        void printm()
        {
            for(const auto& i : SeriesIdToMemberTable)
            {    cout << i.first << " -> " ;
                for(const auto& j : i.second)
                    cout << j << " , ";
                cout << endl;
            }      
        }

        void printx()
        {
            for(const auto& i : MemberToFreeSlotTable)
            {    cout << i.first << " -> " ;
                for(const auto& j : i.second)
                    cout << j << " , ";
                cout << endl;
            }      
        }

};

string idtoname(vector<series>& ghi,int p){
    for(const auto& i : ghi)
    {
        if(i.id == p)
            return i.name;
    }
    return " ";
}

bool conflict(int value,HashTable& hasht,int incrementJ,int day){
    for(int i=0 ; i<hasht.ShowtimeToSeriesTable[incrementJ].size() ; i++)
    {
        int sd = hasht.ShowtimeToSeriesTable[incrementJ][i];
        for(int k=0 ; k<hasht.SeriesIdToMemberTable[sd].size() ; k++)
        {
            string str = hasht.SeriesIdToMemberTable[sd][k];
            if(hasht.MemberToFreeSlotTable[str][day] == value)
            {
                return true;
            }
        }
    }
    return false;
}


void TVScheduleFunction(HashTable& sample,vector<TVShow>& tv,vector<series>& ghi,vector<record>& tvRecord){
    
    for(int p=0 ; p<7 ; p++)
    {
        for(int i=1 ; i<=5 ; i++)
        {
            int f = 0, n=0;
            for(int j=0 ; j<sample.ShowtimeToSeriesTable[i].size() ; j++)
            {
                int h = sample.ShowtimeToSeriesTable[i][j];
                for(int k=0 ; k<sample.SeriesIdToMemberTable[h].size() ; k++)
                {
                    int jsincrement = j + 1;
                    string str = sample.SeriesIdToMemberTable[h][k];
                    if(sample.MemberToFreeSlotTable[str][p] == i && !conflict(i,sample,jsincrement,p))
                    {
                        slot d;
                        d.name = str;
                        d.tvshowID = idtoname(ghi,h);
                        d.slotid = i;
                        tv[p].day.push_back(d);
                        f = 1;

                        break;
                    }
                    else
                    {
                        if(n==0)
                        {
                            record r;
                            r.Day = idToDay(p);
                            r.memberName = str;
                            r.seriesID = h;
                            r.slot = i;
                            n = 1;
                            tvRecord.push_back(r);
                        }
                    }
                }
                if(f == 1)
                    break;
            }
        }
    }
}

void printTVSchedule(const vector<TVShow>& abc){
    for(const auto& i : abc)
    {
        for(const auto& j : i.day)
        {
            cout << j.name << " -> " << j.tvshowID << " -> " << j.slotid << endl;
        }
        cout << endl;
    }
}

void printRecord(vector<record>& v1){
    for(const auto& i : v1)
    {
        cout << "Member Name: " << i.memberName << endl;
        cout << "slotId : " << i.slot << endl;
        cout << "Day : " << i.Day << endl;
        cout << "seriesId : " << i.seriesID << endl;
        cout << endl;
    }
}

int main(){
    

    system("clear");
    ifstream sample("TempFile.csv");
    ifstream sh("sampleshowtime.csv");
    string line;

    vector<series> ghi;
    vector<Member> abc;
    getline(sh,line);
    while(getline(sh,line))
    {
        stringstream ss(line);
        string token;
        series p;
        getline(ss,token,',');
        p.id = stoi(token);
        getline(ss,token,',');
        p.name = token;
        getline(ss,token);
        p.showtime = slotId(token);
        ghi.push_back(p);
    }
    getline(sample,line);
    getline(sample,line);
    while(getline(sample,line))
    {
        stringstream ss(line);
        string token;
        Member m;
        getline(ss,token,',');
        m.member_id = token;
        getline(ss,token,',');
        m.name = token;
        for(int i = 0; i<7 ; i++)
        {
            getline(ss,token,',');
            m.availability.push_back(slotId(token));
        }
        while(getline(ss,token,','))
        {
            m.favorite_series.push_back(token);
            m.favserID.push_back(sereiseID(ghi,token));
        }
        abc.push_back(m);
    }
    HashTable seriestable;
    for(const auto& i : abc)
    {
        for(const auto& j : i.favorite_series)
        {
            seriestable.insert(i.name,j);
        }
    }

    for(const auto& j : ghi)                        
    {
        seriestable.insert(j.showtime,j.id);
    }
    
    for(const auto& i : abc)
    {
        for(const auto& j : i.favserID)
        {
            seriestable.insert(j,i.name);
        }
    }

    seriestable.insert(abc);

    vector<record> tvRecord;
    
    vector<TVShow> tv(10);
    TVScheduleFunction(seriestable,tv,ghi);
    cout << endl;

    cout << "TV Schedule is :- " << endl;
    printTVSchedule(tv);

   printRecord(tvRecord);

    return 0;
}
