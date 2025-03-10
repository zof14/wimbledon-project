#include "single_only.h"


using namespace std;


int Player::get_ranking(const Ranking *ranking) const{
    return ranking->get_rank(this);
}

char Player::get_gender() const{
    return this->gender;
}
std::string Player::get_name() const{
    return this->name;
}

int Player::get_age() const{
    return this->age;
}

bool Player::is_playing() const{
    return (this->still_playing_singles || this->still_playing_doubles);
}

void Player::player_info() const {
    cout << this->name << " (age: " << this->age << ", nationality: " << this->nationality << " rank: " << this->ranking << ")";
}

std::string Player::get_nationality() const{
    return this->nationality;
}

void Player::add_match_result(const std::string &opponent_name, const std::string &result){
    match_results.push_back({opponent_name,result});
}
int Player::get_points() const{
    return points;
}
void Player::add_points(int pts){
    points+=pts;
}
void Player::set_current_opponent(Player *other, int type){
    
    if(type==1){
    current_opponent = other;
    is_assigned=1;}
    else{
        current_opponent_doubles = other;
        is_assigned_doubles=1;
    }
}
Player *Player::return_doubles_partner() const{
    return doubles_partner;
}

Player *Player::return_current_opponent(int type) const{
    if(type==1){
    return current_opponent;}
    else{
        return current_opponent_doubles;
    }
}
int Player::is_assigned_check(int type){
    if(type==1){
    return is_assigned;}
    else{
        return is_assigned_doubles;
    }
}
void Player::reset_assigned(int type) {
    if(type==1){
    is_assigned = 0;}
    else{
    is_assigned_doubles=0;}
}

const std::vector<std::pair<std::string, std::string>> &Player::get_match_results() const{
    return match_results;
}
void Player::set_rank(int i){
    ranking =i;
}

void Player::doubles_add_match_result(const std::string &opponent1_name, const std::string &opponent2_name, const std::string &result){
    double_match_results.push_back({{opponent1_name,opponent2_name},result});
}
void Player::set_partner(Player *player){
    doubles_partner = player;
    player->doubles_partner = this;
}
const std::vector<std::pair<std::pair<std::string, std::string>, std::string>> Player::get_doubles_match_res() const{
    return double_match_results;
}