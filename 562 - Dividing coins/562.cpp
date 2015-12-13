#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// a variation of the 1-0 knapsack problem,
// where the weights and values of the items are equal,
// and the capacity of the knapsack is (sum of values)/2

int main()
{
	int n; cin >> n;
	while (n--) {
		vector<int> values;
		vector< vector<int> > P;
		int m; cin >> m;

		// slot in for easy array access; value won't be used.
		values.push_back(-1);

		int val, sum = 0;

		for (int i = 0; i < m; i++) {
			cin >> val;
			sum += val;
			values.push_back(val);
		}

		int maxCap = sum / 2;
		P.resize(m + 1, vector<int>(maxCap + 1, 0));

		for (int i = 1; i <= m; i++) { // i is scope of items in consideration
			for (int j = 1; j <= maxCap; j++) { // j is max size of bag
				if (values[i] > j) {
					P[i][j] = P[i - 1][j];
				} else {
					P[i][j] = max(P[i - 1][j], values[i] + P[i - 1][j - values[i]]);
				}
			}
		}

		// if it is divided equally, P[N][maxCap] * 2 == sum
		cout << sum - P[m][maxCap] * 2 << endl;
	}
}
