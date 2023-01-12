#include <memory>
#include <iostream>
#include <unordered_map>

class LRUCache {
private:
    std::unique_ptr<int[]> _arr;  // [int,int,int,int], [key, value, pre, next]
    unsigned short _n, _capacity, _head, _tail;
    std::unordered_map<int,unsigned short> _record; // <key, offset>

public:
    LRUCache(int capacity): _arr(std::make_unique<int[]>(capacity*4))
        , _capacity(capacity), _n(0), _head(0), _tail(0) 
    {
        //_record.reserve(capacity);
    }
    
    int get(int key) {
        auto it = _record.find(key);
        if (it == _record.end())    return -1;

        // move to head
        if (it->second != _head) {
            auto next_offset = _arr[it->second +3];
            auto pre_offset = _arr[it->second +2];

            _arr[pre_offset +3] = next_offset;  // pre->next = it->next
            if (_tail != it->second)    _arr[next_offset +2] = pre_offset;  // !notice next->pre = it->pre
            _arr[it->second +3] = _head;        // it->next = old head
            _arr[it->second +2] = -1;
            _arr[_head + 2] = it->second;       // old head->pre = it
            _head = it->second;

            // update tail
            if (_tail == it->second)    {
                _tail = pre_offset;
                _arr[_tail + 3] = -1;
            }

            //_record[key] = _head;
        }

        // return value
        return _arr[_head+1];
    }
    
    void put(int key, int value) {
        // exist
        if (get(key) != -1) {
            _arr[_head+1] = value;
            return;
        }

        unsigned short id;
        if (_n >= _capacity) {
            // move LRU unit
            id = _tail;
            _record.erase(_arr[_tail]); // remove key

            _tail = _arr[_tail + 2];
            _arr[_tail+3] = -1;     // pre->next = null
        }
        else {
            ++_n;
            // insert
            id = 4*(_n-1);
        }

        // become head
        _arr[id] = key;
        _arr[id+1] = value;
        _arr[id+2] = -1;
        _arr[id+3] = _head;
        _arr[_head+2] = id;  // old head ->pre = id
        _head = id;

        // update key hash
        _record[key] = id;
    }
};

int main() {
    LRUCache u(3);
    u.put(1, 1);
    u.put(2, 2);
    u.put(3, 3);
    u.put(4, 4);

    int ret;

    ret = u.get(4);
    ret = u.get(3);
    ret = u.get(2);
    ret = u.get(1);

    u.put(5, 5);

    ret = u.get(1);
    ret = u.get(2);
    ret = u.get(3);
    ret = u.get(4);
    ret = u.get(5);

    return 0;
}

// ["LRUCache","put","put","put","put","get","get","get","get","put","get","get","get","get","get"]
//  [[3],[1,1],[2,2],[3,3],[4,4],[4],[3],[2],[1],[5,5],[1],[2],[3],[4],[5]]
// [null,null,null,null,null,4,3,2,-1,null,-1,2,3,-1,5]
/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */