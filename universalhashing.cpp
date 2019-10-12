#include <bits/stdc++.h>

using namespace std;


class MyHashSet {
public:
    
    MyHashSet() {
    	srand(time(NULL));
    	this->h = vector<list<int> >(mod, list<int>());
    	this->kvec = vector<int>();
    	this->kvec.push_back(rand() % mod);
    	this->kvec.push_back(rand() % mod); 
    }
    
    void add(int key) {
        vector<int> tmp = compute(key);
        long long k = 0;
        k = k + (long long) kvec[0] * (long long) tmp[0] + (long long) kvec[1] * (long long) tmp[1];
        k = k % mod;
        for (auto num : h[k]) {
        	if (num == key) return;
        }
        h[k].push_back(key);
    }
    
    void remove(int key) {
        vector<int> tmp = compute(key);
        long long k = 0;
        k = k + (long long) kvec[0] * (long long) tmp[0] + (long long) kvec[1] * (long long) tmp[1];
        k = k % mod;
        list<int> :: iterator iter = h[k].begin();
        while (iter != h[k].end()) {
        	if (*iter == key) {
        		h[k].erase(iter++);
        		break;
        	}
        	iter++;
        }
    }
    
    /** Returns true if this set contains the specified element */
    bool contains(int key) {
        vector<int> tmp = compute(key);
        long long k = 0;
        k = k + (long long) kvec[0] * (long long) tmp[0] + (long long) kvec[1] * (long long) tmp[1];
        k = k % mod;
        for (auto num : h[k]) {
        	if (num == key) return true;
        }
        
        return false;
    }
    
private:
	int mod = 202403;
	vector<list<int> > h;
	// the <> vector
	vector<int> kvec;
	
	vector<int> compute(int num) {
		vector<int> ret;
		ret.push_back(num / mod);
		num = num / mod;
		ret.push_back(num);
		return ret;
	}
};

int main(int argc, char *argv[]) {
	int i, j, cnt = 0;
	if (argc != 2) {
		cout << "supply the number of testcases as cmdline argument!" << endl;
		return 0;
	}
	int T = atoi(argv[1]);
	for (i = 1 ; i <= T; i++) {
		MyHashSet ms = MyHashSet();
		unordered_set<int> h;
		int n = 20 + rand() % 100000;
		bool flag = true;
		for (j = 1; j <= n; j++) {
			int v = rand() % 1000001;
			int t = rand() % 3;
			if (t == 0) {
				ms.add(v);
				h.insert(v);
			} else if (t == 1) {
				ms.remove(v);
				h.erase(v);
			} else {
				if (ms.contains(v) != (h.find(v) != h.end())) {
					flag = false;
					break;
				}
			}
		}
		
		if (flag) {
			cnt++;
			cout << "pass test case " << i << " (n= " << n << ")" << endl;
		} else {
			cout << "fail test case " << i << " (n= " << n << ")" << " the " << j << " th operation is wrong" << endl;
		}
	}
	
	cout << "pass " << cnt << " fail " << T - cnt << endl;
	return 0;
}
