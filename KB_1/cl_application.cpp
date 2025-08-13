#include "cl_application.h"
#include "cl_base.h"
#include "cl_obj.h"
#include <iostream>

cl_application::cl_application(cl_base* p_head_object) : cl_base(p_head_object) {}

void cl_application::build_tree_objects() {
	string s_head, s_sub;	
	cl_base* p_head;
	cl_base* p_sub = nullptr;

	cin >> s_head;
	this->set_name(s_head);
	
	p_head = this;

	while (true) {
		cin >> s_head >> s_sub;
		
		if (s_head == s_sub) {
			break;
		}

		if (p_sub && s_head == p_sub->get_name()) {
			p_head = p_sub;
		}

		if (!p_head->get_subordinate(s_sub) && s_head == p_head -> get_name()) { 
			p_sub = new cl_obj(p_head, s_sub);
		}
	}
}

int cl_application::exec_app() {
	cout << this->get_name();
	this->print_tree();
	return 0;
}
