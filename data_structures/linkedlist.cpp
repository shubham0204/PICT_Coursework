#include <iostream>
#include <memory>

class ListNode {
    public:
    int val = 0;
    ListNode* next = nullptr;
    ListNode* prev = nullptr;
};

class LinkedList {

    protected:
    ListNode* head = nullptr;
    ListNode* tail = nullptr;

    public:

    virtual void insert(int element) = 0;
    virtual void remove(int element) = 0;

    void print() {
        ListNode* curr_node = head;
        while (curr_node != nullptr) {
            std::cout << curr_node -> val << ' ';
            curr_node = curr_node -> next;
        }
        std::cout << '\n';
    }

    ~LinkedList() {
        ListNode* curr_node = head;
        while (curr_node != nullptr) {
            ListNode* temp = curr_node -> next;
            delete curr_node;
            curr_node = temp;
        }
    }

};

class SinglyLinkedList: public LinkedList {

    public:

    void insert(int element) override {
        if (head == nullptr) {
            head = new ListNode();
            head -> val = element;
            tail = head;
        }
        else {
            ListNode* new_node = new ListNode();
            new_node -> val = element;
            tail -> next = new_node;
            tail = new_node;
        }
    }

    void remove(int element) override {
        ListNode* prev_node = nullptr;
        ListNode* curr_node = head;
        while (curr_node != nullptr) {
            if (curr_node -> val == element) {
                prev_node -> next = curr_node -> next;
                delete curr_node;
                break;
            }
            prev_node = curr_node;
            curr_node = curr_node -> next;
        }
    }

};

class DoublyLinkedList: public LinkedList {

    public:

    void insert(int element) {
        if (head == nullptr) {
            head = new ListNode();
            head -> val = element;
            tail = head;
        }
        else {
            ListNode* new_node = new ListNode();
            new_node -> val = element;
            new_node -> prev = tail;
            tail -> next = new_node;
            tail = new_node;
        }
    }

    void remove(int element) override {
        ListNode* prev_node = nullptr;
        ListNode* curr_node = head;
        while (curr_node != nullptr) {
            if (curr_node -> val == element) {
                prev_node -> next = curr_node -> next;
                curr_node -> next -> prev = prev_node;
                delete curr_node;
                break;
            }
            prev_node = curr_node;
            curr_node = curr_node -> next;
        }
    }

};

int main(int argc, char* argv[]) {
    std::unique_ptr<LinkedList> list1 = std::make_unique<SinglyLinkedList>(SinglyLinkedList());
    std::unique_ptr<LinkedList> list2 = std::make_unique<DoublyLinkedList>(DoublyLinkedList());

    for (int i = 0; i < 5; i++) {
        list1 -> insert(i);
        list2 -> insert(i);
    }

    list1 -> print();
    list2 -> print();

    list1 -> remove(3);
    list2 -> remove(4);

    list1 -> print();
    list2 -> print();

    return 0;
}