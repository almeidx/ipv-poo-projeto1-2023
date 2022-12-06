#ifndef XMLWRITER_HPP
#define XMLWRITER_HPP

#include <fstream>
#include <iostream>
#include <iterator>
#include <list>

using namespace std;

class XMLWriter {
	list<string> tags;
	int indent;
	ostream *file;

	void WriteIndent() {
		if (indent > 0) {
			*file << string(indent, '\t');
		}
	}

public:
	XMLWriter(ostream &f) {
		indent = 0;
		file = &f;
	}
	~XMLWriter() {}

	void WriteElementString(string el, string valor) {
		WriteIndent();

		*file << "<" << el << ">" << valor << "</" << el << ">" << endl;
	}

	void WriteStartElement(string el) {
		WriteIndent();
		indent++;

		*file << "<" << el << ">" << endl;

		tags.push_front(el);
	}

	void WriteEndElement() {
		if (tags.empty()) {
			cerr << "[" << __FUNCTION__ << "] A lista de tags está vazia" << endl;
			return;
		}

		indent--;
		WriteIndent();

		string tag_name = tags.front();
		tags.pop_front();

		*file << "</" << tag_name << ">" << endl;
	}
};

#endif // XMLWRITER_HPP
