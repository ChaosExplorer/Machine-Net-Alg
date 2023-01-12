#include "ctimer.h"


// merge
void merge(vector<int>& vec, int p, int m, int q) {
    vector<int> ret(q-p+1, 0);
    //ret.reserve(q-p+1); // notice , it's wrong if u use ret[i] soon. use push_back

    int i = p, j = m+1, t = 0;  // notice, i , j do not start at 0
    while (i <= m && j <= q) {      // notice not length, it's offset
        if (vec[i] <= vec[j]) {
            ret[t] = vec[i];
            ++i;
        }
        else {
            ret[t] = vec[j];
            ++j;
        }

        ++t;
    }
    
    // conjunction with these left
    int tail = i, end = m;
    if (i > end) { tail = j; end = q; }

    while (tail <= end) {
        ret[t] = vec[tail];
        ++t;
        ++tail;
    }

    // move
    --t;  // notice err, t already > end
    for (; t >= 0; --t) {
        vec[q] = ret[t];    // notice , not vec[t] !
        --q;
    }
}

// sort

void mergeSort (vector<int>& vec, uint left, uint right) {
    if (right <= left)  return;

    int mid = left + (right - left) / 2;    // notice : left +

    // merge(vec) = merge(merge(leftvec), merge(rightvec))
    mergeSort(vec, left, mid);
    mergeSort(vec, mid+1, right);

    merge(vec, left, mid, right);
}



int main() {
    vector<int> data;
    generateVec(data, 20, 1000);

    auto t1 = t_now();
    //mergeSort(data, 0, data.size() - 1);
    auto t2 = t_now();
    t_cal_echo(t1, t2);

    checkVecOrder(data);

    return 0;
}