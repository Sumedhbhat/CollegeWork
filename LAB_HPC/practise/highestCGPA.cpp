#include <cstdlib>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int size=0;
    double max=(double)INT_MIN;
    cout<<"Enter the number of students"<<endl;
    cin>>size;
    double students[size];
    for (int i=0; i<size; i++) {
        students[i]=(double)(rand()%100)/10;
        cout<<students[i]<<endl;
    }
#pragma omp parallel
    {
#pragma omp for
        for (int i=0; i<size; i++) {
#pragma omp critical
            if(students[i]>max)
                max=students[i];
        }
    }
        cout<<"The max CGPA among students is "<<max<<endl;
    return 0;
}
