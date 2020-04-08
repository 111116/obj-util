#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

struct ID {
	int indices[3] = {0, 0, 0};
};
std::istream& operator>> (std::istream& in, ID& a)
{
    for (int i = 0; i < 3; ++i) {
        if (in.peek() != '/')
            in >> a.indices[i];
        if (in.peek() == '/')
            in.get();
        else break;
    }
    while (isspace(in.peek()))
        in.get();
    while (in.peek() == '\r')
    	in.get();
    return in;
}
std::ostream& operator<< (std::ostream& out, const ID& a)
{
	out << a.indices[0];
	if (!a.indices[1] && !a.indices[2]) return out;
	out << "/";
	if (a.indices[1]) out << a.indices[1];
	if (!a.indices[2]) return out;
	out << "/";
	out << a.indices[2];
	return out;
}

int main(int argc, char* argv[])
{
	std::string line;
	while (std::getline(std::cin, line))
	{
		if (isalpha(line[0])) {
			std::stringstream in(line);
			std::string cmd;
			in >> cmd;
			if (cmd == "f") {
				std::vector<ID> a;
				while (1) {
					ID v;
					bool t = !!(in >> v);
					a.push_back(v);
					if (!t) break;
				}
				for (int i=2; i<a.size(); ++i)
					std::cout << "f " << a[0] << " " << a[i-1] << " " << a[i] << "\n";
			}
			else {
				std::cout << line << std::endl;
			}
		}
		else {
			std::cout << line << std::endl;
		}
	}
}
