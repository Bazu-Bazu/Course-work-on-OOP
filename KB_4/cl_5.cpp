#include "cl_5.h"

cl_5::cl_5(cl_base* p_head_object, string s_object_name) : cl_base(p_head_object, s_object_name) {
	this->class_num = 5;
}

void cl_5::signal_f(string& s_command) {
	cout << "Signal from " << get_absolute_path() << endl;
	s_command += " (class: " + to_string(class_num) + ")";
}

void cl_5::handler_f(string s_command) {
	cout << "Signal to " << get_absolute_path() << " Text: " << s_command <<
		endl;
}