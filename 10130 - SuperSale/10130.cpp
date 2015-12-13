#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	int T; cin >> T;

	while (T--) {
		vector<int> ps, ws, gs;
		int N; cin >> N;

		// slot these in for easy array access; 
		// values themselves won't be used.
		ws.push_back(-1);
		ps.push_back(-1);

		int P, W;
		for (int i = 0; i < N; i++) {
			cin >> P >> W;
			ws.push_back(W);
			ps.push_back(P);
		}

		int G; cin >> G;
		int gt;
		while (G--) {
			cin >> gt;
			gs.push_back(gt);
		}

		sort(gs.begin(), gs.end());

		int MW = gs[gs.size() - 1];

		vector< vector<int> > DP(N + 1, vector<int>(MW + 1, 0));

		for (int i = 1; i <= N; i++) { // i is scope of items in consideration
			for (int j = 1; j <= MW; j++) { // j is max size of bag
				if (ws[i] > j) {
					DP[i][j] = DP[i - 1][j];
				} else {
					DP[i][j] = max(DP[i - 1][j], ps[i] + DP[i - 1][j - ws[i]]);
				}
			}
		}

		int maxPrice = 0;

		for (auto &k : gs) maxPrice += DP[N][k];

		cout << maxPrice << endl;
	}
}
