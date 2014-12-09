#include <iostream>

using namespace std;

int getCycleLen(int n) 
{
	int len = 1;
	while (n != 1) {
		//~ cout << n << " ";
		n % 2 != 0 ? n = 3*n + 1 : n = n/2; 
		len++;
	};
	//~ cout << n;
	return len;
}

int main()
{
	int n1, n2, maxCycle;
	while (cin >> n1 >> n2) {
		cout << n1 << " " << n2 << " ";
		if(n1 > n2) swap(n1, n2);
		
		maxCycle = 0;
		
		for (int i = n1; i <= n2; i++) {
			int cycle = getCycleLen(i);
			//~ cout << i << ": " << cycle << endl;
			if (cycle > maxCycle) maxCycle = cycle;
		}
		
		cout << maxCycle << endl;
	}
	
	return 0;
}


