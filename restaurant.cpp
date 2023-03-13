#include "main.h"

class Queue {
private:
    table* front;
    table* rear;  
    int size; // <= MAXSIZE
public:
    Queue() {
        front = NULL;
        rear = NULL;
        size = 0;
    }
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
    res += to_string(front->ID) + " " + front->name + " " + to_string(front->age);
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
    int size; // 1->2*MAXSIZE
public:
    table* top;
    Stack() {
        top = NULL;
        size = 0; 
    }
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

void reg(const string& cmd, restaurant* r, Queue* customer_queue, Stack* customer_stack) {
    // REG [ID] <name> <age>
    //// get ID, name, age from cmd
    string temp_ID = "";
    string name;
    string temp_age;

    if (isdigit(cmd.front())) {
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
    if (numberOfTables(r) < MAXSIZE) {
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

void cle(string cmd, restaurant* r, Queue* customer_queue, Stack* customer_stack) {
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
            reg(customer_queue->toStringFront(), r, customer_queue, customer_stack);                
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

void pq(string cmd, restaurant* r, Queue* customer_queue) {
    // PQ [NUM]
    // cmd = NUM

    if (cmd == "PQ") {
        customer_queue->printQueue(MAXSIZE);
    } else {
        if(!checkNum(cmd)) {
            return;
        }
        customer_queue->printQueue(stoi(cmd));
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
    Stack* customer_stack = new Stack;
    ifstream myfile(filename);
    string cmd;
    while(getline(myfile, cmd)) {
        string key = cmd.substr(0, cmd.find(" "));
        cmd = cmd.substr(cmd.find(" ") + 1);
        if (key == "REG") {
            reg(cmd, r, customer_queue, customer_stack);
        } else if (key == "REGM") {
            regm(cmd, r, customer_stack);
        } else if (key == "CLE") {
            cle(cmd, r, customer_queue, customer_stack);
        } else if (key == "PS") {
            ps(cmd, r, customer_queue, customer_stack);
        } else if (key == "PQ") {
            pq(cmd, r, customer_queue);
        } else if (key == "SQ") {
            sq(cmd, r, customer_queue);
        } else if (key == "PT") {
            pt(r, customer_queue, customer_stack);
        }
    }
    delete customer_queue;
    delete customer_stack;
}

