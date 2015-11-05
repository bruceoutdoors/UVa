#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
#include <functional>

using namespace std;

struct Box
{
	int id;
	vector<int> ds;
};

template<typename T>
deque<T> find_lis(const vector<T> &a,
	function<bool(const T &, const T &)> comp = [&](const T &a, const T &b)->bool { return a < b; })
{
	int maxLength = 1, bestEnd = 0;

	vector<int> DP(a.size(), 1);
	vector<int> prev(a.size(), -1);

	for (int i = 1; i < a.size(); i++) {
		for (int j = i - 1; j >= 0; j--) {
			if (DP[j] + 1 > DP[i] && comp(a[j], a[i])) {
				DP[i] = DP[j] + 1;
				prev[i] = j;
			}
		}

		if (DP[i] > maxLength) {
			bestEnd = i;
			maxLength = DP[i];
		}
	}

	deque<T> lis;
	for (int i = bestEnd; i != -1; i = prev[i]) {
		lis.push_front(a[i]);
	}

	return lis;
}

bool canFit(const Box *a, const Box *b)
{
	for (int i = 0; i < a->ds.size(); i++) {
		if (a->ds[i] >= b->ds[i]) return false;
	}

	return true;
}

int main()
{
	int k, n;

	while (cin >> k >> n) {
		vector<Box*> boxes;
		int c, m, p;

		c = 1;
		p = k;

		/** add and sort boxes **/
		while (p--) {
			Box *b = new Box();
			boxes.push_back(b);

			b->id = c++;
			for (int i = 0; i < n; i++) {
				cin >> m;
				b->ds.push_back(m);
			}

			sort(b->ds.begin(), b->ds.end());
		}

		sort(boxes.begin(), boxes.end(), [](Box *a, Box *b)->bool { return a->ds < b->ds; });

		auto comp = [&](const Box *a, const Box *b)->bool { return canFit(a, b); };
		auto lis = find_lis<Box*>(boxes, comp);

		cout << lis.size() << endl;
		for (auto b : lis) cout << b->id << " ";
		cout << endl;

		for (auto b : boxes) {
			//cout << b->id << ": ";
			//for (auto &r : b->ds) cout << r << " ";
			//cout << endl;
			delete b;
		}
	}
}
