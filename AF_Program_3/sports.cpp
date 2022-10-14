#include "sports.h"

/* Andy Fleischer - CS202 - Program 3 - 8/6/2021
 * ---------------------------------------------
 * This file implements the classes that form the basic
 * hierarchy of Olympic sports and athletes. Every
 * athlete has a country, name, and background info.
 * The supported sports are running, swimming, and 
 * baseball, each of which derives from Sport and has
 * unique data, plus a list of necessary skills.
*/


// ==== SPORT ==== //


Sport::Sport() 
{}

Sport::~Sport()
{}

bool Sport::operator == (const Sport& other_sport)
{
    for (int i = 0; i < (int)skills.size(); ++i)
    {
        if (skills.at(i) != other_sport.skills.at(i))
            return false;
    }
    return true;
}

bool Sport::operator != (const Sport& other_sport)
{
    for (int i = 0; i < (int)skills.size(); ++i)
    {
        if (skills.at(i) == other_sport.skills.at(i))
            return false;
    }
    return true;
}

std::ostream& operator << (std::ostream& out, const Sport& my_sport)
{
    out << "Skills needed:" << std::endl;
    for (int i = 0; i < (int)my_sport.skills.size(); ++i)
        out << " - " << my_sport.skills.at(i) << std::endl;
    if (my_sport.skills.size() == 0)
        out << " None" << std::endl;

    return out;
}

std::istream& operator >> (std::istream& in, Sport& my_sport)
{
    my_sport.read(in);
    return in;
}

void Sport::read(std::istream& in)
{
    int num_skills;
    std::cout << "Number of skills needed: ";
    in >> num_skills;
    in.ignore(1000, '\n'); in.clear();

    for (int i = 0; i < num_skills; ++i)
    {
        std::string skill;
        std::cout << "Necessary skill: ";
        std::getline(in, skill);
        skills.push_back(skill);

    }
}


// ==== RUNNING ==== //


Running::Running() : meters(100), is_relay(false)
{}

bool Running::operator == (const Running& other_running)
{
    if (meters != other_running.meters || is_relay != other_running.is_relay)
        return false;
    return Sport::operator==(other_running);
}

bool Running::operator != (const Running& other_running)
{
    if (meters == other_running.meters || is_relay == other_running.is_relay)
        return false;
    return Sport::operator!=(other_running);
}

std::ostream& operator << (std::ostream& out, const Running& my_running)
{
    out << my_running.meters << " meter ";
    if (my_running.is_relay)
        out << "relay" << std::endl;
    else
        out << "run" << std::endl;

    out << (Sport)my_running << std::endl;
    return out;
}

std::istream& operator >> (std::istream& in, Running& my_running)
{
    std::cout << "Length (meters): ";
    in >> my_running.meters;
    in.ignore(1000, '\n'); in.clear();

    char relay;
    std::cout << "Relay? (y/n) ";
    in >> relay;
    in.ignore(1000, '\n'); in.clear();

    if (tolower(relay) == 'y')
        my_running.is_relay = true;
    else
        my_running.is_relay = false;

    my_running.read(in);

    return in;
}


// ==== SWIMMING ==== //


Swimming::Swimming() : meters(50), stroke("Freestyle")
{}

bool Swimming::operator == (const Swimming& other_swimming)
{
    if (meters != other_swimming.meters || stroke != other_swimming.stroke)
        return false;
    return Sport::operator==(other_swimming);
}

bool Swimming::operator != (const Swimming& other_swimming)
{
    if (meters == other_swimming.meters || stroke == other_swimming.stroke)
        return false;
    return Sport::operator!=(other_swimming);
}

std::ostream& operator << (std::ostream& out, const Swimming& my_swimming)
{
    out << my_swimming.meters << " meter " << my_swimming.stroke << std::endl;

    out << (Sport)my_swimming << std::endl;
    return out;
}

std::istream& operator >> (std::istream& in, Swimming& my_swimming)
{
    std::cout << "Length (meters): ";
    in >> my_swimming.meters;
    in.ignore(1000, '\n'); in.clear();

    std::cout << "Stroke: ";
    std::getline(in, my_swimming.stroke);

    my_swimming.read(in);
    return in;
}


// ==== BASEBALL === //


Baseball::Baseball()
{}

bool Baseball::operator == (const Baseball& other_baseball)
{
    if (stadium != other_baseball.stadium ||
        first_country != other_baseball.first_country ||
        second_country != other_baseball.second_country)
        return false;
    return Sport::operator==(other_baseball);
}

bool Baseball::operator != (const Baseball& other_baseball)
{
    if (stadium == other_baseball.stadium ||
        first_country == other_baseball.first_country ||
        second_country == other_baseball.second_country)
        return false;
    return Sport::operator!=(other_baseball);
}

std::ostream& operator << (std::ostream& out, const Baseball& my_baseball)
{
    out << "Baseball game - " << my_baseball.first_country << " vs. " << my_baseball.second_country << std::endl;
    out << "At " << my_baseball.stadium << " stadium" << std::endl;

    out << (Sport)my_baseball << std::endl;
    return out;
}

std::istream& operator >> (std::istream& in, Baseball& my_baseball)
{
    std::cout << "Country 1: ";
    std::getline(in, my_baseball.first_country);
    std::cout << "Country 2: ";
    std::getline(in, my_baseball.second_country);
    std::cout << "Stadium: ";
    std::getline(in, my_baseball.stadium);

    my_baseball.read(in);
    return in;
}


// ==== ATHLETE ==== //


Athlete::Athlete()
{
    name = NULL;
    country = NULL;
    for (int i = 0; i < 3; ++i)
        medals_won[i] = 0;
}

Athlete::~Athlete()
{
    delete [] name;
    delete [] country;
}

Athlete::Athlete(const Athlete& source)
{
    name = new char[strlen(source.name) + 1];
    strcpy(name, source.name);

    country = new char[strlen(source.country) + 1];
    strcpy(country, source.country);
    
    for (int i = 0; i < 3; ++i)
        medals_won[i] = source.medals_won[i];

    past_olympics = source.past_olympics;

    sports = source.sports;
}

Athlete& Athlete::operator = (const Athlete& other_athlete)
{
    if (this == &other_athlete) //self-assignment
        return *this;
    if (name)
        delete [] name;
    if (country)
        delete [] country;

    name = new char[strlen(other_athlete.name) + 1];
    strcpy(name, other_athlete.name);

    country = new char[strlen(other_athlete.country) + 1];
    strcpy(country, other_athlete.country);
    
    for (int i = 0; i < 3; ++i)
        medals_won[i] = other_athlete.medals_won[i];

    past_olympics = other_athlete.past_olympics;

    sports = other_athlete.sports;

    return *this;
}

std::ostream& operator << (std::ostream& out, const Athlete& my_athlete)
{
    out << my_athlete.name << std::endl;
    out << "Country: " << my_athlete.country << std::endl;

    out << "Past olympics: " << std::endl;
    for (int i = 0; i < (int)my_athlete.past_olympics.size(); ++i)
        out << " - " << my_athlete.past_olympics.at(i) << std::endl;
    if (my_athlete.past_olympics.size() == 0)
        out << " None" << std::endl;
    
    out << "Medals won: " << std::endl;
    out << " " << my_athlete.medals_won[0] << " Bronze" << std::endl;
    out << " " << my_athlete.medals_won[1] << " Silver" << std::endl;
    out << " " << my_athlete.medals_won[2] << " Gold" << std::endl;

    //out << "Competing in:" << std::endl;
    //out << my_athlete.sports << std::endl;

    return out;
}

std::istream& operator >> (std::istream& in, Athlete& my_athlete)
{
    char name[50];
    char country[50];

    std::cout << "Name: ";
    in.get(name, 50);
    in.ignore(1000, '\n'); in.clear();
    my_athlete.name = new char[strlen(name) + 1];
    strcpy(my_athlete.name, name);

    std::cout << "Country: ";
    in.get(country, 50);
    in.ignore(1000, '\n'); in.clear();
    my_athlete.country = new char[strlen(country) + 1];
    strcpy(my_athlete.country, country);

    int num_past;
    std::cout << "Number of past olympics: ";
    in >> num_past;
    in.ignore(1000, '\n'); in.clear();

    for (int i = 0; i < num_past; ++i)
    {
        std::string past;
        std::cout << "Country and year: ";
        std::getline(in, past);
        my_athlete.past_olympics.push_back(past);
    }

    std::cout << "Medals won" << std::endl;
    std::cout << "----------" << std::endl;
    std::cout << " Bronzes: ";
    in >> my_athlete.medals_won[0];
    std::cout << " Silvers: ";
    in >> my_athlete.medals_won[1];
    std::cout << " Golds: ";
    in >> my_athlete.medals_won[2]; 

/*
    int num_sports;
    std::cout << "Number of sports competing in: ";
    in >> num_sports;
    in.ignore(1000, '\n'); in.clear();
    
    for (int i = 0; i < num_sports; ++i)
    {
        Running run;
        Swimming swim;
        Baseball bb;

        int choice;
        std::cout << "Running (1), swimming (2), or baseball (3)? ";
        in >> choice;
        in.ignore(1000, '\n'); in.clear();

        switch (choice)
        {
            case 1: in >> run;
                    my_athlete.sports += &run;
                    break;
            case 2: in >> swim;
                    my_athlete.sports += &swim;
                    break;
            case 3: in >> bb;
                    my_athlete.sports += &bb;
                    break;
            default: break;
        }
    }
    */
   
    return in;
}

bool Athlete::operator < (const char* other_name)
{ return strcmp(name, other_name) < 0; }

bool Athlete::operator <= (const char* other_name)
{ return strcmp(name, other_name) <= 0; }

bool Athlete::operator > (const char* other_name)
{ return strcmp(name, other_name) > 0; }

bool Athlete::operator >= (const char* other_name)
{ return strcmp(name, other_name) >= 0; }

bool Athlete::operator == (const char* other_name)
{ return strcmp(name, other_name) == 0; }

bool Athlete::operator != (const char* other_name)
{ return strcmp(name, other_name) != 0; }



bool Athlete::operator < (const Athlete& other_athlete)
{ return strcmp(name, other_athlete.name) < 0; }

bool Athlete::operator <= (const Athlete& other_athlete)
{ return strcmp(name, other_athlete.name) <= 0; }

bool Athlete::operator > (const Athlete& other_athlete)
{ return strcmp(name, other_athlete.name) > 0; }

bool Athlete::operator >= (const Athlete& other_athlete)
{ return strcmp(name, other_athlete.name) >= 0; }

bool Athlete::operator == (const Athlete& other_athlete)
{ return strcmp(name, other_athlete.name) == 0; }

bool Athlete::operator != (const Athlete& other_athlete)
{ return strcmp(name, other_athlete.name) != 0; }
