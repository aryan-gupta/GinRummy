
#include <vector>
#include <iostream>

using namespace std;

typedef vector<int> IV;

IV master;

void func(int start, int depth, int fDepth, IV vec, vector<IV> &pos) {
	cout << depth << start << endl;
	if(depth == fDepth) {
		pos.push_back(vec);
		return;
	}
	
	vec.push_back(master[start]);
	for(; start < master.size(); ++start) {
		func(start + 1, depth + 1, fDepth, vec, pos);
	}

}

int main() {
	master = {1, 2, 3, 4};
	
	vector<IV> pos(master.size());
	
	//for(int  i = 0; i < master.size(); ++i) {
		IV one;
		func(0, 0, 2, one, pos);
		
	//}
	
	for(IV& tmpIV : pos) {
		for(int tmpInt : tmpIV) {
			cout << tmpInt << " ";
		}
		cout << endl;
	}
	
	return 0;
}