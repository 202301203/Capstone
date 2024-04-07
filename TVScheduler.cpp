#include<windows.h>
#include<iostream>
#include<map>
#include<fstream>
#include<sstream>
#include<string>
#include<unordered_map>
#include <vector>
#include<list>
#include<queue>
#include<cstdlib>
#include<unistd.h>
#include<iomanip>
#include <stdio.h>
#include<algorithm>
#include <cstdio>
#define N 10
#define S 15
#define TABLE_SIZE 20

using namespace std;

class slot;
class Member {
    public:
        string member_id;
        string name;
        vector<string> favorite_series;
        vector<int> availability;
        vector<int> favserID;
        int flag = 0;
};

int slotId(string s)
{
    map<string,int> TimeToSlot;
    TimeToSlot["8:00-9:00"] = 1;
    TimeToSlot["9:00-10:00"] = 2;
    TimeToSlot["10:00-11:00"] = 3;
    TimeToSlot["11:00-12:00"] = 4;
    TimeToSlot["12:00-13:00"] = 5;
    TimeToSlot["13:00-14:00"] = 6;
    TimeToSlot["14:00-15:00"] = 7;
    TimeToSlot["15:00-16:00"] = 8;
    TimeToSlot["16:00-17:00"] = 9;
    TimeToSlot["17:00-18:00"] = 10;
    TimeToSlot["18:00-19:00"] = 11;
    TimeToSlot["19:00-20:00"] = 12;
    TimeToSlot["20:00-21:00"] = 13;
    TimeToSlot["21:00-22:00"] = 14;
    TimeToSlot["22:00-23:00"] = 15;
    for(const auto& i : TimeToSlot)
    {
        if(i.first == s)
            return i.second;
    }
    return 0;
}

int slotIdtoTime(int k)
{
    switch(k)
    {
        case 1:
            return 8;
        case 2:
            return 9;
        case 3:
            return 10;
        case 4:
            return 11;
        case 5:
            return 12;
        case 6:
            return 13;
        case 7:
            return 14;
        case 8:
            return 15;
        case 9:
            return 16;
        case 10:
            return 17;
        case 11:
            return 18;
        case 12:
            return 19;
        case 13:
            return 20;
        case 14:
            return 21;
        case 15:
            return 22;
        case 16:
            return 23;
        default:
            return 0;
    }
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

class slot{
    public:
        string tvshowName;
        int slotid;
        string day;
        vector<Member> m2;
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

struct MyComparator {
    bool operator()(const slot& a, const slot& b) const {
        int s=a.m2[0].flag , r=b.m2[0].flag;
        for(const auto& i : a.m2)
        {
            if(i.flag < s)
                s = i.flag;
        }
        for(const auto& i : b.m2)
        {
            if(i.flag < r)
                r = i.flag;
        }
        return s > r;
    }
};

class TVShow{                                       //vector<TVShow>
    public:
        vector<slot> DaysOfWeek;
};


class HashTable{
    public:
        unordered_map<int,vector<int>> ShowtimeToSeriesTable;
        unordered_map<int,vector<Member> SeriesIdToMemberTable;
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
};

string idtoname(vector<series>& ghi,int p){
    for(const auto& i : ghi)
    {
        if(i.id == p)
            return i.name;
    }
    return " ";
}

//conflict function
bool conflict(int value,HashTable& hasht,int incrementJ,int day){
    for(int i=0 ; i<hasht.ShowtimeToSeriesTable[incrementJ].size() ; i++)
    {
        int sd = hasht.ShowtimeToSeriesTable[incrementJ][i];
        for(int k=0 ; k<hasht.SeriesIdToMemberTable[sd].size() ; k++)
        {
            if(hasht.SeriesIdToMemberTable[sd][k].availability[day] == value)
            {
                return true;
            }
        }
    }
    return false;
}

//TVSchedule Function
void TVScheduleFunction(HashTable& sample,vector<TVShow>& tv,vector<series>& ghi,vector<slot>& tvrecord,vector<Member>& m1,vector<vector<bool>>& slotavailability)
{
    int numDays = 7;
    int numSlot = 15;
    //int l = numDays*numSlot;
    //tvrecord.resize(l);
    slotavailability.resize(numDays);
    for(int i=0 ; i<numDays ; i++)
    {
        slotavailability[i].resize(numSlot,false);
    }

    for(int divas=0 ; divas<7 ; divas++)
    {
        for(int sl=1 ; sl<=numSlot ; sl++)
        {
            priority_queue<slot,vector<slot>,MyComparator> pq;
            int f = 0;
            for(int j=0 ; j<sample.ShowtimeToSeriesTable[sl].size() ; j++)
            {
                int Jsincrement = j + 1;
                if(f == 0 && !conflict(sl,sample,Jsincrement,divas))
                {
                    int h = sample.ShowtimeToSeriesTable[sl][j];
                    for(int k=0 ; k<sample.SeriesIdToMemberTable[h].size() ; k++)
                    {
                        if(sample.SeriesIdToMemberTable[h][k].availability[divas] == sl)
                        {
                            slot temp;
                            temp.m2.push_back(sample.SeriesIdToMemberTable[h][k]);      //Member Name
                            temp.tvshowName = idtoname(ghi,h);
                            temp.slotid = sl;
                            temp.day = idToDay(divas);
                            tv[divas].DaysOfWeek.push_back(temp);
                            f = 1;
                            for(int g=0 ; g<m1.size() ; g++)
                            {
                                if(m1[g].name == sample.SeriesIdToMemberTable[h][k].name)
                                {
                                    m1[g].flag++;
                                    break;
                                }
                            }
                            slotavailability[divas][sl-1] = true;
                        }
                        else
                        {
                            slot temp;
                            temp.m2.push_back(sample.SeriesIdToMemberTable[h][k]);        //Member Name
                            temp.tvshowName = idtoname(ghi,h);
                            temp.slotid = sl;
                            temp.day = idToDay(divas);
                            for(int g=0 ; g<m1.size() ; g++)
                            {
                                if(m1[g].name == sample.SeriesIdToMemberTable[h][k].name)
                                {
                                    temp.m2[0].flag = m1[g].flag;
                                    break;
                                }
                            }
                            pq.push(temp);
                        }
                    }
                }
            }
            if(!pq.empty())
            {
                tvrecord.push_back(pq.top());
                for(int g=0 ; g<m1.size() ; g++)
                {
                    for(int p=0 ; p<pq.top().m2.size() ; p++)
                    {
                        if(m1[g].name == pq.top().m2[p].name)
                        {
                            m1[g].flag++;
                            break;
                        }
                    }
                }
            }    
        }
    }
}

//notification function
void Notification(vector<TVShow>& tv)
{
    for(int d=0 ; d<7 ; d++)
    {   
        
        int i=0; 
        while(1)
        {
            time_t samay;
            time(&samay);
            struct tm* ti = localtime(&samay);
            if((slotIdtoTime(tv[d].DaysOfWeek[i].slotid)-1) == ti->tm_hour)
            {
                string buffer = tv[d].DaysOfWeek[i].m2[0].name;
                // Format the message
                for(int l=1 ; l<tv[d].DaysOfWeek[i].m2.size()-1 ; l++)
                {
                    buffer += tv[d].DaysOfWeek[i].m2[l].name;
                    if(l<(tv[d].DaysOfWeek[i].m2.size()-2))
                        buffer += " and ";
                }
                buffer += " is Scheduled for the TV after an Hour!";
                MessageBox(NULL,buffer.c_str(),"Notification",MB_OK);
                i++;
                if(i == 15)
                    break;
            }
            else if(slotIdtoTime(i) < ti->tm_hour)
            {
                i++;
            }
        }
    }
}

//schedule recorder data
void ScheduleRecorded(vector<TVShow>& tv,vector<slot>& record,vector<vector<bool>>& availStatus,vector<Member>& m1,HashTable& ht)
{
    for(int i=0 ; i<7 ; i++)
    {
        for(int j=1 ; j<=S ; j++)
        {
            priority_queue<slot,vector<slot>,MyComparator> pq;
            slot w;
            for(int k=0 ; k<record.size() ; k++)
            {
                if(!availStatus[i][j-1] && ht.MemberToFreeSlotTable[record[k].m2[0].name][i] == j)
                {
                    record[k].slotid = j;
                    for(int g=0 ; g<m1.size() ; g++)
                    {
                        if(m1[g].name == record[k].m2[0].name)
                        {
                            m1[g].flag++;
                            break;
                        }
                    }
                    pq.push(record[k]);
                }
            }
            if(!pq.empty())
            {
                int removeIndex = -1;
                tv[i].DaysOfWeek.push_back(pq.top());
                availStatus[i][j] = true;
                for(int r=0 ; r<record.size() ; r++)
                {
                    if(record[r].m2[0].name == pq.top().m2[0].name && record[r].tvshowName == pq.top().tvshowName)
                    {
                        removeIndex = r;
                        if (removeIndex != -1) 
                        {
                            record.erase(record.begin() + removeIndex);
                            break;
                        }
                    }
                }
            }
        }
    }
}

void printTable(const vector<TVShow>& tvShows) {
    // Print header
    cout << setw(10) << "TV Schedule" << endl;
    cout << "-------------------------------------------------------------------" << endl;
    cout << setw(10) << "Day" << setw(20) << "Member Name" << setw(25) << "TV Show Name" << setw(10) << "Slot" << endl;
    cout << "-------------------------------------------------------------------" << endl;

    // Print data
    for (int day = 0; day < tvShows.size(); ++day) {
        for (int k=0 ; k<tvShows[day].DaysOfWeek.size() ; k++) {
            for(int p=0 ; p<tvShows[day].DaysOfWeek[k].m2.size() ; p++)
            cout << "|" << setw(9) << idToDay(day) << setw(1) << "|" << setw(19) << tvShows[day].DaysOfWeek[k].m2[p].name << setw(1) << "|" << setw(24) << tvShows[day].DaysOfWeek[k].tvshowName << setw(1) << "|" << setw(9) << tvShows[day].DaysOfWeek[k].slotid << setw(1) << "|" << endl;
        }
        cout << endl;
        if(day == 6)
            cout << "---------------------------------------------------------------------" << endl;
    }    
}
void sort(vector<TVShow>& tv)
{
    for(int i=0 ; i<7 ; i++)
    {
        for(int j=0 ; j<tv[i].DaysOfWeek.size() ; j++)
        {
            for(int k=j ; k<tv[i].DaysOfWeek.size() ; k++)
            {
                if(tv[i].DaysOfWeek[j].slotid > tv[i].DaysOfWeek[k].slotid)
                {
                    slot temp = tv[i].DaysOfWeek[j];
                    tv[i].DaysOfWeek[j] = tv[i].DaysOfWeek[k];
                    tv[i].DaysOfWeek[k] = temp;
                }
            }
        }
    }
}

int main(){
    
    system("cls");
    ifstream sample("TempFileSaloni.csv");
    ifstream sh("sampleshowtimeSaloni.csv");
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
    
    seriestable.insert(abc);

    for(const auto& j : ghi)                        
    {
        seriestable.insert(j.showtime,j.id);
    }
    
    for(const auto& i : abc)
    {
        for(const auto& j : i.favserID)
        {
            seriestable.insert(j,i);
        }
    }
    
    vector<slot> tvRecord;

    vector<vector<bool>> assignStatus; 
    
    vector<TVShow> tv(105);
    TVScheduleFunction(seriestable,tv,ghi,tvRecord,abc,assignStatus);
    cout << endl;

    cout << "\nSeries to be record : - " << endl;
    printRecord(tvRecord);
    
    ScheduleRecorded(tv, tvRecord,assignStatus,abc,seriestable);
    sort(tv);
   
    printTable(tv);
    Notification(tv);
    
    return 0;
}
