#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>

using namespace std;

// tda -> descent + ascent time, 3(w * d_i)
vector<int> v, d, tda;
deque<int> selected; // used as stack
vector< vector<int> > DP;

void pick(int i, int j)
{
	if (i <= 0 || j <= 0) return;

	int k = DP[i][j];
	if (k != DP[i - 1][j]) {
		selected.push_front(i);
		// item is selected, capacity decreases
		pick(i - 1, j - tda[i]);
	} else {
		// move on to next item; capacity no change
		pick(i - 1, j);
	}
}

int main()
{
	bool isFirst = true;
	int t, w, n; 
	while (cin >> t >> w >> n) {
		if (isFirst) {
			isFirst = false;
		} else cout << endl; // separate datasets by blank line

		/*
		* because descent + ascent time is a multiple of 3,
		* we optimize the algorithm such that it evaluates
		* depth times in multiples of 3, thereby cutting the
		* space and run time by 1/3.
		*/
		t = t / 3;

		// slot these in for easy array access; 
		// values themselves won't be used.
		d.push_back(-1);
		v.push_back(-1);
		tda.push_back(-1);

		int dt, vt;
		for (int i = 0; i < n; i++) {
			cin >> dt >> vt;
			d.push_back(dt);
			v.push_back(vt);
			tda.push_back(w * dt);
		}

		DP.resize(n + 1, vector<int>(t + 1, 0));

		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= t; j++) {
				if (tda[i] > j) {
					DP[i][j] = DP[i - 1][j];
				} else {
					DP[i][j] = max(DP[i - 1][j], v[i] + DP[i - 1][j - tda[i]]);
				}
			}
		}

		cout << DP[n][t] << endl;
		pick(n, t);
		cout << selected.size() << endl;
		for (auto &s : selected) cout << d[s] << " " << v[s] << endl;

		// cleanup for next input:
		DP.clear();
		v.clear(); 
		d.clear();
		tda.clear();
		selected.clear();
	}
}
