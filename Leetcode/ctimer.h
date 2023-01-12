#ifndef __CTIMER_H_
#define __CTIMER_H_

#include<chrono>
#include<iostream>
#include<vector>
#include<cstdlib>

using std::cout;
using std::endl;
using std::vector;
using namespace std::chrono;

typedef high_resolution_clock::time_point t_type;

static inline t_type t_now()
{
	return high_resolution_clock::now();
}


static inline double t_cal(t_type& t1, t_type& t2)
{
	return duration<double, std::milli>(t2 - t1).count();
}

static inline void t_cal_echo(t_type& t1, t_type& t2)
{
	auto t = duration<double, std::milli>(t2 - t1);
	cout << "time cost : " << t.count() << "  ms" << endl;
}

static void generateVec(vector<int>& in, int n, int range)
{
	for (int i = 0; i < n; ++i) {
		in.emplace_back(rand() % range + 1);
	}
}

static void checkVecOrder(vector<int>& in)
{
	bool ret = true;
	
	short ascend_flag = 0;
	for(int i = 1; i < in.size()-1; ++i) {
		if(in[i] < in[i+1]) {
			if (ascend_flag == -1)	{ 
				ret = false; break; 
			}
			ascend_flag = 1; 
		}
		else if(in[i] > in[i+1]) { 
			if (ascend_flag == 1)	{
				ret = false; break; 
			}
			ascend_flag = -1; 
		}
	}
	
	if (ret)
		cout << endl << "Sorted !!" << endl;
	else
		cout << endl << "Not Sorted !!" << endl;
}

template <class T>
static void printVec(vector<T>& in) {
	if (in.empty())	return;
	cout << "vector : " << endl;
	int i = 0;	// notice : if use size_t, in.size() - 2 maybe trigger overflow
	for (; i <= (int)in.size() - 2; ++i) {	// size() - 2 overflows when size <= 1
		cout << in[i] << "  |  ";
	}
	//std::for_each(in.begin(), in.end(), [](T& it) { cout << it << " , "; });
	cout << in[i] << endl;
}


#endif   // __CTIMER_H_