#include "main.h"

class Queue {
public:
    class Node {
    public:
        table* t;
        int ord_num;
        Node* next;
        Node(): t(NULL), ord_num(0), next(NULL) {}
        ~Node() {
            delete t;
            next = NULL;
        }
        Node(table* t, Node* next) : t(t), next(next) {}
        Node(table* t, int ord_num, Node* next) : t(t), ord_num(ord_num), next(next) {}
    };
public:
    Node* front;
    int size; // <= MAXSIZE
    int ord_num_Q;
    Queue() : front(NULL), size(0), ord_num_Q(0) {}
    ~Queue() {
        Node* currTable = front;
        while (currTable != NULL) {
            Node* temp = currTable;
            currTable = currTable->next;
            delete temp;
        }
        currTable = NULL;
        size = 0;
    }
    void enQueue(int, string, int);
    void deQueue();
    int getSize();
    string toStringFront();
    void swapInfo(Node*, Node*);
    void selectionSort(int);
    void printQueue(int);
    void popAt(table*);
    table* Front() { return front->t; }
};

int Queue::getSize() {
    return this->size;
}

void Queue::enQueue(int ID, string name, int age) {
    if (this->size == MAXSIZE) {
        return;
    }
    ord_num_Q++;
    table* newTable = new table(ID, name, age, NULL);
    Node* newNode = new Node(newTable, ord_num_Q, NULL);
    if (this->size == 0) {
        this->front = newNode;
        this->size++;
        return;
    }
    Node* currTable = this->front;
    while (currTable->next != NULL) {
        currTable = currTable->next;
    }
    currTable->next = newNode;
    this->size++;
}

void Queue::deQueue() {
    if (this->size == 0) {
        return;
    }
    Node* temp = this->front;
    this->front = this->front->next;
    delete temp;
    this->size--;
}

string Queue::toStringFront() {
    string res = "";
    res += (front->t->ID == 0 ? "" : to_string(front->t->ID)  + " ") + front->t->name + " " + to_string(front->t->age);
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

    Node* temp = this->front;
    for (int i = 0; i < n; i++) {
        if(temp == NULL) {
            return;
        }
        cout << temp->t->name << endl;
        temp = temp->next;
    }
}

void Queue::swapInfo(Node* n1, Node* n2) {
    swap(n1->t->ID, n2->t->ID);
    swap(n1->t->name, n2->t->name);
    swap(n1->t->age, n2->t->age);
    swap(n1->ord_num,n2->ord_num);
}

void Queue::selectionSort(int n) {
    Node* temp_head = front;
    while (temp_head != NULL) {
        if (n == 0) {
            return;
        }
        Node* temp = temp_head;
        Node* max_age = temp_head;
        while (temp != NULL) {
            if (temp->t->age > max_age->t->age || (temp->t->age == max_age->t->age && temp->ord_num < max_age->ord_num)) {
                max_age = temp;
            }
            temp = temp->next;
        }
        swapInfo(temp_head, max_age);
        n--;
        temp_head = temp_head->next;
    }
}

void Queue::popAt(table* popTable) {
    if (front->t->name == popTable->name && front->t->age == popTable->age) {
        Node* temp = front;
        front = front->next;
        delete temp;
        this->size--;
        return;
    }

    Node* prev = front;
    while (prev != NULL) {
        if (prev->next->t->name == popTable->name && prev->next->t->age == popTable->age) {
            break;
        }
        prev = prev->next;
    }
    Node* temp = prev->next;
    prev->next = temp->next;
    delete temp;
    this->size--;
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

bool hasID(string cmd) {
    //ID-name-age
    //name-age
    if (cmd.find(' ') == cmd.rfind(' ')) {
        return false;
    }
    return true;
}

void reg(const string& cmd, restaurant*& r, Queue*& customer_queue, Stack*& customer_stack, Queue*& customer_queue_to_print) {
    // REG {ID} <name> <age>
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
        bool check_greater_ID_exist = 0;
        for (int i = 1; i<= MAXSIZE; i++) {
            if (currTable->ID >= ID) {
                check_greater_ID_exist = 1;
                break;
            }
            currTable = currTable->next;
        }
        if (ID && check_greater_ID_exist) { // if customer has ID -> seach ID table
            int min_ID = MAXSIZE;
            for (int i = 1; i <= MAXSIZE; i++) {
                if (currTable->ID >= ID && currTable->ID <= min_ID) {
                    min_ID = currTable->ID;
                    minIDTable = currTable;
                }
                currTable = currTable->next;
            }
        } else { // if no ID -> seach minID table
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

void regm(string cmd, restaurant*& r, Stack*& customer_stack, table*& unmergeTable) {
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

void cle(string cmd, restaurant*& r, Queue*& customer_queue, Stack*& customer_stack, Queue*& customer_queue_to_print, table*& unmergeTable) {
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
            customer_queue_to_print->popAt(customer_queue->Front()); 
            reg(customer_queue->toStringFront(), r, customer_queue, customer_stack, customer_queue_to_print);
            empty_table--;
        }    
    } else { // clear single table
        currTable = r->recentTable;
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
            currTable->name = ""; // clear info
            currTable->age = 0;
            if (customer_queue->getSize() > 0) {
                customer_queue_to_print->popAt(customer_queue->Front()); 
                reg(customer_queue->toStringFront(), r, customer_queue, customer_stack, customer_queue_to_print);
            }
        } else {
            return;
        }
    }
}

void ps(string cmd, Stack* customer_stack) {
    // PS {NUM}
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

void pq(string cmd, Queue* customer_queue_to_print) {
    // PQ {NUM}
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

void sq(string cmd, Queue*& customer_queue) {
    // SQ <NUM>  selection sort
    // cmd = NUM
    if (cmd == "SQ" || !checkNum(cmd)) {
        return;
    }
    int num = stoi(cmd);
    customer_queue->selectionSort(num);
    customer_queue->printQueue(MAXSIZE);

}

void pt(restaurant* r) {
    table* currTable = r->recentTable;
    do {
        if (currTable->name == "") {
            currTable = currTable->next;
            continue;
        }
        cout << currTable->ID << "-" << currTable->name << endl;
        currTable = currTable->next;
    } while (currTable != r->recentTable);
}

void simulate(string filename, restaurant* r)
{   
    Queue* customer_queue = new Queue;
    Queue* customer_queue_to_print = new Queue;
    Stack* customer_stack = new Stack;
    table* unmergeTable = NULL;
    ifstream myfile(filename);
    string cmd;
    while(getline(myfile, cmd)) {
        string key = cmd.substr(0, cmd.find(" "));
        cmd = cmd.substr(cmd.find(" ") + 1);
        if (key == "REG") {
            reg(cmd, r, customer_queue, customer_stack, customer_queue_to_print);
        } else if (key == "REGM") {
            regm(cmd, r, customer_stack, unmergeTable);
        } else if (key == "CLE") {
            cle(cmd, r, customer_queue, customer_stack, customer_queue_to_print, unmergeTable);
        } else if (key == "PS") {
            ps(cmd, customer_stack);
        } else if (key == "PQ") {
            pq(cmd, customer_queue_to_print);
        } else if (key == "SQ") {
            sq(cmd, customer_queue);
        } else if (key == "PT") {
            pt(r);
        } 
    }
    delete customer_queue;
    delete customer_queue_to_print;
    delete customer_stack;

    table *temp = r->recentTable->next;
    while (temp != r->recentTable)
    {
        table *curr = temp;
        temp = temp->next;
        delete curr;
    }
}
