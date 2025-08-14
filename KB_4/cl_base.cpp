#include "cl_base.h"
#include <iostream>
#include <vector>
#include <stack>
#include <queue>

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

cl_base* cl_base::search_current(string s_object_name) {
    cl_base* success = nullptr;
    queue<cl_base*> que;
    que.push(this);

    while (!que.empty()) {
        cl_base* element = que.front();
        que.pop();

        if (element->get_name() == s_object_name) {
            if (success) {
                return nullptr;
            }
            else {
                success = element;
            }
        }

        for (int i = 0; i < element->subordinate_objects.size(); i++) {
            que.push(element->subordinate_objects[i]);
        }
    }
    return success;
}

cl_base* cl_base::search_tree(string s_object_name) {
    if (p_head_object) {
        return p_head_object->search_tree(s_object_name);
    }
    else {
        return search_current(s_object_name);
    }
}

void cl_base::set_state(int state) {
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

void cl_base::print_obj(int space) {
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

void cl_base::print_obj_states(int space) {
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

bool cl_base::set_head(cl_base* new_p) {
    if (get_head() == new_p) {
        return false;
    }
    if (!new_p) {
        return false;
    }
    if (new_p->get_subordinate(get_name())) {
        return false;
    }

    stack<cl_base*> stck;
    stck.push(this);

    while (!stck.empty()) {
        cl_base* curr_node_p = stck.top();
        stck.pop();

        if (curr_node_p == new_p) {
            return false;
        }

        for (int i = 0; i < curr_node_p->subordinate_objects.size(); i++) {
            stck.push(curr_node_p->subordinate_objects[i]);
        }
    }

    if (get_head()) {
        auto& vec = get_head()->subordinate_objects;
        for (int i = 0; i < vec.size(); i++) {
            if (vec[i] == this) {
                vec.erase(vec.begin() + i);
                break;
            }
        }
    }

    new_p->subordinate_objects.push_back(this);
    p_head_object = new_p;
    return true;
}

void cl_base::remove_sub(string s_object_name) {
    vector<cl_base*>& vec = subordinate_objects;
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i]->get_name() == s_object_name) {
            delete vec[i];
            vec.erase(vec.begin() + i);
        }
    }
}

cl_base* cl_base::get_p(string path) {
    if (path.empty()) {
        return nullptr;
    }
    if (path == ".") {
        return this;
    }
    if (path[0] == '.') {
        return search_current(path.substr(1));
    }
    if (path.substr(0, 2) == "//") {
        return search_tree(path.substr(2));
    }
    if (path[0] != '/') {
        int slash_index = path.find('/');
        cl_base* p_sub = get_subordinate(path.substr(0, slash_index));
        if (!p_sub || slash_index == string::npos) {
            return p_sub;
        }
        return p_sub->get_p(path.substr(slash_index + 1));
    }

    cl_base* root_p = this;
    while (root_p->get_head()) {
        root_p = root_p->get_head();
    }

    if (path == "/") {
        return root_p;
    }
    return root_p->get_p(path.substr(1));
}

void cl_base::set_connect(TYPE_SIGNAL p_signal, cl_base* p_object, TYPE_HANDLER p_ob_handler) {
    o_sh* p_value;

    for (int i = 0; i < connects.size(); i++) {
        if (connects[i]->p_signal == p_signal && connects[i]->p_cl_base == p_object &&
            connects[i]->p_handler == p_ob_handler) {
            return;
        }
    }

    p_value = new o_sh();
    p_value->p_signal = p_signal;
    p_value->p_cl_base = p_object;
    p_value->p_handler = p_ob_handler;
    connects.push_back(p_value);
}

void cl_base::delete_connect(TYPE_SIGNAL p_signal, cl_base* p_object, TYPE_HANDLER p_ob_handler) {
    for (int i = 0; i < connects.size(); i++) {
        if (connects[i]->p_signal == p_signal && connects[i]->p_cl_base == p_object &&
            connects[i]->p_handler == p_ob_handler) {
            delete connects[i];
            connects.erase(connects.begin() + i);
            return;
        }
    }
}

void cl_base::emit_signal(TYPE_SIGNAL p_signal, string& s_command) {
    if (state == 0) {
        return;
    }

    TYPE_HANDLER p_handler;
    cl_base* p_object;

    (this->*p_signal)(s_command);

    for (int i = 0; i < connects.size(); i++) {
        if (connects[i]->p_signal == p_signal && connects[i]->p_cl_base->state != 0) {
            p_handler = connects[i]->p_handler;
            p_object = connects[i]->p_cl_base;
            (p_object->*p_handler)(s_command);
        }
    }
}

string cl_base::get_absolute_path() {
    string s_path = "";
    cl_base* p_buff_obj = this;

    while (p_buff_obj->get_head()) {
        s_path = "/" + p_buff_obj->get_name() + s_path;
        p_buff_obj = p_buff_obj->get_head();
    }

    if (s_path == "") {
        return "/";
    }
    else {
        return s_path;
    }
}

vector<cl_base*> cl_base::get_subordinate_objects() {
    return subordinate_objects;
}

int cl_base::get_class_num() {
    return class_num;
}