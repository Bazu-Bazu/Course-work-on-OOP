#ifndef CL_BASE_H
#define CL_BASE_H
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class cl_base {
private:
	string s_object_name;
	cl_base* p_head_object;
	vector < cl_base* > subordinate_objects;
	int state;
public:
	cl_base(cl_base* p_head_object, string s_object_name = "Base_object");
	bool set_name(string s_object_name);
	string get_name();
	cl_base* get_head();
	cl_base* get_subordinate(string s_object_name);
	~cl_base();
	cl_base* search_current(string s_object_name);
	cl_base* search_tree(string s_object_name);
	void set_state(int state);
	void print_obj(int space = 4);
	void print_obj_states(int space = 4);
};
#endif