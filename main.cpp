#include<iostream>
#include<cassert>
#include <stdexcept>
#include<vector>
using namespace std;

class empty_node_error:public exception {
public:
    const char* what() const throw() {
        return "! Node which we are trying to delete is empty !";
    }
};

class FullNodeException:public exception {
public:
    const char* what() const throw() {
        return "The node you are trying to insert is full.";
    }
};

template <typename T>
class Node {
public:
    Node<T>* L;
    Node<T>* R;
    Node<T>* C;
    T key;

    Node(T k):key(k),L(nullptr),R(nullptr),C(nullptr) {}

    bool isFull() {
        return L && R && C;
    }

    bool isEmpty() {
        return !L && !R && !C;
    }
};

template <typename T>
class QST {
private:
    Node<T>* root;
    Node<T>* insert(Node<T>* node, T key) 
    {
        if (node == nullptr) {
            return new Node<T>(key);
        }

        if (key < node->key) {
            node->L = insert(node->L, key);
        } else if (key > node->key) {
            node->R = insert(node->R, key);
        } else {
            throw runtime_error("Element already present");
        }
        if (node->L && node->R && !node->C) {
            node->C = node->L;
            node->L = nullptr;
        }

        return node;
    }

    Node<T>* deleteNode(Node<T>* node, T key) {
        if (node == nullptr) {
            throw empty_node_error();
        }

        if (key < node->key) {
            node->L = deleteNode(node->L, key);
        } else if (key > node->key) {
            node->R = deleteNode(node->R, key);
        } else {
            if(node->L||node->R||node->C) {
                if (node->L) {
                    node->L=delete_max_value(node->L);
                } else if(node->R) 
                {
                    node->R=delete_min_value(node->R);
                } else {
                    node->C=delete_max_value(node->C);
                }
            } 
            else {
                delete node;
                return nullptr;
            }
        }
        return node;
    }

    Node<T>* delete_min_value(Node<T>* node) 
    {
        if (node->L == nullptr) 
        {
            Node<T>* temp = node->R;
            delete node;
            return temp;
        }

        node->L = delete_min_value(node->L);
        return node;
    }

    Node<T>* delete_max_value(Node<T>* node) 
    {
        if (node->R == nullptr) {
            Node<T>* temp=node->L;
            delete node;
            return temp;
        }

        node->R=delete_max_value(node->R);
        return node;
    }

    void ppreoder(Node<T>* node) {
        if (node == nullptr) {
            return;
        }

        cout<<node->key<<" ";
        ppreoder(node->L);
        ppreoder(node->R);
        ppreoder(node->C);
    }

    void ppostorder(Node<T>* node) {
        if (node == nullptr) {
            return;
        }

        ppostorder(node->L);
        ppostorder(node->R);
        ppostorder(node->C);
        cout << node->key << " ";
    }

public:
    QST():root(nullptr) {}

    void insert(T key) {
        root=insert(root, key);
    }

    void deleteNode(T key) {
        root=deleteNode(root, key);
    }

    void ppreoder() {
        ppreoder(root);
        cout<<endl;
    }

    void ppostorder() {
        ppostorder(root);
        cout<<endl;
    }
};

int main() {
    QST<int> qst;

    while (1) {
        cout<<"**********************"<<endl;
        cout<<"1.Insert element"<<endl;
        cout<<"2.Delete element"<<endl;
        cout<<"3.Preorder traversal"<<endl;
        cout<<"4.Postorder traversal"<<endl;
        cout<<"5.Quit"<<endl;
        cout<<"Enter your choice: ";

        int n;
        cin>>n;

        switch(n) 
        {
            case 1:
                int key;
                cout<<"Enter element to insert: ";
                cin>>key;
                qst.insert(key);
                break;
            case 2:
                cout<<"Enter Element to delete: ";
                cin>>key;
                qst.deleteNode(key);
                break;
            case 3:
                cout<<"Preorder traversal: ";
                qst.ppreoder();
                break;
            case 4:
                cout<<"Postorder traversal: ";
                qst.ppostorder();
                break;
            case 5:
                return 0;
            default:
                cout<<"Invalid choice. Try again."<<endl;
        }
    }
}