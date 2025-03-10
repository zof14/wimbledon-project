#include "single_only.h"


void Match::match_info() const{
   if (match_type == 1) {
        cout << "\t\t";
        player1->player_info();
        cout << " VS "<<endl;
        cout<<"\t\t";
        player2->player_info();
        cout << endl;
       
    }
    else{
        
        cout << "\t\t";
        player1->player_info();
        cout <<" & ";
        player2->player_info();
        cout << "VS" << endl;
        cout << "\t\t";
        player3->player_info();
        cout <<" & ";
        player4->player_info();


    }
}
int Match::get_result() const{
    return result;
}
void Match::generate_result(){
    std::srand(static_cast<unsigned>(std::time(0)));

    // Generate a random number between 1 and 2
    result= rand() % 2 + 1;}

void Match::run_match(){
    
    generate_result();
   std::this_thread::sleep_for(std::chrono::seconds(1));
    cout << "\t*now playing*" << endl;

    cout << "\t\t";
    std::this_thread::sleep_for(std::chrono::seconds(1)); 
    if(match_type==1){
    player1->player_info();

    cout << " VS ";
    player2->player_info();
    cout << endl;}
    
    if(match_type==2){
        player1->player_info();
        cout << "& ";
        player2->player_info();
        cout << endl;
        cout << " VS ";
        player3->player_info();
        cout << "& ";
        player4->player_info();
        cout << endl;}

    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    if (result == 1) {
       std::this_thread::sleep_for(std::chrono::seconds(1));
        cout << "\t*result*" << endl;
       std::this_thread::sleep_for(std::chrono::seconds(1));
        cout<<"* ";
       std::this_thread::sleep_for(std::chrono::seconds(1));
        cout<<"* ";
       std::this_thread::sleep_for(std::chrono::seconds(1));
        cout<<"* "<< endl;
       std::this_thread::sleep_for(std::chrono::seconds(1));
       if(match_type==1){
        cout << "\t\t" << player1->get_name() << " defeats " << player2->get_name() << endl;
        player1->add_match_result(player2->get_name(), "won");
        
        player2->add_match_result(player1->get_name(), "lost");}
        else{
            cout << "\t\t" << player1->get_name() <<" & "<<player2->get_name() << " defeat " << player3->get_name() <<" & "<<player4->get_name()<< endl;
            player1->doubles_add_match_result(player3->get_name(),player4->get_name(),"won");
            player2->doubles_add_match_result(player3->get_name(),player4->get_name(),"won");
            player3->doubles_add_match_result(player1->get_name(),player2->get_name(),"lost");
            player4->doubles_add_match_result(player1->get_name(),player2->get_name(),"lost");

        }
       std::this_thread::sleep_for(std::chrono::seconds(1));
    } else if (result == 2) {
       std::this_thread::sleep_for(std::chrono::seconds(2));

        cout << "\t*result*" << endl;
       std::this_thread::sleep_for(std::chrono::seconds(1));
        cout<<"* ";
       std::this_thread::sleep_for(std::chrono::seconds(1));
        cout<<"* ";
       std::this_thread::sleep_for(std::chrono::seconds(1));
        cout<<"* "<< endl;
       std::this_thread::sleep_for(std::chrono::seconds(1));
        if(match_type==1){
        cout << "\t\t" << player2->get_name() << " defeats " << player1->get_name() << endl;
       std::this_thread::sleep_for(std::chrono::seconds(1));
        player1->add_match_result(player2->get_name(), "lost");
        player2->add_match_result(player1->get_name(), "won");}
        else{
             cout << "\t\t" << player3->get_name() <<" & "<<player4->get_name() << " defeat " << player1->get_name() <<" & "<<player2->get_name()<< endl;
            player1->doubles_add_match_result(player3->get_name(),player4->get_name(),"lost");
            player2->doubles_add_match_result(player3->get_name(),player4->get_name(),"lost");
            player3->doubles_add_match_result(player1->get_name(),player2->get_name(),"won");
            player4->doubles_add_match_result(player1->get_name(),player2->get_name(),"won");

        }
    }
}

const Player *Match::get_player1() const{
    return player1;
}
const Player *Match::get_player2() const{
    return player2;
}

const Player *Match::get_player3() const{
    return player3;
}

const Player *Match::get_player4() const{
    return player4;
}