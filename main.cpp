#include "single_only.h"

int main() {
    
    
    Player player1("Iga Swiatek", 'F', 22, 5000, "Polish", 1);
    Player player2("Naomi Osaka", 'F', 23, 4500, "Japanese",2);
    Player player3("Coco Gauff", 'F', 20, 3000, "USA",2);
    Player player4("Aryna Sabalenka", 'F', 24, 4900, "Belarus",2);

    Player player5("Hubert Hurkacz",'M', 27, 3675, "Polish", 1);
    Player player6("Carlos Alcaraz", 'M',21, 7300, "Spanish",1);

    Wimbledon wimbledon(2024);

    wimbledon.singles_add_player(&player1);
   //TESTING
    vector<Player *> players = wimbledon.players_vec('F',1);
    if(players.size()!=1){
        cerr<<"adding player failed"<<endl;
        return 0;
    }
    if(players[0]->get_name() != "Iga Swiatek"){
        cerr<<"get_name() failed"<<endl;
        return 0;
    }
    if(players[0]->get_gender() != 'F' ){
         cerr<<"mistake in player information"<<endl;
         return 0;

    }
    if(players[0]->is_assigned_check(1)!=0 || players[0]->is_assigned_check(2)!=0){
        cerr<<"mistake in player information"<<endl;
        return 0;
    }
    //END
    
    wimbledon.singles_add_player(&player2);
    wimbledon.singles_add_player(&player3);
    wimbledon.singles_add_player(&player4);
    //TESTING
    players = wimbledon.players_vec('F',1);
    if(players.size()!=4){
        cerr<<"adding player failed"<<endl;
        return 0;  }
    for(size_t i=0;i<players.size();i++){
       if(players[i]->is_assigned_check(1)!=0 || players[i]->is_assigned_check(2)!=0 ||players[i]->get_gender()!='F' ){
        cerr<<"mistake in player information"<<endl;
        return 0;
    }
    }
    //END
   
    wimbledon.doubles_add_player(&player1,&player2);
    wimbledon.doubles_add_player(&player3,&player4);
    

    wimbledon.singles_add_player(&player5);
    wimbledon.singles_add_player(&player6);
    wimbledon.wildcard(2,'M');

    wimbledon.set_initial_players();
    //TESTING
    players = wimbledon.players_vec('M',1);
    if(players.size()!=4){
        cerr<<"adding player failed"<<endl;
        return 0;  }
    if(players[0]->get_name()!="Hubert Hurkacz" || players[1]->get_name()!="Carlos Alcaraz" ){
         cerr<<"mistake in player information"<<endl;
        return 0;
    }
    players = wimbledon.players_vec('F',2);
     if(players.size()!=4){
        cerr<<"doubles adding players failed"<<endl;
        return 0; }

    if(!wimbledon.verify_num_players()){
        cerr<<"Invalid number of players!"<<endl;
        return 0;
    }
    //END
    wimbledon.display_wimbledon();
    wimbledon.menu();
    
   
    
    

    
}