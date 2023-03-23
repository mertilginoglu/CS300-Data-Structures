#include <iostream>
#include <string>
#include "Templated_HashTable.h"
#include "Templated_BST.h"
#include "WordItem.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cctype>
#include <map>
#include <chrono>
#include "Templated_Sorting.h"

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
		if (!std::isalpha(line[i]))
		{
			line[i] = ' ';
		}
	}

	//Make it lowercase.
	std::transform(line.begin(), line.end(), line.begin(), std::tolower);
}


//Binary search function that returns the index of searched item.
int binarySearch(vector<WordItem> & arr, int p, int r, WordItem & toBeSearched) {
   if (p <= r) {
      int mid = (p + r)/2;
      if (arr[mid] == toBeSearched)
      return mid ;
      if (arr[mid] > toBeSearched)
      return binarySearch(arr, p, mid-1, toBeSearched);
      if (arr[mid] < toBeSearched)
      return binarySearch(arr, mid+1, r, toBeSearched);
   }
   return -1;
}
int main()
{
	
	int numInputFiles;
	
	cout << "Enter number of input files: ";
	cin >> numInputFiles;

	//To store our filenames
	vector<string> fileList;
	vector<WordItem> allUniqueWords;
	//ItemNotFound for Hash Table and BST.
	WordItem itemNotFound;
	BinarySearchTree<WordItem> infoTree(itemNotFound);
	HashTable<WordItem> hashTable(itemNotFound, 53);
	//Storing filenames.
	for (int i = 0; i < numInputFiles; i++)
	{
		string fileName;
		cout << "Enter " << i+1 << ". file name: ";
		cin >> fileName;
		fileList.push_back(fileName);
	}

	//Preprocessing files.
	for (int i = 1; i <= numInputFiles; i++)
	{
		string fileName = fileList[i-1];
		string line;


		ifstream myFile(fileName);
		
		if(myFile.is_open())
		{
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
						DocumentItem docItem;
						docItem.count = 1;
						docItem.documentName = fileName;
						WordItem currWord(word,	docItem);
						WordItem * foundItem = &hashTable.find(currWord);
						if (*(foundItem) == itemNotFound)
						{
							hashTable.insert(currWord);
							infoTree.insert(currWord);
							allUniqueWords.push_back(currWord);
						}
						else
						{
							foundItem->incrementDoc(fileName);
							WordItem * bstItem = &infoTree.find(currWord);
							bstItem->incrementDoc(fileName);
							for(int i = 0; i < allUniqueWords.size(); i++)
							{
								if(allUniqueWords[i] == currWord)
									allUniqueWords[i].incrementDoc(fileName);
							}
						}
					}
				}
			}
			//PrintMap(wordsCount);
		
		}
		myFile.clear();
		myFile.seekg(0);
		myFile.close();
		
		/*
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
		
			DocumentItem newDoc;
			newDoc.documentName = fileName;
			newDoc.count = it->second;
			WordItem newInfo = WordItem(it->first, newDoc);
			if (allUniqueWords.empty())
			{
				allUniqueWords.push_back(newInfo);
			}
			else
			{
				bool loopDone = false;
				for (int i = 0; i < allUniqueWords.size() && !loopDone; i++)
				{
					if (allUniqueWords[i] == newInfo)
					{
						allUniqueWords[i].addToList(newDoc);
						loopDone = true;
					}
					else if( i == (allUniqueWords.size() - 1))
					{
						allUniqueWords.push_back(newInfo);
						loopDone = true;
					}
				}
			}


		}
		*/
	}
	
	
	//Query process.
	bool anyFound = false;
	string query;
	hashTable.showLoadFactor();
	cout << "Enter the queried words in one line: ";
	cin.ignore();
	getline(cin,query);

	lowerAndRemovePunc(query);
	vector<string> wordList;
	istringstream iss(query);
	string word;



	//Add lowered version of query words to the vector.
	while(iss >> word)
	{
		std::transform(word.begin(), word.end(), word.begin(), ::tolower);
		wordList.push_back(word);
	}

	double endMerge, endHeap, endInsertion, endQuicksort, endRandomQuicksort, endFirstQuicksort;

	vector<WordItem> mergeList = allUniqueWords;
	vector<WordItem> heapList = allUniqueWords;
	vector<WordItem> insertionList = allUniqueWords;
	vector<WordItem> quickList = allUniqueWords;
	vector<WordItem> firstQuickList = allUniqueWords;
	vector<WordItem> randomQuickList = allUniqueWords;


	///////////CALCULATING SORT TIMES///////////
    clock_t begin_time = clock();
	mergeSort(mergeList);
	endMerge = float(clock() - begin_time);

    begin_time = clock();
	heapsort(heapList);
	endHeap = float(clock() - begin_time);

	begin_time = clock();
	insertionSort(insertionList);
	endInsertion = float(clock() - begin_time);

    begin_time = clock();
	quicksort(quickList);
	endQuicksort = float(clock() - begin_time);

	begin_time = clock();
	quicksortRandom(randomQuickList);
	endRandomQuicksort = float(clock() - begin_time);

	begin_time = clock();
	quicksortFirst(firstQuickList);
	endFirstQuicksort = float(clock() - begin_time);
	//////////////////////////////////////////////////


	int k = 100;
	begin_time = clock();
	////////////BST QUERY///////////////////
	for (int xx = 0; xx < k; xx++)
	{
		bool wordMissing = false;
		bool noneFound = true;

		//To store the document lists of the words.
		vector<vector<DocumentItem>> docList;
		//Search the words.
		for(int i = 0; i < wordList.size(); i++)
		{
				WordItem tempObj;
				tempObj.setKey(wordList[i]);
				tempObj = infoTree.find(tempObj);
				if(tempObj == itemNotFound)
				{
					wordMissing = true;
				}
				else
				{
					docList.push_back(tempObj.getList());
				}

		}
		//If we found all the words.
		for(int i = 0; i < numInputFiles && !wordMissing; i++)
		{
			string outputResult;
			bool allFound = true;
			outputResult = "in Document " + fileList[i] + ", ";
			//Iterate over words
			for(int j = 0; j < docList.size(); j++)
			{
				bool found = false;
				//Iterate over word's document list
				for(int jj = 0; jj < docList[j].size(); jj++)
				{
					if (docList[j][jj].documentName == fileList[i])
					{
						outputResult += wordList[j] + " found " + to_string(docList[j][jj].count) + " times, ";
						found = true;
					}
				}
				//We couldnt the document.
				if(!found)
				{
					allFound = false;
				}
			}
			//If all words were found in the file.
			if(allFound && xx == k-1)
			{
				outputResult[outputResult.size()-2] = '.';
				outputResult += "\n";
				cout << outputResult;
				noneFound = false;
			}
		}

		if(noneFound && xx == k-1)
		{
			cout << "No document contains the query." << endl;
		}

	}
	//////////////////////////////////////////////////////////////

    double endBST = float(clock() - begin_time);
    


    begin_time = clock();


	////////////HASHTABLE QUERY///////////////////
	//Same thing as BST, but BST object is replaced with Hash Table object//
	for (int xx = 0; xx < k; xx++)
	{
		bool wordMissing = false;
		bool noneFound = true;

		vector<vector<DocumentItem>> docList;

		
		for(int i = 0; i < wordList.size(); i++)
		{
				WordItem tempObj;
				tempObj.setKey(wordList[i]);
				tempObj = hashTable.find(tempObj);
				if(tempObj == itemNotFound)
				{
					wordMissing = true;
				}
				else
				{
					docList.push_back(tempObj.getList());
				}

		}
		for(int i = 0; i < numInputFiles && !wordMissing; i++)
		{
			string outputResult;
			bool allFound = true;
			outputResult = "in Document " + fileList[i] + ", ";
			for(int j = 0; j < docList.size(); j++)
			{
				bool found = false;
				//Iterate over word's document list
				for(int jj = 0; jj < docList[j].size(); jj++)
				{
					if (docList[j][jj].documentName == fileList[i])
					{
						outputResult += wordList[j] + " found " + to_string(docList[j][jj].count) + " times, ";
						found = true;
					}
				}
				if(!found)
				{
					allFound = false;
				}
			}
			if(allFound && xx == k-1)
			{
				outputResult[outputResult.size()-2] = '.';
				outputResult += "\n";
				cout << outputResult;
				noneFound = false;
			}
		}

		if(noneFound && xx == k-1)
		{
			cout << "No document contains the query." << endl;
		}

	}


	/////////////////////////////////////////////////////////////////////////////
    double endHT = float(clock() - begin_time);
    

	begin_time = clock();
	/////BINARY SEARCH QUERY////////////////
    for (int xx = 0; xx < k;xx++)
	{
		bool wordMissing = false;
		bool noneFound = true;

		//To store the document lists of the words.
		vector<vector<DocumentItem>> docList;
		//Search the words.
		for(int i = 0; i < wordList.size(); i++)
		{
				WordItem tempObj;
				tempObj.setKey(wordList[i]);
				int index = binarySearch(mergeList, 0, mergeList.size()-1, tempObj);
				if(index == -1)
				{
					wordMissing = true;
				}
				else
				{
					docList.push_back(mergeList[index].getList());
				}

		}
		//If we found all the words.
		for(int i = 0; i < numInputFiles && !wordMissing; i++)
		{
			string outputResult;
			bool allFound = true;
			outputResult = "in Document " + fileList[i] + ", ";
			//Iterate over words
			for(int j = 0; j < docList.size(); j++)
			{
				bool found = false;
				//Iterate over word's document list
				for(int jj = 0; jj < docList[j].size(); jj++)
				{
					if (docList[j][jj].documentName == fileList[i])
					{
						outputResult += wordList[j] + " found " + to_string(docList[j][jj].count) + " times, ";
						found = true;
					}
				}
				//We couldnt the document.
				if(!found)
				{
					allFound = false;
				}
			}
			//If all words were found in the file.
			if(allFound && xx == k-1)
			{
				outputResult[outputResult.size()-2] = '.';
				outputResult += "\n";
				cout << outputResult;
				noneFound = false;
			}
		}

		if(noneFound && xx == k-1)
		{
			cout << "No document contains the query." << endl;
		}

	}
    double endBS = float(clock() - begin_time);
    
	
	/*
	int k = 10000;
	auto start = std::chrono::high_resolution_clock::now();



	for (int ab = 0; ab < k; ab++)
		{
				for(int j = 0; j < wordList.size(); j++)
					{

						WordItem tempObj;
						tempObj.setKey(wordList[j]);
						tempObj = infoTree.find(tempObj);
				}
		}
	auto BSTTime = std::chrono::duration_cast<std::chrono::nanoseconds> 
	(std::chrono::high_resolution_clock::now() - start);
	cout << "\nTime: " << BSTTime.count() / k << "\n";



	auto start1 = std::chrono::high_resolution_clock::now();
	for (int ab = 0; ab < k; ab++)
	{
			for(int j = 0; j < wordList.size(); j++)
				{

					WordItem tempObj;
					tempObj.setKey(wordList[j]);
					tempObj = hashTable.find(tempObj);
			}
	}
	auto HTTime = std::chrono::duration_cast<std::chrono::nanoseconds> 
(std::chrono::high_resolution_clock::now() - start1);
	cout << "\nTime: " << HTTime.count() / k << "\n";
	cout  << "Speed up: " << double(BSTTime.count()) / HTTime.count();
	*/

	cout << "\nBinary Search Tree Time: " << endBST / k << "\n";
	cout << "Hash Table Time: " << endHT / k << "\n";
	cout << "Binary Search Time: " << endBS / k << "\n";

	cout << "\nQuick Sort(median) Time: " << endQuicksort << endl;
	cout << "Quick Sort(random) Time: " << endRandomQuicksort << endl;
	cout << "Quick Sort(first) Time: " << endFirstQuicksort << endl;
	cout << "Merge Sort Time: " << endMerge << endl;
	cout << "Heap Sort Time: " << endHeap << endl;
	cout << "Insertion Sort Time: " << endInsertion << endl << endl;
	
	cout << "Speed up BST/HST: " << endBST/endHT << endl;
	cout << "Speed Up Merge Sort/Quick Sort(Median): " << endMerge / endQuicksort << endl;
	cout << "Speed Up Heap Sort/Quick Sort(Median): " << endHeap / endQuicksort << endl;
	cout << "Speed Up Insertion Sort/Quick Sort(Median): " << endInsertion / endQuicksort << endl;

	cout << "\nSpeed Up Binary Search / Binary Search Tree Time: " << endBST / endBS << endl;
	cout << "Speed Up Binary Search / Hash Table Time: " << endHT / endBS << endl;

	return 0;
}