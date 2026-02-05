#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

// Define a structure for a Person
struct Person {
    int personID;
    int arrivalTime;
    int urgencyLevel;
    int serviceType;
    
    Person(int id, int arrival, int urgency, int service) 
        : personID(id), arrivalTime(arrival), urgencyLevel(urgency), serviceType(service) {}
};

// Fixed user_logic function
vector<int> user_logic(int N, int K, vector<Person>& people) 
{
    
    stable_sort(people.begin(), people.end(), [](const Person& a, const Person& b)
    {
        
        if(a.urgencyLevel!=b.urgencyLevel)
        {
            return a.urgencyLevel>b.urgencyLevel;
        }
        
        if(a.arrivalTime != b.arrivalTime)
        {
            return a.arrivalTime<b.arrivalTime;
        }
        
        return a.serviceType<b.serviceType;
    }); 

    
    vector<int> result;
    for (int i = 0; i < K && i < (int)people.size(); ++i) 
    {
        result.push_back(people[i].personID);
    }

    return result;
}

int main() 
{
    int N, K;
    if (!(cin >> N >> K)) return 0;

    vector<Person> people;
    people.reserve(N); 
    
    for (int i = 0; i < N; ++i) {
        int id, arrival, urgency, service;
        cin >> id >> arrival >> urgency >> service;
        people.emplace_back(id, arrival, urgency, service);
    }

    
    vector<int> result = user_logic(N, K, people);

    
    for(int personID : result)
    {
        cout << personID << endl; 
    }

    return 0;
}
