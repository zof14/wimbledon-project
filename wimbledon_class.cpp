#include "single_only.h"
//WIMBLEDON CLASS
void Wimbledon::singles_add_player(Player *player){
    if (player->get_name().empty() || player->get_age() <= 0 || player->get_nationality().empty()) {
        cerr << "Invalid player data!" << endl;
        return;
    }
    for (Player* existing_player : single_fplayers) {
        if (existing_player->get_name() == player->get_name()) {
            cerr << "Player " << player->get_name() << " already  added" << endl;
            return;
        }
    }
    for (Player* existing_player : single_mplayers) {
        if (existing_player->get_name() == player->get_name()) {
            cerr << "Player " << player->get_name() << "already added" << endl;
            return;
        }
    }
    if (player->get_gender() == 'F') {
        single_fplayers.push_back(player);
        fsplayers_num+=1;
    
    }
    else{
        single_mplayers.push_back(player);
        msplayers_num+=1;

    }
    ranking.add_player(player);
    player->reset_assigned(1);
    player->reset_assigned(2);


}
void Wimbledon::doubles_add_player(Player *player1, Player*player2){
    if (player1->get_gender() == 'F') {
        double_fplayers.push_back(player1);
        
        double_fplayers.push_back(player2);
        fdplayers_num+=2;

        
    }
    else{
        
        double_mplayers.push_back(player1);
        double_mplayers.push_back(player2);
        mdplayers_num+=2;
    
    }
    player1->set_partner(player2);}



// Wimbledon::~Wimbledon() {
//     for (Round* round : rounds) {
//         delete round;
//     }
// }
bool Wimbledon::verify_num_players() const{
    int f=0;
    int m=0;
    int fd;
    int md;
//     if(single_fplayers.size() %4 != 0 || single_mplayers.size() %4 != 0){
//         return 0;
//     }
//     return 1;
// }
if(single_fplayers.size() <2 && single_mplayers.size() >=2){
    f=1;
}
else if(single_mplayers.size() <2 && single_fplayers.size() >=2){
    m=1;
}
if(single_fplayers.size() ==2 || single_fplayers.size() ==4 || single_fplayers.size() ==8 || single_fplayers.size() ==16){
    f=1;
}
if(single_mplayers.size() ==2 || single_mplayers.size() ==4 || single_mplayers.size() ==8 || single_mplayers.size() ==16){
    m=1;
}
if (double_fplayers.size()==0 || double_fplayers.size()==4 || double_fplayers.size()==16){
    fd=1;
}
if (double_mplayers.size()==0 || double_mplayers.size()==4 || double_mplayers.size()==16){
    md=1;
}
if( f==1 && m==1 && md==1 && fd==1){
    return 1;
}
return 0;

}
Player *Wimbledon::get_winner(int type, char gender){
    if(type==1){

    if (gender == 'F') {
       return single_fplayers[0];
    }
    else{
        return single_mplayers[0];
    }}
     if(type==2){
        if (gender=='F'){
            return double_fplayers[0];
        }
        else{
        return double_mplayers[0];
    }
      }

    return nullptr;
}

vector<Player *> Wimbledon:: players_vec(char gender,int type){
    if( type==1){
        if(gender=='F'){
        return single_fplayers;}
        else{
            return single_mplayers;}
    }
    else{
        if(gender=='F'){
        return double_fplayers;}
        else{
            return double_mplayers;}
    }
}


int Wimbledon::find_singles_info(std::string name){
    
    for(int i=0; i < static_cast<int>(single_fplayers.size());i++){
        if (single_fplayers[i]->get_name() == name){
            cout<<"DISPLAYING PLAYER INFORMATION:"<<endl;
            single_fplayers[i]->player_info();
            cout<<" "<<endl;
            return 1;
        }
    }
    for(int i=0; i < static_cast<int>(single_mplayers.size());i++){
        if (single_mplayers[i]->get_name() == name){
            single_mplayers[i]->player_info();
            return 1;
        }
    }
    return 0;

}
void Wimbledon::display_wimbledon(){
    
    std::this_thread::sleep_for(std::chrono::seconds(2)); 
    cout<<"**********WIMBLEDON ";
    std::this_thread::sleep_for(std::chrono::milliseconds(500)); 
    cout<<"2";
    std::this_thread::sleep_for(std::chrono::milliseconds(500)); 
    cout<<"0";
    std::this_thread::sleep_for(std::chrono::milliseconds(500)); 
    cout<<"2";
    std::this_thread::sleep_for(std::chrono::milliseconds(500)); 
    cout<<"4";
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    cout<<"**********"<<endl;
     //
    single_fplayers=ranking.sort_players(single_fplayers);
    single_mplayers=ranking.sort_players(single_mplayers);
    ranking.display_ranking(single_fplayers,'F');
    ranking.display_ranking(single_mplayers,'M');



}
void Wimbledon::update_points_win(int round_number, std::vector<Player *> players){
     for (Player* player : players) {
            ranking.update_ranking(player,100*round_number);
            
}
}
void Wimbledon::run_wimbledon(){
  
    int round_number = 1;
    while (single_fplayers.size() > 1 || single_mplayers.size() > 1 || double_fplayers.size()>2 || double_mplayers.size()>2) {
        Round* round = new Round(round_number);
        cout << "****ROUND " << round_number << "****" << endl;
        if(single_fplayers.size() > 1){
        round->carry_round(single_fplayers, 'F',1);

        // Remove losers from the ranking based on match results
        vector<Player*> updated_single_fplayers;
        for (Player* player : single_fplayers) {
            const auto& match_results = player->get_match_results();
            bool lost = false;
            for (const auto& result : match_results) {
                if (result.second == "lost") {
                    lost = true;
                    break;
                }
            }
            if (!lost) {
                updated_single_fplayers.push_back(player);
            }
        }
        single_fplayers = updated_single_fplayers;}
        update_points_win(round_number, single_fplayers);
        
        if(single_mplayers.size()>1){
            round->carry_round(single_mplayers, 'M',1);

        // Remove losers from the ranking based on match results
        vector<Player*> updated_single_mplayers;
        for (Player* player : single_mplayers) {
            const auto& match_results = player->get_match_results();
            bool lost = false;
            for (const auto& result : match_results) {
                if (result.second == "lost") {
                    lost = true;
                    break;
                }
            }
            if (!lost) {
                updated_single_mplayers.push_back(player);
            }
        }
        single_mplayers = updated_single_mplayers;}
        update_points_win(round_number, single_mplayers);
        


     if(double_fplayers.size()>2){
            round->carry_round(double_fplayers, 'F',2);

        // Remove losers from the ranking based on match results
        vector<Player*> updated_double_fplayers;
        for (Player* player : double_fplayers) {
            const auto& match_results = player->get_doubles_match_res();
            bool lost = false;
            for (const auto& result : match_results) {
                if (result.second == "lost") {
                    lost = true;
                    break;
                }
            }
            if (!lost) {
                updated_double_fplayers.push_back(player);
            }
        }
        double_fplayers = updated_double_fplayers;}
        update_points_win(round_number, double_fplayers);
        

         if(double_mplayers.size()>2){
            round->carry_round(double_mplayers, 'M',2);

       
        vector<Player*> updated_double_mplayers;
        for (Player* player : double_mplayers) {
            const auto& match_results = player->get_doubles_match_res();
            bool lost = false;
            for (const auto& result : match_results) {
                if (result.second == "lost") {
                    lost = true;
                    break;
                }
            }
            if (!lost) {
                updated_double_mplayers.push_back(player);
            }
        }
        double_mplayers = updated_double_mplayers;}
        update_points_win(round_number, double_mplayers);

        
        
        // Store the round object
        rounds.push_back(round);

        // Increment round number
        round_number++;
    }
    cout<<"----------------------------"<<endl;
    cout<<"**********WINNERS**********"<<endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    cout<<"   *******SINGLES*******   "<<endl;
   std::this_thread::sleep_for(std::chrono::seconds(1));
   if(fsplayers_num!=0){
    cout<<"\t\t" << get_winner(1,'F')->get_name()<<endl;}
   std::this_thread::sleep_for(std::chrono::seconds(1));
   if(msplayers_num!=0){
    cout<<"\t\t" << get_winner(1,'M')->get_name()<<endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
   }

   if(fdplayers_num>1 || mdplayers_num>1){
     cout<<"   *******DOUBLES*******   "<<endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    if(fdplayers_num>1){
     Player* winner =  get_winner(2,'F');
     cout<<"\t\t" << winner->get_name()<<" & "<<winner->return_doubles_partner()->get_name()
     <<endl;}
   
   std::this_thread::sleep_for(std::chrono::seconds(1));
     if(mdplayers_num>1){
     Player* winner =  get_winner(2,'M');
     cout<<"\t\t" << winner->get_name()<<" & "<<winner->return_doubles_partner()->get_name()
     <<endl;}
std::this_thread::sleep_for(std::chrono::seconds(1));
   }
    cout<<"Ranking after tournament"<<endl;
    single_fplayers=ranking.sort_players(initial_fplayers);
    single_mplayers=ranking.sort_players(initial_mplayers);
    ranking.display_ranking(single_fplayers,'F');
    ranking.display_ranking(single_mplayers,'M');



    
}

void Wimbledon::display_round_results(int round) const{
    if (round <= 0 || round > static_cast<int>(rounds.size())) {
        cout << "Invalid round number!" << endl;
        return;
    }

    const Round* round_ptr = rounds[round - 1];

    cout << "**** ROUND " << round << " RESULTS ****" << endl;

    // Display female singles results
    cout << "\t**** FEMALE SINGLES ****" << endl;
    const auto& female_matches = round_ptr->get_female_matches();
    
    for (size_t i=0;i<female_matches.size();i++) {
        const Match & match = female_matches[i];
        const Player* player1 = match.get_player1();
        const Player* player2 = match.get_player2();
        int result = match.get_result();
       
        if (result == 1) {
            cout << "\t\t" << player1->get_name() << " defeats " << player2->get_name() << endl;
        } else if (result == 2) {
            cout << "\t\t" << player2->get_name() << " defeats " << player1->get_name() << endl;
        }
    }

    // Display male singles results
    cout << "\t**** MALE SINGLES ****" << endl;
    const auto& male_matches = round_ptr->get_male_matches();
    for (const Match& match : male_matches) {
        const Player* player1 = match.get_player1();
        const Player* player2 = match.get_player2();
        int result = match.get_result();
        if (result == 1) {
            cout << "\t\t" << player1->get_name() << " defeats " << player2->get_name() << endl;
        } else if (result == 2) {
            cout << "\t\t" << player2->get_name() << " defeats " << player1->get_name() << endl;
        }
    }

     // Display female singles results
    cout << "\t**** FEMALE DOUBLES ****" << endl;
     const auto& dfemale_matches = round_ptr->get_doubles_female_matches();
    
    for (size_t i=0;i<dfemale_matches.size();i++) {
        const Match & match = dfemale_matches[i];
        const Player* player1 = match.get_player1();
       
        const Player* player3 = match.get_player3();

        int result = match.get_result();
       
        if (result == 1) {
            cout << "\t\t" << player1->get_name() <<" & "<< player1->return_doubles_partner()->get_name() << endl;
            cout << " defeat " << player3->get_name()<<" & "<< player3->return_doubles_partner()->get_name() << endl;
        } else if (result == 2) {
           cout << "\t\t" << player3->get_name() <<" & "<< player3->return_doubles_partner()->get_name() << endl;
            cout << " defeat " << player1->get_name()<<" & "<< player1->return_doubles_partner()->get_name() << endl;
    }}

    cout << "\t**** MALE DOUBLES ****" << endl;
     const auto& dmale_matches = round_ptr->get_doubles_male_matches();
   
    for (size_t i=0;i<dmale_matches.size();i++) {
        const Match & match = dfemale_matches[i];
        const Player* player1 = match.get_player1();
       
        const Player* player3 = match.get_player3();

        int result = match.get_result();
       
        if (result == 1) {
            cout << "\t\t" << player1->get_name() <<" & "<< player1->return_doubles_partner()->get_name() << endl;
            cout << " defeat " << player3->get_name()<<" & "<< player3->return_doubles_partner()->get_name() << endl;
        } else if (result == 2) {
           cout << "\t\t" << player3->get_name() <<" & "<< player3->return_doubles_partner()->get_name() << endl;
            cout << " defeat " << player1->get_name()<<" & "<< player1->return_doubles_partner()->get_name() << endl;
    }

}
}


void Wimbledon::menu(){
     int action;
     int after;
     
    
    do {
        cout << "Choose action:" << endl;
        cout << "1. Player information" << endl;
        cout << "2. Start tournament" << endl;
        cout << "0. Exit" << endl;
        cin >> action;

        switch (action) {
            case 1: {
                string find;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "Type player's name:";
                std::getline(std::cin, find);
                
                int res = find_singles_info(find);
                if (!res) {
                    cout << "Player is not participating" << endl;
                }
                
                break;
            }
            case 2:
                
                run_wimbledon();
                run=1;
                action= 0;
                break;
            case 0:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please choose again." << endl;
        }
    } while (action != 0);
    
    if (run == 1){
        do{
        cout<< endl;
        cout<<"*TOURNAMENT ENDED*"<<endl;
        cout << "Choose action:" << endl;
        cout << "1. Player information" << endl;
        cout << "2. Round information" << endl;

        cout << "0. Exit" << endl;
        cin >> after;
        switch (after) {
            case 1: {
                string find;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "Type player's name:";
                std::getline(std::cin, find);
                
                int res = find_singles_info(find);
                if (!res) {
                    cout << "Player is not participating" << endl;
                }
                
                break;
            }
            case 2:
                int r;
                cout << "search for round: "<<endl;
                cin>> r;
                display_round_results(r);
                break;
                

            case 0:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please choose again." << endl;
            } 
        } while (after != 0);


    }
    
}
void Wimbledon::wildcard(int num,char gender){
     std::vector<Player*> wildcards_female;
     std::vector<Player*> wildcards_male;
    if (num < 0 || num > 3 || (gender!='F' && gender!='M')) {
        cerr << "information" << endl;
        return;
    }
    wildcards_female.push_back(new Player("Madison Keys", 'F', 29, 3283, "USA", 1));
    wildcards_female.push_back(new Player("Karolina Muchova", 'F', 27, 2810, "CZE", 1));
    wildcards_female.push_back(new Player("Elina Svitolina", 'F', 29, 2290, "UKR", 1));
    
    
    wildcards_male.push_back(new Player("Ben Shelton", 'M', 22, 2500, "USA", 1));
    wildcards_male.push_back(new Player("Alexander Bublik", 'M', 26, 2110, "Kazakhstan", 1));
    wildcards_male.push_back(new Player("Alex de Minaur", 'M', 25, 3490, "Australia", 1));
    if (gender =='F'){
        for(int i=0;i<num;i++){
            singles_add_player( wildcards_female[i]);
        }
    }
    if (gender=='M'){
         for(int i=0;i<num;i++){
            singles_add_player( wildcards_male[i]);
        }
    }


}


int Wimbledon::finished(){
    return run;
}

void Wimbledon::set_initial_players() {
    initial_fplayers = single_fplayers;
    initial_mplayers = single_mplayers;
    initial_double_fplayers=double_fplayers;
    initial_double_mplayers=double_mplayers;
}