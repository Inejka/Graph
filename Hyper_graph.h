//
// Created by inejka on 10.12.2020.
//

#ifndef GRAPH_HYPER_GRAPH_H
#define GRAPH_HYPER_GRAPH_H

#include <vector>
#include <iostream>

template<class type>
class hyper_graph {
protected:
    std::vector<type> nodes;
    std::vector<std::vector<type> > arcs;
public:
    typedef typename std::vector<std::vector<type> >::iterator arc_iterator;
    typedef typename std::vector<type>::iterator node_iterator;
    typedef typename std::vector<type>::const_iterator node_const_iterator;
    typedef typename std::vector<type>::reverse_iterator node_reverse_iterator;
    typedef typename std::vector<type>::const_reverse_iterator node_const_reverse_iterator;

    typedef typename std::vector<std::vector<type> >::const_iterator arc_const_iterator;
    typedef typename std::vector<std::vector<type> >::reverse_iterator arc_reverse_iterator;
    typedef typename std::vector<std::vector<type> >::const_reverse_iterator arc_const_reverse_iterator;

    node_iterator node_begin() noexcept {
        return nodes.begin();
    }

    node_iterator node_end() noexcept {
        return nodes.end();
    }

    arc_iterator arc_begin() noexcept {
        return arcs.begin();
    }

    arc_iterator arc_end() noexcept {
        return arcs.end();
    }

    class arc_find {
        hyper_graph<type> &grph;
    public:
        arc_find(hyper_graph<type> &grph) : grph(grph) {}

        arc_iterator operator()(const std::vector<type> &to_find) noexcept {
            for (arc_iterator tmp = grph.arcs.begin(); tmp != grph.arcs.end(); tmp++) {
                for (int i = 0; i <= to_find.size(); i++) {
                    if (i == to_find.size())return tmp;
                    bool is_found = false;
                    for (int j = 0; j < (*tmp).size(); j++)
                        if (to_find[i] == (*tmp)[j]) {
                            is_found = true;
                            break;
                        }
                    if (!is_found)break;
                }
            }
            return grph.arcs.end();
        }
    };


    class node_find {
        hyper_graph<type> &grph;
    public:
        node_find(hyper_graph<type> &grph) : grph(grph) {}

        node_iterator operator()(const type &to_search) noexcept {
            for (auto tmp = grph.nodes.begin(); tmp != grph.nodes.end(); tmp++)
                if (*tmp == to_search)return tmp;
            return grph.nodes.end();
        }
    };

    void add_node(const type &to_add) noexcept {
        if (node_find(*this)(to_add) != node_end())return;
        nodes.push_back(to_add);
    }

    void add_arc(std::vector<type> to_add) noexcept {
        for (auto &i:to_add)
            if (node_find(*this)(i) == node_end())return;
        arcs.push_back(std::move(to_add));
    }

    void clear() noexcept {
        arcs.clear();
        nodes.clear();
    }

    bool empty() noexcept {
        return nodes.empty();
    }

    unsigned long node_size() noexcept {
        return nodes.size();
    }

    unsigned long arc_size() noexcept {
        return arcs.size();
    }

    unsigned long node_capacity() noexcept {
        return nodes.capacity();
    }

    unsigned long arc_capacity() noexcept {
        return arcs.capacity();
    }

    void arc_erase(arc_iterator to_delete) noexcept {
        arcs.erase(to_delete);
    }

    void arc_erase(arc_iterator from, arc_iterator to) noexcept {
        arcs.erase(from, to);
    }

    void arc_erase(const type &to_delete) noexcept {
        for (auto i = arcs.begin(); i != arcs.end(); i++) {
            for (auto &j:*i)
                if (j == to_delete) {
                    arcs.erase(i);
                    i--;
                }
        }
    }

    void node_erase(node_iterator to_delete) noexcept {
        arc_erase(*to_delete);
        nodes.erase(to_delete);
    }

    void node_erase(node_iterator from, node_iterator to) noexcept {
        while (from != to) {
            arc_erase(*from);
            nodes.erase(from);
            from++;
        }
    }

    void node_erase(const type &to_delete) noexcept {
        node_erase(node_find(*this)(to_delete));
    }

    node_const_iterator node_cbegin() noexcept {
        return nodes.cbegin();
    }

    node_const_iterator node_cend() const noexcept {
        return nodes.cend();
    }

    node_reverse_iterator node_rbegin() noexcept {
        return nodes.rbegin();
    }

    node_reverse_iterator node_rend() noexcept {
        return nodes.rend();
    }

    node_const_reverse_iterator node_crbegin() const noexcept {
        return nodes.crbegin();
    }

    node_const_reverse_iterator node_crend() const noexcept {
        return nodes.crend();
    }

    arc_const_iterator arc_cbegin() const noexcept {
        return arcs.cbegin();
    }

    arc_const_iterator arc_cend() const noexcept {
        return arcs.cend();
    }

    arc_reverse_iterator arc_rbegin() noexcept {
        return arcs.rbegin();
    }

    arc_reverse_iterator arc_rend() noexcept {
        return arcs.rend();
    }

    arc_const_reverse_iterator arc_crbegin() const noexcept {
        return arcs.crbegin();
    }

    arc_const_reverse_iterator arc_crend() const noexcept {
        return arcs.crend();
    }


};

#endif //GRAPH_HYPER_GRAPH_H
