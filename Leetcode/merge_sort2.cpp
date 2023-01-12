#include "ctimer.h"



// merge
vector<int> merge(vector<int>& vec1, vector<int>& vec2) {
    int span;
    if (vec1.back() > vec2.back()) {    // notice : when == , vec1 should push , vec2
        span = vec1.back()+1;
        vec2.push_back(span);
    }
    else {
        span = vec2.back()+1;
        vec1.push_back(span);
    }

    vector<int> ret(vec1.size()+vec2.size()+1, 0);

    int i = 0, j = 0, t = 0;  
    while (i < vec1.size() && j < vec2.size()) {      // notice : only i < vec1.size() is wrong
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
    
    ret.pop_back();

    return ret;
}

vector<int> merge2(vector<int>& vec1, vector<int>& vec2) {
    vector<int> ret(vec1.size()+vec2.size(), 0);

    int i = 0, j = 0, t = 0;  
    while (i < vec1.size() && j < vec2.size()) {      // notice : only i < vec1.size() is wrong
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
    
    while (i < vec1.size()) {   ret[t++] = vec1[i++]; }
    while (j < vec2.size()) {   ret[t++] = vec2[j++]; }
    

    return ret;
}

// test : merge2 faster than merge, although merge is briefer, got one loop

// sort

void mergeSort (vector<int>& vec, uint left, uint right) {
    if (right <= left)  return;

    int mid = left + (right - left) / 2;    // notice : left +

    // merge(vec) = merge(merge(leftvec), merge(rightvec))
    
    mergeSort(vec, left, mid);
    
    mergeSort(vec, mid+1, right);

    //vector<int> vec1(&vec[left], &vec[mid+1]);   // notice: left close, right open
    vector<int> vec1(vec.begin()+left, vec.begin()+ mid+1);   // notice: left close, right open
    //vector<int> vec2;
    //if (right < vec.size()-1)   vec2.assign( vec.begin()+mid+1, vec.begin()+right+1);
    //else vec2.assign(vec.begin()+mid+1, vec.end());
    vector<int> vec2(&vec[mid+1], &vec[right+1]);    // notice , cann't use when right+1 reach vec.end(), maybe it has checks. - X
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
    generateVec(data, 1000000, 90000);
    //printVec(data);

    auto t1 = t_now();

    mergeSort(data, 0, data.size() - 1);

    auto t2 = t_now();
    t_cal_echo(t1, t2);


    //printVec(data);
    auto ret = std::is_sorted(data.begin(), data.end());
    checkVecOrder(data);

    return 0;
}