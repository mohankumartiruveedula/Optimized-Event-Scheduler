#include <bits/stdc++.h>
#include "httplib.h"
#include "json.hpp"

using json = nlohmann::json;

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

int main(){
    httplib::Server svr;

    svr.Post("/process",[](const httplib::Request &req,httplib::Response &res){
        
        std::vector<std::vector<int>> events;
        int k = -1;

        try{
            json data = json::parse(req.body);
            

            for (const auto& item : data) {
                if(k==-1){
                    k = item.at("k").get<int>();
                    continue;
                }
                auto description = item.at("description").get<std::string>();
                auto startDate = item.at("startDate").get<int>();
                auto endDate = item.at("endDate").get<int>();
                auto quantity = item.at("quantity").get<int>();
                events.push_back({startDate,endDate,quantity});
            }
            
            

        }catch(json::exception& e){
            std::cerr << "JSON Parse Error: " << e.what() << std::endl;
            res.status = 400; // Bad Request
            res.set_content("Invalid JSON format", "text/plain");
            return;
        }

        json response_json;

        std::vector<int> result = maxValue(events,k);

        response_json["totalValue"] = result[0];
        
        res.set_content(response_json.dump(), "application/json");
        res.set_header("Access-Control-Allow-Origin", "*");
    });

    std::cout << "C++ Backend Server (with Array support) started on http://localhost:1234" << std::endl;
    svr.listen("localhost", 8080);

    return 0;
}