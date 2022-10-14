#include <cstring>
#include <iostream>
#include <vector>

/* Andy Fleischer - CS202 - Program 3 - 8/6/2021
 * ---------------------------------------------
 * This file lays out the classes that form the basic
 * hierarchy of Olympic sports and athletes. Every
 * athlete has a country, name, and background info.
 * The supported sports are running, swimming, and 
 * baseball, each of which derives from Sport and has
 * unique data, plus a list of necessary skills.
*/

class Sport
{
    public:
        Sport();
        virtual ~Sport();
        
        bool operator == (const Sport&); //is it a match
        bool operator != (const Sport&); //is it not a match
        //Sport& operator += (const std::string&); //add a skill
        //Sport& operator -= (const std::string&); //remove a skill

        std::string& operator [] (int index); //get certain skill

        friend std::ostream& operator << (std::ostream&, const Sport&); //display
        friend std::istream& operator >> (std::istream&, Sport&); //read


    protected:
        void read(std::istream&);

        std::vector<std::string> skills; 
};

class Running: public Sport
{
    public:
        Running();

        bool operator == (const Running&); //is it a match
        bool operator != (const Running&); //is it not a match
        friend std::ostream& operator << (std::ostream&, const Running&); //display
        friend std::istream& operator >> (std::istream&, Running&); //read

    private:
        int meters;
        bool is_relay;
};

class Swimming: public Sport
{
    public:
        Swimming();
        
        bool operator == (const Swimming&); //is it a match
        bool operator != (const Swimming&); //is it not a match
        friend std::ostream& operator << (std::ostream&, const Swimming&); //display
        friend std::istream& operator >> (std::istream&, Swimming&); //read

    private:
        int meters;
        std::string stroke;
};

class Baseball: public Sport
{
    public:
        Baseball();

        bool operator == (const Baseball&); //is it a match
        bool operator != (const Baseball&); //is it not a match
        friend std::ostream& operator << (std::ostream&, const Baseball&); //display
        friend std::istream& operator >> (std::istream&, Baseball&); //read
    
    private:
        std::string stadium;
        std::string first_country;
        std::string second_country;
};

class Node
{
    public:
        Node();
        ~Node();

        Node *& go_next();
        void set_next(Node* new_next);
        Sport * get_sport();
        void set_sport(Sport* new_sport);

    private:
        Sport* sport;
        Node* next;    
};

class LLL
{
    public:
        LLL();
        LLL(const LLL& source);
        ~LLL();

        LLL& operator = (const LLL&);

        //LLL operator + (const LLL&) const; //concatenate this and list
        //LLL& operator += (const LLL&); //concatenate list to this

        LLL operator + (void*) const; //add this and sport
        LLL& operator += (Sport*); //add sport to this

        LLL operator - (void*) const; //subtract this and sport
        LLL& operator -= (Sport*); //remove sport from this

        Node& operator [] (int index) const;

        friend std::ostream& operator << (std::ostream&, const LLL&); //display
        
        void remove_all(); //remove all nodes

    private:
        //helpers
        void copy(Node*& head, Node* source_head);
        //void concat(Node*& head, Node* source_head);
        bool remove(Node*& head, Sport* to_remove);
        void display(std::ostream& out, Node* head) const;
        void remove_all(Node*& head);

        Node* head;
};


class Athlete //Athlete last since it contains an LLL
{
    public:
        Athlete();
        ~Athlete();
        Athlete(const Athlete&);

        Athlete& operator = (const Athlete&);

        bool operator < (const char*);
        bool operator <= (const char*);
        bool operator > (const char*);
        bool operator >= (const char*);
        bool operator == (const char*);
        bool operator != (const char*);

        bool operator < (const Athlete&);
        bool operator <= (const Athlete&);
        bool operator > (const Athlete&);
        bool operator >= (const Athlete&);
        bool operator == (const Athlete&);
        bool operator != (const Athlete&);

        friend std::ostream& operator << (std::ostream&, const Athlete&); //display
        friend std::istream& operator >> (std::istream&, Athlete&); //read

    private:
        char* name;
        char* country;
        int medals_won[3]; // [bronzes, silvers, golds]
        std::vector<std::string> past_olympics;

        LLL sports;
};


