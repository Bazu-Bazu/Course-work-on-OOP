#include "cl_base.h"
#include <iostream>
#include <vector>

using namespace std;

cl_base::cl_base(cl_base* p_head_object, string s_object_name)
{
    this->p_head_object = p_head_object;
    this->s_object_name = s_object_name;
    if (p_head_object) {
        p_head_object->subordinate_objects.push_back(this);
    }
}

bool cl_base::set_name(string s_object_name)
{
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

string cl_base::get_name()
{
    return s_object_name;
}

cl_base* cl_base::get_head()
{
    return p_head_object;
}

cl_base* cl_base::get_subordinate(string s_object_name)
{
    for (int i = 0; i < subordinate_objects.size(); i++) {
        if (subordinate_objects[i]->get_name() == s_object_name) {
            return subordinate_objects[i];
        }
    }
    return nullptr;
}

cl_base::~cl_base()
{
    for (int i = 0; i < subordinate_objects.size(); i++) {
        delete subordinate_objects[i];
    }
}

cl_base* cl_base::search_current(string s_object_name)
{
    if (get_name() == s_object_name) {
        return this;
    }
    for (int i = 0; i < subordinate_objects.size(); i++) {
        cl_base* p_sub = subordinate_objects[i]->search_current(s_object_name);
        if (p_sub) {
            return p_sub;
        }
    }
    return nullptr;
}

cl_base* cl_base::search_tree(string s_object_name)
{
    cl_base* p_root = this;
    while (p_root->get_head()) {
        p_root = this->get_head();
    }
    return p_root->search_current(s_object_name);
}

void cl_base::set_state(int state)
{
    if (get_head() && get_head()->state == 0) {
        this->state = 0;
    }
    else {
        this->state = state;
    }
    if (state == 0) {
        for (int i = 0; i < subordinate_objects.size(); i++) {
            subordinate_objects[i]->set_state(state);
        }
    }
}

void cl_base::print_obj(int space)
{
    cout << get_name();
    if (subordinate_objects.size() != 0) {
        for (int i = 0; i < subordinate_objects.size(); i++) {
            cout << endl;
            for (int j = 0; j < space; j++) {
                cout << " ";
            }
            subordinate_objects[i]->print_obj(space + 4);
        }
    }
}

void cl_base::print_obj_states(int space)
{
    cout << get_name();
    if (state == 0) {
        cout << " is not ready";
    }
    else {
        cout << " is ready";
    }
    if (subordinate_objects.size() != 0) {
        for (int i = 0; i < subordinate_objects.size(); i++) {
            cout << endl;
            for (int j = 0; j < space; j++) {
                cout << " ";
            }
            subordinate_objects[i]->print_obj_states(space + 4);
        }
    }
}