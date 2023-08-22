#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>
#include <map>
#include <random>
#include "time.h"
#include "ape_header.h"

using namespace std;

/*-----------global variables-----------*/
static default_random_engine randEng(time(0));
vector<Issue> allIssues;
vector<Party> parties;
vector<Electorate> electorates;
vector<PartyLeader> leaders;
vector<Event> events;


int randint(){                  //generate random integer between 0-100

    int x = randEng()%100;
    return x;

}

int randintRange(int rangeNum){             //generate a random integer with a range constrant

    //random number will be within 3 standard deviations from the range
    normal_distribution<> normal(rangeNum, 3);  //normal(mean, standard deviation)
        int x=(int)(normal(randEng));
    if(x<0)
        x = 0;
    else if(x>100)
        x=100;

    return x;

}

bool chance(){
    if((randEng()%2+1)==1)
        return true;
    else
        return false;

}

/*----------------------ISSUE FUNCTIONS---------------------*/
void loadIssues(){

    ifstream inputFile("issue.txt");

      if(!inputFile.good())                                              //Checking status of file
        Error("Unable to access file titled: issue.txt");         //send message to error function

     vector <string> inputText;
     string line;

     while(getline(inputFile,line)){
        inputText.push_back(line);
     }

     inputFile.close();

    Issue issue1(1, AIRQUALITY, inputText[0]);
    Issue issue2(2, HOUSING, inputText[1]);
    Issue issue3(3, CLIMATE, inputText[2]);
    Issue issue4(4, COVID, inputText[3]);
    Issue issue5(5, HOMELESS, inputText[4]);

    allIssues.push_back(issue1);
    allIssues.push_back(issue2);
    allIssues.push_back(issue3);
    allIssues.push_back(issue4);
    allIssues.push_back(issue5);

}

void printIssueVector(){

    for(int i = 0; i < allIssues.size(); i++){
        allIssues[i].printIssue();
        cout << "\n";}

}

string Issue::typeToString(){

    switch(type){
        case AIRQUALITY:
        return "Air Quality";
        case HOUSING:
        return "Housing Crisis";
        case CLIMATE:
        return "Climate Change";
        case COVID:
        return "Covid-19 BA.4 strain";
        case HOMELESS:
        return "Homelessness";
    }

};

/*---------------------HUMAN FUNCTIONS------------------*/

Human::Human(string _name){
        name = _name;

         characteristics.insert ( pair<CHARACTERISTIC, int>(CONNECTION,randint()) );
         characteristics.insert ( pair<CHARACTERISTIC, int>(ECONOMIC_EXP,randint()) );
         characteristics.insert ( pair<CHARACTERISTIC, int>(ENVIRONMENTAL_EXP,randint()) );
         characteristics.insert ( pair<CHARACTERISTIC, int>(EMPLOYMENT_EXP,randint()) );
         characteristics.insert ( pair<CHARACTERISTIC, int>(SCANDAL_EXP,randint()) );
         characteristics.insert ( pair<CHARACTERISTIC, int>(HEALTHCARE_EXP,randint()) );
         characteristics.insert ( pair<CHARACTERISTIC, int>(INFLUENCE,randint()) );
         characteristics.insert ( pair<CHARACTERISTIC, int>(POPULARITY,randint()) );
         characteristics.insert ( pair<CHARACTERISTIC, int>(DEBATE_EXP,randint()) );


        };

void Human::printHuman(){

      map<CHARACTERISTIC,int>::iterator itr;
      for( itr = characteristics.begin(); itr != characteristics.end(); ++itr){

            if(itr->first == CONNECTION)
                cout << "Connection => " << itr->second << endl;
            else if(itr->first == ECONOMIC_EXP)
                cout << "Economic Experience => " << itr->second << endl;
            else if(itr->first == ENVIRONMENTAL_EXP)
                cout << "Environmental Experience => " << itr->second << endl;
            else if(itr->first == EMPLOYMENT_EXP)
                cout << "Employment Experience => " << itr->second << endl;
            else if(itr->first == SCANDAL_EXP)
                cout << "Scandal Experience => " << itr->second << endl;
            else if(itr->first == HEALTHCARE_EXP)
                cout << "Healthcare Experience => " << itr->second << endl;
            else if(itr->first == INFLUENCE)
                cout << "Influence => " << itr->second << endl;
            else if(itr->first == POPULARITY)
                cout << "Popularity => " << itr->second << endl;
            else if(itr->first == DEBATE_EXP)
                cout << "Debate Experience => " << itr->second << endl;

      }

}

void Human::updateCharacteristic(CHARACTERISTIC chrtr, int newVal){

    map<CHARACTERISTIC,int>::iterator itr;

    itr = characteristics.find(chrtr);

        if (itr != characteristics.end()){
            if((itr->second + newVal) > 100)
                 itr->second = 100;
            else if((itr->second + newVal)<0)
                itr->second = 0;
            else
                 itr->second = itr->second + newVal;
        }


}

void Human::printSingleCharacteristic(CHARACTERISTIC chrtr){

    map<CHARACTERISTIC,int>::iterator itr;

    itr = characteristics.find(chrtr);

        if(itr->first == CONNECTION)
                cout << "Connection => " << itr->second << endl;
            else if(itr->first == ECONOMIC_EXP)
                cout << "Economic Experience => " << itr->second << endl;
            else if(itr->first == ENVIRONMENTAL_EXP)
                cout << "Environmental Experience => " << itr->second << endl;
            else if(itr->first == EMPLOYMENT_EXP)
                cout << "Employment Experience => " << itr->second << endl;
            else if(itr->first == SCANDAL_EXP)
                cout << "Scandal Experience => " << itr->second << endl;
            else if(itr->first == HEALTHCARE_EXP)
                cout << "Healthcare Experience => " << itr->second << endl;
            else if(itr->first == INFLUENCE)
                cout << "Influence => " << itr->second << endl;
            else if(itr->first == POPULARITY)
                cout << "Popularity => " << itr->second << endl;
            else if(itr->first == DEBATE_EXP)
                cout << "Debate Experience => " << itr->second << endl;

}

int Human::getChrtrValue(CHARACTERISTIC chrtr){

    int x;
    map<CHARACTERISTIC,int>::iterator itr;

    itr = characteristics.find(chrtr);
    x = itr->second;
    return x;
}

/*-----------------STANCE FUNCTIONS----------------*/

void Stance::updateRadius(int popularity){

    if(influenceRadius!= 100)
        influenceRadius = influenceRadius + (popularity/4);
    else if(influenceRadius + (popularity/4)==100)
        influenceRadius = 100;


}

int Stance::difference(Stance diffStance){

    int appDiff = this->approach - diffStance.getApproach();
    int sigDiff = this->significance - diffStance.getSignificance();

    int difference = (appDiff + sigDiff)/2;
    return difference;
}

/*---------------ELECTORATE FUNCTION-------------*/

Electorate::Electorate(string _area, int _population, string _description) : area(_area), population(_population), description(_description){

    string varName;
    for(int i = 0; i < allIssues.size(); i++){                                              //go through issue vector and add a stance for each issue
       varName = "stance" + to_string(i);
       Stance varName(randint(), randint(), randint(), allIssues[i]);
        elecStances.push_back(varName);
    }

};

void loadElectorates(int totalElecs){

    ifstream inputFile("electorates.txt");

      if(!inputFile.good())                                              //Checking status of file
        Error("Unable to access file titled: electorates.txt");         //send message to error function

     vector <string> inputText;
     string line;
     string varName;

     for(int i=0; i<totalElecs; i++){
        int totalLines = 0;
         while(getline(inputFile,line) && totalLines <= 2){
            inputText.push_back(line);
            totalLines++;
         }
        varName = "electorate" + i;
        Electorate varName(inputText[0], stoi(inputText[1]), inputText[2]);
        electorates.push_back(varName);
         inputText.clear();
     }


    inputFile.close();
};

void Electorate::printEStanceVec(){

    for(int i = 0; i < elecStances.size(); i++){
        elecStances[i].printStance();
        cout << "\n";}

}

void printElectorateReports(){

        for(int eNum = 0; eNum<electorates.size(); eNum++){
        electorates[eNum].electorateReport();
        cout << "\n";}

}

void Electorate::electorateReport(){

    cout.fill('~');
    cout.width(30);
    cout<<"ELECTORATE REPORT";
    cout.width(30);
    cout<<"\n";

    printElectorate();
    cout.fill('=');
    cout.width(35);
    cout<<"\n";

    cout<<"ELECTORATE STANCES"<<endl;
    cout.fill('-');
    cout.width(35);
    cout<<"\n";
    printEStanceVec();
    cout.fill('=');
    cout.width(35);
    cout<<"\n";

    cout.fill('~');
    cout.width(30);
    cout<<"END REPORT";
    cout.width(30);
    cout<<"\n";

}


/*---------------------CANDIDATE FUNCTIONS---------------*/

Candidate::Candidate(string _name, Electorate elec) : Human(_name), electorateRep(elec){};

void Candidate::setStanceVec(map<int,int> rangeMap){

    string varName;
    int x = 0;
    for (auto i = rangeMap.begin(); i != rangeMap.end(); ++i) {
            varName = "stance" + to_string(x);
            Stance varName(randintRange( i->first), randintRange(i->second), randint(), allIssues[x]);
            candStances.push_back(varName);
            x++;

    }


}

void Candidate::printCStanceVec(){
    cout<<name<<": "<<endl;
    for(int i = 0; i < candStances.size(); i++){
        candStances[i].printStance();
        cout << "\n";}

};


/*---------------------PartyLeader FUNCTIONS---------------*/

PartyLeader::PartyLeader(string _name) : Human(_name){};

void PartyLeader::setStanceVec(map<int,int> rangeMap){

    string varName;
    int x = 0;
    for (auto i = rangeMap.begin(); i != rangeMap.end(); ++i) {
            varName = "stance" + to_string(x);
            Stance varName(randintRange( i->first), randintRange(i->second), randint(), allIssues[x]);
            leaderStances.push_back(varName);
            x++;

    }


}

void PartyLeader::printPLStanceVec(){
    cout<<"Leader "<<name<<": "<<endl;
    for(int i = 0; i < leaderStances.size(); i++){
        leaderStances[i].printStance();
        cout << "\n";}

};

void loadPartyLeaders(){

     ifstream inputFile("leaders.txt");

      if(!inputFile.good())                                              //Checking status of file
        Error("Unable to access file titled: leaders.txt");         //send message to error function

     vector <string> inputText;
     string line;

     while(getline(inputFile,line)){
        inputText.push_back(line);
     }

     inputFile.close();

    PartyLeader partyLead1(inputText[0]);
    PartyLeader partyLead2(inputText[1]);
    PartyLeader partyLead3(inputText[2]);


    leaders.push_back(partyLead1);
    leaders.push_back(partyLead2);
    leaders.push_back(partyLead3);


};




/*---------------------ManagerialTeam FUNCTIONS---------------*/

ManagerialTeam::ManagerialTeam(string _name, int _eventImpact) : Human(_name), eventImpact(_eventImpact){};

int ManagerialTeam::eventHandle(int influence, int connection){

    eventImpact = (influence + connection)/2;

};


/*--------------PARTY FUNCTIONS----------------*/


Party::Party(string _name, PartyLeader pLeader, ManagerialTeam mTeam):name(_name), leader(pLeader), mangTeam(mTeam){


         stanceRanges.insert ( pair<int, int>(randint(),randint()) );
         stanceRanges.insert ( pair<int, int>(randint(),randint()) );
         stanceRanges.insert ( pair<int, int>(randint(),randint()) );
         stanceRanges.insert ( pair<int, int>(randint(),randint()) );
         stanceRanges.insert ( pair<int, int>(randint(),randint()) );


};

void Party::printStanceRange(){

    cout.fill(' ');
    cout<<"Issue # ";
    cout.width(15);
    cout<<"Approach ";
    cout.width(10);
    cout<<"Significance \n";
    cout<<"-----------------------------------"<<endl;
    int x = 0;
    for (auto i = stanceRanges.begin(); i != stanceRanges.end(); ++i) {
        x++;
    cout<<"Issue "<<x<<": ";
    cout.width(10);
    cout << i->first;
    cout.width(15);
    cout<< i->second << endl;

    }


}

void genParty(){

            ManagerialTeam mangTeam1("Disney", randint());
            Party party1("Looney Tunes", leaders[0], mangTeam1);

            ManagerialTeam mangTeam2("Nintendo", randint());
            Party party2("Mario Bros", leaders[1], mangTeam2);

            ManagerialTeam mangTeam3("Marvel", randint());
            Party party3("The Avengers", leaders[2], mangTeam3);



            string fileName;
            for(int i=0; i<3; i++){

                fileName = "candidates"+to_string(i+1);

                ifstream inputFile(fileName+".txt");

                  if(!inputFile.good())                                              //Checking status of file
                    Error("Unable to access file titled: "+fileName+".txt");         //send message to error function

                 vector <string> inputText;
                 string line;
                 string candVar;

                int x=0;
                while( x<electorates.size()){
                    x++;
                    candVar = "candidate"+to_string(x+1);
                    int numLines = 0;

                     while(getline(inputFile,line) && numLines<1){
                        inputText.push_back(line);
                        numLines++;
                     }
                     Candidate candVar(inputText[0], electorates[x-1]);

                     if(i==0){
                        party1.setCand(candVar);
                    }
                    else if(i==1){
                        party2.setCand(candVar);
                     }else if(i==2){
                        party3.setCand(candVar);
                     }

                     inputText.clear();
                }

                 inputFile.close();

            }

            party1.setCand_LeadStances();
            party2.setCand_LeadStances();
            party3.setCand_LeadStances();

            parties.push_back(party1);
            parties.push_back(party2);
            parties.push_back(party3);

};

void printPartyReport(){

        for(int pNum = 0; pNum<parties.size(); pNum++){
        parties[pNum].partyReport();
        cout << "\n";}

}

void Party::printPartyCandsVec(){

    for(int i = 0; i < candidates.size(); i++){
        candidates[i].printCand();
        cout << "\n";
        candidates[i].printHuman();
                cout << "\n";
        cout.fill('-');
        cout.width(35);
        cout<<"\n";}

}

void Party::setCand_LeadStances(){

    for(int i = 0; i < candidates.size(); i++){
        candidates[i].setStanceVec(stanceRanges);
        }

    leader.setStanceVec(stanceRanges);

}

void Party::partyReport(){

    cout.fill('~');
    cout.width(30);
    cout<<"PARTY REPORT";
    cout.width(30);
    cout<<"\n";


    printParty();
    cout.fill('=');
    cout.width(35);
    cout<<"\n";


    cout<<"LEADER CHARACTERISTICS"<<endl;
    cout.fill('-');
    cout.width(35);
    cout<<"\n";
    leader.printHuman();
    cout.fill('=');
    cout.width(35);
    cout<<"\n";

    cout<<"MANAGERIAL TEAM STATS"<<endl;
    cout.fill('-');
    cout.width(35);
    cout<<"\n";
    mangTeam.printSingleCharacteristic(INFLUENCE);
    mangTeam.printSingleCharacteristic(CONNECTION);
    cout.fill('=');
    cout.width(35);
    cout<<"\n";

    cout<<"CANDIDATES CHARACTERISTICS"<<endl;
    cout.fill('-');
    cout.width(35);
    cout<<"\n";
    printPartyCandsVec();
    cout.fill('=');
    cout.width(35);
    cout<<"\n";

    cout<<"STANCE RANGE*"<<endl;
    cout.fill('-');
    cout.width(35);
    cout<<"\n";
    printStanceRange();
    cout<<"\n";
    cout<<"*The Candidates and leader stances \nhave normal distribution from this \nnumber with a standard deviation of 3."<<endl;
    cout.fill('=');
    cout.width(35);
    cout<<"\n";

    cout<<"PARTY STANCES"<<endl;
    cout.fill('-');
    cout.width(35);
    cout<<"Leader Stance\n";
    cout.width(35);
    cout<<"\n";
    leader.printPLStanceVec();
    cout.fill('-');
    cout.width(35);
    cout<<"Candidate Stances\n";
    cout.width(35);
    cout<<"\n";
    for(int i = 0; i < candidates.size(); i++){
        candidates[i].printCStanceVec();
        cout.fill('-');
        cout.width(35);
        cout << "\n";}
    cout.fill('=');
    cout.width(35);
    cout<<"\n";

    cout.fill('~');
    cout.width(30);
    cout<<"END REPORT";
    cout.width(30);
    cout<<"\n";

}


/*--------------------EVENT FUNCTIONS----------------------*/

void loadEvents(){

    Event e1(LEADER_DEBATE);
    Event e2(CANDIDATE_DEBATE);
    Event e3(LEADER_BAD);
    Event e4(LEADER_GOOD);
    Event e5(CANDIDATE_BAD);
    Event e6(CANDIDATE_GOOD);
    Event e7(ISSUE_AIR);
    Event e8(ISSUE_COVID);

    events.push_back(e1);
    events.push_back(e2);
    events.push_back(e3);
    events.push_back(e4);
    events.push_back(e5);
    events.push_back(e6);
    events.push_back(e7);
    events.push_back(e8);

}

void runEvent(Event event, Electorate elec){

    if(event.getType() == 0){
        event.runLeaderDebate();
    }else if(event.getType() == 1){
        event.runCandidateDebate(elec);
    }else if(event.getType() == 2){
        event.runLeaderGood(elec);
    }else if(event.getType() == 3){
        event.runLeaderBad(elec);
    }else if(event.getType() == 4){
        event.runCandidateGood(elec);
    }else if(event.getType() == 5){
        event.runCandidateBad(elec);
    }else if(event.getType() == 6){
        event.runIssueAir(elec);
    }else if(event.getType() == 7){
        event.runIssueCovid(elec);
    }

}

void Event::runLeaderDebate(){

    int winner;
    int biggest = 0;
    cout<<"The party leaders are having a debate!\n"<<endl;
    for(int i=0; i<parties.size();i++){
            cout<<parties[i].getLeader()->getName()<<" has ";
            parties[i].getLeader()->printSingleCharacteristic(DEBATE_EXP);
        if(biggest<parties[i].getLeader()->getChrtrValue(DEBATE_EXP)){
            winner = i ;
            biggest = parties[i].getLeader()->getChrtrValue(DEBATE_EXP);}
    }


   int debateIncrease = parties[winner].getLeader()->getChrtrValue(DEBATE_EXP)*0.10 ;                                                                                              //winning a debate increases debateExp by 10%
   int popularityIncrease = (parties[winner].getLeader()->getChrtrValue(POPULARITY)*0.1) + (parties[winner].getMangTeam().getChrtrValue(INFLUENCE)*0.05) ;                         //winning a debate increases popularity by 10% + 5% from Managerial Teams influence

    cout<<"\nThe winner of the debate is "<<parties[winner].getLeader()->getName()<<"!\n +"<<debateIncrease<<" Debate Experience and +"<<popularityIncrease<<" Popularity."<<endl;

    parties[winner].getLeader()->updateCharacteristic(DEBATE_EXP, debateIncrease);
    parties[winner].getLeader()->updateCharacteristic(POPULARITY, popularityIncrease);

}

void Event::runCandidateDebate(Electorate elec){


    int winner;
    int biggest = 0;
    int currentElectorate;
        for(int j=0; j<electorates.size();j++)                                                          //identifies the index of the current electorate in the electorates vector
            if(electorates[j].getArea()==elec.getArea())
                currentElectorate = j;

    cout<<"The candidates of "<<elec.getArea()<<" are having a debate!\n"<<endl;
    for(int i=0; i<parties.size();i++){
                cout<<parties[i].getCanRef(currentElectorate).getName()<<" has ";                       //use getCanRef() in order to change the reference of the object rather than a copy
            parties[i].getCanRef(currentElectorate).printSingleCharacteristic(DEBATE_EXP);
        if(biggest < parties[i].getCanRef(currentElectorate).getChrtrValue(DEBATE_EXP)){                //compares all the experiences and selects the higfhest value as the winner
            winner = i ;
            biggest = parties[i].getCanRef(currentElectorate).getChrtrValue(DEBATE_EXP);
        }
    }


    int debateIncrease = parties[winner].getCanRef(currentElectorate).getChrtrValue(DEBATE_EXP)*0.10 ;                                                                                              //winning a debate increases debateExp by 10%
    int popularityIncrease = (parties[winner].getCanRef(currentElectorate).getChrtrValue(POPULARITY)*0.1) + (parties[winner].getMangTeam().getChrtrValue(INFLUENCE)*0.05);                         //winning a debate increases popularity by 10% + 5% from Managerial Teams influence

    cout<<"\nThe winner of the debate is "<<parties[winner].getCanRef(currentElectorate).getName()<<"!\n+"<<debateIncrease<<" Debate Experience and +"<<popularityIncrease<<" Popularity."<<endl;

    parties[winner].getCanRef(currentElectorate).updateCharacteristic(DEBATE_EXP, debateIncrease);                 //increases the value of the Characteristic according to chrtr increase percentage.
    parties[winner].getCanRef(currentElectorate).updateCharacteristic(POPULARITY, popularityIncrease);

}

void Event::runLeaderGood(Electorate elec){

    int winner;
    int biggest = 0;

    /*Choose a random characteristic to make the speeach about*/
    CHARACTERISTIC chrtr = CHARACTERISTIC((randEng() % 3) + 1);

    string topic;                   //switch creates a string output of the equivalent enum integer. This is to assist in printing out the correct information
        switch(chrtr){
    case ECONOMIC_EXP:
        topic = "Economics";
        break;
    case ENVIRONMENTAL_EXP:
        topic = "Environment";
        break;
    case EMPLOYMENT_EXP:
        topic = "Employment";
        break;
        }

    cout<<"The party leaders are doing speeches about "<<topic<<" in "<<elec.getArea()<<"!\n"<<endl;                //specifies what electorate and topic currently is
    for(int i=0; i<parties.size();i++){
            cout<<parties[i].getLeader()->getName()<<" has ";
            parties[i].getLeader()->printSingleCharacteristic(chrtr);                                               //prints characteristic of debate topic and its value
        if(biggest<parties[i].getLeader()->getChrtrValue(chrtr)){                                                   //compares all the leaders experience and selects the higfhest value as the winner
            winner = i ;
            biggest = parties[i].getLeader()->getChrtrValue(chrtr);}
    }


   int chrtrIncrease = parties[winner].getLeader()->getChrtrValue(chrtr)*0.10 ;                                                                                              //winning increases chharacteristic of topic by 10%
   int popularityIncrease = (parties[winner].getLeader()->getChrtrValue(POPULARITY)*0.2) + (parties[winner].getMangTeam().getChrtrValue(INFLUENCE)*0.05) ;                         //winning a speech increases popularity by 20% + 5% from Managerial Teams influence

    cout<<"\n "<<parties[winner].getLeader()->getName()<<" was particularly charming and won the hearts of the people!\n +"<<chrtrIncrease<<" "<<topic<<" Experience and +"<<popularityIncrease<<" Popularity."<<endl;

    parties[winner].getLeader()->updateCharacteristic(chrtr, chrtrIncrease);                                        //increases the value of the Characteristic according to chrtr increase percentage.
    parties[winner].getLeader()->updateCharacteristic(POPULARITY, popularityIncrease);


}

void Event::runLeaderBad( Electorate elec){

    int rand1 = randEng()%3;
    int rand2 = randEng()%3;
    while(rand2 == rand1)                       //ensures same candidate is not chosen twice
        rand2 = randEng()%3;


    cout<<"Uh Oh! "<<parties[rand1].getLeader()->getName()<<" made inflammatory remarks about "<<parties[rand2].getLeader()->getName()<<" in "<<elec.getArea()<<"!\n";
    cout<<parties[rand2].getLeader()->getName()<<" threw the first punch!\n"<<endl;

    //leader 1 loses popularity and connection depending on how popular and connected leader 2 was
    int lead1Change = (parties[rand2].getLeader()->getChrtrValue(POPULARITY)*0.1) + (parties[rand2].getLeader()->getChrtrValue(CONNECTION)*0.1);
    //leader 2 gains scandal and loses influence depending on how connected leader 1 was
    int lead2Change = parties[rand1].getLeader()->getChrtrValue(CONNECTION)*0.1;

    cout<<parties[rand1].getLeader()->getName()<<" -"<<lead1Change<<" popularity and -"<<lead1Change<<" connection"<<endl;
    cout<<parties[rand2].getLeader()->getName()<<" +"<<lead2Change<<" scandal and -"<<lead2Change<<" influence"<<endl;

    parties[rand1].getLeader()->updateCharacteristic(POPULARITY, (lead1Change*-1));
    parties[rand1].getLeader()->updateCharacteristic(CONNECTION, (lead1Change*-1));

    parties[rand2].getLeader()->updateCharacteristic(SCANDAL_EXP, lead2Change);
    parties[rand2].getLeader()->updateCharacteristic(INFLUENCE, (lead2Change*-1));

}

void Event::runCandidateGood(Electorate elec){

    int index = randEng()%3;
    int currentElectorate;
        for(int j=0; j<electorates.size();j++)                                                          //identifies the index of the current electorate in the electorates vector
            if(electorates[j].getArea()==elec.getArea())
                currentElectorate = j;

    cout<<parties[index].getCanRef(currentElectorate).getName()<<" from "<<parties[index].getName()<<" was spotted in "<<elec.getArea()<<" helping pick up rubbish for clean up Australia day. \nAwww how sweet!"<<endl;

    //candidate gains environmental experience and popularity and loses scandal points. increases stance approach on climate change.
    int environmentChange = parties[index].getCanRef(currentElectorate).getChrtrValue(ENVIRONMENTAL_EXP)*0.1;
    int scandalChange = parties[index].getCanRef(currentElectorate).getChrtrValue(SCANDAL_EXP)*0.1;

    //Popularity is changed 10% of the average between the electorate and the candidates approach to climate change
    int appDiff = (elec.getSingleStance(2).getApproach()+parties[index].getCanRef(currentElectorate).getStanceRef(2).getApproach())/2;
    int popChange = appDiff*0.1;

    cout<<"\n"<<parties[index].getCanRef(currentElectorate).getName()<<" -"<<scandalChange<<" Scandal, +"<<environmentChange<<" Environmental experience and Climate Change stance approach, +"<<popChange<<" popularity."<<endl;

    parties[index].getCanRef(currentElectorate).getStanceRef(2).changeApproach(environmentChange);                      //change stance of candidate
    parties[index].getCanRef(currentElectorate).updateCharacteristic(ENVIRONMENTAL_EXP, environmentChange);                      //change ENVIRONMENT CHRTR of candidate
    parties[index].getCanRef(currentElectorate).updateCharacteristic(SCANDAL_EXP, (scandalChange*-1));                      //reduce SCANDAL CHRTR of candidate
    parties[index].getCanRef(currentElectorate).updateCharacteristic(POPULARITY, popChange);


}

void Event::runCandidateBad(Electorate elec){

    int index = randEng()%3;                                                                               //used to choose a random party
    int currentElectorate;
        for(int j=0; j<electorates.size();j++)                                                          //identifies the index of the current electorate in the electorates vector
            if(electorates[j].getArea()==elec.getArea())
                currentElectorate = j;

    cout<<parties[index].getCanRef(currentElectorate).getName()<<" from "<<parties[index].getName()<<" hosted a rally in "<<elec.getArea()<<" \nUnfortunately, they snubbed a group of people asking about homelessness, the community are furious!"<<endl;

    //CAND -influence, -popularity, +scandal, -homelessness significance
     int scandalChange = parties[index].getCanRef(currentElectorate).getChrtrValue(SCANDAL_EXP)*0.2;        //increase scandal by 20%
     int popChange = elec.getPopulation()*0.0025;                                                           //popularity and influence decreases by 0.25% of the electorate population size
     int sigChange = parties[index].getCanRef(currentElectorate).getStanceRef(4).getSignificance()*0.1;     //significance of homelessness decreases by 10%

     cout<<"\n"<<parties[index].getCanRef(currentElectorate).getName()<<" +"<<scandalChange<<" Scandal, -"<<popChange<<" Popularity and Influence, -"<<sigChange<<" Homelessness stance on significance."<<endl;

    parties[index].getCanRef(currentElectorate).getStanceRef(4).changeSignificance(sigChange);                          //change stance of candidate
    parties[index].getCanRef(currentElectorate).updateCharacteristic(SCANDAL_EXP, scandalChange);                      //change SCANDAL CHRTR of candidate
    parties[index].getCanRef(currentElectorate).updateCharacteristic(POPULARITY, (popChange*-1));                      //reduce POPULARITY CHRTR of candidate
    parties[index].getCanRef(currentElectorate).updateCharacteristic(INFLUENCE, (popChange*-1));                      //reduce INFLUENCE CHRTR of candidate

}


void Event::runIssueAir(Electorate elec){

    int index = randEng()%3;
    int currentElectorate;
        for(int j=0; j<electorates.size();j++)                                                          //identifies the index of the current electorate in the electorates vector
            if(electorates[j].getArea()==elec.getArea())
                currentElectorate = j;

    cout<<parties[index].getCanRef(currentElectorate).getName()<<" from "<<parties[index].getName()<<" was planting trees in "<<elec.getArea()<<" to promote improving air quality!"<<endl;

    //candidate gains environmental experience and increases stance approach and significance on air quality.
    int environmentChange = parties[index].getCanRef(currentElectorate).getChrtrValue(ENVIRONMENTAL_EXP)*0.1;
    int sigChange = parties[index].getCanRef(currentElectorate).getStanceRef(0).getSignificance()*0.2;       //significance of air quality increases by 20%
    int appChange = parties[index].getCanRef(currentElectorate).getStanceRef(0).getApproach()*0.2;           //approach of air quality increases by 20%

    cout<<"\n"<<parties[index].getCanRef(currentElectorate).getName()<<" +"<<environmentChange<<" Environmental experience, +"<<appChange<<" Air quality approach, +"<<sigChange<<" Air quality significance."<<endl;

    parties[index].getCanRef(currentElectorate).getStanceRef(0).changeApproach(appChange);                                      //change stance of candidate
    parties[index].getCanRef(currentElectorate).getStanceRef(0).changeSignificance(sigChange);                                  //change stance of candidate
    parties[index].getCanRef(currentElectorate).updateCharacteristic(ENVIRONMENTAL_EXP, environmentChange);                      //change ENVIRONMENT CHRTR of candidate

}

void Event::runIssueCovid(Electorate elec){

    int winner;
    int biggest = 0;
    int currentElectorate;
        for(int j=0; j<electorates.size();j++)                                                          //identifies the index of the current electorate in the electorates vector
            if(electorates[j].getArea()==elec.getArea())
                currentElectorate = j;

    for(int i=0; i<parties.size();i++){
        if(biggest < parties[i].getCanRef(currentElectorate).getStanceRef(3).getApproach()){                //selects the candidate with the lowest approach to covid
            winner = i ;
            biggest = parties[i].getCanRef(currentElectorate).getStanceRef(3).getApproach();
        }
    }

    cout<<parties[winner].getCanRef(currentElectorate).getName()<<" has gotten the new Covid-19 variant because they didn't get vaccinated due to their covid stance approach!"<<endl;

    //healthcare experience decreases, scandal increases, covid approach increases(they have realised their approach was wrong)

    int appChange = parties[winner].getCanRef(currentElectorate).getStanceRef(0).getApproach()*0.1;           //approach of covid increases by 10%
    int scandalChange = parties[winner].getCanRef(currentElectorate).getChrtrValue(SCANDAL_EXP)*0.1;
    int healthChange = parties[winner].getCanRef(currentElectorate).getChrtrValue(HEALTHCARE_EXP)*0.1;

    cout<<"\n"<<parties[winner].getCanRef(currentElectorate).getName()<<" +"<<appChange<<" approach to Covid-19 BA.4 strain, +"<<scandalChange<<" Scandal, -"<<healthChange<<" Healthcare experience."<<endl;

     parties[winner].getCanRef(currentElectorate).updateCharacteristic(HEALTHCARE_EXP, (healthChange*-1));
     parties[winner].getCanRef(currentElectorate).updateCharacteristic(SCANDAL_EXP, scandalChange);
     parties[winner].getCanRef(currentElectorate).getStanceRef(4).changeApproach(appChange);

}

void Election::runCampaign(int numOfDays){

     cout.fill('=');
    cout.width(30);
     cout<<"ELECTION COMMENCES!";
        cout.width(30);
        cout<<"\n";

    for(int i=1; i<= numOfDays; i++){

    if(i==numOfDays){
            runVotingDay();
            break;
    }
        cout.fill('~');
        cout.width(60);
        cout<<"Day "<<i;
        cout.width(30);
        cout<<"\n";

        bool event;
        int eventType;
        for(int j=0; j<electorates.size(); j++){
            cout.fill('-');
            cout.width(30);
            cout<<"\n";
            event = chance();
            if(event == true){
                eventType = randEng()%7;
                runEvent(events[eventType], electorates[j]);
                cout<<"\n";
            }else
                cout<<"Today everyone in "<<electorates[j].getArea()<<" was busy. No events today!"<<endl;

            cout.fill('-');
            cout.width(30);
            cout<<"\n";
        }

    }

}

void Election::runVotingDay(){

     cout<<"\n\n";
     cout.fill('=');
     cout.width(60);
     cout<<"REITERATION OF CHANGED PARTY REPORTS BEFORE VOTING";
     cout.width(35);
     cout<<"\n\n";
    printPartyReport();
                                                                //ALL TEXT FORMATTING IS TO THE SIDE TO ASSIST IN CLARITY FOR THE MAIN CODE
                                                                cout.fill('=');
                                                                cout.width(35);
                                                                cout<<"VOTING DAY!";
                                                                cout.width(35);
                                                                cout<<"\n";
                                                                int x = 0;
    int winner = 0;
    int biggest;
     for(int j=0; j<electorates.size(); j++){
      castVote(electorates[j], j);
      biggest = 0;
                                                                x++;
                                                                cout.fill('~');
                                                                cout.width(60);
                                                                cout<<"Electorate "<<x;
                                                                cout.width(30);
                                                                cout<<"\n";
         electorates[j].printElectorate();
                                                                cout.fill('-');
                                                                cout.width(35);
                                                                cout<<"\n";
         electorates[j].printEStanceVec();
                                                                cout.fill('=');
                                                                cout.width(35);
                                                                cout<<"\n";
                                                                cout.fill(' ');
        cout<<"Candidate";
        cout.width(20);
        cout<<"Votes";
                                                                cout<<"\n";
                                                                cout.fill('-');
                                                                cout.width(35);
                                                                cout<<"\n";

        for(int i=0; i<parties.size();i++){

                                                                cout.fill(' ');
            cout<<parties[i].getCanRef(j).getName();
                                                                cout.width(10);

           cout<<"\t\t"<<parties[i].getCanRef(j).getVote();

           if(biggest<parties[i].getCanRef(j).getVote()){                //compares all the candidate votes and selects the higfhest value as the winner
            winner = i ;
            biggest = parties[i].getCanRef(j).getVote();}

                                                                cout<<"\n\n";

        }

                                                                cout.fill('-');
                                                                cout.width(35);
                                                                cout<<"\n";

        cout<<"The winner of this vote is "<<parties[winner].getCanRef(j).getName();
        cout<<" from the party "<<parties[winner].getName()<<"!\n";

        parties[winner].addVote();

                                                                cout.fill('=');
                                                                cout.width(35);
                                                                cout<<"\n\n";



     }

        cout.fill('~');
        cout.width(35);
        cout<<"THE FINAL WINNER";
        cout.width(35);
        cout<<"\n\n";

        findWinner();


}

double Election::getLikliehood(Electorate elec, Candidate cand){

    //likliehood candidate will get a vote is dependent on
    //how smmall stance difference is   make the difference the standard deviation
    //how high their influence is     the mean will be the average of influence and popularity
    //how high their popularity is      the random number generated will be the %likliehood the cand will be voted for
    double likliehood;
    int mean;
    int difference = 0;
    for(int i=0; i<elec.getEStanceVec().size(); i++)
        difference = difference + elec.getSingleStance(i).difference(cand.getStanceRef(i));

    difference = difference/2;

    mean = (cand.getChrtrValue(POPULARITY)+cand.getChrtrValue(INFLUENCE))/2;

    normal_distribution<> normal(mean, difference);

    likliehood = (int)(normal(randEng));
    return likliehood/100;


}

void Election::castVote(Electorate elec, int index){

     double sum=0;
     double diff = 0;
     double temp = 0;
     double vote = 0;
/*THIS SECTION IS GETTING THE LIKLIEHOODS OF A CAND BEING VOTED ON AND SCALING THEM EVENLY SO EACH CANDIDATES LIKLIEHOOD ADDED TOGETHER = 100%*/
    for(int i=0; i<parties.size();i++){
        parties[i].getCanRef(index).setLikliehood(getLikliehood(elec, parties[i].getCanRef(index)));                        //getlikliehood method uses a distribution generated by the candidates stances and characteristics to determine the probability they will get voted for
    }


    for(int j=0; j<parties.size();j++){                             //this section gets the sum of likliehoods across the candidates and subtracts them from 1, and divides it by 3. This finds the difference so we can
        sum += parties[j].getCanRef(index).getLikliehood();         //proportionately reduce the likliehoods so they are within the range 0 - 100%
    }

     diff = (1-sum)/3;
    if(diff<0)
        diff =diff*-1;

    for(int k=0; k<parties.size();k++){
       temp = parties[k].getCanRef(index).getLikliehood();
       temp = temp-diff;

       parties[k].getCanRef(index).setLikliehood(temp);
       vote = parties[k].getCanRef(index).getLikliehood();
       vote = vote*elec.getPopulation();                            //times the likliehood by the population of the electorate to get number of votes.

       parties[k].getCanRef(index).setVote(vote);


    }

        /*NOTE:: any rounding errors where the total amount of votes is less than population
        can be attributed to people not voting within the electorate. This is a valid, real
        world occurance*/


}

void Election::findWinner(){

    int winner = -1;
    int totalElecs = electorates.size();

    for(int i=0; i<parties.size();i++){
    cout<<parties[i].getName()<<" has a total of "<< parties[i].getTotalVotes()<<" votes."<<endl;
    if(parties[i].getTotalVotes() > totalElecs*0.5 )
        winner = i;
    }

    if(winner == -1)
        cout<<"\nNo parties won over 50% of the electorates. It is declared a hung parliament. :("<<endl;
    else{
        cout<<"\nParty "<<parties[winner].getName()<<" has won the election! Their leader "<<parties[winner].getLeader()->getName()<<" is the new Prime Minister of Australia!"<<endl;
    }

}





/*--------------------ERROR FUNCTION----------------------*/

int Error(std::string message){

    std::cerr<<"\nError: "<< message<<"\nExiting."<<std::endl;                  //will take a string message for a variety of errors
    exit(1);
};



