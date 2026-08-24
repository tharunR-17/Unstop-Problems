#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Trie ke ek node ki structure
struct Node {
    int count; // Yeh track karne ke liye ki is subtree me kitne elements hain
    int left, right; // Left (0-bit) aur Right (1-bit) child ke indices
};

const int MAX_BITS = 30; // Kyunki a[i] <= 10^9 hai, jo 30 bits me fit ho jayega
vector<Node> trie;
vector<int> roots;

// Trie me naya element insert karne ke liye persistent tareeka
int insert(int prev_root, int val) {
    int new_root = trie.size();
    trie.push_back({0, 0, 0});
    
    int current = new_root;
    int prev = prev_root;
    
    trie[current].count = (prev ? trie[prev].count : 0) + 1;
    
    for (int i = MAX_BITS; i >= 0; --i) {
        int bit = (val >> i) & 1;
        if (bit == 0) {
            // Naya left child banayein aur right child ko purane se copy karein
            trie[current].right = (prev ? trie[prev].right : 0);
            trie[current].left = trie.size();
            trie.push_back({0, 0, 0});
            
            current = trie[current].left;
            prev = (prev ? trie[prev].left : 0);
        } else {
            // Naya right child banayein aur left child ko purane se copy karein
            trie[current].left = (prev ? trie[prev].left : 0);
            trie[current].right = trie.size();
            trie.push_back({0, 0, 0});
            
            current = trie[current].right;
            prev = (prev ? trie[prev].right : 0);
        }
        trie[current].count = (prev ? trie[prev].count : 0) + 1;
    }
    return new_root;
}

// Range [l, r] ke beech maximum XOR khojne ke liye query function
int query(int l_root, int r_root, int x) {
    int ans = 0;
    int curr_l = l_root;
    int curr_r = r_root;
    
    for (int i = MAX_BITS; i >= 0; --i) {
        int bit = (x >> i) & 1;
        // Hum chahte hain ki opposite bit mile taaki XOR maximum (1) ho sake
        int desired_bit = 1 - bit; 
        
        int count_in_range = 0;
        if (desired_bit == 0) {
            int r_child = (curr_r ? trie[curr_r].left : 0);
            int l_child = (curr_l ? trie[curr_l].left : 0);
            count_in_range = (r_child ? trie[r_child].count : 0) - (l_child ? trie[l_child].count : 0);
        } else {
            int r_child = (curr_r ? trie[curr_r].right : 0);
            int l_child = (curr_l ? trie[curr_l].right : 0);
            count_in_range = (r_child ? trie[r_child].count : 0) - (l_child ? trie[l_child].count : 0);
        }
        
        if (count_in_range > 0) {
            // Agar desired bit range me maujood hai, toh us taraf jao
            ans |= (1 << i);
            if (desired_bit == 0) {
                curr_r = (curr_r ? trie[curr_r].left : 0);
                curr_l = (curr_l ? trie[curr_l].left : 0);
            } else {
                curr_r = (curr_r ? trie[curr_r].right : 0);
                curr_l = (curr_l ? trie[curr_l].right : 0);
            }
        } else {
            // Agar desired bit nahi hai, toh majboori me dusri taraf jana hoga
            if (desired_bit == 0) {
                curr_r = (curr_r ? trie[curr_r].right : 0);
                curr_l = (curr_l ? trie[curr_l].right : 0);
            } else {
                curr_r = (curr_r ? trie[curr_r].left : 0);
                curr_l = (curr_l ? trie[curr_l].left : 0);
            }
        }
    }
    return ans;
}

int main() {
    // Fast I/O standard Competitive Programming ke liye
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    if (!(cin >> n)) return 0;
    
    trie.push_back({0, 0, 0}); // Dummy node at index 0
    roots.push_back(0); // Root for empty state (0 elements)
    
    for (int i = 1; i <= n; ++i) {
        int val;
        cin >> val;
        int new_root = insert(roots.back(), val);
        roots.push_back(new_root);
    }
    
    int q;
    cin >> q;
    while (q--) {
        int l, r, x;
        cin >> l >> r >> x;
        // Hame range [l, r] chahiye, isliye roots[r] aur roots[l-1] ka difference check karenge
        cout << query(roots[l - 1], roots[r], x) << "\n";
    }
    
    return 0;
}
