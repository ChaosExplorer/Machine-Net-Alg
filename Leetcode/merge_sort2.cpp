#include "ctimer.h"



// merge
vector<int> merge(vector<int>& vec1, vector<int>& vec2) {
    int span = std::max(vec1.back(), vec2.back()) + 1;
    int span_num = std::abs((int)(vec1.size() - vec2.size()));

    while (vec1.size() < vec2.size())   vec1.push_back(span);
    while (vec2.size() < vec1.size())   vec2.push_back(span);

    vector<int> ret(vec1.size()*2, 0);

    int i = 0, j = 0, t = 0;  
    while (i < vec1.size() && j < vec1.size()) {      // notice : only i < vec1.size() is wrong
        if (vec1[i] <= vec2[j]) {
            ret[t] = vec1[i];
            ++i;
        }
        else {
            ret[t] = vec2[j];
            ++j;
        }

        ++t;
    }
    
    while (span_num-- > 0) {
        ret.pop_back();
    }

    return ret;
}

// sort

void mergeSort (vector<int>& vec, uint left, uint right) {
    if (right <= left)  return;

    int mid = left + (right - left) / 2;    // notice : left +

    // merge(vec) = merge(merge(leftvec), merge(rightvec))
    
    mergeSort(vec, left, mid);
    
    mergeSort(vec, mid+1, right);

    //vector<int> vec1(&vec[left], &vec[mid+1]);   // notice: left close, right open
    vector<int> vec1(vec.begin()+left, vec.begin()+ mid+1);   // notice: left close, right open
    vector<int> vec2;
    if (right < vec.size()-1)   vec2.assign( vec.begin()+mid+1, vec.begin()+right+1);
    else vec2.assign(vec.begin()+mid+1, vec.end());
    //auto vec2 = vector<int>(&vec[mid+1], &vec[right+1]);    // notice , cann't use when right+1 reach vec.end(), maybe it has checks.
    //printVec(vec1);
    //printVec(vec2);
    auto ret = merge(vec1, vec2);
    //printVec(ret);

    // move 
    int t = 0;
    for (int i = left; i <= right; ++i) {
        vec[i] = ret[t++];
    }
}


int main() {
 
    vector<int> data;
    generateVec(data, 10, 100000);
    printVec(data);

    auto t1 = t_now();

    mergeSort(data, 0, data.size() - 1);

    auto t2 = t_now();
    t_cal_echo(t1, t2);


    printVec(data);
    auto ret = std::is_sorted(data.begin(), data.end());
    checkVecOrder(data);

    return 0;
}