#ifndef TRAM_H
#define TRAM_H

#include <string>

using namespace std;

class Station;
class Tram {
public:

    /**
    * \page Constructor
    *
    * @brief Construct a Tram object.
    *
    * \description Construct a tram.
    */
    Tram();
    /*
    Construct a tram
    */

    /**
    * \page Constructor
    *
    * @brief Construct a Tram object with specified parameters.
    *
    * \description Construct a tram with the given parameters.
    *
    * @param lijn The tram line number.
    * @param type The type of tram.
    * @param huidige The current station of the tram.
    * @param voertuigNr The vehicle number of the tram.
    */
    Tram(int lijn, const string &type, Station *huidige, int voertuigNr);
    /*
    Construct a tram with lijn, type, huidige and voertuigNr
    */

    /**
    * \page Deconstructor
    *
    * @brief Destroy the Tram object.
    *
    * \description Destructor for the Tram class.
    */
    virtual ~Tram();
    /*
    Deconstruct a Tram
    */

    /**
    * \page Simulation
    *
    * @brief Move the tram to the next station.
    *
    * \description Move the tram to the next station based on the given parameters.
    * This function will be overridden.
    *
    * @param volgende The next station to move to.
    * @param nextTramMoved Indicates if the next tram has already moved.
    * @return true if the tram successfully moves to the next station, false otherwise.
    */
    virtual bool goTo(Station *volgende, bool nextTramMoved);
    /*
    Move station to next station
    Function will be overriden
    */

    /**
    * \page Getters & Setters
    *
    * @brief Get the speed of the tram.
    *
    * \description Get the speed of the tram.
    * This function will be overridden.
    *
    * @return The speed of the tram.
    */
    virtual int getSnelheid() const;
    /*
    Get Snelheid of Tram
    Function will be overriden
    */

    /**
    * \page Getters & Setters
    *
    * @brief Get the line number of the tram.
    *
    * \description Get the line number of the tram.
    *
    * @return The line number of the tram.
    */
    int getLijn() const;
    /*
    Gets lijn of Tram
    */

    /**
    * \page Getters & Setters
    *
    * @brief Set the line number of the tram.
    *
    * \description Set the line number of the tram.
    *
    * @param lijn The line number to set for the tram.
    */
    void setLijn(int lijn);
    /*
    Sets lijn of Tram
    Parameter lijn of Tram
    */

    /**
    *  \page Getters & Setters
    *
    * @brief Get the type of the tram.
    *
    * \description  Get the type of the tram.
    *
    * @return The type of the tram.
    */
    const string& getType() const;
    /*
    Gets Type of Tram
    */

    /**
    * \page Getters & Setters
    *
    * @brief Set the type of the tram.
    *
    * \description Set the type of the tram.
    *
    * @param type of the tram
    */
    void setType(const string& Type);
    /*
    Sets Type of Tram
    Parameter Type of Tram
    */


    /**
    *  \page Getters & Setters
    *
    * @brief Get the vehicle number of the tram.
    *
    *\description  Get the vehicle number of the tram.
    *
    * @return The vehicle number of the tram.
    */
    int getVoertuigNr() const;
    /*
    Gets Nr of Tram
    */

    /**
    * \page Getters & Setters
    *
    * @brief Set the vehicle number of the tram.
    *
    *\description  Set the vehicle number of the tram.
    *
    * @param voertuigNr The vehicle number to set for the tram.
    */
    void setVoertuigNr(int voertuigNr);
    /*
    Sets Nr of Tram
    Parameter Nr of Tram
    */

    /**
    * \page Getters & Setters
    *
    * @brief Get the current station of the tram.
    *
    * \description Get the current station of the tram.
    *
    * @return The current station of the tram.
    */
    Station* getHuidige() const;
    /*
    Gets Huidige Station of Tram
    */

    /**
    * \page Getters & Setters
    *
    * @brief Set the current station of the tram.
    *
    * \description Set the current station of the tram.
    *
    * @param huidige The current station to set for the tram.
    */
    void setHuidige(Station* huidige);
    /*
    Sets Huidige Station of Tram
    Parameter Huidige Station of Tram
    */

    /**
    *  \page Getters & Setters
    *
    * @brief Check if the tram has moved.
    *
    * \description Check if the tram has moved from its current station.
    *
    * @return true if the tram has moved, false otherwise.
    */
    bool hasItMoved() const;
    /*
    Gets the Move status of a tram
    */

    /**
    * \page Getters & Setters
    *
    * @brief Set the move status of the tram.
    *
    * \description Set the move status of the tram.
    *
    * @param HasMoved The move status of the tram.
    */
    void moved(bool HasMoved);
    /*
    Sets Move status of Tram
    Parameter Move status of Tram
    */

    /**
    * \page Getters & Setters
    *
    * @brief Get the repair cost of the tram.
    *
    * \description Get the repair cost of the tram.
    * This function will be overridden for PCC.
    *
    * @return The repair cost of the tram.
    */
    virtual int getReparatieKost() const;
    /*
    Gets the increment Kost of a tram
    Function will be overriden for PCC
    */

    /**
    * \page Getters & Setters
    *
    * @brief Set the repair cost of the tram.
    *
    * \description Set the repair cost of the tram.
    * This function will be overridden for PCC.
    *
    * @param reparatieKost The repair cost to set for the tram.
    */
    virtual void setReparatieKost(int reparatieKost);
    /*
    Sets the increment Kost of a tram
    Function will be overriden for PCC
    Parameter increment Kost
    */

    /**
    * \page Getters & Setters
    *
    * @brief Get the current cost of the tram.
    *
    * \description Get the current cost of the tram.
    * This function will be overridden for PCC.
    *
    * @return The current cost of the tram.
    */
    virtual int getKost() const;
    /*
    Gets huidige Kost of Tram
    Function will be overriden for PCC
    */

    /**
    * \page Getters & Setters
    *
    * @brief Set the current cost of the tram.
    *
    * \description Set the current cost of the tram.
    * This function will be overridden for PCC.
    *
    * @param kost The current cost to set for the tram.
    */
    virtual void setKost(int kost);
    /*
    Sets huidige Kost of Tram
    Function will be overriden for PCC
    Parameter huidige kost
    */

    /**
    * \page Getters & Setters
    *
    * @brief Get the repair time of the tram.
    *
    * \description Get the repair time of the tram.
    * This function will be overridden for PCC.
    *
    * @return The repair time of the tram.
    */
    virtual int getReparatieTijd() const;
    /*
    Gets the duration of reparation of a tram
    Function will be overriden for PCC
    */

    /**
    * \page Getters & Setters
    *
    * @brief Set the repair time of the tram.
    *
    * \description Set the repair time of the tram.
    * This function will be overridden for PCC.
    *
    * @param reparatieTijd The repair time to set for the tram.
    */
    virtual void setReparatieTijd(int reparatieTijd);
    /*
    Sets the duration of reparation of a tram
    Function will be overriden for PCC
    Parameter duration of reparation
    */

    /**
    * \page Getters & Setters
    *
    * @brief Get the repair progress of the tram.
    *
    * \description Get the repair progress of the tram.
    * This function will be overridden for PCC.
    *
    * @return The repair progress of the tram.
    */
    virtual int getReparatieProgress() const;
    /*
    Gets the reparation progress of a tram
    Function will be overriden for PCC
    */

    /**
    * \page Getters & Setters
    *
    * @brief Set the repair progress of the tram.
    *
    * \description Set the repair progress of the tram.
    * This function will be overridden for PCC.
    *
    * @param reparatieProgress The repair progress to set for the tram.
    */
    virtual void setReparatieProgress(int reparatieProgress);
    /*
    Sets the reparation progress of a tram
    Function will be overriden for PCC
    Parameter reparation progress of tram
    */

    /**
    * \page Getters & Setters
    *
    * @brief Get the number of defects of the tram.
    *
    * \description Get the number of defects of the tram.
    * This function will be overridden for PCC.
    *
    * @return The number of defects of the tram.
    */
    virtual int getDefecten() const;
    /*
    Gets the number of defects of a tram
    Function will be overriden for PCC
    */

    /**
    * \page Getters & Setters
    *
    * @brief Set the number of defects of the tram.
    *
    * \description Set the number of defects of the tram.
    * This function will be overridden for PCC.
    *
    * @param defecten The number of defects to set for the tram.
    */
    virtual void setDefecten(int defecten);
    /*
    Sets the number of defects of a tram
    Function will be overriden for PCC
    Parameter huidige defects
    */

    /**
    * \page Getters & Setters
    *
    * @brief Get the defect limit before the tram breaks down.
    *
    * \description Get the defect limit before the tram breaks down.
    * This function will be overridden for PCC.
    *
    * @return The defect limit before the tram breaks down.
    */
    virtual int getDefectenLimiet() const;
    /*
    Gets the defectlimit before tram breaks
    Function will be overriden for PCC
    */

    /**
    * \page Getters & Setters
    *
    * @brief Set the defect limit before the tram breaks down.
    *
    * \description Set the defect limit before the tram breaks down.
    * This function will be overridden for PCC.
    *
    * @param defectenLimiet The defect limit to set for the tram.
    */
    virtual void setDefectenLimiet(int defectenLimiet);
    /*
    Sets the defectlimit before tram breaks
    Function will be overriden for PCC
    Parameter defectlimit
    */

    /**
    * \page Getters & Setters
    *
    * @brief Check if the tram is in a breakdown state.
    *
    *\description  Check if the tram is in a breakdown state.
    * This function will be overridden for PCC.
    *
    * @return true if the tram is in a breakdown state, false otherwise.
    */
    virtual bool isInPanne() const;
    /*
    Gets the status of a tram
    Function will be overriden for PCC
    */

    /**
    * \page Getters & Setters
    *
    * @brief Set the breakdown status of the tram.
    *
    * \description Set the breakdown status of the tram.
    * This function will be overridden for PCC.
    *
    * @param inPanne The breakdown status of the tram.
    */
    virtual void setInPanne(bool inPanne);
    /*
    Sets the status of a tram
    Function will be overriden for PCC
    Parameter Tram broken status
    */

private:
    int Lijn;
    string type;
    Station* Huidige;
    int VoertuigNr;
    bool hasMoved;
};





class PCC : public  Tram{
public:
    /**
    * \page Constructor
    *
    * @brief Construct a PCC object.
    *
    * \description Construct a PCC tram.
    */
    PCC();
    /*
    Construct PCC
    */

    /**
    * \page Constructor
    *
    * @brief Construct a PCC object with specified parameters.
    *
    * \description Construct a PCC tram with the given parameters.
    *
    * @param lijn The tram line number.
    * @param type The type of tram.
    * @param huidige The current station of the tram.
    * @param voertuigNr The vehicle number of the tram.
    * @param reparatieKost The repair cost of the tram.
    * @param reparatieTijd The repair time of the tram.
    * @param defectenLimiet The defect limit before the tram breaks down.
    */
    PCC(int lijn, const string &type, Station *huidige, int voertuigNr, int reparatieKost, int reparatieTijd, int defectenLimiet);
    /*
    Construct a Stadslijner with lijn, type, beginstation, nr, reparation cost, reparation duration and defect limit
    */

    /**
    * \page Constructor
    *
    * @brief Construct a PCC object with specified parameters.
    *
    * \description Construct a PCC tram with the given parameters.
    *
    * @param lijn The tram line number.
    * @param type The type of tram.
    * @param huidige The current station of the tram.
    * @param voertuigNr The vehicle number of the tram.
    */
    PCC(int lijn, const string &type, Station *huidige, int voertuigNr);
    /*
    Construct a Stadslijner with lijn, type, beginstation and nr
    */

    /**
    * \page Deconstructor
    *
    * @brief Destroy the PCC object.
    *
    * \description Destructor for the PCC class.
    */
    virtual ~PCC();
    /*
    Deconstruct PCC
    */

    /**
    * \page Simulation
    *
    * @brief Move the PCC tram to the next station.
    *
    * \description Move the PCC tram to the next station if the tram is not broken.
    * If the tram is broken, continue the repair process.
    * If the tram cannot move to the next station because the next station is in use and the next tram has already moved, the tram won't move.
    *
    * @param volgende The next station to move to.
    * @param nextTramMoved Indicates if the next tram has already moved.
    * @return true if the PCC tram successfully moves to the next station or continues repair, false otherwise.
    */
    bool goTo(Station *volgende, bool nextTramMoved);
    /*
    Move tram to next station if tram is not broken, else continue reparation of tram
    if tram cannot move to next station because next station is in use and next tram has moved already, then dont move tram
    */

    /**
    * \page Getters & Setters
    *
    * @brief Get the speed of the PCC tram.
    *
    * \description Get the current speed of the PCC tram.
    *
    * @return The speed of the PCC tram.
    */
    int getSnelheid() const;
    /*
    Get Snelheid of PCC
    */

    /**
    * \page Getters & Setters
    *
    * @brief Get the repair cost of the tram.
    *
    * \description Get the repair cost of the tram.
    *
    * @return The repair cost of the tram.
    */
    int getReparatieKost() const;
    /*
    Gets the increment Kost of a tram
    */

    /**
    * \page Getters & Setters
    *
    * @brief Set the repair cost of the tram.
    *
    * \description Set the repair cost of the tram.
    *
    * @param reparatieKost The repair cost to set for the tram.
    */
    void setReparatieKost(int reparatieKost);
    /*
    Sets the increment Kost of a tram
    Parameter increment Kost
    */

    /**
    * \page Getters & Setters
    *
    * @brief Get the current cost of the tram.
    *
    * \description Get the current cost of the tram.
    *
    * @return The current cost of the tram.
    */
    virtual int getKost() const;
    /*
    Gets huidige Kost of Tram
    */

    /**
    * \page Getters & Setters
    *
    * @brief Set the current cost of the tram.
    *
    * \description Set the current cost of the tram.
    *
    * @param kost The current cost to set for the tram.
    */
    virtual void setKost(int kost);
    /*
    Sets huidige Kost of Tram
    Parameter huidige kost
    */

    /**
    * \page Getters & Setters
    *
    * @brief Get the repair time of the tram.
    *
    * \description Get the repair time of the tram.
    *
    * @return The repair time of the tram.
    */
    int getReparatieTijd() const;
    /*
    Gets the duration of reparation of a tram
    Function will be overriden for PCC
    */

    /**
    * \page Getters & Setters
    *
    * @brief Set the repair time of the tram.
    *
    * \description Set the repair time of the tram.
    *
    * @param reparatieTijd The repair time to set for the tram.
    */
    void setReparatieTijd(int reparatieTijd);
    /*
    Sets the duration of reparation of a tram
    Parameter duration of reparation
    */

    /**
    * \page Getters & Setters
    *
    * @brief Get the repair progress of the tram.
    *
    * \description Get the repair progress of the tram.
    *
    * @return The repair progress of the tram.
    */
    int getReparatieProgress() const;
    /*
    Gets the reparation progress of a tram
    */

    /**
    * \page Getters & Setters
    *
    * @brief Set the repair progress of the tram.
    *
    * \description Set the repair progress of the tram.
    *
    * @param reparatieProgress The repair progress to set for the tram.
    */
    virtual void setReparatieProgress(int reparatieProgress);
    /*
    Sets the reparation progress of a tram
    Parameter reparation progress of tram
    */

    /**
    * \page Getters & Setters
    *
    * @brief Get the number of defects of the tram.
    *
    * \description Get the number of defects of the tram.
    *
    * @return The number of defects of the tram.
    */
    int getDefecten() const;
    /*
    Gets the number of defects of a tram
    */

    /**
    * \page Getters & Setters
    *
    * @brief Set the number of defects of the tram.
    *
    * \description Set the number of defects of the tram.
    *
    * @param defecten The number of defects to set for the tram.
    */
    void setDefecten(int defecten);
    /*
    Sets the number of defects of a tram
    Parameter huidige defects
    */

    /**
    * \page Getters & Setters
    *
    * @brief Get the defect limit before the tram breaks down.
    *
    * \description Get the defect limit before the tram breaks down.
    *
    * @return The defect limit before the tram breaks down.
    */
    int getDefectenLimiet() const;
    /*
    Gets the defectlimit before tram breaks
    */

    /**
    * \page Getters & Setters
    *
    * @brief Set the defect limit before the tram breaks down.
    *
    * \description Set the defect limit before the tram breaks down.
    *
    * @param defectenLimiet The defect limit to set for the tram.
    */
    void setDefectenLimiet(int defectenLimiet);
    /*
    Sets the defectlimit before tram breaks
    Parameter defectlimit
    */

    /**
    * \page Getters & Setters
    *
    * @brief Check if the tram is in a breakdown state.
    *
    * \description  Check if the tram is in a breakdown state.
    *
    * @return true if the tram is in a breakdown state, false otherwise.
    */
    bool isInPanne() const;
    /*
    Gets the status of a tram
    */

    /**
    * \page Getters & Setters
    *
    * @brief Set the breakdown status of the tram.
    *
    * \description Set the breakdown status of the tram.
    *
    * @param inPanne The breakdown status of the tram.
    */
    void setInPanne(bool inPanne);
    /*
    Sets the status of a tram
    Parameter Tram broken status
    */

private:
    int reparatieKost;
    int kost;
    int reparatieTijd;
    int reparatieProgress;
    int defecten;
    int defectenLimiet;
    bool inPanne;
};





class Albatros : public  Tram{
public:
    /**
    * \page Constructor
    *
    * @brief Construct a Albatros object.
    *
    * \description Construct a Albatros tram.
    */
    Albatros();
    /*
    Construct an Albatros
    */

    /**
    * \page Constructor
    *
    * @brief Construct a Albatros object with specified parameters.
    *
    * \description Construct a Albatros tram with the given parameters.
    *
    * @param lijn The tram line number.
    * @param type The type of tram.
    * @param huidige The current station of the tram.
    * @param voertuigNr The vehicle number of the tram.
    */
    Albatros(int lijn, const string &type, Station *huidige, int voertuigNr);
    /*
    Construct an Albatros with lijn, type, beginstation and nr
    */

    /**
    * \page Deconstructor
    *
    * @brief Destroy the Albatros object.
    *
    * \description Destructor for the Albatros class.
    */
    virtual ~Albatros();
    /*
    Deconstruct Albatros
    */

    /**
    * \page Getters & Setters
    *
    * @brief Get the speed of the Albatros tram.
    *
    * \description Get the current speed of the Albatros tram.
    *
    * @return The speed of the Albatros tram.
    */
    int getSnelheid() const;
    /*
    Get Snelheid of Albatros
    */

    /**
    * \page Simulation
    *
    * @brief Move the Albatros  tram to the next station.
    *
    * \description Move the Albatros  tram to the next station if the next station is empty and the next tram has not yet moved.
    *
    * @param volgende The next station to move to.
    * @param nextTramMoved Indicates if the next tram has already moved.
    * @return true if the Albatros  tram successfully moves to the next station, false otherwise.
    */
    bool goTo(Station *volgende, bool nextTramMoved);
    /*
    Move Albatros to next station if next station is empty and next tram has not yet moved
    */
};





class Stadslijner : public  Tram{
public:
    /**
    * \page Constructor
    *
    * @brief Construct a Stadslijner object.
    *
    * \description Construct a Stadslijner tram.
    */
    Stadslijner();
    /*
    Construct a Stadslijner
    */

    /**
    * \page Constructor
    *
    * @brief Construct a Stadslijner object with specified parameters.
    *
    * \description Construct a Stadslijner tram with the given parameters.
    *
    * @param lijn The tram line number.
    * @param type The type of tram.
    * @param huidige The current station of the tram.
    * @param voertuigNr The vehicle number of the tram.
    */
    Stadslijner(int lijn, const string &type, Station *huidige, int voertuigNr);
    /*
    Construct a Stadslijner with lijn, type, beginstation and nr
    */

    /**
    * \page Deconstructor
    *
    * @brief Destroy the Stadslijner object.
    *
    * \description Destructor for the Stadslijner class.
    */
    virtual ~Stadslijner();
    /*
    deconstruct a Stadslijner
    */

    /**
    * \page Simulation
    *
    * @brief Move the Stadslijner tram to the next station.
    *
    * \description Move the Stadslijner tram to the next station if the next station is empty and the next tram has not yet moved.
    *
    * @param volgende The next station to move to.
    * @param nextTramMoved Indicates if the next tram has already moved.
    * @return true if the Stadslijner tram successfully moves to the next station, false otherwise.
    */
    bool goTo(Station *volgende, bool nextTramMoved);
    /*
    Move Stadslijner to next station if next station is empty and next tram has not yet moved
    */

    /**
    * \page Getters & Setters
    *
    * @brief Get the speed of the Stadslijner tram.
    *
    * \description Get the current speed of the Stadslijner tram.
    *
    * @return The speed of the Stadslijner tram.
    */
    int getSnelheid() const;
    /*
    Get Snelheid of Stadslijner
    */
};


#endif //TRAM_H
