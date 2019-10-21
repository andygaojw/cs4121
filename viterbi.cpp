#include <bits/stdc++.h>
#define MAX_SIZE 111
using namespace std;

double pp[MAX_SIZE];
double dp[MAX_SIZE][MAX_SIZE];
double emission[MAX_SIZE][MAX_SIZE];
double transition[MAX_SIZE][MAX_SIZE];
int observe[MAX_SIZE];
int rec[MAX_SIZE][MAX_SIZE];

int main() {
	int n, k;
	// n states and k observations
	scanf("%d%d", &n, &k);
	int i, j;
	// observasion sequence
	for (i = 1; i <= k; i++) {
		scanf("%d", &observe[i]);
	}
	
	// state initial probability
	for (i = 1; i <= n; i++) {
		scanf("%lf", &pp[i]);
	}
	
	// emission probability
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++) {
			scanf("%lf", &emission[i][j]);
		}
	}
	
	// transition probability
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++) {
			scanf("%lf", &transition[i][j]);
		}
	}
	
	for (i = 1; i <= n; i++) {
		dp[1][i] = pp[i] * emission[observe[1]][i];
	}
	
	double ans = 0.0;
	int index = 0;
	for (i = 2; i <= k; i++) {
		for (j = 1; j <= n; j++) {
			for (int t = 1; t <= n; t++) {
				if (dp[i][j] < dp[i-1][t] * transition[t][j] * emission[observe[i]][j]) {
					dp[i][j] = dp[i-1][t] * transition[t][j] * emission[observe[i]][j];
					rec[i][j] = t;
				} 
			}
			
			if (i == k && ans < dp[i][j]) {
				ans = dp[i][j];
				index = j;
			}
		}
	}
	
	cout << ans << endl;
	vector<int> ret;
	ret.push_back(index);
	index = rec[k][index];
	for (i = k - 1; i >= 1; i--) {
		ret.push_back(index);
		index = rec[i][index];
	}
	
	reverse(ret.begin(), ret.end());
	for (i = 0; i < (int) ret.size(); i++) {
		cout << ret[i] << " ";
	}
	cout << endl;
	return 0;
}
