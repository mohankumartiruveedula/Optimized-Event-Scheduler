#include <bits/stdc++.h>
using namespace std;

//core logic methods
int ub(int index,std::vector<std::vector<int>>& events);
int rec(int ind,int k,std::vector<std::vector<int>>& events,std::vector<std::vector<int>> &dp);
std::vector<int> maxValue(std::vector<std::vector<int>> events, int k);

//handler functions
void addEvent(vector<vector<int>> &events,vector<string> &eventNames);
void removeEvent(vector<vector<int>> &events,vector<string> &eventNames);
void displayEvent(vector<vector<int>> &events,vector<string> &eventNames);
void optimizeEvent(vector<vector<int>> &events,vector<string> &eventNames);

int main(){
    int choice = 0;
    vector<vector<int>> events;
    vector<string> eventNames;

    while(choice!=5){
        cout<<"               Optimized Event Scheduler              \n\n";
        cout<<"Select Operation :-   \n";
        cout<<"->1 Add Event\n";
        cout<<"->2 Remove Event\n";
        cout<<"->3 Display Events\n";
        cout<<"->4 Optimize Events\n";
        cout<<"->5 Exit";
        cin>>choice;

        switch(choice){
            case 1:addEvent(events,eventNames);break;
            case 2:removeEvent(events,eventNames);break;
            case 3:displayEvent(events,eventNames);break;
            case 4:optimizeEvent(events,eventNames);break;
            case 5:break;
            default:cout<<"\nPlease Select a valid option";
        }

        system("cls");
    }

    return 0;
}


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

std::vector<int> maxValue(std::vector<std::vector<int>> events, int k) {
    int n = events.size();
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