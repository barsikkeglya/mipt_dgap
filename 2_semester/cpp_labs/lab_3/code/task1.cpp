#include <iostream>

struct LinkedList{
    int data;
    LinkedList *next;
};

LinkedList* insert_after(LinkedList * const current){
    if (current == nullptr){
        return new LinkedList{0,nullptr};
    }  
    LinkedList* new_node = new LinkedList{0,current->next};
    current->next = new_node;
    return new_node;
}

LinkedList* remove_after(LinkedList * const current){
    if (nullptr == current or current->next == nullptr){
        return nullptr;
    }
    LinkedList* new_next = current->next->next;
    delete current->next;
    current->next = new_next;
    return current->next;
}

void erase(LinkedList * const head){
    while (head->next != nullptr){
        head->next = remove_after(head);
    }
    delete head;
}

LinkedList* reverse_rec(LinkedList * const head){
    if (head->next != nullptr){
        LinkedList* tmp = head->next;
        LinkedList* n = reverse_rec(tmp);
        tmp->next = head;
        head->next = nullptr;
        return n;
    }
}

LinkedList* reverse_itr(LinkedList * const head){
    LinkedList* current = head;
    LinkedList* tmp = head -> next;
    head->next = nullptr;
    while(tmp != nullptr){
        LinkedList* previous = current;
        current = tmp;
        tmp = current -> next;
        current -> next = previous;
    }
    return current;
}

#define length 10

int main(){
    int i = 0;
    auto current = insert_after(nullptr);
    auto first = current;
    current -> data = 0;
    i++;

    while (i < length){
        current = insert_after(current);
        current -> data = i;
        i++;
    }

    current = first;

    while (current != nullptr){
        std::cout << current -> data << " ";
        current = current -> next;
    }

    std::cout << "\n\n";

    remove_after(first->next->next);
    current = first;

    while (current != nullptr){
        std::cout << current -> data << " ";
        current = current -> next;
    }

    std::cout << "\n\n";

    first = reverse_itr(first);
    current = first;

    while (current != nullptr){
        std::cout << current -> data << " ";
        current = current -> next;
    }

    std::cout << "\n\n";

    first = reverse_rec(first);
    current = first;

    while (current != nullptr){
        std::cout << current -> data << " ";
        current = current -> next;
    }
    return 0;

}