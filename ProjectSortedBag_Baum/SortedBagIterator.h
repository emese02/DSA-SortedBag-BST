#pragma once
#include "SortedBag.h"

class SortedBag;

class SortedBagIterator
{
	friend class SortedBag;

private:
	const SortedBag& bag;
	SortedBagIterator(const SortedBag& b);

	//TODO - Representation
    BTNode* currentNode;
    BTNode** it_stack;
    int freq;
    int nr_elems;
    int cap;

public:
	TComp getCurrent();
	bool valid();
	void next();
	void first();

    void push(BTNode* new_node);
    BTNode* pop();
    BTNode* top();
    bool isEmpty();
};

