#ifndef CL_BASE_H
#define CL_BASE_H

#include <iostream>
#include <vector>

using namespace std;

class cl_base {
private:
	string s_object_name;
	cl_base* p_head_object;
	vector<cl_base*> subordinate_objects;

public:
	cl_base(cl_base* p_head_object, string s_object_name = "Base_object");
	bool set_name(string s_object_name);
	string get_name();
	cl_base* get_head();
	void print_tree();
	cl_base* get_subordinate(string s_object_name);
	~cl_base();
};

#endif
