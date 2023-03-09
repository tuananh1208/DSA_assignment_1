#include "main.h"
#include "restaurant.cpp"

int main(int argc, char* argv[]) {
    restaurant* r = new restaurant();
    string fileName = "test.txt";

    //initialize table with ID, name and age
    for (int i = 1; i <= MAXSIZE; i++)
    {
        r->recentTable = r->insert(r->recentTable,i,"",0);
    }

    simulate(fileName,r);
    // for (int i = 1; i <= MAXSIZE; i++)
    // {
    //     cout << r->recentTable->ID << " " << r->recentTable->name << " " << r->recentTable->age << endl;
    //     r->recentTable = r->recentTable->next;
    // }
    delete r;

    return 0;
}


