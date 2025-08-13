#ifndef CL_APPLICATION_H
#define CL_APPLICATION_H
#include "cl_base.h"
#include "cl_2.h"
#include "cl_3.h"
#include "cl_4.h"
#include "cl_5.h"
#include "cl_6.h"

class cl_application : public cl_base {
public:
	cl_application(cl_base* p_head_object); 
	void build_tree_objects(); 
	int exec_app(); 
};

#endif

