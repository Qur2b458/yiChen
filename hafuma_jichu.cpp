#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

struct HuffmanNode {
	char ch;          
	int freq;          
	HuffmanNode* left; 
	HuffmanNode* right;
	
	HuffmanNode(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
	HuffmanNode(int f) : ch('\0'), freq(f), left(nullptr), right(nullptr) {}
};

struct Compare {
	bool operator()(HuffmanNode* a, HuffmanNode* b) {
		return a->freq > b->freq; 
	}
};

class HuffmanCoding {
private:
	HuffmanNode* root;
	unordered_map<char, string> huffmanCodes;
	
	void buildCodes(HuffmanNode* node, string code) {
		if (!node) return;
		
		if (!node->left && !node->right) {
			huffmanCodes[node->ch] = code;
			return;
		}
		
		buildCodes(node->left, code + "0");
		buildCodes(node->right, code + "1");
	}
	
	void deleteTree(HuffmanNode* node) {
		if (!node) return;
		deleteTree(node->left);
		deleteTree(node->right);
		delete node;
	}
	
public:
	HuffmanCoding() : root(nullptr) {}
	
	~HuffmanCoding() {
		deleteTree(root);
	}
	
	void buildHuffmanTree(const unordered_map<char, int>& freqMap) {
		priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> minHeap;
		
		for (const auto& pair : freqMap) {
			minHeap.push(new HuffmanNode(pair.first, pair.second));
		}
		
		while (minHeap.size() > 1) {
			HuffmanNode* left = minHeap.top(); minHeap.pop();
			HuffmanNode* right = minHeap.top(); minHeap.pop();
			
			HuffmanNode* newNode = new HuffmanNode(left->freq + right->freq);
			newNode->left = left;
			newNode->right = right; 
			
			minHeap.push(newNode);
		}
		
		if (!minHeap.empty()) {
			root = minHeap.top();
		}
		
		huffmanCodes.clear();
		if (root) {
			buildCodes(root, "");
		}
	}
	
	string getCode(char ch) {
		return huffmanCodes.count(ch) ? huffmanCodes[ch] : "";
	}
	
	const unordered_map<char, string>& getAllCodes() {
		return huffmanCodes;
	}
	
	void displayCodes() {
		cout << "哈夫曼编码表:" << endl;
		for (const auto& pair : huffmanCodes) {
			if (pair.first == ' ') {
				cout << "空格: " << pair.second << endl;
			} else if (pair.first == '\n') {
				cout << "换行: " << pair.second << endl;
			} else {
				cout << pair.first << ": " << pair.second << endl;
			}
		}
	}
	
	string encode(const string& text) {
		string encoded = "";
		for (char ch : text) {
			encoded += getCode(ch);
		}
		return encoded;
	}
	
	string decode(const string& encodedStr) {
		string decoded = "";
		HuffmanNode* current = root;
		
		for (char bit : encodedStr) {
			if (bit == '0') {
				current = current->left;
			} else {
				current = current->right;
			}
			
			if (!current->left && !current->right) {
				decoded += current->ch;
				current = root; 
			}
		}
		
		return decoded;
	}
	
	double calculateCompressionRatio(const string& original) {
		if (original.empty()) return 0.0;
		
		int originalBits = original.length() * 8; 
		string encoded = encode(original);
		int encodedBits = encoded.length();      
		
		return (1.0 - (double)encodedBits / originalBits) * 100.0;
	}
};

unordered_map<char, int> calculateFrequency(const string& text) {
	unordered_map<char, int> freqMap;
	for (char ch : text) {
		freqMap[ch]++;
	}
	return freqMap;
}

int main() {
	HuffmanCoding huffman;
	string text;
	
	cout << "=== 哈夫曼编码系统 ===" << endl;
	cout << "请输入要编码的文本: ";
	getline(cin, text);
	
	if (text.empty()) {
		cout << "输入为空!" << endl;
		return 1;
	}
	
	unordered_map<char, int> freqMap = calculateFrequency(text);
	
	huffman.buildHuffmanTree(freqMap);
	
	huffman.displayCodes();
	
	string encoded = huffman.encode(text);
	cout << "\n编码结果: " << encoded << endl;
	
	string decoded = huffman.decode(encoded);
	cout << "解码结果: " << decoded << endl;
	
	return 0;
}
