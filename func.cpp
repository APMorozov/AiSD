#include "Graph.h"

template<class Value, class Distance = double>
Vertex<Value, Distance> find_most_remote_clinic(const Graph<Value, Distance>& graph) {
    if (graph.order() == 0) {
        throw ("Graph is empty");
    }

    Vertex<Value, Distance> most_remote;
    Distance max_avg_distance = -1;
    bool found = false;

    graph.walk(graph.get_any_vertex(), [&](const Vertex<Value, Distance>& vertex) {
        Distance total_distance = 0;
        size_t edge_count = 0;

        for (const auto& edge : *(vertex.Edges)) {
            total_distance += edge.weight;
            edge_count++;
        }

        if (edge_count > 0) {
            Distance avg_distance = total_distance / edge_count;

            if (avg_distance > max_avg_distance || !found) {
                max_avg_distance = avg_distance;
                most_remote = vertex;
                found = true;
            }
        }
        });

    if (!found) {
        throw ("No edges found in graph");
    }

    return most_remote;
}