#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

int sequentialSearch(const vector<int>& arr, int target) {
	int comparisons = 0;
	for (int i = 0; i < arr.size(); ++i) {
		comparisons++;
		cout << "Comparing " << arr[i] << " with " << target << endl;
		if (arr[i] == target) {
			return comparisons;
		}
	}
	return comparisons; 
}

int binarySearch(const vector<int>& arr, int target) {
	int left = 0, right = arr.size() - 1;
	int comparisons = 0;
	while (left <= right) {
		comparisons++;
		int mid = left + (right - left) / 2;
		cout << "Comparing " << arr[mid] << " with " << target << endl;
		if (arr[mid] == target) {
			return comparisons;
		} else if (arr[mid] < target) {
			left = mid + 1;
		} else {
			right = mid - 1;
		}
	}
	return comparisons; 
}

int hashTableSearch(const unordered_map<int, int>& hashTable, int target) {
	int comparisons = 0;
	cout << "检查哈希表中是否存在: " << target << endl;
	if (hashTable.find(target) != hashTable.end()) {
		comparisons++;
		return comparisons; 
	}
	return comparisons; 
}

int main() {
	vector<int> arr = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21};
	int target;
	
	cout << "输入1组有序数据: ";
	cin >> target;
	
	cout << "\n顺序搜索:" << endl;
	int seqComparisons = sequentialSearch(arr, target);
	cout << "顺序查找中的总比较次数: " << seqComparisons << endl;
	
	cout << "\n二分查找:" << endl;
	int binComparisons = binarySearch(arr, target);
	cout << "二分查找中的总比较次数: " << binComparisons << endl;
	
	unordered_map<int, int> hashTable;
	for (int i = 0; i < arr.size(); ++i) {
		hashTable[arr[i]] = i; 
	}
	
	cout << "\n哈希表查找:" << endl;
	int hashComparisons = hashTableSearch(hashTable, target);
	cout << "哈希表搜索中的总比较次数: " << hashComparisons << endl;
	
	cout << "\n时间复杂度分析：" << endl;
	cout << "顺序搜索：O(n)" << endl;
	cout << "二分查找：O(log n)" << endl;
	cout << "哈希表查找：平均情况下为 O(1)，但在有很多冲突的情况下最坏情况下为 O(n)" << endl;
	
	return 0;
}
