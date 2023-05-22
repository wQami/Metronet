#ifndef SPOOR_H
#define SPOOR_H

class Station;
class Spoor {
private:
    int spoorNr;
    Station* Volgende;
    Station* Vorige;
    int Bezoeken;
    bool bezet;
    int bezetting;
    bool empty;

public:
    //_________________ Construct & Deconstruct _________________//
    Spoor();
    Spoor(int spoorNr, Station *volgende, Station *vorige);
    virtual ~Spoor();

    //_________________ Output _________________//
    void incrementBezoeken();
    void incrementBezetting();

    //_________________ Getters & Setter _________________//
    int getSpoorNr() const;
    void setSpoorNr(int spoornr);

    Station *getVolgende() const;
    void setVolgende(Station *volgende);

    Station *getVorige() const;
    void setVorige(Station *vorige);

    int getBezoeken() const;
    void setBezoeken(int bezoeken);

    bool isBezet() const;
    void setBezet(bool bezet);

    int getBezetting() const;
    void setBezetting(int bezetting);

    bool isEmpty() const;

    void setEmpty(bool empty);
};


#endif //SPOOR_H
