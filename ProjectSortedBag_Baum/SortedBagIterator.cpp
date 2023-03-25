#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

// Complexity: theta(1)
BTNode* SortedBagIterator::pop()
{
    BTNode* last_node = it_stack[nr_elems-1];
    this->nr_elems--;
    return last_node;
}

// Complexity: theta(n) amortisiert
void SortedBagIterator::push(BTNode* new_node)
{
    // resize
    if (this->cap == this->nr_elems)
    {
        this->cap *= 2;
        auto *newElements = new BTNode* [this->cap];
        for (int index = 0; index < this->nr_elems; index++)
            newElements[index] = this->it_stack[index];
        this->it_stack = newElements;
    }
    this->it_stack[this->nr_elems] = new_node;
    this->nr_elems++;
}

// Complexity: theta(1)
BTNode* SortedBagIterator::top()
{
    return this->it_stack[nr_elems-1];
}

// Complexity: theta(1)
bool SortedBagIterator::isEmpty()
{
    return this->nr_elems == 0;
}

// Best Case: theta(1) - tree has only right subtree
// Worst Case: theta(n) - degenerated tree, only left subtree
// Complexity: O(n)
SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
	//TODO - Implementation
    this->cap = 25;
    this->it_stack = new BTNode* [this->cap];
    this->nr_elems = 0;

    BTNode* node = this->bag.root;
    // we go through left part starting with the root
    while (node!= nullptr)
    {
        SortedBagIterator::push(node);
        node = node->left;
    }

    // first leaf will be the first element
    if (!SortedBagIterator::isEmpty())
    {
        this->currentNode = SortedBagIterator::top();
        this->freq = 1;
    }
    else
        this->currentNode = nullptr;
}

// Complexity: theta(1)
TComp SortedBagIterator::getCurrent() {
    //TODO - Implementation
    if (SortedBagIterator::valid())
        return this->currentNode->info.first;
    else
    {
        exception E;
        throw E;
    }
}

// Complexity: theta(1)
bool SortedBagIterator::valid() {
    //TODO - Implementation
    return currentNode!= nullptr;
}

// Best case: theta(1) - just increase frequency
// Worst case: theta(n) - many nodes at the left part
// Complexity: O(n)
void SortedBagIterator::next() {
    //TODO - Implementation
    if (SortedBagIterator::valid())
    {
        // increase frequency if we have multiple appearences
        if (this->freq < this->currentNode->info.second)
        {
            this->freq ++;
        }
        else
        {
            // we move on the next element
            this->freq = 1;
            BTNode* node = SortedBagIterator::pop();
            if (node->right != nullptr)
            {
                node = node->right;
                while (node != nullptr)
                {
                    // we add nodes from the left side
                    SortedBagIterator::push(node);
                    node = node->left;
                }
            }
            if (!SortedBagIterator::isEmpty())
            {
                this->currentNode = SortedBagIterator::top();
            }
            else
                this->currentNode = nullptr;
        }
    }
    else
    {
        exception E;
        throw E;
    }
}

// Best Case: theta(1) - tree has only right subtree
// Worst Case: theta(n) - degenerated tree, only left subtree
// Complexity: O(n)
void SortedBagIterator::first() {
    //TODO - Implementation

    // start empty stack
    this->nr_elems = 0;
    BTNode* node = this->bag.root;
    while (node!= nullptr)
    {
        SortedBagIterator::push(node);
        node = node->left;
    }
    if (!SortedBagIterator::isEmpty())
    {
        this->currentNode = SortedBagIterator::top();
        this->freq = 1;
    }
    else
        this->currentNode = nullptr;
}