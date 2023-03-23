#include <iostream>
#include <string>
#include "Templated_AVL.h"
#include "WordItem.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cctype>
#include <map>

using namespace std;

//Map printing function, was used to debug while writing the code.
//Doesn't have any use in release mode.
template <class KTy, class Ty>
void PrintMap(map<KTy, Ty> map)
{
    typedef std::map<KTy, Ty>::iterator iterator;
    for (iterator p = map.begin(); p != map.end(); p++)
        cout << p->first << ": " << p->second << endl;
}

//Function to remove punctiations from a string and make all its characters lowercase. 

void lowerAndRemovePunc(string & line)
{

	std::size_t l=line.size();
	
	//Iterate over all characters and change punctuations with space.
	for (std::size_t i=0; i<l; i++)
	{
		if (std::ispunct(line[i]))
		{
			line[i] = ' ';
		}
	}

	//Make it lowercase.
	std::transform(line.begin(), line.end(), line.begin(), std::tolower);
}


int main()
{
	
	int numInputFiles;
	
	cout << "Enter number of input files: ";
	cin >> numInputFiles;

	//To store our filenames
	vector<string> fileList;

	//ItemNotFound for AVL tree.
	WordItem itemNotFound;
	AvlTree<WordItem> infoTree(itemNotFound);

	for (int i = 1; i <= numInputFiles; i++)
	{
		map<string, unsigned int> wordsCount;
		string fileName;
		string line;
		
		cout << "Enter " << i << ". file name: ";
		cin >> fileName;

		ifstream myFile(fileName);
		
		if(myFile.is_open())
		{
			fileList.push_back(fileName);
			while(getline(myFile,line))
			{
				lowerAndRemovePunc(line);
				istringstream iss(line);
				string word;

				//Iterate over words one by one
				while(iss >> word)
				{
					//If it is a digit, then don't include.
					if (word <= "9" && word >="1" && word.size() == 1) {}

					//Else add it to map.
					else
					{
						if(wordsCount.find(word) == wordsCount.end())
							wordsCount[word] = 1;
						else
							wordsCount[word]++;
					}
				}
			}
			//PrintMap(wordsCount);
		
		}
		myFile.clear();
		myFile.seekg(0);
		myFile.close();

		//Iterate over map keys. Create WordItem object from key and value, then add the info to tree.
		for(map<string, unsigned int>::iterator it = wordsCount.begin(); it != wordsCount.end(); ++it) 
		{
			DocumentItem newDoc;
			newDoc.documentName = fileName;
			newDoc.count = it->second;
			WordItem newInfo = WordItem(it->first, newDoc);
			WordItem boolVar = infoTree.find(newInfo);

			//If key is not in tree, insert it to tree.
			 if( boolVar == itemNotFound)
			 {
				infoTree.insert(newInfo);
			 }
			//If key is in tree, just push the document info.
			else
			 {
				 WordItem * currNode = &infoTree.find(newInfo);
				 currNode->addToList(newDoc);
			 }

		}
	}

	//Query process.
	bool anyFound = false;
	string query;

	cout << "Enter the queried words in one line: ";
	cin.ignore();
	getline(cin,query);

	vector<string> wordList;
	istringstream iss(query);
	string word;

	//Add lowered version of query words to the vector.
	while(iss >> word)
	{
		std::transform(word.begin(), word.end(), word.begin(), ::tolower);
		wordList.push_back(word);

	}

	//Check each file seperately.
	//To find queried words.
	for(int i = 0; i < numInputFiles; i++)
	{
		vector<int> numberOfOccurences;
		bool allWordsFound = true;
		//Iterate over queried words.
		for(int j = 0; j < wordList.size() && allWordsFound; j++)
		{

			WordItem tempObj;
			tempObj.setKey(wordList[j]);
			tempObj = infoTree.find(tempObj);
			//We could'nt find the word.
			if(tempObj == itemNotFound)
			{
				allWordsFound = false;
			}
			else
			{
				bool currWordFound = false;
				vector<DocumentItem> currDocList = tempObj.getList();
				//Look for the document and count.
				for(int k = 0; k < currDocList.size() && !currWordFound ; k++)
				{
					if(currDocList[k].documentName == fileList[i])
					{
						numberOfOccurences.push_back(currDocList[k].count);
						currWordFound = true;
					}
				}
				//We couldn't find the document in current word's list.
				if(!currWordFound)
					allWordsFound = false;
			}
		}
		//All found.
		if (allWordsFound && numberOfOccurences.size() > 0)
			{
				anyFound = true;
				string toBeStreamed = "in Document " + fileList[i] + ", ";
				for (int ii = 0; ii < wordList.size(); ii++)
				{
					toBeStreamed += wordList[ii] + " found " + to_string(numberOfOccurences[ii]) + " times, ";
				}
				toBeStreamed[toBeStreamed.size()-2] = '.';
				toBeStreamed += "\n";
				cout << toBeStreamed;
			}
	}
	//None of the files contained the query.
	if(!anyFound)
	{
		cout << "No document contains the given query";
	}
	
	return 0;
}