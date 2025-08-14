#ifndef __CL_4__H
#define __CL_4__H
#include "cl_base.h"
#include <iostream>

using namespace std;

class cl_4 : public cl_base {
public:
	cl_4(cl_base* p_head_object, string s_object_name);
	void signal_f(string& s_command);
	void handler_f(string s_command);
};

#endif