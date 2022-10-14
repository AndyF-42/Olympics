#include "sports.h"

/* Andy Fleischer - CS202 - Program 3 - 8/6/2021
 * ---------------------------------------------
 * This file lays out the classes for the data
 * structures of the sports. Athletes have an LLL
 * of sports, and BST is a binary search tree
 * of Athletes.
 */


class BNode
{
    public:
        BNode();

        BNode *& go_left();
        BNode *& go_right();
        Athlete& get_athlete();
        void set_left(BNode* new_left);
        void set_right(BNode* new_right);
        void set_athlete(const Athlete& new_athlete);

    private:
        Athlete athlete;
        BNode* left;
        BNode* right;
};

class BST
{
    public:
        BST();
        BST(const BST& source);
        ~BST();

        BST& operator = (const BST&);

        BST operator + (const Athlete&) const; //add this and athlete
        BST& operator += (const Athlete&); //add athlete to this

        BST operator - (const char*) const; //subtract this and name
        BST& operator -= (const char*); //remove athlete (from name) from this

        friend std::ostream& operator << (std::ostream&, const BST&); //display
        
        void remove_all(); //remove all nodes

    private:
        //helpers
        void copy(BNode*& root, BNode* source_root);
        void insert(BNode*& root, const Athlete& to_add);
        bool remove(BNode*& root, const char* to_remove); //returns if successful
        void display(std::ostream& out, BNode* root) const;
        void remove_all(BNode*& root);
        void find_smallest(BNode* root, BNode*& parent, BNode*& fill) const;
    
        BNode* root; 
};


