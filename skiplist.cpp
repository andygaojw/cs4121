#include <bits/stdc++.h>
#define INVALID -1048576

using namespace std;

class Skiplist {
public:
    Skiplist() {
		this->head = NULL;        
    	this->level = 0;
    	srand(time(NULL));
    }
    
    bool search(int target) {
        if (this->head == NULL) return false;
        node *curr = this->head;
        while (curr != NULL) {
        	while (curr->next != NULL && curr->next->val < target) {
        		curr = curr->next;
        	}
        	
        	if (curr->next != NULL && curr->next->val == target) return true;
        	curr = curr->down;
        }
        
        return false;
    }
    
    void add(int num) {
        node *curr = this->head;
        vector<node *> parent(this->level, NULL);
        int i;
        for (i = this->level - 1; i >= 0; i--) {
        	while (curr->next != NULL && curr->next->val < num) {
        		curr = curr->next;
        	}
        	
        	parent[i] = curr;
        	curr = curr->down;
        }
        
        for (i = 0 ; i <= (int) parent.size(); i++) {
        	curr = new node(num);
            if (i == (int) parent.size()) {
            	node* last = head;
                this->head = new node();
                this->head->down = last;
                this->head->next = curr;
                curr->pre = this->head;
                this->level++;
            } else {
                curr->next = parent[i]->next;
                curr->pre = parent[i];
                parent[i]->next = curr;
                if (curr->next) curr->next->pre = curr;
            }
            
            if (i != 0) {
                curr->down = parent[i - 1]->next;
            }
            
            if (rand() % 2 == 1) {
                break;
            }
        }
    }
    
    bool erase(int num) {
        node *curr = this->head;
        int i;
        for (i = this->level - 1; i >= 0; i--) {
        	while (curr->next != NULL && curr->next->val < num) {
        		curr = curr->next;
        	}
        	
        	if (curr->next != NULL && curr->next->val == num) {
                curr = curr->next;
                while (curr != NULL) {
                	curr->pre->next = curr->next;
                    if (curr->next != NULL) curr->next->pre = curr->pre;
                    curr = curr->down;
                }
				
				while(this->head != NULL && this->head->next == NULL) {
                    head = head->down;
                    this->level--;
                }
                
                return true;
            } else {
                curr = curr->down;
                if (curr == NULL) {
                	return false;
               	}
            }
        }
        
        return false;
    }

private:
	struct node {
		struct node *next, *pre, *down;
		int val;
		node(int val = INVALID) {
			this->val = val;
			this->next = this->pre = this->down = NULL;
		}
	};
	
	// head is pointing to the leftmost top level node
	node *head;
	int level;
};

int main(int argc, char *argv[]) {
	if (argc != 2) {
		cout << "please provide a cmdline argument indicate the number of testcases" << endl;
		return 0;
	}
	int T = atoi(argv[1]);
	int i, n, j, cnt = 0;
	for (i = 1; i <= T; i++) {
		n = 100000;
		Skiplist sl = Skiplist();
		multiset<int> s;
		int v = -500 + rand() % 1000;
		bool flag = true;
		for (j = 1; j <= n; j++) {
			int t = rand() % 3;
			if (t == 0) {
				if (sl.search(v) != (s.find(v) != s.end())) {
					flag = false;
					break;
				}
			} else if (t == 1) {
				s.insert(v);
				sl.add(v);
			} else {
				multiset<int> :: iterator iter = s.find(v);
				if (iter != s.end()) {
					s.erase(iter);
				}
				sl.erase(v);
			}		
		}
		
		if (!flag) {
			cout << "fail testcase " << i << endl;
		} else {
			cnt++;
			cout << "pass testcase " << i << endl;
		}
	}
	
	cout << "pass " << cnt << ", fail " << T - cnt << endl;
	return 0;
}
