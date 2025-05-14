#pragma once
#include <set>
#include <list>
#include <map>
#include <vector>
#include <functional>
#include <queue>
#include <iostream>
#include "HashTable.h"  // Используйте относительные пути

template<class Value, class Distance = double>
struct Vertex;

template<class Value, class Distance = double>
struct Edge {
    Vertex<Value, Distance>* adjacentVertex;
    Distance weight;
    Edge(Vertex<Value, Distance>* adjacentNode, Distance wight)
        : adjacentVertex(adjacentNode), weight(wight) {
    }

    bool operator<(const Edge<Value, Distance>& other) const {
        if (this->adjacentVertex != other.adjacentVertex)
            return this->adjacentVertex < other.adjacentVertex;
        return this->weight < other.weight;
    }
};

template <class Value, class Distance = double>
struct Vertex {
    Value value;
    std::set<Edge<Value, Distance>>* Edges;

    Vertex(Value val) : value(val), Edges(new std::set<Edge<Value, Distance>>{}) {}
    Vertex() : value({}), Edges(new std::set<Edge<Value, Distance>>{}) {}

    bool operator<(const Vertex<Value, Distance>& other) const {
        return this->value < other.value;
    }

    bool operator!=(const Vertex<Value, Distance>& other) const {
        return this->value != other.value;
    }
    bool operator==(const Vertex<Value, Distance>& other) const {
        return this->value == other.value;
    }
};

template<class Value, class Distance>
std::ostream& operator<<(std::ostream& stream, const Edge<Value, Distance>& edge) {
    stream << "Weight: " << edge.weight << " AdjacentVertex: " << edge.adjacentVertex->value;
    return stream;
}

template<class Value, class Distance>
std::ostream& operator<<(std::ostream& stream, const Vertex<Value, Distance>& vertex) {
    //stream << " " << vertex.value;
    for (auto it = vertex.Edges->begin(); it != vertex.Edges->end(); ++it) {
        stream << " Edge (" << it->adjacentVertex->value << ", " << it->weight <<")";
    }
    return stream;
}

template<class Value, class Distance>
class Graph {
private:
    HashTable<Value, Vertex<Value, Distance>, std::list<Node<Value, Vertex<Value, Distance>>>> _verteces;
public:
    Graph(): _verteces(15){}

    Graph(size_t size): _verteces(size){}

    ~Graph() = default;

    Graph(const Graph<Value, Distance>& other) = default;

    bool has_vertex(const Vertex<Value, Distance>& vertex) const{
       return this->_verteces.contains(vertex);
    }

    bool add_vertex(const Vertex<Value, Distance>& vertex) {
        if (this->has_vertex(vertex)) {
            return false;
        }
        this->_verteces.insert(vertex.value, vertex);
        return true;
    }

    void print() {
        for (size_t outer_idx = 0; outer_idx < _verteces.getDefaultSize(); ++outer_idx) {
            std::cout << outer_idx << " ";
            for (auto inner_it = _verteces[outer_idx].begin(); inner_it != _verteces[outer_idx].end(); ++inner_it) {
                std::cout << *inner_it << " ";
            }
            std::cout << std::endl;
        }
    }

    bool remove_vertex(const Vertex<Value, Distance>& vertex) {
        if (this->has_vertex(vertex)) {
            for (size_t outer_idx = 0; outer_idx < _verteces.getDefaultSize(); ++outer_idx) {
                for (auto inner_it = _verteces[outer_idx].begin(); inner_it != _verteces[outer_idx].end(); ++inner_it) {
                    auto set_it_end = inner_it->value.Edges->end();
                    for (auto set_it = inner_it->value.Edges->begin(); set_it != set_it_end;) {
                        if (vertex.value == set_it->adjacentVertex->value) {
                            set_it = inner_it->value.Edges->erase(set_it);
                        }
                        else {
                            ++set_it;
                        }
                    }
                }

            }
            _verteces.erase(vertex.value);
            return true;
        }
        return false;
    }

    void add_edge(Vertex<Value, Distance>& from, Vertex<Value, Distance>& to,Distance distance) {
        if (this->has_vertex(from) && this->has_vertex(to)) {
            const Vertex<Value, Distance>* data =  _verteces.search(from.value);
            Edge<Value, Distance> new_edge(&to, distance);
            data->Edges->insert(new_edge);
            _verteces.insert_or_assign(from.value, *data);
        }
    }

    bool remove_edge(const Vertex<Value, Distance>& from, const Vertex<Value, Distance>& to) {
        if (!has_vertex(from) || !has_vertex(to)) {
            return false;
        }

        const Vertex<Value, Distance>* from_vertex = _verteces.search(from.value);
        if (!from_vertex) return false;

        bool removed = false;
        for (auto it = from_vertex->Edges->begin(); it != from_vertex->Edges->end(); ) {
            if (it->adjacentVertex->value == to.value) {
                it = from_vertex->Edges->erase(it);
                removed = true;
            }
            else {
                ++it;
            }
        }

        return removed;
    }

    bool remove_edge(Vertex<Value,Distance>& from,const Edge<Value, Distance>& e) {
        if (!e.adjacentVertex) return false;

        const Vertex<Value, Distance>* from_vertex = _verteces.search(from.value);
        if (!from_vertex) return false;

        auto it = from_vertex->Edges->find(e);
        if (it != from_vertex->Edges->end()) {
            from_vertex->Edges->erase(it);
            return true;
        }
        return false;
    }

    bool has_edge(const Vertex<Value, Distance>& from, const Vertex<Value, Distance>& to) const {
        if (!has_vertex(from) || !has_vertex(to)) {
            return false;
        }

        const Vertex<Value, Distance>* from_vertex = _verteces.search(from.value);
        if (!from_vertex) return false;

        for (const auto& edge : *(from_vertex->Edges)) {
            if (edge.adjacentVertex->value == to.value) {
                return true;
            }
        }
        return false;
    }

    bool has_edge(const Vertex<Value, Distance>& from, const Edge<Value, Distance>& e) const {
        if (!e.adjacentVertex) return false;

        const Vertex<Value, Distance>* from_vertex = _verteces.search(from.value);
        if (!from_vertex) return false;

        return from_vertex->Edges->count(e) > 0;
    }

    std::vector<Edge<Value, Distance>> edges(const Vertex<Value, Distance>& vertex) const {
        std::vector<Edge<Value, Distance>> result;
        if (!has_vertex(vertex)) return result;

        const Vertex<Value, Distance>* v = _verteces.search(vertex.value);
        if (v) {
            for (const auto& edge : *(v->Edges)) {
                result.push_back(edge);
            }
        }
        return result;
    }

    size_t degree(const Vertex<Value, Distance>& v) const {
        if (!has_vertex(v)) return 0;

        size_t out_degree = 0;
        size_t in_degree = 0;

        const Vertex<Value, Distance>* vertex = _verteces.search(v.value);
        if (vertex) {
            out_degree = vertex->Edges->size();
        }

        for (size_t i = 0; i < _verteces.getDefaultSize(); ++i) {
            for (const auto& node : _verteces[i]) {
                for (const auto& edge : *(node.value.Edges)) {
                    if (edge.adjacentVertex->value == v.value) {
                        in_degree++;
                    }
                }
            }
        }

        return out_degree + in_degree;
    }

    size_t order() const {
        return _verteces.getCurrentSize();
    }

    bool is_connected() const {
        if (_verteces.getDefaultSize() == 0) return true;

        for (size_t i = 0; i < _verteces.getDefaultSize(); ++i) {
            for (const auto& node : _verteces[i]) {
                std::set<Value> visited;
                std::list<Value> queue;

                visited.insert(node.value.value);
                queue.push_back(node.value.value);

                while (!queue.empty()) {
                    Value current = queue.front();
                    queue.pop_front();

                    const Vertex<Value, Distance>* current_vertex = _verteces.search(current);
                    if (!current_vertex) continue;

                    for (const auto& edge : *(current_vertex->Edges)) {
                        if (visited.count(edge.adjacentVertex->value) == 0) {
                            visited.insert(edge.adjacentVertex->value);
                            queue.push_back(edge.adjacentVertex->value);
                        }
                    }
                }

                if (visited.size() != _verteces.getCurrentSize()) {
                    return false;
                }
            }
        }
        return true;
    }

    std::vector<Edge<Value, Distance>> shortest_path(const Vertex<Value, Distance>& from,
        const Vertex<Value, Distance>& to) const {
        std::vector<Edge<Value, Distance>> path;
        if (!has_vertex(from) || !has_vertex(to)) return path;


        std::map<Value, Distance> distances;
        std::map<Value, Value> previous;

        for (size_t i = 0; i < _verteces.getDefaultSize(); ++i) {
            for (const auto& node : _verteces[i]) {
                distances[node.value.value] = std::numeric_limits<Distance>::max();
            }
        }
        distances[from.value] = 0;

        for (size_t i = 1; i < _verteces.getDefaultSize(); ++i) {
            for (size_t j = 0; j < _verteces.getDefaultSize(); ++j) {
                for (const auto& node : _verteces[j]) {
                    const Vertex<Value, Distance>* u = &node.value;
                    for (const auto& edge : *(u->Edges)) {
                        Value v = edge.adjacentVertex->value;
                        Distance weight = edge.weight;

                        if (distances[u->value] != std::numeric_limits<Distance>::max() &&
                            distances[u->value] + weight < distances[v]) {
                            distances[v] = distances[u->value] + weight;
                            previous[v] = u->value;
                        }
                    }
                }
            }
        }

        for (size_t j = 0; j < _verteces.getDefaultSize(); ++j) {
            for (const auto& node : _verteces[j]) {
                const Vertex<Value, Distance>* u = &node.value;
                for (const auto& edge : *(u->Edges)) {
                    Value v = edge.adjacentVertex->value;
                    Distance weight = edge.weight;

                    if (distances[u->value] != std::numeric_limits<Distance>::max() &&
                        distances[u->value] + weight < distances[v]) {
                        throw "negative cycle";
                    }
                }
            }
        }

        Value current = to.value;
        while (previous.count(current)) {
            Value prev = previous[current];
            const Vertex<Value, Distance>* prev_vertex = _verteces.search(prev);
            if (!prev_vertex) break;

            for (const auto& edge : *(prev_vertex->Edges)) {
                if (edge.adjacentVertex->value == current) {
                    path.push_back(edge);
                    break;
                }
            }
            current = prev;
        }

        std::reverse(path.begin(), path.end());
        return path;
    }

    void walk(const Vertex<Value, Distance>& start_vertex,
        std::function<void(const Vertex<Value, Distance>&)> action) const {
        if (!has_vertex(start_vertex)) return;

        std::set<Value> visited;
        std::queue<Value> q;

        visited.insert(start_vertex.value);
        q.push(start_vertex.value);

        while (!q.empty()) {
            Value current = q.front();
            q.pop();

            const Vertex<Value, Distance>* current_vertex = _verteces.search(current);
            if (!current_vertex) continue;

            action(*current_vertex);

            for (const auto& edge : *(current_vertex->Edges)) {
                if (visited.count(edge.adjacentVertex->value) == 0) {
                    visited.insert(edge.adjacentVertex->value);
                    q.push(edge.adjacentVertex->value);
                }
            }
        }
    }

    Vertex<Value, Distance> get_any_vertex() const {
        for (size_t i = 0; i < _verteces.getDefaultSize(); ++i) {
            if (!_verteces[i].empty()) {
                return _verteces[i].front().value;
            }
        }
        throw ("Graph is empty");
    }

};