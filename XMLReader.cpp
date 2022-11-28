#include "XMLReader.h"

XMLReader::XMLReader() {
	cout << "XMLReader::XMLReader()" << endl;
}

XMLReader::~XMLReader() {
	cout << "XMLReader::~XMLReader()" << endl;
}

string XMLReader::Trim_Whitespace(string line) {

	int lastChar = 0;

	for (int i = 0; i < line.length(); i++) {
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n') {
			lastChar = i;
			break;
		}
	}

	return line.substr(lastChar);
}

string XMLReader::read_tag(string line, char *val) {
	string tag_name = "";
	int i;

	for (i = 1; i < line.length(); i++) {
		if (line[i] == '>') {
			break;
		}

		tag_name += line[i];
	}

	if (line[i + 1] == '<') {
		strcpy(val, "");
	} else {
		strcpy(val, line.substr(i + 1, line.find("</") - i - 1).c_str());
	}

	return tag_name;
}

void XMLReader::read(const char *filename) {
	cout << "XMLReader::read(" << filename << ")" << endl;

	ifstream f(filename);
	if (!f.is_open()) {
		cout << "[" << __FUNCTION__ << "] Não foi possível abrir o ficheiro " << filename << endl;
		return;
	}

	string line;
	while (getline(f, line)) {
		line = Trim_Whitespace(line);

		if (line.length() == 0) {
			continue;
		}

		cout << line << endl;

		if (line[0] != '<') {
			cout << "[" << __FUNCTION__ << "] Linha inválida: " << line << endl;
			continue;
		}

		char *val = (char *)malloc(150 * sizeof(char));
		string tag_name = read_tag(line, val);

		cout << "Tag: " << tag_name << endl;

		if (val) {
			cout << "Valor: " << val << endl;
		}

		cout << line << endl;
	}

	f.close();
}
