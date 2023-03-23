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
		WordItem(string Key, DocumentItem docItem)
		{
			vector<DocumentItem> list;
			list.push_back(docItem);
			elementKey = Key;
			docList = list;
		}

		bool operator==( WordItem & rhs)  {return this->elementKey == rhs.elementKey;} 
		bool operator>( WordItem & rhs)  {return this->elementKey > rhs.elementKey;}
		bool operator<( WordItem & rhs) {return this->elementKey < rhs.elementKey;}

		bool operator==( string & rhs) {return this->elementKey == rhs;} 
		bool operator>( string & rhs) {return this->elementKey > rhs;}
		bool operator<( string & rhs) {return this->elementKey < rhs;}

		void addToList(DocumentItem docItem) {docList.push_back(docItem);}
		void setKey(string Key) { elementKey = Key;}
		void setList(vector<DocumentItem> List)  {docList = List;}
		vector<DocumentItem> getList(){return docList;}

		WordItem()
		{
			elementKey = "";

			vector<DocumentItem> list;
			docList = list;
		}
};

#endif