//https://practice.geeksforgeeks.org/problems/transitive-closure-of-a-graph/0


#include <iostream>
#include <vector>
#include <queue>



using namespace std;


void transitive_closure(vector<vector<int>> &matrix) {

	for(int i = 0;i < matrix.size();i++) {
		for(int j = 0;j < matrix.size();j++) {
			for(int k = 0;k < matrix.size();k++) {

				//if(i == j && )

				int through = matrix[i][k] + matrix[k][j];

				if(through < matrix[i][j]) {
					matrix[i][j] = through;
				}

			}
		}
	}
 
	/*for(int i = 0;i < matrix.size();i++) {
		for(int j = 0;j < matrix.size();j++) {
			cout << " " << matrix[i][j];
		}
	}
	cout << endl;*/

	for(int i = 0;i < matrix.size();i++) {
		for(int j = 0;j < matrix.size();j++) {
			if(i == matrix.size() - 1 && j == matrix.size()-1) {
				if(matrix[i][j] >= 1e9) {
					cout << "0" << endl;
				} else {
					//cout << matrix[i][j] << endl;
					cout << "1" << endl;
				}

			} else {
				if(matrix[i][j] >= 1e9) {
					cout << "0 ";
				} else {
					//cout << matrix[i][j] << " ";
					cout << "1 ";
				}
			}
		}
	}


}


int main() {
	//code
	int T;
	cin >> T;

	vector<vector<int>> matrix;
			
	//cout << "T :" << T << endl;
	while(T--) {
		int matrix_size;
		cin >> matrix_size;
		cout << "matrix_size : " << matrix_size << endl;
		matrix = vector<vector<int>>(matrix_size, vector<int>(matrix_size, 0));

		for(int i = 0;i < matrix_size;i++) {
			for(int j = 0;j < matrix_size;j++) {

				cin >> matrix[i][j];
				if(matrix[i][j] == 0) {
					matrix[i][j] = 1e9;
				}
				
				// workaround 
				// 看了下面的討論區，要預設自己能到的了自己(but...why ?)
				//   我大概懂了， transitive closure 主要目的就是想知道 i 能不能到 j 。 而 i == j 的話，就必定能到的了(原本就在那一點了)
				if(i == j) {
					matrix[i][j] = 1;
				}
				//cout << matrix[i][j] << endl;
			}
		}
		cout << endl;

		transitive_closure(matrix);
	}	
	
	return 0;
}


