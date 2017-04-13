
#include <vector>
#include <iostream>

using namespace std;

typedef vector<int> IV;

IV master;

void func(IV::iterator start, int depth, int fDepth, IV &vec) {
	if(depth == fDepth)
		return;
	for(auto i = start; start != master.end(); ++i) {
		vec.push_back(*start);
		func(i, depth + 1, fDepth, vec);
	}

}

int main() {
	IV master = {1, 2, 3};
	
	vector<IV> pos;
	
	for(int  i = 0; i < master.size(); ++i) {
		IV one;
		func(master.begin(), 0, i, one);
		pos.push_back(one);
	}
	
	for(IV& tmpIV : pos) {
		cout << "[ ";
		for(int tmpInt : tmpIV) {
			cout << tmpInt << ", ";
		}
		cout << " ]" << endl;
	}
	
	return 0;
}