#include "pch.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<int> antiQuickSort(int n) {
	vector<int> a(n);
	a[0] = 1;
	for (int i = 1; i < n; i++) { //начнем с конца, постепенно увеличивая размер массива (до n)
		a[i] = i + 1;
		swap(a[i / 2], a[i]); //на место опорного эл-та ставим максимальный эл-т в массиве, тем самым на каждом шаге сортировки массив k разбивается на подмассивы k-1 и 0
	}
	return a;
}

int main()
{
	ifstream fin;
	fin.open("in.txt");
	ofstream fout;
	fout.open("out.txt");
	int n;
	fin >> n;
	vector<int> a = antiQuickSort(n);
	for (int i = 0; i < n; i++) {
		fout << a[i] << " ";
	}
}