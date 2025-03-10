//RANKING CLASS
#include "single_only.h"

void Ranking::add_player(Player *player){
    if (player->get_gender() == 'F'){
        
        female_players_ranking.push_back(player);
    }
    else{
        male_players_ranking.push_back(player);
    }
    
}
vector<Player*>& Ranking::sort_players(vector<Player*>& players) {
   
    
    for (int i = 0; i < static_cast<int>(players.size()); i++) {
         for (int j = 0; j <  static_cast<int>(players.size())- i - 1; j++) {
            if(players[j]->get_points()< players[j+1]->get_points()){
                Player* key = players[j];
                players[j]=players[j+1];
                players[j+1]= key;
         }
    }}

    for(int i = 0; i < static_cast<int>(players.size()); i++) {
        players[i]->set_rank(i+1);
    }
    return players;
}

void Ranking::update_ranking(Player *player, int points){
    player->add_points(points);
   
    if (player->get_gender() == 'M') {
        male_players_ranking=sort_players(male_players_ranking);
    } else {
        female_players_ranking=sort_players(female_players_ranking);
    }
    
}
void Ranking::remove_from_ranking(Player *player){
    int index;
    if(player->get_gender()=='F'){
        for(size_t i=0;i<female_players_ranking.size();i++){
            if(female_players_ranking[i]->get_name()==player->get_name()){
                index=i;
                break;

            }
        }
         if(index != -1){
           
            for(size_t i = index; i < female_players_ranking.size() - 1; i++){
                female_players_ranking[i] = female_players_ranking[i + 1];
            }
           
            female_players_ranking.pop_back();
    }}
     if(player->get_gender()=='M'){
        for(size_t i=0;i<male_players_ranking.size();i++){
            if(male_players_ranking[i]->get_name()==player->get_name()){
                index=i;
                break;

            }
        }
         if(index != -1){
            
            for(size_t i = index; i < male_players_ranking.size() - 1; i++){
                male_players_ranking[i] = male_players_ranking[i + 1];
            }
            
            male_players_ranking.pop_back();
    }
}}
void Ranking::display_ranking(vector<Player*>& players,char gender) const{
    if(gender == 'F'){

        cout<<"FEMALE RANKING"<<endl;}

    else{
         cout<<"MALE RANKING"<<endl;

    }
    std::this_thread::sleep_for(std::chrono::seconds(1));

    
    for(size_t i=0;i<players.size();i++){
        cout<< i+1 << ". " << players[i]->get_name() << "     "<< players[i]->get_points()<<endl;

    }}
   


int Ranking::get_rank(const Player *player) const{
    int index;
    if(player->get_gender()=='F'){
        for(size_t i=0;i<female_players_ranking.size();i++){
            if(female_players_ranking[i]->get_name()==player->get_name()){
                index=i;
                return index;

}}}
if(player->get_gender()=='M'){
        for(size_t i=0;i<male_players_ranking.size();i++){
            if(male_players_ranking[i]->get_name()==player->get_name()){
                index=i;
                return index;

}}}
return 0;
}