
#include "Graph.h"
#include "Hyper_graph.h"
#include <algorithm>
#include <set>

using namespace std;

void graph_test();

void hyper_graph_test();

void print_hyper_graph_edge(const vector<string> &to_print) {
    cout << '{';
    for (int i = 0; i < to_print.size() - 1; i++)
        cout << to_print[i] << ',';
    cout << to_print[to_print.size() - 1] << "}\n";
}

vector<string> incidence_find(const hyper_graph<string> &find_in, const string &to_find) {
    set<string> to_fill;
    for_each(find_in.arc_cbegin(), find_in.arc_cend(), [&to_fill, to_find](const vector<string> &find_in) {
        for (auto &i:find_in)
            if (i == to_find) {
                for (auto &j:find_in) {
                    to_fill.insert(j);
                }
                break;
            }
    });
    to_fill.erase(to_fill.find(to_find));
    vector<string>to_return;
    for_each(to_fill.begin(),to_fill.end(),[&to_return](const string& to_push){to_return.push_back(to_push);});
    return to_return;
}

int main() {
    graph_test();
    hyper_graph_test();
}

void graph_test() {
    cout << "Graph:\n";
    graph<string> a;
    for_each(a.node_begin(), a.node_end(), graph<string>::node_find(a));
    a.add_node("1");
    a.add_node("2");
    a.add_node("3");
    a.add_node("4");
    a.add_arc("1", "2");
    a.add_arc("3", "2");
    a.add_arc("4", "1");
    a.add_arc("1", "3");
    for_each(a.node_begin(), a.node_end(), [](const string &a) { cout << a << ' '; });
    std::cout << endl;
    for_each(a.arc_begin(), a.arc_end(),
             [](const pair<string, string> &a) { cout << a.first << "->" << a.second << endl; });;
    a.arc_erase(graph<string>::arc_find(a)("3", "2"));
    std::cout << "After deleting:\n";
    for_each(a.node_begin(), a.node_end(), [](const string &a) { cout << a << ' '; });
    std::cout << endl;
    for_each(a.arc_begin(), a.arc_end(),
             [](const pair<string, string> &a) { cout << a.first << "->" << a.second << endl; });
    //Как оказалось при ипользовании ссылок всё идёт не так как задумывалось,прошу сделать подсказу,где я допустил ошибку,т.к. сохранить привязку рёбер к узлам хочется.
}

void hyper_graph_test() {
    cout << "Hyper_graph:\n";
    hyper_graph<string> a;
    a.add_node("1");
    a.add_node("2");
    a.add_node("3");
    a.add_node("4");
    a.add_node("5");
    a.add_node("6");
    a.add_arc({"1", "2", "3"});
    a.add_arc({"6", "4", "5"});
    a.add_arc({"2", "4", "5"});
    a.add_arc({"1", "4", "3"});
    for_each(a.node_begin(), a.node_end(), [](string a) { cout << a << ' '; });
    std::cout << endl;
    for_each(a.arc_begin(), a.arc_end(), [](vector<string> nodes) { print_hyper_graph_edge(nodes); });
    std::cout << "incidence to 6 " ; print_hyper_graph_edge(incidence_find(a,"6"));
    std::cout << "After deleting:\n";
    a.node_erase("1");
    a.arc_erase(hyper_graph<string>::arc_find(a)({"4", "5", "2"}));
    for_each(a.node_begin(), a.node_end(), [](string a) { cout << a << ' '; });
    std::cout << endl;
    for_each(a.arc_begin(), a.arc_end(), [](vector<string> nodes) { print_hyper_graph_edge(nodes); });
    //Тут ничего не ломается,но и дуги никак не связаны с вершинами :C
};


