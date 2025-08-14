#include "cl_2.h"

cl_2::cl_2(cl_base* p_head_object, string s_object_name) : cl_base (p_head_object, s_object_name) { 
		this->class_num = 2;
}

void cl_2::signal_f(string& s_command) {
	cout << "Signal from " << get_absolute_path() << endl;
	s_command += " (class: " + to_string(class_num) + ")";
}

void cl_2::handler_f(string s_command) {
	cout << "Signal to " << get_absolute_path() << " Text: " << s_command <<
		endl;
}