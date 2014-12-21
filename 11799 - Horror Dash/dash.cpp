#include <iostream>

using namespace std;

int main()
{
	int T;
    
    cin >> T;
    
    for (int i = 1; i <= T; i++) {
        int N, speed, maxSpeed;
        maxSpeed = 0;
        cin >> N;
        while (N--) {
            cin >> speed;
            if (speed > maxSpeed) 
                maxSpeed = speed;
        }
        cout << "Case " << i << ": " << maxSpeed << endl;
    }
    
	return 0;
}
