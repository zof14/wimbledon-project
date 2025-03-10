// ROUND CLASS
#include "single_only.h"

void Round::add_match(const Match &match, int gender,int type){
    if(gender==1){
        if (type ==1){
        matches_singles_female.push_back(match);}
        else{
            matches_doubles_female.push_back(match);

        }

    }
    else{
        if (type ==1){
        matches_singles_male.push_back(match);}
        else{
            matches_doubles_male.push_back(match);

        }

    }
}


void Round::display_round_info(char gender,int type) const{
    
   std::this_thread::sleep_for(std::chrono::seconds(2));
   
   std::this_thread::sleep_for(std::chrono::seconds(1));
    if (gender=='F'){
        if(type==1){
        cout << "\t****FEMALE SINGLES****" << endl;
        cout << "\tscheduled matches:" << endl;
        for (size_t i = 0; i < matches_singles_female.size(); i++) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
            matches_singles_female[i].match_info();
            cout<<"\t\t----------------------------- "<<endl;
        }}
        else{
        cout << "\t****FEMALE DOUBLES****" << endl;
        cout << "\tscheduled matches:" << endl;
        for (size_t i = 0; i < matches_doubles_female.size(); i++) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        matches_doubles_female[i].match_info();
        cout<<"\t\t----------------------------- "<<endl;}
    }}
    
    
    else{
         if(type==1){
        cout << "\t****MALE SINGLES****" << endl;
         cout << "\tscheduled matches:" << endl;
        for (size_t i = 0; i < matches_singles_male.size(); i++) {
        std::this_thread::sleep_for(std::chrono::seconds(2));
            matches_singles_male[i].match_info();
            cout<<"\t\t----------------------------- "<<endl;
        }}
        else{
        cout << "\t****MALE DOUBLES****" << endl;
        cout << "\tscheduled matches:" << endl;
        for (size_t i = 0; i < matches_doubles_male.size(); i++) {
        std::this_thread::sleep_for(std::chrono::seconds(2));
            matches_doubles_male[i].match_info();
            cout<<"\t\t----------------------------- "<<endl;}
        }

    
    }
}
void Round::run_matches(char gender,int type){
    if(gender=='F'){
        if (type==1){

            for (size_t i=0; i< matches_singles_female.size();i++){
                matches_singles_female[i].run_match();}
        }
        else{
             for (size_t i=0; i< matches_doubles_female.size();i++){
                matches_doubles_female[i].run_match();}
        }
            
    }
    else{
        if (type==1){
            for (size_t i=0; i< matches_singles_male.size();i++){
                matches_singles_male[i].run_match();}
   
        }
        else{
            for (size_t i=0; i< matches_doubles_male.size();i++){
                matches_doubles_male[i].run_match();}

        }
    }


}
Round *Wimbledon::find_round(int round){
    return rounds[round-1];
}


int Round::get_round_number() const{
    return round_number;
}

void Round::generate_opponents(vector<Player*> single_players,char gender,int type){

  std::srand(static_cast<unsigned int>(std::time(nullptr)));
    int gen;
    if (gender == 'F') {
         gen=1;}
    if (gender == 'M') {
        gen=2;}
        int max = static_cast<int>(single_players.size());
        if (type==2){
        for (int i = 0; i < max - 1; ++i) {  
            
            if (!single_players[i]->is_assigned_check(type)) {
                
                int index;
                do {
                    index = std::rand() % max;  // Adjust index calculation here
                } while (index == i || single_players[index]->is_assigned_check(type) || single_players[index]== single_players[i]->return_doubles_partner());

                single_players[i]->set_current_opponent(single_players[index],type);
                single_players[index]->set_current_opponent(single_players[i],type);
                (single_players[i]->return_doubles_partner())->set_current_opponent(single_players[index]->return_doubles_partner(),type);
                (single_players[index]->return_doubles_partner()) ->set_current_opponent(single_players[i]->return_doubles_partner(),type);

                Match match(single_players[i],single_players[i]->return_doubles_partner(), single_players[index],single_players[index]->return_doubles_partner());
                
                add_match(match, gen,2);
            }
        }
        }
        
        if (type==1){
             for (int i = 0; i < max - 1; ++i) {  
            
            if (!single_players[i]->is_assigned_check(type)) {
                
                int index;
                do {
                    index = std::rand() % max;
                } while (index == i || single_players[index]->is_assigned_check(type) );

                single_players[i]->set_current_opponent(single_players[index],type);
                single_players[index]->set_current_opponent(single_players[i],type);

                Match match(single_players[i], single_players[index]);
                add_match(match, gen,1);
            }
        }

        }
        {
    }
   
}

void Round::carry_round(std::vector<Player *> single_players, char gender,int type){
    generate_opponents(single_players, gender,type);
    
    display_round_info(gender,type);
    run_matches(gender,type);
    for (Player* player : single_players) {
        player->reset_assigned(type);  
    }


}
const std::vector<Match> &Round::get_female_matches() const{
    return matches_singles_female;
}
const std::vector<Match> &Round::get_male_matches() const{
    return matches_singles_male;
}


const std::vector<Match> &Round::get_doubles_female_matches() const{
    return matches_doubles_female;
}
const std::vector<Match> &Round::get_doubles_male_matches() const{
    return matches_doubles_male;
}