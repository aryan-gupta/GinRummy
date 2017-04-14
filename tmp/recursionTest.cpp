
#include <vector>
#include <iostream>

using namespace std;

typedef vector<int> IV;

IV master;

void func(int start, int depth, const int &fDepth, IV vec, vector<IV> &pos) {
	vec.push_back(master[start]);
	
	if(depth == fDepth) {
		pos.push_back(vec);
		return;
	}
	
	for(int i = start + 1; i < master.size(); ++i) {
		func(i, depth + 1, fDepth, vec, pos);
	}
}

int main() {
	master = {1, 2, 3, 4};
	
	vector<IV> pos;
	
	IV vec;
	for(int maxDepth = 0; maxDepth < master.size(); ++maxDepth)
		for(int start = 0; start < master.size(); ++start)
			func(start, 0, maxDepth, vec, pos);
		
	
	for(IV& tmpIV : pos) {
		for(int tmpInt : tmpIV) {
			cout << tmpInt << " ";
		}
		cout << endl;
	}
	
	return 0;
}