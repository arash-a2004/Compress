#include <bits/stdc++.h>
#include <fstream>
#include <string>
#include <utility>
#include <bitset>
#include <sstream>

using namespace std;

struct MinHeapNode
{
	char data; 
	MinHeapNode *left, *right;
	MinHeapNode(char data)
	{
		left = right = NULL;
		this->data = data;
	}
};

MinHeapNode *root=new MinHeapNode('*');

string DTB();
void insert();
string decode_file(string s);

int main(){

	insert();
	//cout<<DTB();
	string result = decode_file(DTB());
	ofstream MyFile("Decompress.txt");
    MyFile << result;
    MyFile.close();
	
	return 0;
}

string DTB()
{
	string binaryResult,myText;
	char ch1;
	ifstream MyFile1("Compress.cmp");
	do{
		int a;
		getline(MyFile1,myText);
		for(int i=0;i<myText.length();i++)
		{
			a= int(myText[i]);
			if(a==128)
			    a=26;
		    ostringstream binaryStringStream;
            bitset<8> eightBitsBinary(a);
            binaryStringStream << eightBitsBinary;
            binaryResult += binaryStringStream.str();
		}
	}while(!MyFile1.eof());
	MyFile1.close();
	return binaryResult;
}

void insert()
{
	ifstream MyFile1("codes.txt");
	string str;
	char ch;
	while(getline (MyFile1, str)){
		ch=str[0];
		MinHeapNode	*p = root;
    	for(int i = 2; i < str.length(); i++)
	    {
		    switch (str[i])
		    {
		        case '0' :
				    if (p->left == 0) // create node along path
				    p->left = new MinHeapNode('*');
				    p = p->left;
				    break;
		        case '1' :
				    if (p->right == 0) // create node along path
				    p->right = new MinHeapNode('*');
				    p = p->right;
				    break;
		        default:
			        cerr << "*** Illegal character in code ***\n";
			        exit(1);
		    }
	    }
	    p->data = ch;
	}
	MyFile1.close();
}

string decode_file(string s)
{
	string ans = "";
	struct MinHeapNode* curr = root;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '0')
			curr = curr->left;
		else
			curr = curr->right;

		// reached leaf node
		if (curr->left == NULL and curr->right == NULL) {
			ans += curr->data;
			curr = root;
		}
	}
	// cout<<ans<<endl;
	return ans + '\0';
}

