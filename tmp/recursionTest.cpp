
#include <vector>
#include <iostream>

using namespace std;

typedef vector<int> IV;
IV master; // master list of vector

void func(int start, int depth, const int &fDepth, IV vec, vector<IV> &pos) {
	vec.push_back(master[start]); // store the current node in vector
	
	if(depth == fDepth) {   // if we are at the depth we need to go to then ...
		pos.push_back(vec); // ... add the accumulated nodes ...
		return;             // ... and exit
	}
	
	for(int i = start + 1; i < master.size(); ++i) // for each node below us ...
		func(i, depth + 1, fDepth, vec, pos); // ... spawn a func
	
	// if we reached an end node then exit
}

int main() {
	master = {1, 2, 3, 4, 5};
	
	vector<IV> pos; // stores all the combinations of master vector
	
	IV vec; // stores the accumulated nodes
	for(int maxDepth = 0; maxDepth < master.size(); ++maxDepth)
		for(int start = 0; start < master.size(); ++start)
			func(start, 0, maxDepth, vec, pos);
		
	// output all the combinations of master
	for(IV& tmpIV : pos) {
		for(int tmpInt : tmpIV)
			cout << tmpInt << " ";
		cout << endl;
	}
	
	return 0;
}