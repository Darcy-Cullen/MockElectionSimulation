#include <vector>
#include <iterator>
#include <map>
#include <iomanip>

#ifndef APE_HEADER_H_INCLUDED
#define APE_HEADER_H_INCLUDED

int randint();
int randintRange(int);
void loadIssues();
void printIssueVector();
void loadPartyLeaders();
void loadElectorates(int);
void genParty();
void printElectorateReports();
void printPartyReport();
void loadEvents();






enum ISSUE_TYPE{AIRQUALITY, HOUSING, CLIMATE, COVID, HOMELESS};

class Issue{
private:
    int issueNum;
    ISSUE_TYPE type;
    std::string statement;
public:
    Issue()=default;
    Issue(int _num, ISSUE_TYPE _type, std::string _statement){
    issueNum = _num;
    type = _type;
    statement = _statement;
    };
    ~Issue(){};

    int getIssueNum(){
        return issueNum;
    };

    ISSUE_TYPE getType(){
        return type;
    };

    std::string typeToString();

    void printIssue(){

        std::cout<<"Issue "<<issueNum<<": "<<statement<<std::endl;
    };

};

class Stance{
private:
    int approach;
    int significance;
    int influenceRadius;
    Issue issue;

public:
    Stance()=default;
    Stance(int _approach, int _significance, int _influenceRadius, Issue _issue){
    approach = _approach;
    significance = _significance;
    influenceRadius =_influenceRadius;
    issue = _issue;
    };
    ~Stance(){};
    void updateRadius(int);         //(popularity)
    int difference(Stance);       //difference between electorate and party stance

    void changeSignificance(int newSig){
        if((significance + newSig) > 100)
                significance = 100;
        else if((significance + newSig)<0)
            significance = 0;
        else
            significance = significance + newSig;
    };
    void changeApproach(int newApp){
        if((approach + newApp) > 100)
                approach = 100;
        else if((approach + newApp)<0)
            approach = 0;
        else
            approach = approach + newApp;
    };

    int getInfluenceRadius(){
        return influenceRadius;};

    int getApproach(){
        return approach;};

    int getSignificance(){
        return significance;};

    void printStance(){
        std::cout.fill(' ');
        std::cout<<"Issue "<<issue.getIssueNum()<<": "<<issue.typeToString()<<std::endl;
        std::cout<<"Approach: "<<approach<<std::setw(20)<<"Significance: "<<significance<<std::endl;

    }


};

class Electorate{
private:
    std::string area;
    std::string description;
    int population;
    std::vector<Stance> elecStances;
public:
    Electorate()=default;
    Electorate(std::string, int, std::string);
    ~Electorate(){};

    void printEStanceVec();
    void printElectorate(){
        std::cout<<"Electorate: "<<area<<"\nPopulation: "<<population<<"\n"<<description<<std::endl;
    };
    std::string getArea(){
        return area;
    }

    int getPopulation(){
        return population;
    }

    Stance getSingleStance(int i){
        return elecStances[i];
    }

    void electorateReport();

    std::vector<Stance> getEStanceVec(){
        return elecStances;
    }

};

enum CHARACTERISTIC{CONNECTION, ECONOMIC_EXP, ENVIRONMENTAL_EXP, EMPLOYMENT_EXP, SCANDAL_EXP, HEALTHCARE_EXP, INFLUENCE, POPULARITY, DEBATE_EXP};

class Human{
protected:
    std::map<CHARACTERISTIC, int> characteristics;
    std::string name;
public:
    Human()=default;
    Human(std::string);
    ~Human(){};
    void updateCharacteristic(CHARACTERISTIC, int);  //chrtr, value
    void printSingleCharacteristic(CHARACTERISTIC);
    void printHuman();
    int getChrtrValue(CHARACTERISTIC);
    std::string getName(){
        return name;
    }
};

class Candidate : public Human{
private:
    int voteCount;
    double likliehood;
    std::vector<Stance> candStances;
    Electorate electorateRep;
public:
    Candidate()=default;
    Candidate(std::string, Electorate);
    ~Candidate(){};
    void setVote(int votes){
        voteCount = votes;
    }

    int getVote(){
        return voteCount;
    }

    void setLikliehood(double d){
        if(d<0)
            likliehood=0;
        else
            likliehood = d;}

    double getLikliehood(){
        return likliehood;}


    void setStanceVec(std::map<int, int>);
    void printCStanceVec();

    std::vector<Stance>* getCandStances(){
        return &candStances;
    }

    Stance& getStanceRef(int i){

        return (*getCandStances())[i];

    }
    void printCand(){
        std::cout<<"Candidate Name: "<<name<<std::setw(20)<<"Electorate: "<<electorateRep.getArea()<<std::endl;
    }

};

class PartyLeader : public Human{
private:
    std::vector<Stance> leaderStances;
public:
    PartyLeader()=default;
    PartyLeader(std::string);
    ~PartyLeader(){};

    void printPLStanceVec();
    void setStanceVec(std::map<int, int>);

};

class ManagerialTeam : public Human{
private:
    int eventImpact;

public:
    ManagerialTeam()=default;
    ManagerialTeam(std::string, int);
    ~ManagerialTeam(){};

    int eventHandle(int, int);

};

class Party{
private:
    std::string name;
    PartyLeader leader;
    std::vector<Candidate> candidates;
    ManagerialTeam mangTeam;
    int totalVotes =0;
    std::map<int, int> stanceRanges;
public:
    Party()=default;
    Party(std::string, PartyLeader, ManagerialTeam);                //cand vector
    ~Party(){};
    void addVote(){
        totalVotes++;
    };

    int getTotalVotes(){
    return totalVotes;}

    void printParty(){
        std::cout<<"Party: "<<name<<"\nLeader: "<<leader.getName()<<"\nManagerial Team: "<<mangTeam.getName()<<std::endl;
    };

    void setCand(Candidate c){
        candidates.push_back(c);
    };

    std::vector<Candidate>* getCandidatesVec(){
        return &candidates;
    }

    Candidate& getCanRef(int i){

        return (*getCandidatesVec())[i];

    }

    std::map<int, int> getRangeMap(){
        return stanceRanges;
    }

    void printPartyCandsVec();
    void partyReport();
    void printStanceRange();
    std::string getName(){
        return name;
    }

    PartyLeader* getLeader(){
        return &leader;
    }
    ManagerialTeam getMangTeam(){
        return mangTeam;
    }
    void setCand_LeadStances();             //sets the candidate and leader stances using the party ranges

};


enum EVENT_TYPE{LEADER_DEBATE, CANDIDATE_DEBATE, LEADER_GOOD, LEADER_BAD, CANDIDATE_GOOD, CANDIDATE_BAD, ISSUE_AIR, ISSUE_COVID};


class Event{
private:
    EVENT_TYPE type;
public:
    Event()=default;
    Event(EVENT_TYPE _type) : type(_type){};
    ~Event(){};

    EVENT_TYPE getType(){
        return type;
    }
    void runLeaderDebate();
    void runCandidateDebate(Electorate);
    void runLeaderBad(Electorate);
    void runLeaderGood(Electorate);
    void runCandidateGood(Electorate);
    void runCandidateBad(Electorate);
    void runIssueAir(Electorate);
    void runIssueCovid(Electorate);

};

class Election{
public:
    Election()=default;
    void runCampaign(int);
    void runVotingDay();
    double getLikliehood(Electorate, Candidate);
    void castVote(Electorate, int);
    void findWinner();


};

void runEvent(Event, Electorate);

int Error(std::string);

#endif // APE_HEADER_H_INCLUDED
