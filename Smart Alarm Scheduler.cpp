#include <bits/stdc++.h>
using namespace std;
void find_next_alarm(int N, int S, int K, std::vector<std::string> &alarms, std::string &current_time) 
{
    vector<int> v;
    for(int i=0;i<N;i++)
    {
        string s="";
        int a=0;
        for(int j=0;j<alarms[i].length();j++)
        {
            if(alarms[i][j]!=':')
            {
                s+=alarms[i][j];
            }
            else
            {
                a=stoi(s)*60;
                s="";
            }
        }
        a+=stoi(s);
        if(a<1440)
        {
            v.push_back(a);
        }
        for(int j=0;j<K;j++)
        {
            a+=S;
            if(a<1440)
            {
                v.push_back(a);
            }
        }
    }
    int a=0,b=0;
    string s="";
    for(int j=0;j<current_time.length();j++)
        {
            if(current_time[j]!=':')
            {
                s+=current_time[j];
            }
            else
            {
                a=stoi(s)*60;
                s="";
            }
        }
        a+=stoi(s);
        sort(v.begin(),v.end());
    for(int i=0;i<v.size();i++)
    {
        if(a<v[i])
        {
            if(v[i]/60<10)
            {
                cout<<'0';
            }
            cout<<v[i]/60<<':';
            if(v[i]%60<10)
            {
                cout<<0;
            }
            cout<<v[i]%60;
            b++;
            break;
        }
    }
    if(b==0)
    {
        cout<<-1;
    }
}

int main() {
    int N, S, K;
    std::cin >> N >> S >> K;

    std::vector<std::string> alarms(N);
    for (int i = 0; i < N; i++) {
        std::cin >> alarms[i];
    }

    std::string current_time;
    std::cin >> current_time;

    find_next_alarm(N, S, K, alarms, current_time);
    return 0;
}
