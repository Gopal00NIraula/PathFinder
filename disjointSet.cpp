//
// Created by scsiet on 10/18/24.
//

#include "disjointSet.h"

DisjointSet::DisjointSet(uint32_t n) {

    rank = new uint32_t[n];
    elements = new uint32_t[n];

    for (uint32_t i=0; i < n; i++)
        elements[i] = i;

    for (uint32_t i = 0; i < n; i++)
        rank[i] = 0;


}

DisjointSet::~DisjointSet() {
    delete[] elements;
    delete[] rank;
}


void DisjointSet::join(uint32_t a, uint32_t b) {
    a = find(a);
    b = find(b);

    if (a != b) {
        if (rank[a] < rank [b])
            elements[a] = b;
        else {
           if(rank[a] == rank[b])
                rank[a]++;
           elements[b] = a;
        }
    }
}

uint32_t DisjointSet::find(uint32_t a) {
    if (elements[a]!= a) {
        elements[a] = find(elements[a]);
    }
    return elements[a];
}

