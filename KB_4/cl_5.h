#ifndef __CL_5__H
#define __CL_5__H
#include "cl_base.h"
#include <iostream>

using namespace std;

class cl_5 : public cl_base {
public:
	cl_5(cl_base* p_head_object, string s_object_name);
	void signal_f(string& s_command);
	void handler_f(string s_command);
};

#endif