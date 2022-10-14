#include "nodes.h"


// ==== NODE ==== //


Node::Node()
{
    sport = NULL;
    next = NULL;
}

Node::~Node()
{
    //if (sport)
    //    delete static_cast<Sport*>(sport);
    //if (sport)
    //    delete sport;
}

Node *& Node::go_next()
{ return next; }

void Node::set_next(Node* new_next)
{ next = new_next; }

Sport * Node::get_sport()
{ return sport; }

void Node::set_sport(Sport* new_sport)
{ sport = new_sport; }


// ==== LLL ==== //


LLL::LLL()
{ 
    head = NULL;
}

LLL::LLL(const LLL& source)
{
    copy(head, source.head);
}

LLL::~LLL()
{
    remove_all(head);
    head = NULL;
}

Node& LLL::operator [] (int index) const
{
    Node* current = head;
    for (int i = 0; i < index; ++i)
        current = current->go_next();
    return *current;
}

LLL& LLL::operator = (const LLL& source)
{
    if (this == &source)
        return *this;

    remove_all(head);
    copy(head, source.head);
    return *this;
}

LLL& LLL::operator += (Sport* to_add)
{
    Node* new_head = new Node();
    new_head->set_sport(to_add);
    new_head->set_next(head);
    head = new_head;
    
    return *this;
}

LLL& LLL::operator -= (Sport* to_remove)
{
    if (remove(head, to_remove))
        std::cout << "Removed." << std::endl;
    else
        std::cout << "Could not remove." << std::endl;
    return *this;
}

std::ostream& operator << (std::ostream& out, const LLL& my_list)
{
    my_list.display(out, my_list.head);
    return out;
}

void LLL::remove_all()
{
    remove_all(head);
    head = NULL;
}

void LLL::copy(Node*& head, Node* source_head)
{
    if (!source_head)
    {
        head = NULL;
        return;
    }

    head = new Node();
    head->set_sport(source_head->get_sport());
    copy(head->go_next(), source_head->go_next());
}

bool LLL::remove(Node*& head, Sport* to_remove)
{
    if (!head)
        return false;

    if (head->get_sport() == to_remove)
    {
        Node* temp = head->go_next();
        delete head;
        head = temp; 
        return true;
    }
    return remove(head->go_next(), to_remove);
}

void LLL::display(std::ostream& out, Node* head) const
{
    if (!head)
        return;

    out << *(head->get_sport()) << std::endl;
    display(out, head->go_next());
}

void LLL::remove_all(Node*& head)
{
    if (!head)
        return;

    Node* temp = head->go_next();
    delete head;
    head = NULL;
    remove_all(temp);
}


// ==== BNODE ==== //


BNode::BNode()
{
    left = NULL;
    right = NULL;
}

BNode *& BNode::go_left()
{ return left; }

BNode *& BNode::go_right()
{ return right; }

Athlete& BNode::get_athlete()
{ return athlete; }

void BNode::set_left(BNode* new_left)
{ left = new_left; }

void BNode::set_right(BNode* new_right)
{ right = new_right; }

void BNode::set_athlete(const Athlete& new_athlete)
{ athlete = new_athlete; }


// ==== BST ==== //


BST::BST()
{
    root = NULL;
}

BST::BST(const BST& source)
{
    //copy
}

BST::~BST()
{
    remove_all(root);
}

BST& BST::operator = (const BST&)
{
    return *this;
}

//BST operator + (Athlete*) const

BST& BST::operator += (const Athlete& to_add)
{
    insert(root, to_add);
    return *this;
}

//BST operator - (Athlete*) const; //subtract this and athlete

BST& BST::operator -= (const char* name)
{
    if (remove(root, name))
        std::cout << "Removed." << std::endl;
    else
        std::cout << "Could not find that name." << std::endl;

    return *this;
}

std::ostream& operator << (std::ostream& out, const BST& my_tree)
{
    my_tree.display(out, my_tree.root);
    return out;
}

void BST::remove_all()
{
    remove_all(root);
}

//void copy(BNode*& root, BNode* source_root);

void BST::insert(BNode*& root, const Athlete& to_add)
{
    if (!root)
    {
        root = new BNode(); 
        root->set_athlete(to_add);
        return;
    }

    if (root->get_athlete() < to_add)
        insert(root->go_right(), to_add);
    else if (root->get_athlete() > to_add)
        insert(root->go_left(), to_add);
    else
        std::cout << "cry" << std::endl;
}

bool BST::remove(BNode*& root, const char* to_remove)
{
    if (!root)
        return false;

    if (root->get_athlete() == to_remove)
    {
        BNode* temp = NULL;

        if (!root->go_right() && root->go_left())
            temp = root->go_left();
        else if (!root->go_left() && root->go_right())
            temp = root->go_right();
        else if (root->go_left() && root->go_right())
        {
            find_smallest(root->go_right(), root, temp);
            temp->set_left(root->go_left());
            temp->set_right(root->go_right());
        }

        delete root;
        root = temp;
        return true;
    }
    
    if (root->get_athlete() < to_remove)
        return remove(root->go_right(), to_remove);
    return remove(root->go_left(), to_remove);
}

void BST::find_smallest(BNode* root, BNode*& parent, BNode*& fill) const
{
    if (!root->go_left())
    {
        fill = root;
        if (parent->go_right() == root)
            parent->set_right(root->go_right());
        else
            parent->set_left(root->go_right());
        return;
    }
    find_smallest(root->go_left(), root, fill);
}

// in-order traversal
void BST::display(std::ostream& out, BNode* root) const
{
    if (!root)
        return;

    display(out, root->go_left());
    out << root->get_athlete() << std::endl;
    display(out, root->go_right());
}

void BST::remove_all(BNode*& root)
{
    if (!root)
        return;

    remove_all(root->go_left());
    remove_all(root->go_right());
    delete root; 
    root = NULL;
}
