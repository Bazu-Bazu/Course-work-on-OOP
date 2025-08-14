#include "cl_application.h"
#include "cl_base.h"
#include <iostream>
#include <stack>
#include <limits>

using namespace std;

cl_application::cl_application(cl_base* p_head_object) : cl_base(p_head_object) {}

void cl_application::build_tree_objects() {
    cout << "Object tree" << endl;
    string path, s_sub;
    int i_class;

    cin >> s_sub;
    set_name(s_sub);

    cl_base* par_node_p;
    cl_base* last_node_p = this;

    cin >> path;
    while (path != "endtree") {
        cin >> s_sub >> i_class;
        par_node_p = last_node_p->get_p(path);

        if (!par_node_p) {
            print_obj();
            cout << endl << "The head object " << path << " is not found";
            exit(1);
        }

        if (par_node_p->get_subordinate(s_sub)) {
            cout << endl << path << " Dubbing the names of subordinate objects";
        }
        else {
            switch (i_class) {
            case 1:
                last_node_p = new cl_application(par_node_p);
                break;
            case 2:
                last_node_p = new cl_2(par_node_p, s_sub);
                break;
            case 3:
                last_node_p = new cl_3(par_node_p, s_sub);
                break;
            case 4:
                last_node_p = new cl_4(par_node_p, s_sub);
                break;
            case 5:
                last_node_p = new cl_5(par_node_p, s_sub);
                break;
            case 6:
                last_node_p = new cl_6(par_node_p, s_sub);
                break;
            }
        }
        cin >> path;
    }
}

int cl_application::exec_app() {
    string command, input;
    cl_base* curr_p = this;
    cl_base* extra_p;
    stack<string> stck;

    print_obj();
    cin >> command;

    while (command != "END") {
        cin >> input;

        if (command == "SET") {
            extra_p = curr_p->get_p(input);
            if (extra_p) {
                curr_p = extra_p;
                cout << endl << "Object is set: " << curr_p->get_name();
            }
            else {
                cout << endl << "The object was not found at the specified coordinate: " << input;
            }
        }
        else if (command == "FIND") {
            extra_p = curr_p->get_p(input);
            if (extra_p) {
                cout << endl << input << " Object name: " << extra_p->get_name();
            }
            else {
                cout << endl << input << " Object is not found";
            }
        }
        else if (command == "MOVE") {
            extra_p = curr_p->get_p(input);
            if (curr_p->set_head(extra_p)) {
                cout << endl << "New head object: " << extra_p->get_name();
            }
            else if (!extra_p) {
                cout << endl << input << " Head object is not found";
            }
            else if (extra_p->get_subordinate(curr_p->get_name()) != nullptr) {
                cout << endl << input << " Dubbing the names of subordinate objects";
            }
            else {
                cout << endl << input << " Redefining the head object failed";
            }
        }
        else if (command == "DELETE") {
            extra_p = curr_p->get_subordinate(input);
            if (extra_p) {
                while (extra_p->get_head()) {
                    stck.push(extra_p->get_name());
                    extra_p = extra_p->get_head();
                }
                curr_p->remove_sub(input);
                cout << endl << "The object ";
                while (!stck.empty()) {
                    cout << "/" << stck.top();
                    stck.pop();
                }
                cout << " has been deleted";
            }
        }
        cin >> command;
    }

    cout << endl << "Current object hierarchy tree" << endl;
    print_obj();
    return 0;
}