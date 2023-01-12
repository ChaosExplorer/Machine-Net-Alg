#include <iostream>

#include "ctimer.h"

using namespace std;


struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
  };
 
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* t1 = head, *t2, *t3;

        if (t1 != nullptr) t2 = t1->next; 
        else return head;

        while(1) {
            if (t2) t3 = t2->next; else break;
            t2->next = t1;
            t1 = t2;
            t2 = t3;
        }

		head->next = nullptr;
        head = t1;

        return head;
    }
};


int main()
{
    // create list
    ListNode *in = nullptr, *head = nullptr;
	
    int myint = 0;
	
	cin >> myint;

	if (-99 != myint)   in = new ListNode(myint);
	head = in;

    while(in) {
    	cin >> myint;
		if (myint == -99) break;
		in->next = new ListNode(myint);
		in = in->next;
    }

	if(in)  in->next = nullptr;
	

    // cal
	auto t1 = t_now();
    
	Solution s;
	head = s.reverseList(head);
	
	auto t2 = t_now();
	t_cal_echo(t1, t2);
	

    // print and clean
    in = head;
	while (in) {
		cout << in->val << endl;
        delete in;

		in = in->next;
	}
	
    cin.get();

    return 0;
}
