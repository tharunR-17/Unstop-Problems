#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, Q;
    if (!(cin >> N >> Q)) return 0;

    string S;
    cin >> S;

    int M = 1;
    while (M < N) {
        M *= 2;
    }

    vector<int> tree(2 * M, 0);

    for (int i = 0; i < N; i++) {
        if (S[i] == '.') {
            tree[M + i] = 1;
        }
    }

    for (int i = M - 1; i > 0; i--) {
        tree[i] = tree[2 * i] + tree[2 * i + 1];
    }

    auto update = [&](int idx, int val) {
        idx += M;
        tree[idx] = val;
        idx /= 2;
        while (idx > 0) {
            tree[idx] = tree[2 * idx] + tree[2 * idx + 1];
            idx /= 2;
        }
    };

    auto find_first = [&](int ql, int qr) -> int {
        if (ql > qr) return -1;
        
        int l = ql + M;
        int r = qr + M;
     
        int left_nodes[40];
        int right_nodes[40];
        int l_cnt = 0, r_cnt = 0;
        
        while (l <= r) {
            if (l % 2 == 1) left_nodes[l_cnt++] = l++;
            if (r % 2 == 0) right_nodes[r_cnt++] = r--;
            l /= 2;
            r /= 2;
        }
        int nodes[80];
        int n_cnt = 0;
        for (int i = 0; i < l_cnt; i++) {
            nodes[n_cnt++] = left_nodes[i];
        }
        for (int i = r_cnt - 1; i >= 0; i--) {
            nodes[n_cnt++] = right_nodes[i];
        }
        
        for (int i = 0; i < n_cnt; i++) {
            int node = nodes[i];
            if (tree[node] > 0) {
                int curr = node;
                while (curr < M) {
                    if (tree[2 * curr] > 0) {
                        curr = 2 * curr; 
                    } else {
                        curr = 2 * curr + 1; 
                    }
                }
                return curr - M;
            }
        }
        return -1;
    };

    vector<int> booking_pos;
    vector<bool> booking_active;
    booking_pos.push_back(-1);
    booking_active.push_back(false);
    
    vector<int> results;
    results.reserve(Q);

    for (int i = 0; i < Q; i++) {
        int q;
        cin >> q;
        if (q > 0) {
            int pref = q - 1;
            int pos = find_first(pref, N - 1);
            if (pos == -1) {
                pos = find_first(0, pref - 1);
            }
            
            if (pos != -1) {
                update(pos, 0);
                booking_pos.push_back(pos);
                booking_active.push_back(true);
                results.push_back(pos + 1);
            } else {
                booking_pos.push_back(-1);
                booking_active.push_back(false);
                results.push_back(0);
            }
        } else {
            int j = -q;
            if (j >= 1 && j < booking_active.size() && booking_active[j]) {
                int pos = booking_pos[j];
                if (pos != -1) {
                    update(pos, 1); 
                }
                booking_active[j] = false;
            }
        }
    }
for (int i = 0; i < results.size(); i++) {
        cout << results[i] << (i == results.size() - 1 ? "" : " ");
    }
    cout << "\n";

    return 0;
}
