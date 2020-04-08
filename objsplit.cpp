// tool that splits obj file by material
// no vt/vn supported!

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

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
    return in;
}
// std::ostream& operator<< (std::ostream& out, const ID& a)
// {
// 	if (!a.indices[1] && !a.indices[2])
// 		return out << a.indices[0];

// }

struct face {
	ID a,b,c;
};
std::istream& operator>> (std::istream& in, face& a)
{
	return in >> a.a >> a.b >> a.c;
}


std::vector<std::string> v,vn,vt;
void save(std::string filename, std::vector<face> poly)
{
	// save vertex only!!!
	std::ofstream out(filename);
	__gnu_pbds::tree<int,__gnu_pbds::null_type,std::less<int>,__gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update> vid;
	for (auto f: poly) {
		vid.insert(f.a.indices[0]);
		vid.insert(f.b.indices[0]);
		vid.insert(f.c.indices[0]);
	}
	for (int id: vid) {
		out << v[id-1] << std::endl;
	}
	for (auto f: poly) {
		out << "f " << vid.order_of_key(f.a.indices[0])+1
			<< " "  << vid.order_of_key(f.b.indices[0])+1
			<< " "  << vid.order_of_key(f.c.indices[0])+1
			<< "\n";
	}
}

int main(int argc, char* argv[])
{
	if (argc<=1) {
		std::cerr << "arg: obj file\n";
		return 1;
	}
	// read obj file
	std::string curmtl;
	std::unordered_map<std::string, std::vector<face>> group;
	std::ifstream fin(argv[1]);
	std::string line;
	while (std::getline(fin, line))
	{
		if (isalpha(line[0])) {
			std::stringstream in(line);
			std::string cmd;
			in >> cmd;
			if (cmd == "v") v.push_back(line);
			if (cmd == "vt") vt.push_back(line);
			if (cmd == "vn") vn.push_back(line);
			if (cmd == "usemtl") in >> curmtl;
			if (cmd == "f") {
				face f;
				in >> f;
				group[curmtl].push_back(f);
			}
		}
	}
	// save by group
	for (auto p: group)
		save(p.first+".obj", p.second);
}
