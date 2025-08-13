#ifndef CL_APPLICATION_H
#define CL_APPLICATION_H
#include "cl_base.h"

class cl_application : public cl_base {
public:
	cl_application(cl_base* p_head_object); 
	void build_tree_objects(); 
	int exec_app(); 
};

#endif

