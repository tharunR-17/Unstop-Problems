#include <bits/stdc++.h>
using namespace std;
typedef long long ll ;

struct ListNode {
    int val;
        ListNode* next;
            ListNode(int x) : val(x), next(NULL) {}
            };

            string user_logic(ListNode* head) {
                /*
                    Write your logic here.
                        Parameters:
                                head (ListNode*): Head node of the singly linked list
                                    Returns:
                                            string: "even" if the final number is an even number, otherwise "odd"
                                                */
                                                    return "";
                                                    }

                                                    int main() {
                                                        int N;
                                                            cin >> N;
                                                                ListNode* head = NULL;
                                                                    ListNode* tail = NULL;
                                                                        for (int i = 0; i < N; i++) {
                                                                                int value;
                                                                                        cin >> value;
                                                                                                ListNode* newNode = new ListNode(value);
                                                                                                        if (!head) {
                                                                                                                    head = newNode;
                                                                                                                            } else {
                                                                                                                                        tail->next = newNode;
                                                                                                                                                }
                                                                                                                                                        tail = newNode;
                                                                                                                                                            }
                                                                                                                                                                // string result = user_logic(head);
                                                                                                                                                                    ListNode* curr = head ;
                                                                                                                                                                        ll num = 0 ;
                                                                                                                                                                            ll sum = 0 ;
                                                                                                                                                                                stack<int> st ;
                                                                                                                                                                                    while(head){
                                                                                                                                                                                            // num = num * 10 + (head -> val) ;
                                                                                                                                                                                                    if(st.empty() && (head -> val) == 0){
                                                                                                                                                                                                                head = head -> next ;
                                                                                                                                                                                                                            continue ;
                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                            st.push(head -> val) ;
                                                                                                                                                                                                                                                    sum += (head -> val) ;
                                                                                                                                                                                                                                                            head = head -> next ;
                                                                                                                                                                                                                                                                }
                                                                                                                                                                                                                                                                    while(st.size()){
                                                                                                                                                                                                                                                                            num = num * 10 + (st.top()) ;
                                                                                                                                                                                                                                                                                    st.pop() ;
                                                                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                                                                                            ll diff = num - sum ;
                                                                                                                                                                                                                                                                                                if(diff & 1) cout<<"odd"<<endl ;
                                                                                                                                                                                                                                                                                                    else cout<<"even"<<endl ;





                                                                                                                                                                                                                                                                                                        // cout << result << endl;
                                                                                                                                                                                                                                                                                                            return 0;
                                                                                                                                                                                                                                                                                                            }
