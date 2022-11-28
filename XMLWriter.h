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

	void write_indents() {
		*file << string(indent, '\t');
	}

	bool document_started() {
		if (file == nullptr) {
			cerr << "[" << __FUNCTION__ << "] Document has not been started" << endl;
			return false;
		}
		return true;
	}

public:
	XMLWriter() {}
	~XMLWriter() {}

	void WriteStartDocument(ostream &f) {
		// if (file) {
		// 	cerr << "[" << __FUNCTION__ << "] Document has already been started" << endl;
		// 	return;
		// }

		indent = 0;
		file = &f;
	}

	void WriteEndDocument() {
		if (!document_started())
			return;

		if (!tags.empty()) {
			cerr << "[" << __FUNCTION__ << "] O documento ainda tem tags por fechar" << endl;
			return;
		}

		// file->close();
		// delete file;
	}

	void WriteElementString(string el, string valor) {
		if (!document_started())
			return;

		write_indents();

		*file << "<" << el << ">" << valor << "</" << el << ">" << endl;
	}

	void WriteStartElement(string el) {
		if (!document_started())
			return;

		write_indents();

		*file << "<" << el << ">" << endl;

		tags.push_front(el);
		indent++;
	}

	void WriteEndElement() {
		if (!document_started())
			return;

		if (tags.empty()) {
			cerr << "[" << __FUNCTION__ << "] A lista de tags está vazia" << endl;
			return;
		}

		indent--;
		write_indents();

		string tag_name = tags.front();
		tags.pop_front();

		*file << "</" << tag_name << ">" << endl;
	}
};

#endif // XMLWRITER_HPP
