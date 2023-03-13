#include "main.h"

class Queue {
private:
    table* front;
    table* rear;  
    int size; // <= MAXSIZE
public:
    Queue() : front(NULL), rear(NULL), size(0) {}
    ~Queue() {
        table* currTable = front;
        while (currTable != NULL) {
            table* temp = currTable;
            currTable = currTable->next;
            delete temp;
        }
    }
    void enQueue(int, string, int);
    void deQueue();
    int getSize(); 
    void getFront(table*);
    string toStringFront();
    void swapInfo(table*, table*);
    void selectionSort(int);
    void printQueue(int);
};

int Queue::getSize() {
    return this->size;
}

void Queue::enQueue(int ID, string name, int age) {
    if (this->size == MAXSIZE) {
        return;
    }
    table* newTable = new table(ID, name, age, NULL);

    if (this->size == 0) {
        this->front = newTable;
        this->rear = newTable;
        this->size++;
        return;
    }
    this->rear->next = newTable;
    this->rear = newTable;
    this->size++;
}

void Queue::deQueue() {
    if (this->size == 0) {
        return;
    }
    table* temp = this->front;
    this->front = this->front->next;
    delete temp;
    this->size--;
}

void Queue::getFront(table* t) {
    if (this->size == 0) {
        return;
    }
    
    t->name = front->name;
    t->age = front->age;

    deQueue();
}

string Queue::toStringFront() {
    string res = "";
    res += (front->ID == 0 ? "" : to_string(front->ID)  + " ") + front->name + " " + to_string(front->age);
    deQueue();
    return res;
}

void Queue::printQueue(int n) {
    if (n < 1 || n > MAXSIZE) {
        return;
    }

    if (this->size == 0) {
        cout << "Empty" << endl;
    }

    table* temp = this->front;
    for (int i = 0; i < n; i++) {
        if(temp == NULL) {
            return;
        }
        cout << temp->name << endl;
        temp = temp->next;
    }
}

void Queue::swapInfo(table* t1, table* t2) {
    swap(t1->ID, t2->ID);
    swap(t1->name, t2->name);
    swap(t1->age, t2->age);
}

void Queue::selectionSort(int n) {
    table* temp_head = front;
    while (temp_head != NULL) {
        if (n == 0) {
            return;
        }
        table* temp = temp_head;
        table* max_age = temp_head;
        while (temp != NULL) {
            if (temp->age > max_age->age) {
                max_age = temp;
            }
            temp = temp->next;
        }
        swapInfo(temp_head, max_age);
        n--;
        temp_head = temp_head->next;
    }
}

class Stack {
private:
    table* top;
    int size; // 1->2*MAXSIZE
public:
    Stack() : top(NULL), size(0) {}
    ~Stack() {
        table* currTable = top;
        while (currTable != NULL) {
            table* temp = currTable;
            currTable = currTable->next;
            delete temp;
        }
    }
    void push(table*);
    void popAt(string, int);
    void printStack(int);
    bool isExist(string, int);
    int getSize() {
        return this->size;
    }
};

void Stack::push(table* t) {
    if (size >= 2*MAXSIZE) {
        return;
    }
    table* temp = t;
    if (top == NULL) {
        temp->next = NULL;
        top = temp;
    } else {
        temp->next = top;
        top = temp;
    }
    size++;
}

void Stack::popAt(string name, int age) {
    if (size == 0) {
        return;
    }
    
    if (top->name == name && top->age == age) { // delete top
        table* temp = top;
        top = top->next;
        delete temp;
        size--;
        return;
    }
    table* pre_temp = top; // delete others
    while (pre_temp->next != NULL) {
        if (pre_temp->next->name == name && pre_temp->next->age == age) {
            table* temp = pre_temp->next;
            pre_temp->next = temp->next;
            delete temp;
            size--;
            return;
        }
        pre_temp = pre_temp->next;
    }
}

void Stack::printStack(int n) {
    if (n < 1 || n > 2*MAXSIZE) {
        return;
    }
    table* temp = top;
    for (int i = 0; i < n; i++) {
        if (temp == NULL) {
            return;
        }
        cout << temp->name << endl;
        temp = temp->next;
    }
}

bool Stack::isExist(string name, int age) {
    table* temp = top;
    while (temp != NULL) {
        if (temp->name == name && temp->age == age) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

bool checkID(string& ID) {
    if (ID.size() == 0) {
        ID = "0";
        return true;
    }
    if(stoi(ID) < 1 || stoi(ID) > MAXSIZE) {
            return false;
    } else {
        return true;
    }
    
}

bool checkAge(const string& age) {
    if(stoi(age) < 16 || stoi(age) > 115) {
        return false;
    } else {
        return true;
    }
}

bool checkNum(const string& num) {
    if(stoi(num) <= 0 || stoi(num) > MAXSIZE) {
        return false;
    } else {
        return true;
    }
}

int numberOfTables(restaurant* r) {
    int count = 0;
    table* temp = r->recentTable;
    do {
        count++;
        temp = temp->next;

    } while (temp != r->recentTable);
    return count;
}

bool isFull(restaurant* r) {
    table* currTable = r->recentTable;
    bool is_full = 1;
    for (int i = 1; i <= MAXSIZE; i++) {
        if (currTable->name == "") {
            is_full = 0;
            break;
        }
        currTable = currTable->next;
    }
    return is_full;
}

table* unmergeTable = NULL;

bool hasID(string cmd) {
    //ID-name-age
    //name-age
    if (cmd.find(' ') == cmd.rfind(' ')) {
        return false;
    }
    return true;
}

void reg(const string& cmd, restaurant* r, Queue* customer_queue, Stack* customer_stack, Queue* customer_queue_to_print) {
    // REG [ID] <name> <age>
    //// get ID, name, age from cmd
    string temp_ID = "";
    string name;
    string temp_age;

    if (hasID(cmd)) {
        temp_ID = cmd.substr(0, cmd.find(' '));
        name = cmd.substr(cmd.find(' ') + 1, cmd.rfind(' ') - cmd.find(' ') - 1);
        temp_age = cmd.substr(cmd.rfind(' ') + 1);
    } else {
        name = cmd.substr(0, cmd.find(' '));
        temp_age = cmd.substr(cmd.rfind(' ') + 1);
    }

    // check ID, name, age validity
    if (!checkID(temp_ID) || !checkAge(temp_age)) { 
        return;
    }

    int ID = stoi(temp_ID);
    int age = stoi(temp_age);

    ////
    table* currTable = r->recentTable;
    if (isFull(r)) { // if full
        if (customer_queue->getSize() < MAXSIZE) { // return if queue is full
            customer_queue->enQueue(ID, name, age); // add to queue
            customer_queue_to_print->enQueue(ID, name, age);

            if (!customer_stack->isExist(name, age)) {         // if name is not exist in stack
                table* push_table = new table(0, name, age, NULL); // push to stack
                customer_stack->push(push_table);
            }
        }
    } else {         // if not full
        table* minIDTable = r->recentTable;
        if (ID) { // if customer has ID -> seach ID table
            int min_ID = MAXSIZE;
            for (int i = 1; i <= MAXSIZE; i++) {
                if (currTable->ID >= ID && currTable->ID <= min_ID) {
                    min_ID = currTable->ID;
                    minIDTable = currTable;
                }
                currTable = currTable->next;
            }
        } else { // if no ID -> seach 1st table
            int min_ID = MAXSIZE;
            for (int i = 1; i <= MAXSIZE; i++) {
                if (currTable->ID <= min_ID) {
                    min_ID = currTable->ID;
                    minIDTable = currTable;
                }
                currTable = currTable->next;
            }
        }
        while (minIDTable->name != "") {       // if table is taken
            minIDTable = minIDTable->next; // go to next table
        }
        minIDTable->name = name;     // update info and return
        minIDTable->age = age; 
        r->recentTable = minIDTable;

        /// push to stack
        if (!customer_stack->isExist(name, age)) { // if name is not exist in stack and queue is not full
            table* push_table = new table(0, name, age, NULL);
            customer_stack->push(push_table);
        }
    }
}

void regm(string cmd, restaurant* r, Stack* customer_stack) {
    //// if there was a merge table -> return
    if (unmergeTable != NULL) {
        return;
    }

    // REGM <name> <age> <num>
    //// get name, age, num from cmd
    string name;
    string temp_age;
    string temp_num;

    name = cmd.substr(0, cmd.find(' '));
    temp_age = cmd.substr(cmd.find(' ') + 1, cmd.rfind(' ') - cmd.find(' ') - 1);
    temp_num = cmd.substr(cmd.rfind(' ') + 1);
    

    // check ID, name, age validity
    if (isFull(r) || !checkAge(temp_age) || !checkNum(temp_num)) { 
        return;
    }

    int age = stoi(temp_age);
    int num = stoi(temp_num);

    
    
    /// initialize table status
    table* currTable = r->recentTable;
    while (currTable->ID != 1) { // go to 1st table
        currTable = currTable->next;
    }
    // after loop, currTable->ID == 1

    /// merge table
    // 1, 2, 3,..., MAXSIZE, 1, 2, 3,...
    //                      |num - 1    |
    int count = 0;
    int table_ID = 0;
    table* mergeTable = currTable;
    table* nextTable = currTable;

    for (int i = 1; i <= MAXSIZE + num - 1; i++) { // 1 -> MAXSIZE+num-1
        if (currTable->name == "") {
            count++;
            if (count >= num) {
                table_ID = i - num + 1;
                mergeTable = currTable;
                nextTable = currTable;
            }
        } else {
            count = 0;
        }
        currTable = currTable->next;
    }
    
    if (table_ID == 0) { // if can't find consecutive empty table, return
        return;
    }

    //// save info & merge table
    nextTable  = nextTable->next;

    
    for (int i = 0; i < MAXSIZE-num+1; i++) { 
        mergeTable = mergeTable->next;
    }
    mergeTable->name = name;
    mergeTable->age = age;
    r->recentTable = mergeTable;

    unmergeTable = mergeTable->next; // unmerge table
    mergeTable->next = nextTable;

    table* push_table = new table(0, name, age, NULL); // push to stack
    customer_stack->push(push_table);
}

void cle(string cmd, restaurant* r, Queue* customer_queue, Stack* customer_stack, Queue* customer_queue_to_print) {
    // CLE <ID>
    if (!checkID(cmd)) {
        return;
    }

    int ID = stoi(cmd);
    table* currTable = r->recentTable;
    bool clear_merged_table = 0;

    if (unmergeTable != NULL && (ID == unmergeTable->ID-1 || (ID == MAXSIZE && unmergeTable->ID == 1))) { // if clear merged table
        clear_merged_table = 1;
    }

    if (clear_merged_table) {
        int empty_table = MAXSIZE - numberOfTables(r) + 1;
        while (currTable->ID != ID) {
            currTable = currTable->next;
        }
        customer_stack->popAt(currTable->name, currTable->age); // pop stack
        currTable->name = ""; // clear info
        currTable->age = 0;
        currTable->next = unmergeTable;
        
        r->recentTable = currTable;   // update recent table
        unmergeTable = NULL;

        while (empty_table && customer_queue->getSize() > 0) { // add cus from queue
            reg(customer_queue->toStringFront(), r, customer_queue, customer_stack, customer_queue_to_print);
            customer_queue_to_print->deQueue();                
            empty_table--;
        }    
    } else { // clear single table
        table* currTable = r->recentTable;
        bool found_ID = 0;

        for (int i = 0; i < MAXSIZE; i++) {
            if (currTable->ID == ID) {
                found_ID = 1;
                break;
            }
            currTable = currTable->next;
        }
        
        if (found_ID) {
            // if queue is not empty -> clear table & add from queue
            // if queue is empty -> clear table
            if (currTable->name == "") {
                return;
            }
            r->recentTable = currTable; // update recent table

            customer_stack->popAt(currTable->name, currTable->age); // pop stack
            if (customer_queue->getSize() == 0) {
                currTable->name = ""; // clear info
                currTable->age = 0;
            } else {
                customer_queue->getFront(currTable);
                customer_queue_to_print->deQueue();
            }
        } else {
            return;
        }
        
    }
}

void ps(string cmd, restaurant* r, Queue* customer_queue, Stack* customer_stack) {
    // PS [NUM]
    int num;
    if (cmd == "PS") {
        num = 2*MAXSIZE;
    } else {
        if (stoi(cmd) <= 0 || stoi(cmd) > 2*MAXSIZE) {
            return;
        } else {
            num = stoi(cmd);
        }
    }
    if (customer_stack->getSize() == 0) {
        cout << "Empty" << endl;
    }
    customer_stack->printStack(num);
}

void pq(string cmd, restaurant* r, Queue* customer_queue_to_print) {
    // PQ [NUM]
    // cmd = NUM

    if (cmd == "PQ") {
        customer_queue_to_print->printQueue(MAXSIZE);
    } else {
        if(!checkNum(cmd)) {
            return;
        }
        customer_queue_to_print->printQueue(stoi(cmd));
    }
}

void sq(string cmd, restaurant* r, Queue* customer_queue) {
    // SQ <NUM>  selection sort
    // cmd = NUM
    if (cmd == "SQ" || !checkNum(cmd)) {
        return;
    }
    int num = stoi(cmd);
    customer_queue->selectionSort(num);
    customer_queue->printQueue(MAXSIZE);

}

void pt(restaurant* r, Queue* customer_queue, Stack* customer_stack) {
    table* currTable = r->recentTable;
    do {
        cout << currTable->ID << "-" << (currTable->name == "" ? "Empty" : currTable->name) << endl;
        currTable = currTable->next;
    } while (currTable != r->recentTable);
}

void simulate(string filename, restaurant* r)
{
    Queue* customer_queue = new Queue;
    Queue* customer_queue_to_print = new Queue;
    Stack* customer_stack = new Stack;
    ifstream myfile(filename);
    string cmd;
    while(getline(myfile, cmd)) {
        string key = cmd.substr(0, cmd.find(" "));
        cmd = cmd.substr(cmd.find(" ") + 1);
        if (key == "REG") {
            reg(cmd, r, customer_queue, customer_stack, customer_queue_to_print);
        } else if (key == "REGM") {
            regm(cmd, r, customer_stack);
        } else if (key == "CLE") {
            cle(cmd, r, customer_queue, customer_stack, customer_queue_to_print);
        } else if (key == "PS") {
            ps(cmd, r, customer_queue, customer_stack);
        } else if (key == "PQ") {
            pq(cmd, r, customer_queue_to_print);
        } else if (key == "SQ") {
            sq(cmd, r, customer_queue);
        } else if (key == "PT") {
            pt(r, customer_queue, customer_stack);
        }
    }
    delete customer_queue;
    delete customer_queue_to_print;
    delete customer_stack;
}

// fix reg cle pq












































































// #include "main.h"

// template <class T>
// class DLinkedList
// {
// public:
//     class Node
//     {
//     public:
//         T data;
//         Node *next;
//         Node *prev;
//         Node(const T &data = T{}, Node *next = nullptr, Node *prev = nullptr) : data(data), next(next), prev(prev) {}
//     };

// public:
//     Node *head;
//     Node *tail;
//     int count;

//     DLinkedList() : head(nullptr), tail(nullptr), count(0) {}
//     ~DLinkedList()
//     {
//         this->clear();
//     }

//     void add(const T &e)
//     {
//         add(size(), e);
//     }

//     void add(int index, const T &e)
//     {
//         if (index < 0 || index > size())
//         {
//             throw std::out_of_range("Index out of bounds");
//         }

//         Node *newNode = new Node(e, nullptr, nullptr);

//         if (size() == 0)
//         {
//             head = tail = newNode;
//         }
//         else if (index == 0)
//         {
//             newNode->next = head;
//             head->prev = newNode;
//             head = newNode;
//         }
//         else if (index == size())
//         {
//             newNode->prev = tail;
//             tail->next = newNode;
//             tail = newNode;
//         }
//         else
//         {
//             Node *current = head;
//             for (int i = 0; i < index; i++)
//             {
//                 current = current->next;
//             }

//             newNode->prev = current->prev;
//             newNode->next = current;
//             current->prev->next = newNode;
//             current->prev = newNode;
//         }

//         count++;
//     }

//     T removeAt(int index)
//     {
//         if (index < 0 || index >= size())
//         {
//             throw std::out_of_range("Index out of bounds");
//         }
//         if (index == this->size() - 1)
//         {
//             if (index == 0)
//             {
//                 T data = head->data;
//                 delete head;
//                 head = nullptr;
//                 count--;
//                 return data;
//             }
//             T data = tail->data;
//             Node *curr = tail;
//             tail = tail->prev;
//             tail->next = nullptr;
//             delete curr;
//             count--;
//             return data;
//         }
//         Node *current = head;
//         for (int i = 0; i < index; i++)
//         {
//             current = current->next;
//         }

//         T data = current->data;

//         if (size() == 1)
//         {
//             head = tail = nullptr;
//         }
//         else if (current == head)
//         {
//             head = current->next;
//             head->prev = nullptr;
//         }
//         else if (current == tail)
//         {
//             tail = current->prev;
//             tail->next = nullptr;
//         }
//         else
//         {
//             current->prev->next = current->next;
//             current->next->prev = current->prev;
//         }

//         delete current;
//         count--;

//         return data;
//     }

//     bool removeItem(const T &removeItem)
//     {
//         Node *current = head;
//         while (current != nullptr)
//         {
//             if (current->data == removeItem)
//             {
//                 if (size() == 1)
//                 {
//                     head = tail = nullptr;
//                 }
//                 else if (current == head)
//                 {
//                     head = current->next;
//                     head->prev = nullptr;
//                 }
//                 else if (current == tail)
//                 {
//                     tail = current->prev;
//                     tail->next = nullptr;
//                 }
//                 else
//                 {
//                     current->prev->next = current->next;
//                     current->next->prev = current->prev;
//                 }

//                 delete current;
//                 count--;
//                 return true;
//             }
//             current = current->next;
//         }

//         return false;
//     }

//     bool empty() const
//     {
//         return (count == 0);
//     }

//     int size() const
//     {
//         return count;
//     }
//     void clear()
//     {
//         while (head != nullptr)
//         {
//             Node *temp = head;
//             head = head->next;
//             delete temp;
//         }
//         tail = nullptr;
//         count = 0;
//     }
//     T get(int index)
//     {
//         if (index < 0 || index >= size())
//         {
//             throw std::out_of_range("Index out of bounds");
//         }
//         Node *current = head;
//         if (index == 0)
//         {
//             return head->data;
//         }
//         if (index == this->size() - 1)
//         {
//             return tail->data;
//         }
//         for (int i = 0; i < index; i++)
//         {
//             current = current->next;
//         }
//         return current->data;
//     }
//     void set(int index, const T &e)
//     {
//         if (index < 0 || index >= size())
//         {
//             throw std::out_of_range("Index out of bounds");
//         }
//         Node *current = head;
//         for (int i = 0; i < index; i++)
//         {
//             current = current->next;
//         }
//         current->data = e;
//     }
//     int indexOf(const T &item)
//     {
//         Node *current = head;
//         int index = 0;
//         while (current != nullptr)
//         {
//             if (current->data == item)
//             {
//                 return index;
//             }
//             current = current->next;
//             index++;
//         }
//         return -1;
//     }
//     bool contains(const T &item)
//     {
//         return indexOf(item) != -1;
//     }
// };

// // Khach khong co ID thi cho id = 0
// void reg(int id, string name, int age, restaurant *&r, DLinkedList<pair<string, int>> *&st, DLinkedList<pair<pair<int, string>, int>> *&q, DLinkedList<pair<string, int>> *&stable_q, int &singleTable, table *&mergeTableHead, table *&recentAddedTable)
// {
//     if (id == 0)
//     {
//         if (singleTable == MAXSIZE)
//         {
//             table *temp = r->recentTable->next;
//             int count = 1;
//             while (true)
//             {
//                 if (count > singleTable)
//                 {
//                     if (q->size() < MAXSIZE)
//                     {
//                         q->add(make_pair(make_pair(q->size(), name), age));
//                         stable_q->add(make_pair(name, age));
//                         st->add(make_pair(name, age));
//                     }
//                     break;
//                 }
//                 else if (temp->age == 0)
//                 {
//                     temp->age = age;
//                     temp->name = name;
//                     st->add(make_pair(name, age));
//                     recentAddedTable = temp;
//                     break;
//                 }
//                 else
//                 {
//                     temp = temp->next;
//                     count += 1;
//                 }
//             }
//         }
//         else
//         {
//             table *temp = mergeTableHead;
//             bool flag = false;
//             while (temp != nullptr)
//             {
//                 if (temp->ID == id)
//                 {
//                     flag = true;
//                     break;
//                 }
//                 temp = temp->next;
//             }
//             if (flag)
//             {
//                 temp = r->recentTable;
//             }
//             else
//             {
//                 table *curr = r->recentTable;
//                 int MIN = MAXSIZE + 1;
//                 int count = 1;
//                 while (true)
//                 {
//                     if (count > singleTable)
//                     {
//                         break;
//                     }
//                     if (curr->ID < MIN)
//                     {
//                         MIN = curr->ID;
//                         temp = curr;
//                     }
//                     count++;
//                     curr = curr->next;
//                 }
//             }
//             int count = 1;
//             while (true)
//             {
//                 if (count > singleTable)
//                 {
//                     if (q->size() < MAXSIZE)
//                     {
//                         q->add(make_pair(make_pair(q->size(), name), age));
//                         stable_q->add(make_pair(name, age));
//                         st->add(make_pair(name, age));
//                     }
//                     break;
//                 }
//                 else if (temp->age == 0)
//                 {
//                     temp->age = age;
//                     temp->name = name;
//                     st->add(make_pair(name, age));
//                     recentAddedTable = temp;
//                     break;
//                 }
//                 else
//                 {
//                     temp = temp->next;
//                     count += 1;
//                 }
//             }
//         }
//     }
//     else
//     {
//         if (singleTable == MAXSIZE)
//         {
//             table *temp = r->recentTable->next;
//             while (true)
//             {
//                 if (temp->ID == id)
//                 {
//                     break;
//                 }
//                 temp = temp->next;
//             }
//             int count = 1;
//             while (true)
//             {
//                 if (count > singleTable)
//                 {
//                     if (q->size() < MAXSIZE)
//                     {
//                         q->add(make_pair(make_pair(q->size(), name), age));
//                         stable_q->add(make_pair(name, age));
//                         st->add(make_pair(name, age));
//                     }
//                     break;
//                 }
//                 else if (temp->age == 0)
//                 {
//                     temp->age = age;
//                     temp->name = name;
//                     st->add(make_pair(name, age));
//                     recentAddedTable = temp;
//                     break;
//                 }
//                 else
//                 {
//                     temp = temp->next;
//                     count++;
//                 }
//             }
//         }
//         else
//         {
//             table *temp = mergeTableHead;
//             bool flag = false;
//             while (temp != nullptr)
//             {
//                 if (temp->ID == id)
//                 {
//                     flag = true;
//                     break;
//                 }
//                 temp = temp->next;
//             }
//             if (flag)
//             {
//                 temp = r->recentTable;
//             }
//             else
//             {
//                 table *curr = r->recentTable;
//                 int count = 1;
//                 while (true)
//                 {
//                     if (count > singleTable)
//                     {
//                         break;
//                     }
//                     if (curr->ID == id)
//                     {
//                         temp = curr;
//                         break;
//                     }
//                     count++;
//                     curr = curr->next;
//                 }
//             }
//             int count = 1;
//             while (true)
//             {
//                 if (count > singleTable)
//                 {
//                     if (q->size() < MAXSIZE)
//                     {
//                         q->add(make_pair(make_pair(q->size(), name), age));
//                         stable_q->add(make_pair(name, age));
//                         st->add(make_pair(name, age));
//                     }
//                     break;
//                 }
//                 else if (temp->age == 0)
//                 {
//                     temp->age = age;
//                     temp->name = name;
//                     st->add(make_pair(name, age));
//                     recentAddedTable = temp;
//                     break;
//                 }
//                 else
//                 {
//                     temp = temp->next;
//                     count += 1;
//                 }
//             }
//         }
//     }
// }

// void regm(string name, int age, int num, restaurant *&r, DLinkedList<pair<pair<int, string>, int>> *&q, DLinkedList<pair<string, int>> *&st, int &singleTable, table *&mergeTableHead, table *&mergeTableTail, table *&recentAddedTable)
// {
//     if (singleTable < MAXSIZE)
//     {
//         return;
//     }
//     if (num > singleTable)
//     {
//         return;
//     }
//     table *temp = r->recentTable;
//     while (temp->ID != 1)
//     {
//         temp = temp->next;
//     }
//     temp = temp->next;
//     table *check = temp;
//     bool valid = false;
//     int count = 0;
//     for (int i = 0; i < MAXSIZE - 1; i++)
//     {
//         if (temp->age == 0)
//         {
//             count++;
//         }
//         else
//         {
//             check = check->next;
//         }
//         if (count == num)
//         {
//             valid = true;
//         }
//         if (count > num)
//         {
//             count = num;
//             check = check->next;
//         }
//         temp = temp->next;
//     }
//     if (valid)
//     {
//         singleTable = MAXSIZE - num;
//         table *temp = check;
//         while (mergeTableHead == nullptr || mergeTableTail == nullptr)
//         {
//             if (temp == check)
//             {
//                 mergeTableHead = temp;
//             }
//             if (temp->ID == (check->ID + num - 1) % MAXSIZE || temp->ID == (check->ID + num - 1))
//             {
//                 mergeTableTail = temp;
//             }
//             temp = temp->next;
//         }
//         mergeTableHead->age = age;
//         mergeTableHead->name = name;
//         recentAddedTable = mergeTableHead;
//         st->add(make_pair(mergeTableHead->name, mergeTableHead->age));
//         table *pre = nullptr;
//         table *past = nullptr;
//         while (pre == nullptr || past == nullptr)
//         {
//             if (temp->next == mergeTableHead)
//             {
//                 pre = temp;
//             }
//             if (temp == mergeTableTail->next)
//             {
//                 past = temp;
//             }
//             temp = temp->next;
//         }
//         pre->next = past;
//         r->recentTable = past;
//         mergeTableTail->next = nullptr;
//     }
// }

// void cle(int id, restaurant *&r, DLinkedList<pair<pair<int, string>, int>> *&q, DLinkedList<pair<string, int>> *&st, DLinkedList<pair<string, int>> *&stable_q, int &singleTable, table *&mergeTableHead, table *&mergeTableTail, table *&recentAddedTable)
// {
//     table *temp = r->recentTable;
//     int count = 1;
//     while (count <= singleTable)
//     {
//         if (temp->ID == id)
//         {
//             break;
//         }
//         temp = temp->next;
//         count++;
//     }
//     if (count <= singleTable)
//     {
//         st->removeItem(make_pair(temp->name, temp->age));
//         temp->age = 0;
//         temp->name = "";
//         recentAddedTable = temp;
//         if (q->size() > 0)
//         {
//             temp->age = q->head->data.second;
//             temp->name = q->head->data.first.second;
//             recentAddedTable = temp;
//             q->removeAt(0);
//             stable_q->removeItem(make_pair(temp->name, temp->age));
//         }
//     }
//     else
//     {
//         if (id != mergeTableHead->ID)
//         {
//             return;
//         }
//         st->removeItem(make_pair(mergeTableHead->name, mergeTableHead->age));
//         mergeTableHead->age = 0;
//         mergeTableHead->name = "";
//         recentAddedTable = mergeTableHead;
//         table *temp = r->recentTable;
//         while (temp->next != r->recentTable)
//         {
//             temp = temp->next;
//         }
//         temp->next = mergeTableHead;
//         mergeTableTail->next = r->recentTable;
//         table *trv = mergeTableHead;
//         singleTable = MAXSIZE;
//         while (trv != mergeTableTail->next)
//         {
//             if (q->empty())
//             {
//                 break;
//             }
//             else
//             {
//                 DLinkedList<pair<pair<int, string>, int>>::Node *curr = q->head;
//                 trv->name = curr->data.first.second;
//                 trv->age = curr->data.second;
//                 recentAddedTable = trv;
//                 q->removeAt(0);
//                 stable_q->removeItem(make_pair(trv->name, trv->age));
//             }
//             trv = trv->next;
//         }
//         mergeTableHead = mergeTableTail = nullptr;
//     }
// }

// void ps(int num, DLinkedList<pair<string, int>> *&st)
// {
//     if (st->count == 0)
//     {
//         cout << "Empty" << endl;
//         return;
//     }
//     DLinkedList<pair<string, int>>::Node *temp = st->tail;
//     int i;
//     if (num <= st->size())
//     {
//         i = num;
//     }
//     else
//     {
//         i = st->size();
//     }
//     while (i--)
//     {
//         cout << temp->data.first << endl;
//         temp = temp->prev;
//     }
// }

// void pq(int num, DLinkedList<pair<string, int>> *&stable_q)
// {
//     if (stable_q->count == 0)
//     {
//         cout << "Empty" << endl;
//         return;
//     }
//     DLinkedList<pair<string, int>>::Node *temp = stable_q->head;
//     int i;
//     if (num <= stable_q->size())
//     {
//         i = num;
//     }
//     else
//     {
//         i = stable_q->size();
//     }
//     while (i--)
//     {
//         cout << temp->data.first << endl;
//         temp = temp->next;
//     }
// }

// void sq(int num, DLinkedList<pair<pair<int, string>, int>> *&q)
// {
//     if (q->count == 0)
//     {
//         cout << "Empty" << endl;
//         return;
//     }
//     DLinkedList<pair<pair<int, string>, int>>::Node *curr = q->head;
//     if (num > q->size())
//     {
//         num = q->size();
//     }
//     int current = 0;
//     while (current <= num - 1)
//     {
//         DLinkedList<pair<pair<int, string>, int>>::Node *largest = curr;
//         DLinkedList<pair<pair<int, string>, int>>::Node *walker = curr->next;
//         while (walker != nullptr)
//         {
//             if (walker->data.second > largest->data.second)
//             {
//                 largest = walker;
//             }
//             walker = walker->next;
//         }
//         pair<pair<int, string>, int> temp = largest->data;
//         largest->data = curr->data;
//         curr->data = temp;
//         curr = curr->next;
//         current += 1;
//     }
//     curr = q->head;
//     DLinkedList<pair<pair<int, string>, int>>::Node *trv = curr->next;
//     while (trv != nullptr)
//     {
//         if (curr->data.second == trv->data.second && curr->data.first.first > trv->data.first.first)
//         {
//             pair<pair<int, string>, int> temp = trv->data;
//             trv->data = curr->data;
//             curr->data = temp;
//         }
//         curr = curr->next;
//         trv = trv->next;
//     }
//     curr = q->head;
//     while (curr != nullptr)
//     {
//         cout << curr->data.first.second << endl;
//         curr = curr->next;
//     }
// }
// void pt(restaurant *&r, DLinkedList<pair<pair<int, string>, int>> *&q, DLinkedList<pair<string, int>> *&st, int &singleTable, table *&mergeTableHead, table *&mergeTableTail, table *&recentAddedTable)
// {
//     if (singleTable < MAXSIZE)
//     {
//         table *temp = recentAddedTable;
//         while (temp->next != recentAddedTable)
//         {
//             cout << temp->ID << "-" << temp->name << endl;
//             temp = temp->next;
//         }
//         cout << temp->ID << "-" << temp->name << endl;
//     }
//     else
//     {
//         table *temp = recentAddedTable;
//         if (temp == mergeTableHead)
//         {
//             cout << temp->ID << "-" << temp->name << endl;
//             temp = r->recentTable;
//             while (temp->next != r->recentTable)
//             {
//                 cout << temp->ID << "-" << temp->name << endl;
//                 temp = temp->next;
//             }
//             cout << temp->ID << "-" << temp->name << endl;
//         }
//         else
//         {
//             while (temp->next != recentAddedTable)
//             {
//                 if (temp->next == r->recentTable)
//                 {
//                     cout << temp->ID << "-" << temp->name << endl;
//                     cout << mergeTableHead->ID << "-" << mergeTableHead->name << endl;
//                 }
//                 else
//                 {
//                     cout << temp->ID << "-" << temp->name << endl;
//                 }
//                 temp = temp->next;
//             }
//         }
//     }
// }

// int convertNumber(string s)
// {
//     for (char c : s)
//     {
//         if ('0' > c || c > '9')
//         {
//             return -1;
//         }
//     }
//     return stoi(s);
// }

// void Command(DLinkedList<string> *&command, restaurant *&r, DLinkedList<pair<string, int>> *&st, DLinkedList<pair<pair<int, string>, int>> *&q, DLinkedList<pair<string, int>> *&stable_q, int &singleTable, table *&mergeTableHead, table *&mergeTableTail, table *&recentAddedTable)
// {
//     DLinkedList<string>::Node *temp = command->head;
//     if (temp->data == "REG")
//     {
//         if (command->size() <= 2 || command->size() >= 5)
//         {
//             return;
//         }
//         else if (command->size() == 3)
//         {
//             string s1 = temp->next->data;
//             string s2 = temp->next->next->data;
//             if (convertNumber(s2) == -1)
//             {
//                 return;
//             }
//             if (stoi(s2) > 115 || stoi(s2) < 16)
//             {
//                 return;
//             }
//             reg(0, s1, stoi(s2), r, st, q, stable_q, singleTable, mergeTableHead, recentAddedTable);
//         }
//         else
//         {
//             string s1 = temp->next->data;
//             string s2 = temp->next->next->data;
//             string s3 = temp->next->next->next->data;
//             if (convertNumber(s1) == -1 || convertNumber(s3) == -1)
//             {
//                 return;
//             }
//             if (stoi(s3) > 115 || stoi(s3) < 16)
//             {
//                 return;
//             }
//             if (stoi(s1) < 1 || stoi(s1) > MAXSIZE)
//             {
//                 return;
//             }
//             reg(stoi(s1), s2, stoi(s3), r, st, q, stable_q, singleTable, mergeTableHead, recentAddedTable);
//         }
//     }
//     else if (temp->data == "REGM")
//     {
//         if (command->size() != 4)
//         {
//             return;
//         }
//         else
//         {
//             string s1 = temp->next->data;
//             string s2 = temp->next->next->data;
//             string s3 = temp->next->next->next->data;
//             if (convertNumber(s2) == -1 || convertNumber(s3) == -1)
//             {
//                 return;
//             }
//             if (stoi(s2) > 115 || stoi(s2) < 16)
//             {
//                 return;
//             }
//             if (stoi(s3) < 1 || stoi(s3) > MAXSIZE)
//             {
//                 return;
//             }
//             regm(s1, stoi(s2), stoi(s3), r, q, st, singleTable, mergeTableHead, mergeTableTail, recentAddedTable);
//         }
//     }
//     else if (temp->data == "PT")
//     {
//         if (command->size() != 1)
//         {
//             return;
//         }
//         pt(r, q, st, singleTable, mergeTableHead, mergeTableTail, recentAddedTable);
//     }
//     else if (temp->data == "CLE")
//     {
//         if (command->size() != 2)
//         {
//             return;
//         }
//         else
//         {
//             string s1 = temp->next->data;
//             if (stoi(s1) == -1)
//             {
//                 return;
//             }
//             if (stoi(s1) > MAXSIZE || stoi(s1) < 1)
//             {
//                 return;
//             }
//             cle(stoi(s1), r, q, st, stable_q, singleTable, mergeTableHead, mergeTableTail, recentAddedTable);
//         }
//     }
//     else if (temp->data == "PS")
//     {
//         if (command->size() > 2 || command->size() < 1)
//         {
//             return;
//         }
//         else if (command->size() == 2)
//         {
//             string s1 = temp->next->data;
//             if (stoi(s1) == -1)
//             {
//                 return;
//             }
//             if (stoi(s1) > 2 * MAXSIZE || stoi(s1) < 1)
//             {
//                 return;
//             }
//             ps(stoi(s1), st);
//         }
//         else
//         {
//             ps(st->size(), st);
//         }
//     }
//     else if (temp->data == "PQ")
//     {
//         if (command->size() > 2 || command->size() < 1)
//         {
//             return;
//         }
//         else if (command->size() == 2)
//         {
//             string s1 = temp->next->data;
//             if (stoi(s1) == -1)
//             {
//                 return;
//             }
//             if (stoi(s1) > MAXSIZE || stoi(s1) < 1)
//             {
//                 return;
//             }
//             pq(stoi(s1), stable_q);
//         }
//         else
//         {
//             pq(q->size(), stable_q);
//         }
//     }
//     else if (temp->data == "SQ")
//     {
//         if (command->size() != 2)
//         {
//             return;
//         }
//         string s1 = temp->next->data;
//         if (convertNumber(s1) == -1)
//         {
//             return;
//         }
//         sq(stoi(s1), q);
//     }
//     else
//     {
//         return;
//     }
// }

// void ReadFile(string filename, restaurant *&r, DLinkedList<pair<string, int>> *&st, DLinkedList<pair<pair<int, string>, int>> *&q, DLinkedList<pair<string, int>> *&stable_q, int &singleTable, table *&mergeTableHead, table *&mergeTableTail, table *&recentAddedTable)
// {
//     ifstream myfile(filename);
//     // myfile.open(filename);
//     if (!myfile.is_open())
//     {
//         cout << "Error: cannot open file " << filename << endl;
//         return;
//     }
//     string line;
//     while (getline(myfile, line))
//     {
//         DLinkedList<int> *space_pos = new DLinkedList<int>();
//         DLinkedList<string> *command = new DLinkedList<string>();
//         size_t pos = -1;
//         while ((pos = line.find(' ', pos + 1)) != string::npos)
//         {
//             space_pos->add(pos);
//         }
//         DLinkedList<int>::Node *temp = space_pos->head;
//         while (temp != nullptr)
//         {
//             temp = temp->next;
//         }
//         temp = space_pos->head;
//         int prev_pos = 0;
//         while (temp != nullptr)
//         {
//             command->add(line.substr(prev_pos, temp->data - prev_pos));
//             prev_pos = temp->data + 1;
//             temp = temp->next;
//         }
//         command->add(line.substr(prev_pos, line.size() - prev_pos));
//         Command(command, r, st, q, stable_q, singleTable, mergeTableHead, mergeTableTail, recentAddedTable);
//         delete command;
//         delete space_pos;
//     }
//     myfile.close();
// }

// void simulate(string filename, restaurant *r)
// {
//     DLinkedList<pair<string, int>> *st = new DLinkedList<pair<string, int>>();
//     DLinkedList<pair<string, int>> *stable_q = new DLinkedList<pair<string, int>>();
//     DLinkedList<pair<pair<int, string>, int>> *q = new DLinkedList<pair<pair<int, string>, int>>();
//     int singleTable = MAXSIZE;
//     table *mergeTableHead = nullptr;
//     table *mergeTableTail = nullptr;
//     table *recentAddedTable = nullptr;
//     ReadFile(filename, r, st, q, stable_q, singleTable, mergeTableHead, mergeTableTail, recentAddedTable);
//     table *temp = r->recentTable->next;
//     r->recentTable->next = nullptr;
//     while (temp != r->recentTable)
//     {
//         table *curr = temp;
//         temp = temp->next;
//         delete curr;
//     }
//     temp = mergeTableHead;
//     while (temp != nullptr)
//     {
//         table *curr = temp;
//         temp = temp->next;
//         delete curr;
//     }
//     delete st;
//     delete q;
//     delete stable_q;
// }