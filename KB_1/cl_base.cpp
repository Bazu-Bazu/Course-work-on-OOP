#include "cl_base.h"
#include <iostream>
#include <vector>

using namespace std;

cl_base::cl_base(cl_base* p_head_object, string s_object_name) {
    this->p_head_object = p_head_object;
    this->s_object_name = s_object_name;
    if (p_head_object) {
        p_head_object->subordinate_objects.push_back(this);
    }
}

bool cl_base::set_name(string s_object_name) {
    if (p_head_object) {
        for (int i = 0; i < p_head_object->subordinate_objects.size(); i++) {
            if (p_head_object->subordinate_objects[i]->get_name() == s_object_name) {
                return false;
            }
        }
    }
    this->s_object_name = s_object_name;
    return true;
}

string cl_base::get_name() {
    return s_object_name;
}

cl_base* cl_base::get_head() {
    return p_head_object;
}

void cl_base::print_tree() {
    if (subordinate_objects.size() != 0) {
        cout << endl << this->get_name();
        for (int i = 0; i < subordinate_objects.size(); i++) {
            cout << " " << subordinate_objects[i]->get_name();
            subordinate_objects[i]->print_tree();
        }
    }
}

cl_base* cl_base::get_subordinate(string s_object_name) {
    for (int i = 0; i < subordinate_objects.size(); i++) {
        if (subordinate_objects[i]->get_name() == s_object_name) {
            return subordinate_objects[i];
        }
    }
    return nullptr;
}

cl_base::~cl_base() {
    for (int i = 0; i < subordinate_objects.size(); i++) {
        delete subordinate_objects[i];
    }
}