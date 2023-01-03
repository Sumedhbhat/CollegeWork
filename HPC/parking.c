#include <stdio.h>
#include<iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

void display1(int a[]) {
    cout << "Parking display system" << endl;
#pragma omp parallel for
    for (int i = 0; i < 3; i++) {
        cout << "Slots in Floor " << i + 1 << ": " << a[i] << endl;
    }
    cout << endl << endl;
}

int vacant(int a[]) { return a[0] + a[1] + a[2]; }

void event(int* park) {
#pragma omp parallel for
    for (int i = 0; i < 3; i++) {
        park[i] -= rand() % park[i];
    }
}
int main() {

    int floors = 3;

    time_t t;

    srand((unsigned)time(&t));
    int park[3];
    park[0] = 50;
    park[1] = 50;
    park[2] = 50;
    cout << "Full capacity" << endl;
    display1(park);

    cout << "Initially" << endl;
    event(park);
    display1(park);

    cout << "After 5 minutes" << endl;
    event(park);
    display1(park);
    cout << "After another 5 minutes" << endl;
    event(park);
    display1(park);
    cout << "After another 5 minutes" << endl;
    event(park);
    display1(park);
}
