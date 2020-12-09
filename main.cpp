
#include "Graph.h"
#include "Hyper_graph.h"
#include <algorithm>

using namespace std;

void graph_test();

void hyper_graph_test();

void print_hyper_graph_edge(const vector<int> &to_print) {
    cout << '{';
    for (int i = 0; i < to_print.size() - 1; i++)
        cout << to_print[i] << ',';
    cout << to_print[to_print.size() - 1] << "}\n";
}

int main() {
    graph_test();
    hyper_graph_test();
}

void graph_test() {
    cout << "Graph:\n";
    graph<int> a;
    a.add_node(1);
    a.add_node(2);
    a.add_node(3);
    a.add_node(4);
    a.add_arc(1, 2);
    a.add_arc(3, 2);
    a.add_arc(4, 1);
    a.add_arc(1, 3);
    for_each(a.node_begin(), a.node_end(), [](int a) { cout << a << ' '; });
    std::cout << endl;
    for_each(a.arc_begin(), a.arc_end(), [](pair<int, int> a) { cout << a.first << "->" << a.second << endl; });;
    a.arc_erase(a.arc_find(3, 2));
    std::cout << "After deleting:\n";
    for_each(a.node_begin(), a.node_end(), [](int a) { cout << a << ' '; });
    std::cout << endl;
    for_each(a.arc_begin(), a.arc_end(), [](pair<int, int> a) { cout << a.first << "->" << a.second << endl; });
    //Как оказалось при ипользовании ссылок всё идёт не так как задумывалось,прошу сделать подсказу,где я допустил ошибку,т.к. сохранить привязку рёбер к узлам хочется.
}

void hyper_graph_test() {
    cout << "Hyper_graph:\n";
    hyper_graph<int> a;
    a.add_node(1);
    a.add_node(2);
    a.add_node(3);
    a.add_node(4);
    a.add_node(5);
    a.add_node(6);
    a.add_arc({1, 2, 3});
    a.add_arc({6, 4, 5});
    a.add_arc({2, 4, 5});
    a.add_arc({1, 2, 3});
    for_each(a.node_begin(), a.node_end(), [](int a) { cout << a << ' '; });
    std::cout << endl;
    for_each(a.arc_begin(), a.arc_end(), [](vector<int> nodes) { print_hyper_graph_edge(nodes); });
    std::cout << "After deleting:\n";
    a.node_erase(1);
    a.arc_erase(a.arc_find({4, 5, 2}));
    for_each(a.node_begin(), a.node_end(), [](int a) { cout << a << ' '; });
    std::cout << endl;
    for_each(a.arc_begin(), a.arc_end(), [](vector<int> nodes) { print_hyper_graph_edge(nodes); });
    //Тут ничего не ломается,но и дуги никак не связаны с вершинами :C
};


