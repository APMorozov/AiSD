#pragma once
#include<vector>
#include<string>
#include <time.h> 
#include<iostream>
#include "Binnary_Tree.cpp"
#include <fstream>

static size_t lcg() {
	static size_t x = 0;
	x = (1021 * x + 24631) % 116640;
	return x;
}



static void measureVectorPerformance(size_t size) {
    double fillTime = 0.0;
    double searchTime = 0.0;
    double addRemoveTime = 0.0;

    for (int i = 0; i < 100; ++i) {
        std::vector<size_t> vec;
        clock_t start = clock();
        for (size_t j = 0; j < size; ++j) {
            vec.push_back(lcg());
        }
        clock_t end = clock();
        fillTime += (double)(end - start) / CLOCKS_PER_SEC;
    }
    fillTime /= 100.0;

    std::vector<size_t> vec;
    for (size_t i = 0; i < size; ++i) {
        vec.push_back(lcg());
    }
    for (int i = 0; i < 1000; ++i) {
        clock_t start = clock();
        auto result = std::find(vec.begin(), vec.end(), lcg());
        clock_t end = clock();
        searchTime += (double)(end - start) / CLOCKS_PER_SEC;
    }
    searchTime /= 1000.0;

    vec.clear();
    for (size_t i = 0; i < size; ++i) {
        vec.push_back(lcg());
    }
    for (int i = 0; i < 1000; ++i) {
        clock_t start = clock();
        vec.push_back(lcg());
        auto result = std::find(vec.begin(), vec.end(), lcg());
        if (result != vec.end()) {
            vec.erase(result);
        }
        clock_t end = clock();
        addRemoveTime += (double)(end - start) / CLOCKS_PER_SEC;
    }
    addRemoveTime /= 1000.0;

    std::ofstream file("C:\\Users\\moroz\\OneDrive\\Desktop\\2 kurs\\back\\Aisdd\\lab\\lab1_sem4\\AiSD\\timeVector.txt", std::ios_base::app);
    if (file.is_open()) {
        std::cout << "File Vector is open" << '\n';
        if (file.good()) {
            std::cout << "File is good" << '\n';
        }
        else {
            std::cout << "Error with file" << '\n';
        }

        file << "Size: " << size << std::endl;
        file << "Size: " << std::endl;
        file << "Average fill time: " << fillTime << " seconds" << std::endl;
        file << "Average search time: " << searchTime << " seconds" << std::endl;
        file << "Average add/remove time: " << addRemoveTime << " seconds" << std::endl;
        file << std::endl;

        file.flush(); // Сбрасываем буфер

        file.close();
    }
    else {
        std::cout << "Unable to open file" << '\n';
    }
}

// Функция для бинарного дерева
static void measureBinaryTreePerformance(size_t size) {
    double fillTime = 0.0;
    double searchTime = 0.0;
    double addRemoveTime = 0.0;

    for (int i = 0; i < 100; ++i) {
        Binnary_Tree<size_t> tree(0);
        clock_t start = clock();
        for (size_t j = 0; j < size; ++j) {
            tree.insert(lcg());
        }
        clock_t end = clock();
        fillTime += (double)(end - start) / CLOCKS_PER_SEC;
    }
    fillTime /= 100.0;

    Binnary_Tree<size_t> tree(0);
    for (size_t i = 0; i < size; ++i) {
        tree.insert(lcg());
    }
    for (int i = 0; i < 1000; ++i) {
        clock_t start = clock();
        tree.conteins(lcg());
        clock_t end = clock();
        searchTime += (double)(end - start) / CLOCKS_PER_SEC;
    }
    searchTime /= 1000.0;
    Binnary_Tree<size_t> tree1(0);
    tree = tree1;
    for (size_t i = 0; i < size; ++i) {
        tree.insert(lcg());
    }
    for (int i = 0; i < 1000; ++i) {
        clock_t start = clock();
        tree.insert(lcg());
        tree.erase(lcg());
        clock_t end = clock();
        addRemoveTime += (double)(end - start) / CLOCKS_PER_SEC;
    }
    addRemoveTime /= 1000.0;

    std::ofstream file("C:\\Users\\moroz\\OneDrive\\Desktop\\2 kurs\\back\\Aisdd\\lab\\lab1_sem4\\AiSD\\timeTree.txt", std::ios_base::app);
    if (file.is_open()) {
        std::cout << "File Vector is open" << '\n';
        if (file.good()) {
            std::cout << "File is good" << '\n';
        }
        else {
            std::cout << "Error with file" << '\n';
        }

        file << "Size: " << size << std::endl;
        file << "Average fill time: " << fillTime << " seconds" << std::endl;
        file << "Average search time: " << searchTime << " seconds" << std::endl;
        file << "Average add/remove time: " << addRemoveTime << " seconds" << std::endl;
        file << std::endl;

        file.flush(); // Сбрасываем буфер

        file.close();
    }
    else {
        std::cout << "Unable to open file" << '\n';
    }
}
template<class T>
std::vector<T> intersection(Binnary_Tree<T>& first, Binnary_Tree<T>& second) {
    std::vector<T> answer;
    for (auto it = first.begin(); it.hasNext(); ) {
        T buffer = it.next();
        if (second.conteins(buffer)) {
            answer.push_back(buffer);   
        }  
    }
    return answer;
}

template<class T>
std::vector<T> treeUnion(Binnary_Tree<T>& first, Binnary_Tree<T>& second) {
    std::vector<T> answer;
    for (auto it = first.begin(); it.hasNext(); ) {
        answer.push_back(it.next());
    }
    for (auto it = second.begin(); it.hasNext(); ) {
        T buffer = it.next();
        if (!(first.conteins(buffer))) {
            answer.push_back(buffer);
        }
    }
    return answer;
}
