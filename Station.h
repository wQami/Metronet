#ifndef STATION_H
#define STATION_H

#include "Spoor.h"
#include <string>
#include <vector>

using namespace std;

class Station {
public:
    //_________________ Construct & Deconstruct _________________//
    Station();
    explicit Station(const string &naam);
    Station(const string &naam, const vector<Spoor *> &sporen, const string &type);
    virtual ~Station();

    //_________________ Simulate _________________//
    virtual bool allowed(string tramType);
    Spoor* getSpoor(int lijn);

    //_________________ Input _________________//
    bool initializedCorrectly();

    //_________________ Output _________________//
    void incrementBezoeken();
    void incrementBezetting();

    //_________________ Getters & Setters _________________//
    const string &getNaam() const;
    void setNaam(const string &naam);

    const vector<Spoor *> &getSporen() const;
    void setSporen(const vector<Spoor *> &sporen);

    const string &getType() const;
    void setType(const string &type);

    int getBezoeken() const;
    void setBezoeken(int bezoeken);

    int getBezetting() const;
    void setBezetting(int bezetting);

    bool isBezet() const;
    void setBezet(bool bezet);

private:
    string Naam;
    vector<Spoor*> Sporen;
    string type;
    int bezoeken;
    int bezetting;
    bool bezet;
};


class Metrostation :public Station{
public:
    //_________________ Construct & Deconstruct _________________//
    Metrostation();
    explicit Metrostation(const string &naam);
    Metrostation(const string &naam, const vector<Spoor *> &sporen, const string &type);
    virtual ~Metrostation();

    //_________________ Simulate _________________//
    bool allowed(string tramType);
};

class Halte :public Station{
public:
    //_________________ Construct & Deconstruct _________________//
    Halte();
    explicit Halte(const string &naam);
    Halte(const string &naam, const vector<Spoor *> &sporen, const string &type);

    virtual ~Halte();

    //_________________ Simulate _________________//
    bool allowed(string tramType);
};

#endif //STATION_H
