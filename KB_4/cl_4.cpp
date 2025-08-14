#include "cl_4.h"

cl_4::cl_4(cl_base* p_head_object, string s_object_name) : cl_base(p_head_object, s_object_name) {
	this->class_num = 4;
}

void cl_4::signal_f(string& s_command) {
	cout << "Signal from " << get_absolute_path() << endl;
	s_command += " (class: " + to_string(class_num) + ")";
}

void cl_4::handler_f(string s_command) {
	cout << "Signal to " << get_absolute_path() << " Text: " << s_command <<
		endl;
}