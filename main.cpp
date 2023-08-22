#include <iostream>
#include "ape_header.h"


using namespace std;

int main(int argc, char *argv[])
{
    /*------Validating argument count--------------------------*/

    if(argc != 3){
        Error("Please provide 2 valid arguments.");
    }

    int totalElecs = atoi(argv[1]);
    int electionDays = atoi(argv[2]);

    loadIssues();
    loadElectorates(totalElecs);
    loadPartyLeaders();
    loadEvents();
    genParty();

    printPartyReport();
    printElectorateReports();

    Election election;
    election.runCampaign(electionDays);




    /*Issue issue1(1, AIRQUALITY, "TESTER");
    issue1.printIssue();


    cout<<"\n";

    Human human("jsgfs");
    human.printHuman();
    cout<<"\n";
    human.updateCharacteristic(INFLUENCE, 3000);
    human.printHuman();
    cout<<"\n";

    human.printSingleCharacteristic(INFLUENCE);
    cout<<human.getChrtrValue(POPULARITY);

    Stance stance1(50, 89, 10, issue1);
    Stance stance2(12, 100, 80, issue1);
cout<<"\n";
    cout<<stance1.getInfluenceRadius();
    cout<<"\n";
    stance1.updateRadius(human.getChrtrValue(POPULARITY));
    cout<<stance1.getInfluenceRadius();
    cout<<"\n";

    cout<<stance1.difference(stance2);


    loadIssues();
    printIssueVector();

    //Stance stance1(50, 89, 10, issue1);
    Candidate cand("Wollongong", "Darcy");
    cand.printCStanceVec();

    PartyLeader pl("Wollongong", "Grace");
    pl.printPLStanceVec();


Human human("jsgfs");
    human.printHuman();
    cout<<"\n";
    human.updateCharacteristic(INFLUENCE, 3000);
    human.printHuman();
    cout<<"\n";

    human.printSingleCharacteristic(INFLUENCE);
    cout<<human.getChrtrValue(POPULARITY);


    */


    return 0;
}
