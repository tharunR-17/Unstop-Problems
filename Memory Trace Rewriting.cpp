#include <bits/stdc++.h>

struct Node {
    int id;
    int val;
    Node* next;

    Node(int _id, int _val) : id(_id), val(_val), next(nullptr) {}
};

std::string detect_cycle_or_sum(int n, const std::vector<std::tuple<int, int, int>>& blocks, int head_id) {
    std::unordered_map<int,std::vector<int>> mp;
    for(int i=0;i<n;i++)
    {
        mp[std::get<0>(blocks[i])]={std::get<1>(blocks[i]),std::get<2>(blocks[i]),0};
    }
    int a=0;
    while(head_id!=-1)
    {
        if(mp[head_id][2]==0)
        {
            a+=mp[head_id][0];
            mp[head_id][2]=1;
            head_id=mp[head_id][1];
        }
        else
        {
            return "CYCLE DETECTED";
        }
    }
    return std::to_string(a);
}

int main() {
    int n;
    std::cin >> n;
    std::vector<std::tuple<int, int, int>> blocks(n);

    for (int i = 0; i < n; ++i) {
        int bid, val, nid;
        std::cin >> bid >> val >> nid;
        blocks[i] = std::make_tuple(bid, val, nid);
    }

    int head_id;
    std::cin >> head_id;

    std::string result = detect_cycle_or_sum(n, blocks, head_id);
    std::cout << result << std::endl;

    return 0;
}
