#include "func.cpp"
#include <iostream>

int main() {
    Graph<std::string, double> cityMap(5);
    std::cout << "1. Created empty city graph" << std::endl;

    Vertex<std::string, double> clinic1("Central Hospital");
    Vertex<std::string, double> clinic2("North Clinic");
    Vertex<std::string, double> clinic3("South Clinic");

    cityMap.add_vertex(clinic1);
    cityMap.add_vertex(clinic2);
    cityMap.add_vertex(clinic3);
    std::cout << "2. Added 3 clinics to the map" << std::endl;
    std::cout << std::endl;
    cityMap.print();
    std::cout << std::endl;

    cityMap.add_edge(clinic1, clinic2, 3.5);
    cityMap.add_edge(clinic1, clinic3, 2.6);
    cityMap.add_edge(clinic2, clinic1, 2.2);
    cityMap.add_edge(clinic3, clinic1, 2.9);
    cityMap.add_edge(clinic2, clinic3, 13);

    std::cout << "3. Created connections between clinics" << std::endl;
    std::cout << std::endl;
    cityMap.print();
    std::cout << std::endl;


    std::cout << "4. Checking if 'North Clinic' exists: "
        << (cityMap.has_vertex(clinic2) ? "Yes" : "No") << std::endl;

    Edge<std::string, double> testEdge(&clinic2, 3.5);
    std::cout << "5. Checking connection from South to North: "
        << (cityMap.has_edge(clinic3, testEdge) ? "Exists" : "Missing") << std::endl;

    auto path = cityMap.shortest_path(clinic1, clinic3);
    std::cout << "6. Shortest path from Central to South:" << std::endl;
    for (const auto& edge : path) {
        std::cout << "   - " << edge.adjacentVertex->value << " (" << edge.weight << ")" << std::endl;
    }

    std::cout << "7. Walking through all clinics:" << std::endl;
    cityMap.walk(clinic1, [](const Vertex<std::string, double>& v) {
        std::cout << "   Visited: " << v.value << std::endl;

    });


    auto remote = find_most_remote_clinic(cityMap);
    std::cout << "8. Most remote clinic: " << remote.value << std::endl;
    
     std::cout << "9. Checking is connected graph: "
        << (cityMap.has_vertex(clinic2) ? "Yes" : "No") << std::endl;

    cityMap.remove_edge(clinic1, clinic3);
    std::cout << "10. Removed connection between Central and South" << std::endl;
    std::cout << std::endl;
    cityMap.print();
    std::cout << std::endl;

    cityMap.remove_vertex(clinic2);
    std::cout << "11. Removed North Clinic from the map" << std::endl;
    std::cout << std::endl;
    cityMap.print();
    std::cout << std::endl;
}