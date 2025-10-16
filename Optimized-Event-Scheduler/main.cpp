#include <bits/stdc++.h>
#include <conio.h>
using namespace std;

//Global Variables
int choice = 0;
vector<vector<int>> events;
vector<string> eventNames;
unordered_map<int,pair<vector<vector<int>>::iterator,vector<string>::iterator>> eventMap;

//core logic methods
int ub(int index,std::vector<std::vector<int>>& events);
int rec(int ind,int k,std::vector<std::vector<int>>& events,std::vector<std::vector<int>> &dp);
std::vector<int> maxValue(std::vector<std::vector<int>> events, int k);

//handler functions
void addEvent();
void removeEvent();
void displayEvent();
void optimizeEvent();

int main(){

    while(choice!=5){
        cout<<"               Optimized Event Scheduler              \n\n";
        cout<<"Select Operation :-   \n";
        cout<<"->1 Add Event\n";
        cout<<"->2 Remove Event\n";
        cout<<"->3 Display Events\n";
        cout<<"->4 Optimize Events\n";
        cout<<"->5 Exit\n\n";
        cin>>choice;

        switch(choice){
            case 1:addEvent();break;
            case 2:removeEvent();break;
            case 3:displayEvent();break;
            case 4:optimizeEvent();break;
            case 5:break;
            default:cout<<"\nPlease Select a valid option";
        }

        system("cls");
    }

    return 0;
}

//Upper Bound Binary Search
int ub(int index,std::vector<std::vector<int>>& events){
    int req=events.size();
    int myend = events[index][1];
    int l = index , r = events.size()-1;

    while(l<=r){
        int mid = l + (r-l)/2;
        if(events[mid][0]>myend){
            req = mid;
            r = mid - 1;
        }else{
            l = mid+1;
        }
    }

    return req;
}
//Dp memoization Solution
int rec(int ind,int k,std::vector<std::vector<int>>& events,std::vector<std::vector<int>> &dp){
    if(ind>=events.size() || k==0){
        return 0;
    }

    if(dp[ind][k]!=-1){return dp[ind][k];}

    int notPick = rec(ind+1,k,events,dp);
    int next = ub(ind,events);

    int pick = events[ind][2] + rec(next,k-1,events,dp);


    return dp[ind][k] = std::max(pick,notPick);
}
//Driver method
std::vector<int> maxValue(std::vector<std::vector<int>> events, int k) {
    int n = events.size();

    for(int i=0 ; i < n ; i++){
        events[i].push_back(i);
    }

    sort(events.begin(),events.end());
    std::vector<std::vector<int>> dp(n+1,std::vector<int>(k+1,-1));
    rec(0,k,events,dp);

    int a=0,b=k;
    
    std::vector<int> res(1,dp[0][k]);

    while(a<n && b>0){
        int pick = events[a][2];
        int next = ub(a,events);
        if(next != n){pick += dp[next][b-1];}
        if(pick >= dp[a+1][b]){
            res.push_back(events[a][3]);
            a=next;
            b--;
        }else{
            a++;
        }
    }


    return res;
}

void addEvent(){

    system("cls");

    int eventId , startDate , endDate , priority;
    string eventName;

    cout<<"               Optimized Event Scheduler              \n\n";

    //Random Event Id Generator
    srand(time(0));
    eventId = rand()%1000;
    while(eventMap.count(eventId)){
        eventId = rand()%1000;
    }

    cout<<"Enter Event Name : ";
    cin>>eventName;
    cout<<endl;
    cout<<"Enter Start Date of Event (Please only enter in a number format) (Eg : 1 , 10 etc || Not like 12-10-2025) : ";
    cin>>startDate;
    cout<<endl;
    cout<<"Enter End Date of Event (Please only enter in a number format) (Eg : 1 , 10 etc || Not like 12-10-2025) : ";
    cin>>endDate;
    cout<<endl;
    cout<<"Enter Priority / Importance / Worth Value (Deciding Parameter) : ";
    cin>>priority;
    cout<<endl;

    if(startDate>endDate){
        system("cls");
        cout<<"Please Enter Valid dates";
        _getch();
        return;
    }

    events.push_back({startDate,endDate,priority});
    eventNames.push_back(eventName);
    eventMap[eventId] = {events.end() - 1 , eventNames.end() - 1};

    system("cls");
    cout<<"Event "<<eventId<<" added Successfully !!";
    _getch();
}

void removeEvent(){
    system("cls");

    if(events.size()==0){
        system("cls");
        cout<<"There are No Events to delete";
        _getch();
        return;
    }

    int eventId;

    cout<<"Enter event Id : ";
    cin>>eventId;

    if(!eventMap.count(eventId)){
        system("cls");
        cout<<"Event with "<<eventId<<" does not exist or may be deleted";
        _getch();
    }

    events.erase(eventMap[eventId].first);
    eventNames.erase(eventMap[eventId].second);
    eventMap.erase(eventId);

    system("cls");
    cout<<"Event "<<eventId<<" deleted Successfully !!";
    _getch();
}


void displayEvent(){

}


void optimizeEvent(){

    system("cls");

    if(events.size() == 0){
        cout<<"No Events to Optimize !";
        _getch();
        return;
    }
}