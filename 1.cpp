#include<iostream>
#include<cassert>
#include <stdexcept>
#include<vector>
using namespace std;


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
