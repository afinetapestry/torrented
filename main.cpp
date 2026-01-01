#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

// torrented directory /home/rtorrent/ ~ *
int main(int argc, const char * argv[]) {
	if (argc < 5) {
		cerr << "Usage: torrented property old new files\n\n";
		cerr << "Properties:\ndirectory\nannounce\n...\n";
		return EXIT_FAILURE;
	}
	
	const char * p = argv[1];
	const char * o = argv[2];
	const char * n = argv[3];

	int pLen = strlen(p);
	
	for (int i = 4; i < argc; ++i) {
		ifstream in(argv[i]);
		if (in) {
			cout << argv[i] << "\n";
			
			std::string str;
			in.seekg(0, ios::end);
			str.resize(in.tellg());
			in.seekg(0, ios::beg);
			in.read(&str[0], str.size());
			in.close();
			
			ostringstream ostr;
			
			size_t pos = str.find(p);
			
			ostr.write(&str[0], pos);
			ostr << p;
			
			int oldCount = atoi(&str[0] + pos + pLen);
			ostringstream oldCountStr;
			oldCountStr << oldCount;
			int count = strlen(n);
			ostringstream countStr;
			countStr << count;
			
			if (str.compare(pos + pLen + oldCountStr.str().size() + 1, strlen(o), o) != 0) {
				cout << "No match\n";
				continue;
			}

			cout << "Match\n";
			
			ostr << count << ":" << n;
			size_t lastPos = pos + pLen + countStr.str().size() + 1 + strlen(o);
			ostr.write(&str[0] + lastPos, str.size() - lastPos);
			
			ofstream out(argv[i], ios::out | ios::trunc);
			out.seekp(0, ios::beg);
			out << ostr.str();
			out.close();
		}
	}
	
	return EXIT_SUCCESS;
}
