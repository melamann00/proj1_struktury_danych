#include <iostream>
#include <stdexcept>
#include <string>
#include <chrono>
using namespace std::chrono;
using namespace std;

template<typename T>
class LinkedList {
    struct Node {
        T data;
        Node* next;
        Node(const T& val) : data(val), next(nullptr) {}
    };
    Node* head;
    int size;
public:
    LinkedList() : head(nullptr), size(0) {}
    ~LinkedList(){
        while (head){
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }
    }
    //Dodawanie na początek
    void addFront(const T& val){
        Node* node = new Node(val);
        node->next = head;
        head = node;
        size++;
    }
    //Dodawanie na koniec
    void addBack(const T& val) {
        Node* node = new Node(val);
        if (!head){
            head = node;
        }
        else {
            Node* cur = head;
            while (cur->next){
                cur = cur->next;
            }
            cur->next = node;
        }
        size++;
    }
    //Dodawanie na indeks
    void addAt(int index, const T& val) {
        if (index < 0 || index > size)
            throw out_of_range("Index out of range");
        if (index == 0){
            addFront(val);
            return;
        }
        Node* cur = head;
        for (int i = 0; i < index - 1; i++){
            cur = cur->next;
        }
        Node* node = new Node(val);
        node->next = cur->next;
        cur->next = node;
        size++;
    }
    //Usuwanie z początku
    void removeFront() {
        if (!head){
            throw underflow_error("Empty list error");
        }
        Node* tmp = head;
        head = head->next;
        delete tmp;
        size--;
    }
    //Usuwanie z końca
    void removeBack() {
        if (!head){
            throw underflow_error("Empty list error");
        }
        if (!head->next){
            delete head;
            head = nullptr;
            size--;
            return;
        }
        Node* cur = head;
        while (cur->next->next){
            cur = cur->next;
        }
        delete cur->next;
        cur->next = nullptr;
        size--;
    }
    //Usuwanie z indeksu
    void removeAt(int index) {
        if (index < 0 || index >= size){
            throw out_of_range("Index out of range");
        }
        if (index == 0){
            removeFront();
            return;
        }
        Node* cur = head;
        for (int i = 0; i < index - 1; i++){
            cur = cur->next;
        }
        Node* tmp = cur->next;
        cur->next = tmp->next;
        delete tmp;
        size--;
    }
    //Wyszukiwanie
    int find(const T& val) const {
        Node* cur = head;
        int idx = 0;
        while (cur){
            if (cur->data == val){ 
                return idx;
            }
            cur = cur->next;
            idx++;
        }
        return -1;
    }
    int getSize() const {
        return size;
    }
    void print() const {
        Node* cur = head;
        cout << "[";
        while (cur){
            cout << cur->data;
            if (cur->next){
                cout << ", ";
            }
            cur = cur->next;
        }
        cout << "]\n";
    }
};
template<typename T>
class DynamicArray {
    T* data;
    int size;
    int capacity;
    void resize() {
        capacity *= 2;
        T* newData = new T[capacity];
        for (int i = 0; i < size; i++){
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }
public:
    DynamicArray(int initialCapacity = 4): size(0), capacity(initialCapacity) {
        data = new T[capacity];
    }
    ~DynamicArray(){
        delete[] data;
    }
    //Dodawanie na początek
    void addFront(const T& val) {
        if (size == capacity){
            resize();
        }
        for (int i = size; i > 0; i--){
            data[i] = data[i - 1];
        }
        data[0] = val;
        size++;
    }
    //Dodawanie na koniec
    void addBack(const T& val) {
        if (size == capacity){
            resize();
        }
        data[size++] = val;
    }
    //Dodawanie na indeks
    void addAt(int index, const T& val) {
        if (index < 0 || index > size){
            throw out_of_range("Indeks poza zakresem");
        }
        if (size == capacity){
            resize();
        }
        for (int i = size; i > index; i--){
            data[i] = data[i - 1];
        }
        data[index] = val;
        size++;
    }
    //Usuwanie z początku
    void removeFront() {
        if (size == 0){
            throw underflow_error("Tablica jest pusta");
        }
        for (int i = 0; i < size - 1; i++){
            data[i] = data[i + 1];
        }
        size--;
    }
    //Usuwanie z końca
    void removeBack() {
        if (size == 0){
            throw underflow_error("Tablica jest pusta");
        }
        size--;
    }
    //Usuwanie z indeksu
    void removeAt(int index) {
        if (index < 0 || index >= size){
            throw out_of_range("Indeks poza zakresem");
        }
        for (int i = index; i < size - 1; i++){
            data[i] = data[i + 1];
        }
        size--;
    }
    //Wyszukiwanie
    int find(const T& val) const {
        for (int i = 0; i < size; ++i){
            if (data[i] == val){
                return i;
            }
        }
        return -1;
    }
    int getSize() const{
        return size;
    }
    int getCapacity() const{
        return capacity;
    }
    void print() const {
        cout << "[";
        for (int i = 0; i < size; ++i) {
            cout << data[i];
            if (i < size - 1){
                cout << ", ";
            }
        }
        cout<<"]\n";
    }
};


void wysw() {
    cout<<"Lista wiązana\n";
    LinkedList<int> list;
    {
    auto start = high_resolution_clock::now();
    list.addBack(10);
    list.addBack(20);
    list.addBack(30);
    auto time = duration_cast<nanoseconds>(high_resolution_clock::now()- start).count();
    cout << "addBack(10,20,30): "; 
    list.print();
    cout<<"Czas wykonania: "<<time<<" ns"<<endl;
    }{
    auto start = high_resolution_clock::now();
    list.addFront(5);
    auto time = duration_cast<nanoseconds>(high_resolution_clock::now()- start).count();
    cout << "addFront(5): "; 
    list.print();
    cout<<"Czas wykonania: "<<time<<" ns"<<endl;
    }{
    auto start = high_resolution_clock::now();
    list.addAt(2, 15);
    auto time = duration_cast<nanoseconds>(high_resolution_clock::now()- start).count();
    cout << "addAt(2,15): "; 
    list.print();
    cout<<"Czas wykonania: "<<time<<" ns"<<endl;
    }{
    auto start = high_resolution_clock::now();
    list.removeFront();
    auto time = duration_cast<nanoseconds>(high_resolution_clock::now()- start).count();
    cout << "removeFront(): "; 
    list.print();
    cout<<"Czas wykonania: "<<time<<" ns"<<endl;
    }{
    auto start = high_resolution_clock::now();
    list.removeBack();
    auto time = duration_cast<nanoseconds>(high_resolution_clock::now()- start).count();
    cout << "removeBack(): "; 
    list.print();
    cout<<"Czas wykonania: "<<time<<" ns"<<endl;
    }{
    auto start = high_resolution_clock::now();
    list.removeAt(1);
    auto time = duration_cast<nanoseconds>(high_resolution_clock::now()- start).count();
    cout<< "removeAt(1): "; 
    list.print();
    cout<<"Czas wykonania: "<<time<<" ns"<<endl;
    }{
    auto start = high_resolution_clock::now();
    int a = list.find(10);
    auto time = duration_cast<nanoseconds>(high_resolution_clock::now()- start).count();
    cout<<"find(10) = "<<a<<endl;
    cout<<"Czas wykonania: "<<time<<" ns"<<endl;
    }{
    auto start = high_resolution_clock::now();
    int b = list.find(99);
    auto time = duration_cast<nanoseconds>(high_resolution_clock::now()- start).count();
    cout<<"find(99) = "<<b<<endl;
    cout<<"Czas wykonania: "<<time<<" ns"<<endl;
    }
    cout<< "Tablica dynamiczna\n";
    DynamicArray<int> arr(4);
    {
    auto start = high_resolution_clock::now();
    arr.addBack(10);
    arr.addBack(20);
    arr.addBack(30);
    auto time = duration_cast<nanoseconds>(high_resolution_clock::now()- start).count();
    cout<< "addBack(10,20,30): ";
    arr.print();
    cout<<"Czas wykonania: "<<time<<" ns"<<endl;
    }{
    auto start = high_resolution_clock::now();
    arr.addFront(5);
    auto time = duration_cast<nanoseconds>(high_resolution_clock::now()- start).count();
    cout<< "addFront(5): ";
    arr.print();
    cout<<"Czas wykonania: "<<time<<" ns"<<endl;
    }{
    auto start = high_resolution_clock::now();
    arr.addAt(2, 15);
    auto time = duration_cast<nanoseconds>(high_resolution_clock::now()- start).count();
    cout<< "addAt(2,15): ";
    arr.print();
    cout<<"Czas wykonania: "<<time<<" ns"<<endl;
    }{
    auto start = high_resolution_clock::now();
    arr.addBack(40);
    arr.addBack(50);
    auto time = duration_cast<nanoseconds>(high_resolution_clock::now()- start).count();
    cout<< "addBack(40,50): ";
    arr.print();
    cout<<"Czas wykonania: "<<time<<" ns"<<endl;
    }{
    auto start = high_resolution_clock::now();
    arr.removeFront();
    auto time = duration_cast<nanoseconds>(high_resolution_clock::now()- start).count();
    cout<< "removeFront(): ";
    arr.print();
    cout<<"Czas wykonania: "<<time<<" ns"<<endl;
    }{
    auto start = high_resolution_clock::now();
    arr.removeBack();
    auto time = duration_cast<nanoseconds>(high_resolution_clock::now()- start).count();
    cout<< "removeBack(): ";
    arr.print();
    cout<<"Czas wykonania: "<<time<<" ns"<<endl;
    }{
    auto start = high_resolution_clock::now();
    arr.removeAt(1);
    auto time = duration_cast<nanoseconds>(high_resolution_clock::now()- start).count();
    cout<< "removeAt(1): ";
    arr.print();
    cout<<"Czas wykonania: "<<time<<" ns"<<endl;
    }{
    auto start = high_resolution_clock::now();
    int a = arr.find(10);
    auto time = duration_cast<nanoseconds>(high_resolution_clock::now()- start).count();
    cout<<"find(10) = "<<a<<endl;
    cout<<"Czas wykonania: "<<time<<" ns"<<endl;
    }{
    auto start = high_resolution_clock::now();
    int b = arr.find(99);
    auto time = duration_cast<nanoseconds>(high_resolution_clock::now()- start).count();
    cout<<"find(99) = "<<b<<endl;
    cout<<"Czas wykonania: "<<time<<" ns"<<endl;
    }
}

int main() {
    wysw();
    return 0;
}