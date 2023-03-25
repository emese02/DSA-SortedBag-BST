#include "SortedBag.h"
#include "SortedBagIterator.h"

// Complexity: theta(1)
SortedBag::SortedBag(Relation r) {
	//TODO - Implementation
    this->rel = r;
    this->root = nullptr;
}

// Best case: theta(1) - root contains TComp e, only increase frequency
// Average case: theta(log n) - balanced tree
// Worst case: theta(n) - degenerated tree, add element at the end
// Complexity: O(n)
void SortedBag::add(TComp e) {
    //TODO - Implementation

    // empty tree
    if (this->root == nullptr)
    {
        // new node will be the root
        BTNode *newNode;
        newNode = new BTNode;
        newNode->left = nullptr;
        newNode->right = nullptr;
        newNode->info = std::pair<TComp,TComp> (e,1);
        this->root = newNode;
    }
    else
    {
        // we start with the root and save previous to, in order to set relation after
        BTNode* current = this->root;
        BTNode* prev = nullptr;
        // while we don't find the element / we dont' arrive at the end of the tree we go through the adequate part tree
        while (current!= nullptr && current->info.first != e)
        {
            if (this->rel(current->info.first,e))
            {
                prev = current;
                current = current->right;
            }
            else
            {
                prev = current;
                current = current->left;
            }
        }
        // the element is yet not in the tree -> new node
        if (current == nullptr)
        {
            current = new BTNode;
            current->left = nullptr;
            current->right = nullptr;
            current->info = std::pair<TComp,TComp> (e,1);
            if (rel(prev->info.first, current->info.first))
                prev->right = current;
            else
                prev->left = current;
        }
        else
            // tree contains element -> increase frequency
            current->info.second ++;
    }
}

// Best case: theta(1) - we have such a tree where we have few steps and arrive at the leaves
// Worst case: theta(n) - degenerated tree, go through all nodes (theta(h))
// Complexity: O(n)
bool SortedBag::remove(TComp e) {
    //TODO - Implementation
    BTNode* current = this->root;
    BTNode* parent = nullptr;
    bool found = false;
    // firstly we search the element
    while (current != nullptr && !found)
    {
        // element found
        if (current->info.first == e)
            found = true;
        // we continue searching in the adequate part, respecting the relation
        else if (this->rel(current->info.first, e))
        {
            parent = current;
            current = current->right;
        }
        else
        {
            parent = current;
            current = current->left;
        }
    }
    // if element not in the tree, can't be removed
    if (!found)
        return false;

    // if frequency > 1 -> decrease frequency
    if (current->info.second > 1)
    {
        current->info.second --;
    }
    else
    {
        // otherwise -> delete whole node
        // 1. case: the node has no children
        if (current->left == nullptr && current->right == nullptr) {
            // we only have one node (the root)
            if (current == this->root)
            {
                this->root = nullptr;
                delete(current);
            }
            else
            {
                // we check if current is a left or right child and set the link to null pointer
                if (parent->left == current)
                    parent->left = nullptr;
                else
                    parent->right = nullptr;
                // delete node
                delete (current);
            }
        }
            // 2. case: the node has one child (left)
        else if (current->right == nullptr)
        {
            // current is the root
            if (current == this->root)
                this->root = current->left;
            else
            {
                // we set the link of parent adequately to "grandson"
                if (parent->right == current)
                    parent->right = current->left;
                else
                    parent->left = current->left;
            }
            // delete node
            current ->left = nullptr;
            delete(current);
        }
        // 3. case: node has one child (right)
        else if (current->left == nullptr)
        {
            // current is root -> set new root
            if (current == this->root)
                this->root = current->right;
            else
            {
                // we set the link of parent adequately to "grandson"
                if (parent->left == current)
                    parent->left = current->right;
                else
                    parent->right = current->right;
            }

            // delete node
            current->right = nullptr;
            delete(current);
        }
        // 4. case: the node has two children
        else
        {
            // we search the minimum/maximum in the right part tree (depending on the relation)
            BTNode* min_max = current->right;
            BTNode* parent_min_max = current;
            while (min_max->left != nullptr)
            {
                parent_min_max = min_max;
                min_max = min_max->left;
            }
            auto info_min = min_max->info;
            // we set links of parent adequately
            if (parent_min_max->right == min_max)
                parent_min_max->right = min_max->right;
            else if (parent_min_max->left == min_max)
                    parent_min_max->left = min_max->right;
            // delete node
            delete(min_max);

            // we change info of current to minimum/maximum
            current->info = info_min;
        }
    }
    // successful remove
    return  true;
}

// Best case: theta(1) - root has the searched elem
// Average case: theta(log n)
// Worst case: theta(n) - degenerated tree, element at the end/is not in the tree
// Complexity: O(n)
bool SortedBag::search(TComp elem) const {
    //TODO - Implementation

    // we start with the root
    BTNode* current = this->root;
    bool found = false;
    while (current != nullptr && !found)
    {
        // element found
        if (current->info.first == elem)
            found = true;
        // we continue searching in the adequate part, respecting the relation
        else if (this->rel(current->info.first, elem))
            current = current->right;
        else
            current = current->left;
    }
    return found;
}

// Best case: theta(1) - root has the searched elem
// Average case: theta(log n) - balanced tree
// Worst case: theta(n) - degenerated tree, element at the end/is not in the tree
// Complexity: O(n)
int SortedBag::nrOccurrences(TComp elem) const {
    //TODO - Implementation

    // we start with the root
    BTNode* current = this->root;
    bool found = false;
    int frequency = 0;
    while (current != nullptr && !found)
    {
        // element found, save frequency
        if (current->info.first == elem)
        {
            found = true;
            frequency = current->info.second;
        }
        // we continue searching in the adequate part, respecting the relation
        else if (this->rel(current->info.first, elem))
            current = current->right;
        else
            current = current->left;
    }
    // if element is not in the tree, frequency remains 0
    return frequency;
}

// preorder traversing
void SortedBag::preorder_recursive_for_size (BTNode* current, int &size) const
{
    if (current!= nullptr)
    {
        size += current->info.second;
        SortedBag::preorder_recursive_for_size(current->left,size);
        SortedBag::preorder_recursive_for_size(current->right,size);
    }
}

// Complexity: theta(n)
int SortedBag::size() const {
    //TODO - Implementation
    int nr_elements = 0;
    SortedBag::preorder_recursive_for_size(this->root,nr_elements);
    return nr_elements;
}

// Complexity: theta(1)
bool SortedBag::isEmpty() const {
	//TODO - Implementation
	return this->root == nullptr;
}


SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}

// Complexity: theta(n!)
SortedBag::~SortedBag() {
	//TODO - Implementation
    while (!SortedBag::isEmpty())
        SortedBag::remove(this->root->info.first);
}