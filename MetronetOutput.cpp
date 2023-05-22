#include "MetronetOutput.h"


//________________________ Constructor ________________________//
MetronetOutput::MetronetOutput(const string &Filename) : filename(Filename.substr(0, Filename.size()-4)) {}



//________________________ Output ________________________//
void MetronetOutput::Overview(const vector<Station*>& stations, const vector<Tram*>& trams){
    overviewFilename = filename + "Overview.txt";
    ofstream OverviewFile(overviewFilename.c_str());
    REQUIRE(OverviewFile,"Failed to open Overview file.");

    // Write station information to file
    OverviewFile << "--== STATIONS ==--" << endl;
    for (vector<Station*>::const_iterator st = stations.begin(); st != stations.end(); ++st) {
        const Station* station = *st;

        OverviewFile << "\t= " << station->getType() << " " << station->getNaam() << " =" << endl;

        const vector<Spoor*>& sporen = station->getSporen();
        for (vector<Spoor*>::const_iterator sp = sporen.begin(); sp != sporen.end(); ++sp) {
            Spoor* spoor = *sp;

            OverviewFile << "\t\t* Spoor " << spoor->getSpoorNr() << ":" << endl;
            OverviewFile << "\t\t\t" << "-> " << spoor->getVolgende()->getType() << " " << spoor->getVolgende()->getNaam() << endl;
            OverviewFile << "\t\t\t" << "<- " << spoor->getVorige()->getType() << " " << spoor->getVorige()->getNaam() << endl;
        }
        OverviewFile<<endl;
    }


    // Write tram information to file
    OverviewFile << endl << "--== TRAMS ==--\n";
    for (vector<Tram*>::const_iterator tr = trams.begin(); tr != trams.end(); ++tr) {
        const Tram* tram = *tr;

        OverviewFile << "\tTram " << tram->getLijn() << " nr " << tram->getVoertuigNr() << endl;
        OverviewFile << "\t\ttype: " << tram->getType() << endl;
        OverviewFile << "\t\tsnelheid: " << tram->getSnelheid() << endl;
        OverviewFile << "\t\thuidig station: " << tram->getHuidige()->getNaam() << endl;
        OverviewFile << "\t\treparatiekosten: " << tram->getKost() << " euro" << endl << endl;
    }
    OverviewFile.seekp(0, ios::end);
    ENSURE(OverviewFile.tellp() != 0, "Overview file is empty.");
    OverviewFile.close();
}
void MetronetOutput::Logbook() {
    logbookFilename = filename + "Logbook.txt";
    ofstream LogbookFile(logbookFilename.c_str());
    REQUIRE(LogbookFile, "Failed to open Overview file.");

    LogbookFile<<"\t\t\t╔═══════════════════════╗\n\t\t\t║ Verloop van de ritten ║\n" << "\t ╔══════╩═══════════════════════╩═══════╗\n" << Log << "\t ╚══════════════╧═══════════════════════╝\n";

    LogbookFile.seekp(0, ios::end);
    ENSURE(LogbookFile.tellp() != 0, "Logbook file is empty.");
    LogbookFile.close();
}
void MetronetOutput::operator+(string log){
    Log += log;
}
void MetronetOutput::Position(const vector<Station *> &stations, const vector<Tram *> &trams) {
    positionFilename = filename + "Position.txt";
    ofstream PositionFile(positionFilename.c_str());
    REQUIRE(PositionFile, "Failed to open Position file.");
    PositionFile << "\n\t\t╔═══════════════════════════════╗\n\t\t║\t\tHuidige posities\t\t║\n" << "\t╔═══╩══════════════╤════════════════╩═══╗\n";


    for (vector<Tram*>::const_iterator tram = trams.begin(); tram != trams.end(); ++tram) {
        PositionFile << "\t║\tTram " << (*tram)->getLijn()<< " nr " << (*tram)->getVoertuigNr() << "   │     Station " << (*tram)->getHuidige()->getNaam() << "      ║\n";
    }
    PositionFile << "\t╚══════════════════╧════════════════════╝" << endl;


    PositionFile.seekp(0, ios::end);
    ENSURE(PositionFile.tellp() != 0, "Position file is empty.");
    PositionFile.close();
}
void MetronetOutput::Information(const vector<Station *> &stations, const vector<Tram *> &trams, int runtime) {
    infoFilename = filename + "Info.txt";
    ofstream InformationFile(infoFilename.c_str());
    REQUIRE(InformationFile, "Failed to open Information file.");

    //// Stations ////
    InformationFile<< "--== STATIONS ==--"<<endl;
    for (vector<Station*>::const_iterator st = stations.begin(); st != stations.end(); ++st) {
        const Station *station = *st;
        InformationFile <<"\t-> " <<station->getType() << " " << station->getNaam()<<endl;

        // Bezoeken
        InformationFile<< "\t\ttotale bezoeken: "<< station->getBezoeken() <<endl;
        if(station->getType() == "Metrostation"){
            const vector<Spoor*>& sporen = station->getSporen();
            for (vector<Spoor*>::const_iterator sp = sporen.begin(); sp != sporen.end(); ++sp){
                Spoor* spoor = *sp;
                InformationFile<< "\t\t\t-->Spoor " << spoor->getSpoorNr() <<": "<< spoor->getBezoeken()<<endl;
            }
        }

        // Bezetting
        InformationFile<<"\t\tbezettingsgraad: "<< station->getBezetting() *100.0 / runtime <<"%"<<endl;
        if(station->getType() == "Metrostation"){
            const vector<Spoor*>& sporen = station->getSporen();
            for (vector<Spoor*>::const_iterator sp = sporen.begin(); sp != sporen.end(); ++sp){
                Spoor* spoor = *sp;
                InformationFile<< "\t\t\t-->Spoor " << spoor->getSpoorNr() <<": "<< spoor->getBezetting()*100.0 / runtime<<"%"<<endl;
            }
        }
        InformationFile<< endl;
    }


    //// Trams ////
    InformationFile << endl << "--== TRAMS ==--"<<endl;
    for (vector<Tram*>::const_iterator tr = trams.begin(); tr != trams.end(); ++tr) {
        const Tram* tram = (*tr);

        // Specificaties
        InformationFile <<"\t--> Tram " << tram->getVoertuigNr() << " op Lijn " <<tram->getLijn()<< " :"<<endl;
        InformationFile <<"\t\ttype: \t\t\t\t" <<tram->getType() <<endl;
        InformationFile <<"\t\tsnelheid: \t\t\t" <<tram->getSnelheid()<<" kmh" <<endl;

        // defectie
        InformationFile <<"\t\treparatiekosten: \t€ " <<tram->getKost() <<endl;
        InformationFile <<"\t\tdefecten: \t\t\t" << tram->getDefecten() <<endl;

        // status
        InformationFile <<"\t\tstatus: \t\t\t";
        if (tram->isInPanne()){
            InformationFile << "in panne"<<endl;
            InformationFile <<"\t\treparatiestatus: \t" << tram->getReparatieProgres() * 100.0 / tram->getReparatieTijd() << "%" <<endl<<endl;
        }else{
            InformationFile << "niet in panne"<<endl<<endl;
        }
    }
    InformationFile.seekp(0, ios::end);
    ENSURE(InformationFile.tellp() != 0, "Information file is empty.");
    InformationFile.close();
}
void MetronetOutput::Railnet(const vector<Station *> &stations, const vector<Tram *> &trams) {
    railnetFilename = filename + "Railnet.txt";
    ofstream RailnetFile(railnetFilename.c_str());
    REQUIRE(RailnetFile, "Failed to open Information file.");

    set<int> SpoorNrs;
    for (vector<Tram*>::const_iterator tr = trams.begin(); tr != trams.end(); ++tr) {
        const Tram *tram = (*tr);
        SpoorNrs.insert(tram->getLijn());
    }

    string Location = "  ";
    Station* station = *stations.begin();
    Station* begin = station;
    for(set<int>::const_iterator it = SpoorNrs.begin(); it != SpoorNrs.end(); it++){
        const int spoorNr = *it;
        RailnetFile<<endl<<"==";
        for(unsigned int sp = 0; sp < stations.size(); sp++){
            Spoor* spoor = station->getSpoor(spoorNr);
            if(spoor){
                RailnetFile<<station->getNaam()<<"==";
                if(!spoor->isEmpty()){
                    Location+="T  ";
                }else{
                    Location+="   ";
                }

                station = spoor->getVolgende();
                if(station == begin){
                    break;
                }
            }else{
                station = stations[sp];
                begin = station;
            }
        }
        RailnetFile<<" "<<spoorNr<<endl<<Location<<endl;
        Location = "  ";
    }


    RailnetFile.seekp(0, ios::end);
    ENSURE(RailnetFile.tellp() != 0, "Advanced file is empty.");
    RailnetFile.close();
}


//______________________ Getters and Setter ______________________//
const string &MetronetOutput::getFilename() const {
    return filename;
}
void MetronetOutput::setFilename(const string &Filename) {
    MetronetOutput::filename = Filename.substr(0, Filename.size()-4);
}
const string &MetronetOutput::getLog() const {
    return Log;
}
void MetronetOutput::setLog(const string &log) {
    Log = log;
}

const string &MetronetOutput::getOverviewFilename() const {
    return overviewFilename;
}

const string &MetronetOutput::getInfoFilename() const {
    return infoFilename;
}

const string &MetronetOutput::getPositionFilename() const {
    return positionFilename;
}

const string &MetronetOutput::getLogbookFilename() const {
    return logbookFilename;
}

const string &MetronetOutput::getRailnetFilename() const {
    return railnetFilename;
}


