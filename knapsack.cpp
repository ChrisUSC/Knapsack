// knapsack.cpp
// VERSION 2
// Glenn G. Chappell
// 2 Nov 2012
//
// For CS 411/611 Fall 2012
// Knapsack Problem

#include <iostream>
using std::cout;
using std::endl;
using std::cin;
#include <cstdlib>
using std::size_t;
#include <vector>
using std::vector;
#include <cassert>  // for assert


// knapsack_recurse
// Given lists of object sizes & values, knapsack capacity, and n,
//  returns greatest possible value in knapsack problem using only
//  objects from first n.
// Recursive helper for function knapsack.
int knapsack_recurse(const vector<int> & sizes,
                     const vector<int> & values,
                     int capacity,
                     size_t n)
{
    // BASE CASE
    if (n == 0)
        return 0;

    // RECURSIVE CASE
    int max_without_last = knapsack_recurse(sizes, values,
                                            capacity, n-1);
    int lastsize = sizes[n-1];
    if (lastsize > capacity)
        return max_without_last;
    int max_with_last = values[n-1] +
                        knapsack_recurse(sizes, values,
                                         capacity-lastsize, n-1);
    return (max_with_last > max_without_last) ?
            max_with_last : max_without_last;
}


// knapsack
// Given lists of object sizes & values, and knapsack capacity,
//  returns greatest possible value in knapsack problem.
// Calls recursive helper function knapsack_recurse.
int knapsack(const vector<int> & sizes,
             const vector<int> & values,
             int capacity)
{
    size_t n = sizes.size();
    assert(n == values.size());
    return knapsack_recurse(sizes, values, capacity, n);
}


// knapsack_mem_recurse
// Given lists of object sizes & values, knapsack capacity, and n,
//  returns greatest possible value in knapsack problem using only
//  objects from first n.
// Uses memoizing. Values stored in vector table, which is initialized
//  to all (-1). Value for capacity, n is table[capacity*dim+n].
// Recursive helper for function knapsack_mem.
int knapsack_mem_recurse(const vector<int> & sizes,
                         const vector<int> & values,
                         int capacity,
                         size_t n,
                         vector<int> & table,
                         size_t dim)
{
    // BASE CASE
    if (n == 0)
        return 0;

    // RECURSIVE CASE

    // Check table
    if (table[capacity*dim+n] != -1)
        return table[capacity*dim+n];

    // Compute value
    int max_without_last = knapsack_mem_recurse(sizes, values,
                                                capacity, n-1,
                                                table, dim);
    int result = max_without_last;
    int lastsize = sizes[n-1];
    if (lastsize <= capacity)
    {
        int max_with_last = values[n-1] +
                            knapsack_mem_recurse(sizes, values,
                                                 capacity-lastsize, n-1,
                                                 table, dim);
        if (max_with_last > result)
            result = max_with_last;
    }

    // Store computed value and return it
    table[capacity*dim+n] = result;
    return result;
}


// knapsack_mem
// Given lists of object sizes & values, and knapsack capacity,
//  returns greatest possible value in knapsack problem.
// Uses memoizing.
// Calls recursive helper function knapsack_mem_recurse.
int knapsack_mem(const vector<int> & sizes,
                 const vector<int> & values,
                 int capacity)
{
    size_t n = sizes.size();
    assert(n == values.size());

    // Create space for memoized values.
    // Items start at (-1), meaning not valid.
    // Note that we store values for 0 .. capacity and 0 .. n, so
    //  we need dimensions (capacity+1) and (n+1).
    vector<int> table((capacity+1)*(n+1), -1);
    return knapsack_mem_recurse(sizes, values, capacity, n, table, n+1);
}


// try_knapsack
// Calls functions on given number of objects; prints results.
void try_knapsack(size_t n)
{
    int sizepattern[8] = { 1, 10, 1, 10, 10, 1, 10, 1 };
    int valuepattern[8] = { 1, 10, 4, 6, 4, 6, 1, 10 };
    vector<int> sizes;
    vector<int> values;
    for (size_t i = 0; i < n; ++i)
    {
        sizes.push_back(sizepattern[i%8]);
        values.push_back(valuepattern[i%8]);
    }
    int cap = 4*n;
    cout << "Number of objects: " << n << endl;
    int result;
    cout << "Result (dynamic-programming version): " << endl;
    cout << "    " << knapsack_mem(sizes, values, cap) << endl;
    // To try both versions, uncomment the following 2 lines
    //cout << "Result (non-dynamic-programming version): " << endl;
    //cout << "    " << knapsack(sizes, values, cap) << endl;
    cout << endl;

}


// Main program
// Try functions for increasing input sizes.
int main()
{
    for (size_t i = 0; i < 100000; ++i)
        try_knapsack(i);

    cout << "Press ENTER to quit ";
    while (cin.get() != '\n') ;

    return 0;
}

