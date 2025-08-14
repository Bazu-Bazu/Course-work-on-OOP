#ifndef CL_BASE_H
#define CL_BASE_H
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define SIGNAL_D( signal_f ) ( TYPE_SIGNAL ) ( & signal_f )
#define HANDLER_D( hendler_f ) ( TYPE_HANDLER ) ( & hendler_f )

class cl_base;

typedef void (cl_base ::* TYPE_SIGNAL) (string&);
typedef void (cl_base ::* TYPE_HANDLER) (string);

struct o_sh {
	TYPE_SIGNAL p_signal;
	cl_base* p_cl_base;
	TYPE_HANDLER p_handler;
};

class cl_base {
private:
	string s_object_name;
	cl_base* p_head_object;
	vector < cl_base* > subordinate_objects;
	vector < o_sh* > connects;
protected:
	int state;
	int class_num;
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
	bool set_head(cl_base* new_p);
	void remove_sub(string s_object_name);
	cl_base* get_p(string path);
	void set_connect(TYPE_SIGNAL p_signal, cl_base* p_object, TYPE_HANDLER p_ob_handler);
	void delete_connect(TYPE_SIGNAL p_signal, cl_base* p_object, TYPE_HANDLER p_ob_handler); 
	void emit_signal(TYPE_SIGNAL p_signal, string& s_command);
	string get_absolute_path();
	vector <cl_base* > get_subordinate_objects();
	int get_class_num();
};

#endif