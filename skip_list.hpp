
#ifndef SKIP_LIST_HPP
#define SKIP_LIST_HPP

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <climits>

template<typename T>
class SkipList {
private:
    struct Node {
        T value;
        std::vector<Node*> forward;
        
        Node(const T& val, int level) : value(val), forward(level + 1, nullptr) {}
    };
    
    Node* head;
    int max_level;
    int current_level;
    static const int DEFAULT_MAX_LEVEL = 32;
    static const double PROBABILITY;
    
    int random_level() {
        int level = 0;
        while ((static_cast<double>(rand()) / RAND_MAX) < PROBABILITY && level < max_level) {
            level++;
        }
        return level;
    }
    
public:
    SkipList() : max_level(DEFAULT_MAX_LEVEL), current_level(0) {
        srand(time(nullptr));
        head = new Node(T(), max_level);
    }
    
    ~SkipList() {
        Node* current = head->forward[0];
        while (current != nullptr) {
            Node* next = current->forward[0];
            delete current;
            current = next;
        }
        delete head;
    }
    
    void insert(const T & item) {
        std::vector<Node*> update(max_level + 1, nullptr);
        Node* current = head;
        
        for (int i = current_level; i >= 0; i--) {
            while (current->forward[i] != nullptr && current->forward[i]->value < item) {
                current = current->forward[i];
            }
            update[i] = current;
        }
        
        current = current->forward[0];
        
        if (current == nullptr || current->value != item) {
            int new_level = random_level();
            
            if (new_level > current_level) {
                for (int i = current_level + 1; i <= new_level; i++) {
                    update[i] = head;
                }
                current_level = new_level;
            }
            
            Node* new_node = new Node(item, new_level);
            
            for (int i = 0; i <= new_level; i++) {
                new_node->forward[i] = update[i]->forward[i];
                update[i]->forward[i] = new_node;
            }
        }
    }
    
    bool search(const T & item) {
        Node* current = head;
        
        for (int i = current_level; i >= 0; i--) {
            while (current->forward[i] != nullptr && current->forward[i]->value < item) {
                current = current->forward[i];
            }
        }
        
        current = current->forward[0];
        return current != nullptr && current->value == item;
    }
    
    void deleteItem(const T & item) {
        std::vector<Node*> update(max_level + 1, nullptr);
        Node* current = head;
        
        for (int i = current_level; i >= 0; i--) {
            while (current->forward[i] != nullptr && current->forward[i]->value < item) {
                current = current->forward[i];
            }
            update[i] = current;
        }
        
        current = current->forward[0];
        
        if (current != nullptr && current->value == item) {
            for (int i = 0; i <= current_level; i++) {
                if (update[i]->forward[i] != current) {
                    break;
                }
                update[i]->forward[i] = current->forward[i];
            }
            
            delete current;
            
            while (current_level > 0 && head->forward[current_level] == nullptr) {
                current_level--;
            }
        }
    }
};

template<typename T>
const double SkipList<T>::PROBABILITY = 0.5;

#endif
