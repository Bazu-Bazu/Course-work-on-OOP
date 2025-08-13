#include "cl_application.h"
#include "cl_base.h"
#include <iostream>

cl_application::cl_application(cl_base* p_head_object) : cl_base(p_head_object) {}

void cl_application::build_tree_objects() {
    string s_head, s_sub;
    cl_base* p_head;
    int i_class;

    cin >> s_head;
    this->set_name(s_head);

    while (true) {
        cin >> s_head;
        if (s_head == "endtree") {
            break;
        }

        p_head = search_tree(s_head);
        cin >> s_sub >> i_class;

        if (p_head && !p_head->get_subordinate(s_sub) && i_class >= 2 && i_class <= 6 && !search_tree(s_sub)) {
            switch (i_class) {
            case 2:
                new cl_2(p_head, s_sub);
                break;
            case 3:
                new cl_3(p_head, s_sub);
                break;
            case 4:
                new cl_4(p_head, s_sub);
                break;
            case 5:
                new cl_5(p_head, s_sub);
                break;
            case 6:
                new cl_6(p_head, s_sub);
                break;
            }
        }
    }
}

int cl_application::exec_app() {
    string s_object_name;
    int state;

    cout << "Object tree" << endl;
    print_obj();

    while (true) {
        if (!cin) {
            break;
        }

        cin >> s_object_name >> state;
        cl_base* obj = search_tree(s_object_name);

        if (obj) {
            obj->set_state(state);
        }
    }

    cout << "\nThe tree of objects and their readiness" << endl;
    print_obj_states();
    return 0;
}