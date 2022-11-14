#ifndef XML_READER_H
#define XML_READER_H

#include <fstream>
#include <iostream>
#include <map>
#include <string.h>
#include <string>

using namespace std;

class XMLReader {
	map<string, void *> tags;
	string current_element;

	string Trim_Whitespace(string line);
	string read_tag(string line, char *val);

public:
	XMLReader();
	~XMLReader();
	void read(const char *filename);
	void print();
};

#endif // XML_READER_H
