#ifndef CL_OBJ__H
#define CL_OBJ__H
#include "cl_base.h"
#include <iostream>

using namespace std;

class cl_obj : public cl_base {
public:
	cl_obj(cl_base* p_head_object, std::string s_object_name);
};

#endif
