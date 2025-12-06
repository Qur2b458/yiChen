#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

void printArray(const vector<int>& a) {
	for (int x : a) cout << x << " ";
	cout << endl;
}


int insertionSort(vector<int> a) {
	cout << "\n===== 直接插入排序 =====\n";
	int n = a.size();
	int cmp = 0;
	
	for (int i = 1; i < n; i++) {
		int temp = a[i];
		int j = i - 1;
		
		while (j >= 0) {
			cmp++;
			if (a[j] > temp)
				a[j + 1] = a[j], j--;
			else
				break;
		}
		a[j + 1] = temp;
		
		cout << "第 " << i << " 趟: ";
		printArray(a);
	}
	cout << "比较次数 = " << cmp << endl;
	return cmp;
}


int bubbleSort(vector<int> a) {
	cout << "\n===== 冒泡排序 =====\n";
	int n = a.size();
	int cmp = 0;
	
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - 1 - i; j++) {
			cmp++;
			if (a[j] > a[j + 1]) swap(a[j], a[j + 1]);
		}
		cout << "第 " << i + 1 << " 趟: ";
		printArray(a);
	}
	cout << "比较次数 = " << cmp << endl;
	return cmp;
}


int quickCmp = 0;

void quickSort(vector<int>& a, int low, int high, int depth) {
	if (low >= high) return;
	
	int i = low, j = high;
	int pivot = a[(low + high) / 2];
	
	while (i <= j) {
		while (a[i] < pivot) i++, quickCmp++;
		while (a[j] > pivot) j--, quickCmp++;
		if (i <= j) {
			swap(a[i], a[j]);
			i++; j--;
		}
	}
	
	cout << "分区结果(深度" << depth << "): ";
	printArray(a);
	
	if (low < j) quickSort(a, low, j, depth + 1);
	if (i < high) quickSort(a, i, high, depth + 1);
}

int quickSortStart(vector<int> a) {
	cout << "\n===== 快速排序 =====\n";
	quickCmp = 0;
	quickSort(a, 0, a.size() - 1, 1);
	cout << "比较次数 = " << quickCmp << endl;
	return quickCmp;
}


int selectionSort(vector<int> a) {
	cout << "\n===== 简单选择排序 =====\n";
	int n = a.size();
	int cmp = 0;
	
	for (int i = 0; i < n - 1; i++) {
		int minIndex = i;
		for (int j = i + 1; j < n; j++) {
			cmp++;
			if (a[j] < a[minIndex]) minIndex = j;
		}
		swap(a[i], a[minIndex]);
		
		cout << "第 " << i + 1 << " 趟: ";
		printArray(a);
	}
	cout << "比较次数 = " << cmp << endl;
	return cmp;
}


int main() {
	vector<int> a(10);
	cout << "请输入 10 个正整数：\n";
	for (int i = 0; i < 10; i++) cin >> a[i];
	
	insertionSort(a);
	bubbleSort(a);
	quickSortStart(a);
	selectionSort(a);
	
	return 0;
}
