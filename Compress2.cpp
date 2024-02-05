// C++ program to encode and decode a string using
// Huffman Coding.
#include <bits/stdc++.h>
#include <fstream>
#include <utility>
#include <bitset>
#define MAX_TREE_HT 256
using namespace std;

// to map each character its huffman value
map<char, string> codes;

// To store the frequency of character of the input data
map<char, int> freq;

// A Huffman tree node
struct MinHeapNode {
	char data; // One of the input characters
	int freq; // Frequency of the character
	MinHeapNode *left, *right; // Left and right child

	MinHeapNode(char data, int freq)
	{
		left = right = NULL;
		this->data = data;
		this->freq = freq;
	}
};

// utility function for the priority queue
struct compare {
	bool operator()(MinHeapNode* l, MinHeapNode* r)
	{
		return (l->freq > r->freq);
	}
};

// utility function to print characters along with
// there huffman value
void printCodes(struct MinHeapNode* root, string str)
{
	if (!root)
		return;
	if (root->data != '$')
		cout << root->data << ": " << str << "\n";
	printCodes(root->left, str + "0");
	printCodes(root->right, str + "1");
}

// utility function to store characters along with
// there huffman value in a hash table, here we
// have C++ STL map
void storeCodes(struct MinHeapNode* root, string str)
{
	if (root == NULL)
		return;
	if (root->data != '$')
		codes[root->data] = str;
	storeCodes(root->left, str + "0");
	storeCodes(root->right, str + "1");
}

// STL priority queue to store heap tree, with respect
// to their heap root node value
priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare>
	minHeap;

// function to build the Huffman tree and store it
// in minHeap
void HuffmanCodes(int size)
{
	struct MinHeapNode *left, *right, *top;
	for (map<char, int>::iterator v = freq.begin();
		v != freq.end(); v++)
		minHeap.push(new MinHeapNode(v->first, v->second));
	while (minHeap.size() != 1) {
		left = minHeap.top();
		minHeap.pop();
		right = minHeap.top();
		minHeap.pop();
		top = new MinHeapNode('$',
							left->freq + right->freq);
		top->left = left;
		top->right = right;
		minHeap.push(top);
	}
	storeCodes(minHeap.top(), "");
}

// utility function to store map each character with its
// frequency in input string
void calcFreq(string str, int n)
{
	for (int i = 0; i < str.size(); i++)
		freq[str[i]]++;
}

string BTD(string a)
{
	string result;
	char ch;
	for (size_t i = 0; i < a.length(); i += 8) {
        string eightBit = a.substr(i, 8);
        int decimalValue = bitset<8>(eightBit).to_ulong();
        if(decimalValue==26){
        	decimalValue=128;
		}
        ch=char(decimalValue);
        result+=ch;
        //cout << "Binary: " << sevenBits << "   Decimal: " << decimalValue << std::endl;
    }
    return result;
}

// function iterates through the encoded string s
// if s[i]=='1' then move to node->right
// if s[i]=='0' then move to node->left
// if leaf node append the node->data to our output string


// Driver code
int main()
{
	string str;
	char y;
	ifstream fin;
    fin.open("12mb.txt");
	if(!fin.is_open())
	{
		cout <<"Error !!! Cannot open Source file.\n";
		cin>>y;
		exit(1);
	}
	while(fin.get(y))
	{
		str+=y;
	}
	fin.close();
	
	string encodedString, decodedString;
	calcFreq(str, str.length());
	HuffmanCodes(str.length());
	cout << "Character With there Frequencies:\n";
	
	ofstream MyFile1("codes.txt");
	for (auto v = codes.begin(); v != codes.end(); v++)
	{
		cout << v->first << ' ' << v->second << endl;
		MyFile1 << v->first << ' ' << v->second << endl;
    }
    //cout<<"--------------------------------------------------------------------------------------------------------"<<endl;
    MyFile1.close();
    
	for (auto i : str)
		encodedString += codes[i];
	string help=BTD(encodedString);
		
	//cout << "\nEncoded Huffman data:\n" << encodedString << endl;
	   // Create and open a text file
    ofstream MyFile2("Compress.cmp");

  // Write to the file
    MyFile2 << help;

  // Close the file
    MyFile2.close();
    
	// Function call
	//decodedString
	//	= decode_file(minHeap.top(), encodedString);
	//cout << "\nDecoded Huffman Data:\n"
	//	<< decodedString << endl;
	return 0;
}
