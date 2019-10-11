#include <bits/stdc++.h>
#define INVALID -1048576
using namespace std;

/*
	algorithm description:
	basic idea: 
	findkth(arr, start, end, k) means find the kth largest element in arr[start, end]
	1. choose a random element v from the range [start, end]
	2. call the pivot function and put all the elements less than v on LHS, 
	   and all the elements greater than v on RHS, for elements equal to v
	   simply select L or R randomly, return the order p which v belongs
	3. if p == k simply return v
	4. if p > k return findkth(arr, start, start + p - 2, k)
	5. if p < k return findkth(arr, start + p, end, k - p)
	
*/


int pivot(vector<int> &arr, int low, int high, int val) {
	vector<int> L = vector<int>();
	vector<int> R = vector<int>();
	vector<int> eq = vector<int>();
	int i;
	for (i = low ; i <= high; i++) {
		if (arr[i] < val) {
			L.push_back(arr[i]);
		} else if (arr[i] > val) {
			R.push_back(arr[i]);
		} else {
			eq.push_back(arr[i]);
		}
	}
	
	i = low;
	for (auto num : L) {
		arr[i++] = num;
	}
	
	i = high;
	
	for (auto num : R) {
		arr[i--] = num;
	}
	
	i = low + (int) L.size();
	for (auto num : eq) {
		arr[i++] = num;
	}
	
	int Lindex = low + (int) L.size();
	int Rindex = low + (int) L.size() + (int) eq.size() - 1;
	int ret =  (Rindex - Lindex) / 2  + (int) L.size() + 1;
	return ret;
}

int findkth(vector<int> &arr, int start, int end, int k) {
	if (start > end) return INVALID;
	int index = start + rand() % (end - start + 1);
	int v = arr[index];
	int p = pivot(arr, start, end, v);
	if (p == k) {
		return v;
	}
	
	if (p > k) return findkth(arr, start, start + p - 2, k);
	return findkth(arr, start + p, end, k - p);
}

// return the kth largest number of the array
int randselect(vector<int> &arr, int k) {
	if (k > (int) arr.size() || k <= 0) return INVALID;
	return findkth(arr, 0, (int) arr.size() - 1, k);
}

// the judging program
int jury(vector<int> &arr, int k) {
	if (k > (int) arr.size() || k <= 0) return INVALID;
	sort(arr.begin(), arr.end());
	return arr[k-1];
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		cout << "supply a command line argument indicates the number of test cases!" << endl;
		return 0;
	}
	int i, n, j, k, cnt = 0, T = atoi(argv[1]);
	srand(time(NULL));
	cout << "-------------cases with few duplicates-------------" << endl;
	for (i = 1; i <= T / 2; i++) {
		n = 10 + rand() % 100000;
		k = rand() % n;
		vector<int> a = vector<int>();
		vector<int> b = vector<int>();
		vector<int> ipt = vector<int>();
		for (j = 0 ; j < n; j++) {
			int v = rand() % 10000;
			a.push_back(v);
			b.push_back(v);
			ipt.push_back(v);
		}
		
		int v1 = randselect(a, k);
		int v2 = jury(b, k);
		if (v1 == v2) {
			cout << "pass test case " << i << endl;
			cnt++;
		} else {
			cout << "fail test case " << i << " expected " << v2 << " get " << v1 << endl;
			cout << "input: " << endl;
			cout << n << " " << k << endl;
			for (j = 0 ; j < n; j++) {
				cout << ipt[j] << " ";
			}
			cout << endl;
		}
	}
	cout << "-------------cases with many duplicates-------------" << endl;
	for (i = T / 2 + 1; i <= T; i++) {
		n = 10 + rand() % 100000;
		k = rand() % n;
		vector<int> a = vector<int>();
		vector<int> b = vector<int>();
		vector<int> ipt = vector<int>();
		for (j = 0 ; j < n; j++) {
			int v = rand() % 100;
			a.push_back(v);
			b.push_back(v);
			ipt.push_back(v);
		}
		
		int v1 = randselect(a, k);
		int v2 = jury(b, k);
		if (v1 == v2) {
			cout << "pass test case " << i << endl;
			cnt++;
		} else {
			cout << "fail test case " << i << " expected " << v2 << " get " << v1 << endl;
			cout << "input: " << endl;
			cout << n << " " << k << endl;
			for (j = 0 ; j < n; j++) {
				cout << ipt[j] << " ";
			}
			cout << endl;
		}
	}
	
	cout << "pass " << cnt << ", " << "fail " << T - cnt << endl;
	return 0;
}
