
#include "gtest/gtest.h"
#include "Metronet.h"
#include "DesignByContract.h"
#include "cstring"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct MetronetTests : ::testing::Test {
    MetronetTests(){}


    bool isNumber(const std::string& str) {
        for (long unsigned int i = 0; i < str.size(); i++) {
            if (!isdigit(str[i])) {
                return false;
            }
        }
        return true;
    }

    Station* findOrAddStation(const string &name, vector<Station *> &stations) {
        // Search Station and return it to the datastructure
        for (vector<Station *>::iterator it = stations.begin(); it != stations.end(); ++it) {
            if ((*it)->getNaam() == name){
                return *it;
            }
        }
        // Add the station with the given name to the datastructure
        Station *newStation = new Station(name);
        stations.push_back(newStation);
        return newStation;
    }

    Station* getStation(const string &name, vector<Station *> &stations){
        // Search Station
        Station* station = NULL;
        for (vector<Station *>::iterator it = stations.begin(); it != stations.end(); ++it) {
            if ((*it)->getNaam() == name){
                station =  *it;
            }
        }
        return station;
    }

    bool hasCorrespondingTrack(Station *&station, Tram *&tram) {
        // Get the sporen of the station
        vector<Spoor*> sporen = station->getSporen();

        // Check if any spoor in the station corresponds to the tram's line
        for (vector<Spoor*>::iterator it = sporen.begin(); it != sporen.end(); ++it) {
            Spoor* spoor = *it;

            if (spoor->getSpoorNr() == tram->getLijn()) {
                return true;
            }
        }

        // No corresponding track was found
        return false;
    }

    void validRead(string xml){
        vector<Station*> stations;
        vector<Tram*> trams;

        string filename = xml.substr(0,xml.length()-4) + "Input.txt";
        ofstream errorOutput(filename.c_str());

        // Open document
        TiXmlDocument doc(xml.c_str());
        bool successfulLoad = doc.LoadFile();
        (successfulLoad) ? "" : errorOutput << "Could not load file.";

        // Load metronet element
        TiXmlElement* metronet = doc.FirstChildElement("METRONET");
        (metronet) ? "" : errorOutput << "'Metronet' element not found in file";

        Station* station;
        Station* Next;
        Station* Previous;
        TiXmlElement* name;
        TiXmlElement* type;
        TiXmlElement* spoor;
        Spoor* Track;
        TiXmlElement* spoorNr;
        TiXmlElement* volgende;
        TiXmlElement* vorige;
        string Type;

        // Iterate over stations
        int aantalSporen;
        for (TiXmlElement* stat = metronet->FirstChildElement("STATION"); stat; stat = stat->NextSiblingElement("STATION")){

            // Get name, type and first spoor elements out xml file
            name = stat->FirstChildElement("naam");
            type = stat->FirstChildElement("type");
            spoor = stat->FirstChildElement("SPOOR");

            (name) ? "" : errorOutput << "Station is missing 'name' in XML file";
            (type) ? "" : errorOutput << "Station is missing 'type' in XML file";
            (spoor) ? "" : errorOutput << "Station is missing at least one 'spoor' in XML file";

            (!name->NextSiblingElement("name")) ? "" : errorOutput << "Station has more than one 'name'";
            (!type->NextSiblingElement("type")) ? "" : errorOutput << "Station has more than one 'type'";

            for(TiXmlElement* element = stat->FirstChildElement(); element; element = element->NextSiblingElement()){
                ((string) element->Value() == "naam" || (string) element->Value() == "type" || (string) element->Value() == "SPOOR") ? "" : errorOutput << "Unkown tag!";
            }



            // Create Station or Add it to stations if it doesn't exist yet
            station = findOrAddStation(name->FirstChild()->Value(), stations);

            // Check Type
            Type = type->FirstChild()->Value();
            (Type == "Metrostation" || Type == "Halte") ? "" : errorOutput << "Station type is unknown to system";
            station->setType(Type);

            // Iterate over Sporen
            vector<Spoor*> sporen;
            vector<int> SpoorNrs;
            aantalSporen = 0;
            for (; spoor; spoor = spoor->NextSiblingElement("SPOOR")){
                aantalSporen++;
                (Type != "Halte" || aantalSporen <= 1) ? "" : errorOutput << "Halte cannot have more than one track.";


                // Get spoorNr, volgende and vorige elements out xml file
                spoorNr = spoor->FirstChildElement("spoorNr");
                volgende = spoor->FirstChildElement("volgende");
                vorige = spoor->FirstChildElement("vorige");

                // Preconditions for elke spoor
                (spoorNr) ? "" : errorOutput << "Spoor is missing 'spoorNr' in XML file";
                (volgende) ? "" : errorOutput << "Spoor is missing 'volgende' in XML file";
                (vorige) ? "" : errorOutput << "Spoor is missing 'vorige' in XML file";

                // Only one of each element
                (!spoorNr->NextSiblingElement("spoorNr")) ? "" : errorOutput << "Spoor has more than one 'name'";
                (!volgende->NextSiblingElement("volgende")) ? "" : errorOutput << "Spoor has more than one 'volgende'";
                (!vorige->NextSiblingElement("vorige")) ? "" : errorOutput << "Spoor has more than one 'vorige'";

                // Make new Spoor
                Next = findOrAddStation(volgende->FirstChild()->Value(), stations);
                Previous = findOrAddStation(vorige->FirstChild()->Value(), stations);
                Track = new Spoor(atoi(spoorNr->GetText()), Next , Previous);

                //Make sure certain Spoor isn't more than once in a station
                (find(SpoorNrs.begin(), SpoorNrs.end(), Track->getSpoorNr()) == SpoorNrs.end()) ? "" : errorOutput << "Spoor with certain SpoorNr occurs more than once in station in XML file";

                // Add to sporen
                SpoorNrs.push_back(Track->getSpoorNr());
                sporen.push_back(Track);
            }
            station->setSporen(sporen);
        }

        // Make sure every station on was initialized
        for (vector<Station*>::iterator spoorStation = stations.begin(); spoorStation != stations.end(); ++spoorStation) {
            ((*spoorStation)->initializedCorrectly()) ? "" : errorOutput << "Volgende or Vorige on a Spoor is not specified in XML file";
        }

        Station* BeginStation;
        Tram* newTram;
        TiXmlElement* lijnNr;
        TiXmlElement* voertuigNr;
        TiXmlElement* beginStation;
        TiXmlElement* aantalDefecten;
        TiXmlElement* reparatieTijd;
        TiXmlElement* reparatieKost;

        // Iterate over trams
        for (TiXmlElement* tram = metronet->FirstChildElement("TRAM"); tram; tram = tram->NextSiblingElement("TRAM")){

            // Get lijnNr, type, voertuigNr and beginstation elements out xml file
            lijnNr = tram->FirstChildElement("lijnNr");
            type = tram->FirstChildElement("type");
            voertuigNr = tram->FirstChildElement("voertuigNr");
            beginStation = tram->FirstChildElement("beginStation");
            reparatieTijd = tram->FirstChildElement("reparatieTijd");
            aantalDefecten = tram->FirstChildElement("aantalDefecten");
            reparatieKost = tram->FirstChildElement("reparatieKost");

            // Preconditions for elke tram in XML
            (lijnNr) ? "" : errorOutput << "Tram is missing 'lijnNr' in XML file";
            (type) ? "" : errorOutput << "Tram is missing 'type' in XML file";
            (voertuigNr) ? "" : errorOutput << "Tram is missing 'voertuigNr' in XML file";
            (beginStation) ? "" : errorOutput << "Tram is missing 'beginStation' in XML file";
            (reparatieTijd) ? "" : errorOutput << "Tram is missing 'reparatieTijd' in XML file";
            (aantalDefecten) ? "" : errorOutput << "Tram is missing 'defecten' in XML file";
            (reparatieKost) ? "" : errorOutput << "Tram is missing 'reparatieKost' in XML file";

            // Only one of each element
            (!lijnNr->NextSiblingElement("lijnNr")) ? "" : errorOutput << "Tram has more than one 'lijnNr'";
            (!type->NextSiblingElement("type")) ? "" : errorOutput << "Tram has more than one 'type'";
            (!voertuigNr->NextSiblingElement("voertuigNr")) ? "" : errorOutput << "Tram has more than one 'voertuigNr'";
            (!beginStation->NextSiblingElement("beginStation")) ? "" : errorOutput << "Tram has more than one 'beginStation'";
            (!reparatieTijd->NextSiblingElement("reparatieTijd")) ? "" : errorOutput << "Tram has more than one 'reparatieTijd'";
            (!aantalDefecten->NextSiblingElement("aantalDefecten")) ? "" : errorOutput << "Tram has more than one 'aantalDefecten'";
            (!reparatieKost->NextSiblingElement("reparatieKost")) ? "" : errorOutput << "Tram has more than one 'reparatieKost'";


            for(TiXmlElement* element = tram->FirstChildElement(); element; element = element->NextSiblingElement()){
                ((string) element->Value() == "lijnNr" || (string) element->Value() == "type" || (string) element->Value() == "voertuigNr" || (string) element->Value() == "beginStation" || (string) element->Value() == "reparatieTijd" || (string) element->Value() == "aantalDefecten" || (string) element->Value() == "reparatieKost") ? "" : errorOutput << "Unkown tag!";
            }


            (isNumber(lijnNr->GetText())) ? "" : errorOutput << "'lijnNr' is not a digit";
            (isNumber(voertuigNr->GetText())) ? "" : errorOutput << "'voertuigNr' is not a digit";
            (isNumber(reparatieTijd->GetText())) ? "" : errorOutput << "'reparatieTijd' is not a digit";
            (isNumber(aantalDefecten->GetText())) ? "" : errorOutput << "'aantalDefecten' is not a digit";
            (isNumber(reparatieKost->GetText())) ? "" : errorOutput << "'reparatieKost' is not a digit";


            // Get Type and check if it is allowed
            Type = type->FirstChild()->Value();
            (Type =="PCC" || Type == "Albatros" || Type == "Stadslijner") ? "" : errorOutput << "Tram type is unknown to system";

            // Get beginStation and check if it is initialized
            BeginStation = getStation(beginStation->FirstChild()->Value(),stations);
            (BeginStation) ? "" : errorOutput << "Tram's beginStation does not exist";

            // Create Tram
            newTram = new Tram(atoi(lijnNr->GetText()), Type, BeginStation, atoi(voertuigNr->GetText()));
            newTram->setDefectenLimiet(atoi(aantalDefecten->GetText()));
            newTram->setReparatieKost(atoi(reparatieKost->GetText()));
            newTram->setReparatieTijd(atoi(reparatieTijd->GetText()));
            trams.push_back(newTram);

            // Make Sure begin station has Spoor for the Tram
            (hasCorrespondingTrack(BeginStation,newTram)) ? "" : errorOutput << "There is no Spoor beginstation of Tram";
        }

        // Ensure Elements have been added
        (!stations.empty()) ? "" : errorOutput << "No stations have been added";
        (!trams.empty()) ? "" : errorOutput << "No trams have been added";

        map<int,bool> voertuigWithNr;

        // Make sure every station on was initialized
        for (vector<Tram*>::iterator tr = trams.begin(); tr != trams.end(); ++tr) {
            Tram* tram = *tr;

            // Make sure there aren't 2 Trams with 1 VoertuigNr
            (!voertuigWithNr[tram->getVoertuigNr()]) ? "" : errorOutput << "Tram with the same voertuigNr already exists";

            // Mark this voertuigNr on this lijn as existing
            voertuigWithNr[tram->getVoertuigNr()] = true;

            tram->getHuidige()->getSpoor(tram->getLijn())->setEmpty(false);
        }

        // Testing if the 'name' of every 'STATION' is a letter(s) in the alphabet (ex. A, AA, AZ, AQZ, ...)
        for(unsigned long long int j = 0; j < stations.size(); j++){
            bool letters = true;
            string stationName = stations[j]->getNaam();

            for(unsigned long long int a = 0; a < stationName.length(); a++){
                if(!(stationName[a] >= 'a'&& stationName[a] <= 'z') || !(stationName[a] >= 'A' && stationName[a] <= 'Z')){
                    letters = false;
                }
            }
            (!letters) ? "" : errorOutput << "It is all letters";
        }

        // Testing if every 'BEGINSTATION' exists
        for(unsigned long long int i = 0; i < trams.size(); i++){
            bool correctfound = false;
            for(unsigned long long int j = 0; j < stations.size(); j++){

                if(trams[i]->getHuidige() == stations[j]){
                    correctfound = true;
                }
            }
            (correctfound) ? "" : errorOutput << "'Beginstation' doesn't exist";
        }

        // Testing if every 'SPOOR' has at least one corresponding 'TRAM'
        for(unsigned long long int i = 0; i < stations.size(); i++){
            vector<Spoor*> sporen = stations[i]->getSporen();
            for(unsigned long long int j = 0; j < sporen.size(); j++){
                bool spoorHasTram = false;
                for(unsigned long long int k = 0; k < trams.size(); k++){
                    if(sporen[j]->getSpoorNr() == trams[k]->getLijn()){
                        spoorHasTram = true;
                        break;
                    }
                }
                (spoorHasTram) ? "" : errorOutput << "'SPOOR' has no 'TRAM'";
            }
        }

        // Testing if every 'Tram' is connected
        for(unsigned long long int i = 0; i < trams.size(); i++){
            bool connected = true;
            int lijn = trams[i]->getLijn();
            Station* begin = trams[i]->getHuidige();
            Spoor* huidigeSpoor = begin->getSpoor(lijn);
            (huidigeSpoor) ? "" : errorOutput << "'SPOOR' does not exist";

            Station* volgendeStation = huidigeSpoor->getVolgende();
            int depth = 0;
            while(volgendeStation != begin){
                huidigeSpoor = volgendeStation->getSpoor(lijn);
                (huidigeSpoor) ? "" : errorOutput << "'SPOOR' does not exist";

                volgendeStation = huidigeSpoor->getVolgende();

                if(depth == 27){
                    connected = false;
                    break;
                }

                depth++;
            }
            (connected) ? "" : errorOutput << "'TRAM' is not connected";
        }
    }

    void compareFile(string output, string compare){
        ifstream outputFile;
        outputFile.open(output.c_str());

        ifstream compareFile;
        compareFile.open(compare.c_str());

        string outputLine;
        string compareLine;

        int amountOutputLines = 0;
        int amountCompareLines = 0;

        while(getline(outputFile, outputLine)){
            amountOutputLines++;
        }

        while(getline(compareFile, compareLine)){
            amountCompareLines++;
        }

        ASSERT_EQ(amountOutputLines, amountCompareLines) << "The files are not equal, the amount of lines doesn't match!";

        while(!outputFile.eof()){
            getline(outputFile, outputLine);
            getline(compareFile, compareLine);
            EXPECT_EQ(outputLine, compareLine) << "The files are not equal, the lines do not match!";
        }
    };

    ~MetronetTests(){};
};

TEST_F(MetronetTests, loadingFileRightWay){
    validRead("Basic.xml");
    compareFile("BasicInput.txt", "CompareBasicInput.txt");
}

TEST_F(MetronetTests, simulationOneTram){
    Station A,B,C,D,E;

    Spoor* spoorA = new Spoor (21,&B,&E);
    Spoor* spoorB = new Spoor (21,&C,&A);
    Spoor* spoorC = new Spoor (21,&D,&B);
    Spoor* spoorD = new Spoor(21,&E,&C);
    Spoor* spoorE = new Spoor(21,&A,&D);

    vector<Spoor*> spA;
    spA.push_back(spoorA);

    vector<Spoor*> spB;
    spB.push_back(spoorB);

    vector<Spoor*> spC;
    spC.push_back(spoorC);

    vector<Spoor*> spD;
    spD.push_back(spoorD);

    vector<Spoor*> spE;
    spE.push_back(spoorE);

    A.setNaam("A");
    A.setSporen(spA);
    A.setType("Metrostation");

    B.setNaam("B");
    B.setSporen(spB);
    B.setType("Metrostation");

    C.setNaam("C");
    C.setSporen(spC);
    C.setType("Metrostation");

    D.setNaam("D");
    D.setSporen(spD);
    D.setType("Metrostation");

    E.setNaam("E");
    E.setSporen(spE);
    E.setType("Metrostation");

    vector<Station*> stations;
    stations.push_back(&A);
    stations.push_back(&B);
    stations.push_back(&C);
    stations.push_back(&D);
    stations.push_back(&E);

    Tram twoOne(21,"PCC", &A, 3);
    twoOne.setDefectenLimiet(6);
    twoOne.setReparatieKost(20);
    twoOne.setReparatieTijd(1);

    vector<Tram*> trams;
    trams.push_back(&twoOne);

    MetronetSimulation MS;
    MS.setStations(stations);
    MS.setTrams(trams);

    MS>>3;

    EXPECT_EQ(MS.getTramByNr(3)->getHuidige(), &D) << "Station has not been reached or been surpassed!";
}

TEST_F(MetronetTests, simulationTwoTramDefect){
    Station A,B,C,D,E,F,G,H,I,J;

    Spoor* spoorA = new Spoor(21,&B,&E);
    Spoor* spoorB = new Spoor(21,&C,&A);
    Spoor* spoorC = new Spoor(21,&D,&B);
    Spoor* spoorD = new Spoor(21,&E,&C);
    Spoor* spoorE = new Spoor(21,&A,&D);


    Spoor* spoorF = new Spoor(12,&G,&J);
    Spoor* spoorG = new Spoor(12,&H,&F);
    Spoor* spoorH = new Spoor(12,&I,&G);
    Spoor* spoorI = new Spoor(12,&J,&H);
    Spoor* spoorJ = new Spoor(12,&F,&I);

    vector<Spoor*> spA;
    spA.push_back(spoorA);

    vector<Spoor*> spB;
    spB.push_back(spoorB);

    vector<Spoor*> spC;
    spC.push_back(spoorC);

    vector<Spoor*> spD;
    spD.push_back(spoorD);

    vector<Spoor*> spE;
    spE.push_back(spoorE);

    vector<Spoor*> spF;
    spF.push_back(spoorF);

    vector<Spoor*> spG;
    spG.push_back(spoorG);

    vector<Spoor*> spH;
    spH.push_back(spoorH);

    vector<Spoor*> spI;
    spI.push_back(spoorI);

    vector<Spoor*> spJ;
    spJ.push_back(spoorJ);

    A.setNaam("A");
    A.setSporen(spA);
    A.setType("Metrostation");

    B.setNaam("B");
    B.setSporen(spB);
    B.setType("Metrostation");

    C.setNaam("C");
    C.setSporen(spC);
    C.setType("Metrostation");

    D.setNaam("D");
    D.setSporen(spD);
    D.setType("Metrostation");

    E.setNaam("E");
    E.setSporen(spE);
    E.setType("Metrostation");

    F.setNaam("F");
    F.setSporen(spF);
    F.setType("Metrostation");

    G.setNaam("G");
    G.setSporen(spG);
    G.setType("Metrostation");

    H.setNaam("H");
    H.setSporen(spH);
    H.setType("Metrostation");

    I.setNaam("I");
    I.setSporen(spI);
    I.setType("Metrostation");

    J.setNaam("J");
    J.setSporen(spJ);
    J.setType("Metrostation");

    vector<Station*> stations;
    stations.push_back(&A);
    stations.push_back(&B);
    stations.push_back(&C);
    stations.push_back(&D);
    stations.push_back(&E);
    stations.push_back(&F);
    stations.push_back(&G);
    stations.push_back(&H);
    stations.push_back(&I);
    stations.push_back(&J);

    Tram twoOne(21,"PCC", &A, 3);
    Tram oneTwo(12,"PCC", &G, 5);
    twoOne.setDefectenLimiet(99);
    twoOne.setReparatieTijd(1);
    twoOne.setReparatieKost(120);
    oneTwo.setDefectenLimiet(1);
    oneTwo.setReparatieTijd(2);
    oneTwo.setReparatieKost(120);

    vector<Tram*> trams;
    trams.push_back(&twoOne);
    trams.push_back(&oneTwo);

    MetronetSimulation MS;
    MS.setStations(stations);
    MS.setTrams(trams);

    MS>>2;

    EXPECT_EQ(MS.getTramByNr(3)->getHuidige(), &C) << "Station has not been reached or been surpassed!";
    EXPECT_EQ(MS.getTramByNr(5)->getHuidige(), &H) << "Station has not been reached or been surpassed!";
}

TEST_F(MetronetTests, simulationCollisionPrevention){
    Station A,B,C,D,E;

    Spoor* spoorA = new Spoor(21,&B,&E);
    Spoor* spoorB = new Spoor(21,&C,&A);
    Spoor* spoorC = new Spoor(21,&D,&B);
    Spoor* spoorD = new Spoor(21,&E,&C);
    Spoor* spoorE = new Spoor(21,&A,&D);

    vector<Spoor*> spA;
    spA.push_back(spoorA);

    vector<Spoor*> spB;
    spB.push_back(spoorB);

    vector<Spoor*> spC;
    spC.push_back(spoorC);

    vector<Spoor*> spD;
    spD.push_back(spoorD);

    vector<Spoor*> spE;
    spE.push_back(spoorE);

    A.setNaam("A");
    A.setSporen(spA);
    A.setType("Metrostation");

    B.setNaam("B");
    B.setSporen(spB);
    B.setType("Metrostation");

    C.setNaam("C");
    C.setSporen(spC);
    C.setType("Metrostation");

    D.setNaam("D");
    D.setSporen(spD);
    D.setType("Halte");

    E.setNaam("E");
    E.setSporen(spE);
    E.setType("Metrostation");

    vector<Station*> stations;
    stations.push_back(&A);
    stations.push_back(&B);
    stations.push_back(&C);
    stations.push_back(&D);
    stations.push_back(&E);

    Tram twoOne(21,"PCC", &A, 1);
    Tram twoOneTwo(21,"Stadslijner", &C, 2);
    twoOne.setDefectenLimiet(6);
    twoOne.setReparatieTijd(1);
    twoOne.setReparatieKost(45);
    twoOneTwo.setDefectenLimiet(6);
    twoOneTwo.setReparatieTijd(1);
    twoOneTwo.setReparatieKost(45);

    vector<Tram*> trams;
    trams.push_back(&twoOne);
    trams.push_back(&twoOneTwo);

    MetronetSimulation MS;
    MS.setStations(stations);
    MS.setTrams(trams);

    MS^1;
    MS^1;
    MS>21;
    MS>21;

    EXPECT_EQ(MS.getTramByNr(1)->getHuidige(), &D) << "Station has not been reached or been surpassed!";
    EXPECT_EQ(MS.getTramByNr(2)->getHuidige(), &A) << "Station has not been reached or been surpassed!";
}

TEST_F(MetronetTests, simulationOneTramReparation){
    Station A,B,C,D,E;

    Spoor* spoorA = new Spoor(21,&B,&E);
    Spoor* spoorB = new Spoor(21,&C,&A);
    Spoor* spoorC = new Spoor(21,&D,&B);
    Spoor* spoorD = new Spoor(21,&E,&C);
    Spoor* spoorE = new Spoor(21,&A,&D);

    vector<Spoor*> spA;
    spA.push_back(spoorA);

    vector<Spoor*> spB;
    spB.push_back(spoorB);

    vector<Spoor*> spC;
    spC.push_back(spoorC);

    vector<Spoor*> spD;
    spD.push_back(spoorD);

    vector<Spoor*> spE;
    spE.push_back(spoorE);

    A.setNaam("A");
    A.setSporen(spA);
    A.setType("Metrostation");

    B.setNaam("B");
    B.setSporen(spB);
    B.setType("Metrostation");

    C.setNaam("C");
    C.setSporen(spC);
    C.setType("Metrostation");

    D.setNaam("D");
    D.setSporen(spD);
    D.setType("Metrostation");

    E.setNaam("E");
    E.setSporen(spE);
    E.setType("Metrostation");

    vector<Station*> stations;
    stations.push_back(&A);
    stations.push_back(&B);
    stations.push_back(&C);
    stations.push_back(&D);
    stations.push_back(&E);

    Tram twoOne(21,"PCC", &A, 3);
    twoOne.setDefecten(1);
    twoOne.setDefectenLimiet(1);

    vector<Tram*> trams;
    trams.push_back(&twoOne);

    MetronetSimulation MS;
    MS.setStations(stations);
    MS.setTrams(trams);

    MS>>3;

    EXPECT_EQ(MS.getTramByNr(3)->getHuidige(), &C) << "Station has not been reached or been surpassed!";
}

TEST_F(MetronetTests, simulationOutPutInfo){
    Metronet DeStreep("Basic.xml");
    DeStreep.run(11);
    DeStreep.write();
    DeStreep.reset();

    string infoFilename = DeStreep.getOutput().getInfoFilename();
    string compareInfoFilename = "Compare" + infoFilename;

    compareFile(infoFilename, compareInfoFilename);
}

TEST_F(MetronetTests, simulationOutPutLogbook){
    Metronet DeStreep("Basic.xml");
    DeStreep.run(11);
    DeStreep.write();
    DeStreep.reset();

    string logbookFilename = DeStreep.getOutput().getLogbookFilename();
    string compareLogbookFilename = "Compare" + logbookFilename;

    compareFile(logbookFilename, compareLogbookFilename);
}

TEST_F(MetronetTests, simulationOutPutOverview){
    Metronet DeStreep("Basic.xml");
    DeStreep.run(11);
    DeStreep.write();
    DeStreep.reset();

    string overviewFilename = DeStreep.getOutput().getOverviewFilename();
    string compareOverviewFilename = "Compare" + overviewFilename;

    compareFile(overviewFilename, compareOverviewFilename);
}

TEST_F(MetronetTests, simulationOutPutRailnet){
    Metronet DeStreep("Basic.xml");
    DeStreep.run(11);
    DeStreep.write();
    DeStreep.reset();

    string railnetFilename = DeStreep.getOutput().getRailnetFilename();
    string compareRailnetFilename = "Compare" + railnetFilename;

    compareFile(railnetFilename, compareRailnetFilename);
}

TEST_F(MetronetTests, simulationOutPutPosition){
    Metronet DeStreep("Basic.xml");
    DeStreep.run(11);
    DeStreep.write();
    DeStreep.reset();

    string positionFilename = DeStreep.getOutput().getPositionFilename();
    string comparePositionFilename = "Compare" + positionFilename;

    compareFile(positionFilename, comparePositionFilename);
}

TEST_F(MetronetTests, loadingFileWrongWay){
    validRead("WrongBasic.xml");
    compareFile("WrongBasicInput.txt", "CompareWrongBasicInput.txt");

}

int main(int argc, char** argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}