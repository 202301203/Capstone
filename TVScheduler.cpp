#include<iostream>
#include<vector>
#define M 15
using namespace std;

class TVSeries{
    
};

class Member{
    private:
        string name;
        vector<int> FreeSlots; //1 for free slot , 0 for busy
        vector<string> FavoriteSeries;
    public:
        Member(string s) : name(s) {
            int k;
            cout << "Enter Free Slots of Member " << s << "(1 for free, 0 otherwise) :- ";
            for(int i=0 ; i<M ; i++)
            {
                cin >> k;
                FreeSlots.push_back(k);
            }
            
        } 
};



int main(){

    return 0;
}