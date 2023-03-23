#ifndef WORDITEM_H
#define WORDITEM_H

#include <string>
#include <vector>
using namespace std;

struct DocumentItem {
	string documentName;
	int count;
};

class WordItem
{
	private:
		string elementKey;
		vector<DocumentItem> docList;

	public:
		//CONSTRUCTOR
		WordItem(string Key, DocumentItem docItem)
		{
			vector<DocumentItem> list;
			list.push_back(docItem);
			elementKey = Key;
			docList = list;
		}

		//////OPERATOR OVERLOADS///////////

		bool operator==( WordItem & rhs)   {return this->elementKey == rhs.elementKey;} 
		bool operator!=( WordItem & rhs)   {return this->elementKey != rhs.elementKey;} 
		bool operator!=(const WordItem & rhs) const  {return this->elementKey != rhs.elementKey;} 
		bool operator>( WordItem & rhs)   {return this->elementKey > rhs.elementKey;} 
		bool operator<( WordItem & rhs)  {return this->elementKey < rhs.elementKey;} 
		void operator=( WordItem & rhs) {
			elementKey = rhs.elementKey;
			docList = rhs.docList;
		}

		bool operator==( string & rhs)  {return this->elementKey == rhs;} 
		bool operator!=(  string & rhs)  {return this->elementKey != rhs;} 
		bool operator>( string & rhs)  {return this->elementKey > rhs;} 
		bool operator<( string & rhs)  {return this->elementKey < rhs;} 

		///////////////////////////////////////


		
		void addToList(DocumentItem docItem) {docList.push_back(docItem);}
		void setKey(string Key) { elementKey = Key;}
		void setList(vector<DocumentItem> List)  {docList = List;}
		string getKey()  {return elementKey;}
		vector<DocumentItem> getList(){return docList;}

		
		void incrementDoc(string docName)
		{
			bool foundInList = false;
			for (int i = 0; i < docList.size(); i++)
			{
				if(docList[i].documentName == docName)
				{
					docList[i].count++;
					foundInList = true;
				}
			}
			if(!foundInList)
			{
				DocumentItem newDocItem;
				newDocItem.count = 1;
				newDocItem.documentName = docName;
				docList.push_back(newDocItem);
			}
		}


		WordItem()
		{
			elementKey = "";

			vector<DocumentItem> list;
			docList = list;
		}
};

#endif