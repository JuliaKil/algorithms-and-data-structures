#include "pch.h"
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct Order {
	vector<int> row;
	vector<int> order;
};

Order countingSort(Order order) {
	int rank = 10;
	vector<int> counter(rank, 0);
	vector<int> rowSorted(order.row.size(), 0);
	vector<int> newOrder(order.order.size(), 0);
	for (int i = 0; i < order.row.size(); i++) 
		counter[order.row[i]]++;
	for (int i = 1; i < rank; i++)
		counter[i] += counter[i - 1];
	for (int i = rank - 1; i > 0; i--)
		counter[i] = counter[i-1];
	counter[0] = 0;
	for (int i = 0; i < order.row.size(); i++) {
		rowSorted[counter[order.row[i]]] = order.row[i];
		newOrder[counter[order.row[i]]] = order.order[i];
		counter[order.row[i]]++;
	}
	Order result;
	result.row = rowSorted;
	result.order = newOrder;
	return result;
}

vector<int> radixSort(vector<vector<int>> numbers, int k) {
	int m = numbers.size() - 1;
	int n = numbers[0].size();
	if (k > m) k = m;
	vector<int> copy(n, 0);
	Order order;
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < n; j++) 
			copy[j] = numbers[m - 1 - i][j];
		for (int j = 0; j < n; j++)
			numbers[m - 1 - i][j] = copy[numbers[m][j]];
		order.row = numbers[m - 1 - i];
		order.order = numbers[m];
		order = countingSort(order);
		for (int j = 0; j < n; j++) {
			numbers[m][j] = order.order[j];
		}
	}
	return numbers[m];
}

int main()
{
	ifstream fin;
	fin.open("in.txt");
	ofstream fout;
	fout.open("out.txt");
	int n, m, k;
	fin >> n >> m >> k;
	vector<vector<int> > numbers(m+1, vector<int>(n));
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
			fin >> numbers[i][j];
	}
	for (int i = 0; i < n; i++) //присваиваем числам порядок 0, 1, 2...
		numbers[m][i] = i;
	vector<int> result = radixSort(numbers, k);
	for (int i = 0; i < n; i++)
		fout << result[i] << " ";
}

