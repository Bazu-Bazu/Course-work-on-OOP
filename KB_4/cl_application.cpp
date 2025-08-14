#include "cl_application.h"
#include "cl_base.h"
#include <iostream>
#include <stack>
#include <limits>

using namespace std;

cl_application::cl_application(cl_base* p_head_object) : cl_base(p_head_object) {
    p_signals.push_back(SIGNAL_D(cl_application::signal_f));
    p_signals.push_back(SIGNAL_D(cl_2::signal_f));
    p_signals.push_back(SIGNAL_D(cl_3::signal_f));
    p_signals.push_back(SIGNAL_D(cl_4::signal_f));
    p_signals.push_back(SIGNAL_D(cl_5::signal_f));
    p_signals.push_back(SIGNAL_D(cl_6::signal_f));

    p_handlers.push_back(HANDLER_D(cl_application::handler_f));
    p_handlers.push_back(HANDLER_D(cl_2::handler_f));
    p_handlers.push_back(HANDLER_D(cl_3::handler_f));
    p_handlers.push_back(HANDLER_D(cl_4::handler_f));
    p_handlers.push_back(HANDLER_D(cl_5::handler_f));
    p_handlers.push_back(HANDLER_D(cl_6::handler_f));

    class_num = 1;
}

void cl_application::build_tree_objects() {
    string s_path, s_sub_name;
    int i_sub_class;
    cl_base* p_head_object;
    string s_signal, s_object;
    cl_base* p_signal;
    cl_base* p_object;

    cin >> s_path;
    set_name(s_path);

    while (true) {
        cin >> s_path;
        if (s_path == "endtree") {
            break;
        }

        cin >> s_sub_name >> i_sub_class;
        p_head_object = get_p(s_path);

        if (p_head_object && !p_head_object->get_subordinate(s_sub_name)) {
            switch (i_sub_class) {
            case 2:
                new cl_2(p_head_object, s_sub_name);
                break;
            case 3:
                new cl_3(p_head_object, s_sub_name);
                break;
            case 4:
                new cl_4(p_head_object, s_sub_name);
                break;
            case 5:
                new cl_5(p_head_object, s_sub_name);
                break;
            case 6:
                new cl_6(p_head_object, s_sub_name);
                break;
            }
        }
    }

    cin >> s_signal;
    while (s_signal != "end_of_connections") {
        cin >> s_object;
        p_signal = get_p(s_signal);
        p_object = get_p(s_object);

        if (p_signal && p_object) {
            p_signal->set_connect(
                p_signals[p_signal->get_class_num() - 1],
                p_object,
                p_handlers[p_object->get_class_num() - 1]
            );
        }

        cin >> s_signal;
    }
}

int cl_application::exec_app() {
    string s_action, s_path, s_buff, s_command;
    cl_base* p_object = this;
    cl_base* p_buff_object;
    state = 1;
    vector<cl_base*> objs;
    objs.push_back(this);

    for (int index = 0; index < objs.size(); index++) {
        cl_base* current = objs[index];
        current->set_state(state);

        for (int i = 0; i < current->get_subordinate_objects().size(); i++) {
            objs.push_back(current->get_subordinate_objects()[i]);
        }
    }

    cout << "Object tree" << endl;
    print_obj();
    cout << endl;

    cin >> s_action;
    while (s_action != "END") {
        cin >> s_path;
        p_object = get_p(s_path);

        if (!p_object) {
            cout << "Object " << s_path << " not found" << endl;
        }
        else {
            if (s_action == "EMIT") {
                getline(cin, s_command);
                p_object->emit_signal(
                    p_signals[p_object->get_class_num() - 1],
                    s_command
                );
            }
            else if (s_action == "SET_CONDITION") {
                cin >> state;
                p_object->set_state(state);
            }
            else {
                cin >> s_buff;
                p_buff_object = get_p(s_buff);

                if (!p_buff_object) {
                    cout << "Handler object " << s_buff << " not found" << endl;
                }
                else {
                    if (s_action == "SET_CONNECT") {
                        p_object->set_connect(
                            p_signals[p_object->get_class_num() - 1],
                            p_buff_object,
                            p_handlers[p_buff_object->get_class_num() - 1]
                        );
                    }
                    else if (s_action == "DELETE_CONNECT") {
                        p_object->delete_connect(
                            p_signals[p_object->get_class_num() - 1],
                            p_buff_object,
                            p_handlers[p_buff_object->get_class_num() - 1]
                        );
                    }
                }
            }
        }
        cin >> s_action;
    }

    return 0;
}

void cl_application::signal_f(string& s_command) {
    cout << "Signal from " << get_absolute_path() << endl;
    s_command += " (class: " + to_string(class_num) + ")";
}

void cl_application::handler_f(string s_command) {
    cout << "Signal to " << get_absolute_path() << " Text: " << s_command << endl;
}