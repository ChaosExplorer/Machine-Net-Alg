#include <iostream>
#include <vector>

#include "ctimer.h"

using namespace std;
using std::vector;


struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
  };
 
class Solution {
public:
    bool check(ListNode* head) {
        if (head == nullptr)    return false;
        if (head->next == nullptr)  return true;

        bool Odd = false;
        ListNode *t1 = head, *t2 = head, *t1pre, *t1next;

        // reach mid
        t1next = t1->next;
        while (t2) {
            // two step
            if (t2->next) t2 = t2->next->next;
            else    { Odd = true; break;}

            // one step
            t1pre = t1;
            t1 = t1next;
            t1next = t1->next;
            // reverse
            t1->next = t1pre;
        }

        // reverse front part
        head->next = nullptr;

        // compare
        if (Odd)
            t1 = t1pre;
        else {
            if (t1->val != t1pre->val)  return false;
            else    t1 = t1pre->next;
        }
            
        t2 = t1next;

        while (t2) {
            if (t1->val != t2->val)   return false;
            t1 = t1->next;
            t2 = t2->next;
        }

        return true;
    }

    bool check2(ListNode* head) {
        if (head == nullptr)    return false;
        if (head->next == nullptr)  return true;

        bool Odd = false;
        ListNode *t1 = head, *t2 = head;
        vector<ListNode*> ptr_que;

        // reach mid
        while (t2) {
            // two step
            if (t2->next) t2 = t2->next->next;
            else    { Odd = true; break;}

            // one step
            ptr_que.push_back(t1);
            t1 = t1->next;
        }

        // compare
        t2 = t1->next;
        size_t n = ptr_que.size() - 1;

        if(!Odd) {
            if (ptr_que[n]->val != t1->val)  return false;
            else  n -= 1;
        }
            
        while (t2) {
            if (ptr_que[n]->val != t2->val)   return false;
            --n;
            t2 = t2->next;
        }

        return true;
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
	auto ret = s.check2(head);
	
	auto t2 = t_now();
	t_cal_echo(t1, t2);
	

    // print and clean
    cout << "the ret is " << (ret ? "True" : "False") << endl;
    
    in = head;
    while (in) {
        delete in;
        in = in->next;
    }

	
    cin.get();

    return 0;
}
