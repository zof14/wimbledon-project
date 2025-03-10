#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <chrono>
#include <thread>


#include <random>

using namespace std;

class Ranking;

class Player {
    private:
       
        string name;
        char gender;
        int age;
        int points;
        int ranking;
        string nationality;
        int type; // 1 for singles, 2 for both
        
        Player* current_opponent;
        
        Player* current_opponent_doubles;
        Player* doubles_partner;
        vector<pair<string, string>> match_results; // stores opponent name and result "won", "lost"
        vector<pair<pair<string, string>, string>> double_match_results;
        bool still_playing_singles;
        bool still_playing_doubles;
        int is_assigned;
        int is_assigned_doubles;
       
        
    public:
       Player(const std::string& name, char gender, int age, int points, const std::string& nationality, int match_type)
: name(name), gender(gender), age(age), points(points), nationality(nationality), type(match_type),
  current_opponent(nullptr), current_opponent_doubles(nullptr), doubles_partner(nullptr),
  still_playing_singles(false), still_playing_doubles(false), is_assigned(0), is_assigned_doubles(0) {
                if(match_type == 1 ){
                    this-> still_playing_singles = true;
                    this-> still_playing_doubles = false;
                    doubles_partner=nullptr;

                    
                }
                else if(match_type==2){
                    this-> still_playing_singles = true;
                    this-> still_playing_doubles = true;

                }
               
            }
        ~Player() = default;
        
        void set_partner(Player* player);
        int get_ranking(const Ranking* ranking) const;
        char get_gender() const;
        int get_age() const;
        bool is_playing() const;
        void player_info() const;
        string get_nationality() const;
        string get_name() const;
        void add_match_result(const string& opponent_name, const string& result);
        void doubles_add_match_result(const string& opponent1_name,const string& opponent2_name, const string& result);
        int get_points() const;
        void add_points(int pts);
        void set_current_opponent(Player* other,int type);
        Player* return_current_opponent(int type) const;
        Player* return_doubles_partner() const;
        const vector<pair<string, string>>& get_match_results() const;
        const  vector<pair<pair<string, string>, string>> get_doubles_match_res() const;
        int is_assigned_check(int type);
        void reset_assigned(int type);
        void set_rank(int i);
       
};

class Match {
private:
    Player* player1;
    Player* player2;
    //NEW
    Player* player3;
    Player* player4;
    int match_type; // 1 for singles, 2 for doubles
    int result; // 0 if match hasn't happened yet, 1 if player1 won, 2 if player2 won
   
public:
    Match(Player* player1, Player* player2)
        : player1(player1), player2(player2), match_type(1), result(0) {}

   
    Match(Player* player1, Player* player2, Player* player3, Player* player4)
        : player1(player1), player2(player2), player3(player3), player4(player4), match_type(2), result(0) {}

   
    ~Match() = default;


    void match_info() const;
    int get_result() const;
    void generate_result();
    void run_match();
    const Player* get_player1() const;
    const Player* get_player2() const;
    
    const Player* get_player3() const;
    const Player* get_player4() const;

   
};

class Ranking {
private:
    vector<Player*> male_players_ranking;
    vector<Player*> female_players_ranking;

public:
    Ranking(){};
    ~Ranking()=default;


    void add_player(Player* player);
    vector<Player*>& sort_players(vector<Player*>& players);
    void update_ranking(Player* player, int points);
    void remove_from_ranking(Player* player);
    int get_rank(const Player* player) const;
    void display_ranking(vector<Player*>& players,char gender) const;
    // const vector<Player*>& get_male_players() const;
    // const vector<Player*>& get_female_players() const;
};

class Round {
private:
    int round_number;
    vector<Match> matches_singles_female;
    vector<Match> matches_singles_male;
    
    vector<Match> matches_doubles_female;
    vector<Match> matches_doubles_male;

    // vector<Match> matches_doubles;

public:
    Round(int round_number): round_number(round_number){};
    ~Round()=default;

    void add_match(const Match& match, int gender,int type);
    int get_round_number() const;
    void display_round_info(char gender, int type) const;
    void run_matches(char gender,int type);
    void carry_round(vector<Player*> single_players,char gender,int type);
    
    const std::vector<Match>& get_female_matches() const; 
    const std::vector<Match>& get_male_matches() const ;
    const std::vector<Match>& get_doubles_female_matches() const;
    const std::vector<Match>& get_doubles_male_matches() const;



    // const vector<Match>& get_doubles_matches() const;
    void generate_opponents(vector<Player*> single_players,char gender,int type);
};

class Wimbledon {
    private:
    
       
        int year;
        int fsplayers_num;
        int msplayers_num;
        int fdplayers_num;
        int mdplayers_num;


        int current_round;
        vector<Round*>  rounds;
        Ranking ranking;
       
        int run;
    
        vector<Player*> single_fplayers;
        vector<Player*> single_mplayers;
        vector<Player*> initial_fplayers;
        vector<Player*> initial_mplayers;
        vector<Player*> double_fplayers;
        vector<Player*> double_mplayers;
        vector<Player*> initial_double_fplayers;
        vector<Player*> initial_double_mplayers;
        Player* winner_female_singles;
        Player* winner_male_singles;
        
    public:
        Wimbledon(int year)
            : year(year), fsplayers_num(0), msplayers_num(0),fdplayers_num(0),mdplayers_num(0), current_round(0),
             winner_female_singles(nullptr), winner_male_singles(nullptr)
           {

            run=0;
           }

        ~Wimbledon()=default;
        void display_wimbledon();
        
        void singles_add_player(Player* player);
        void doubles_add_player(Player* player1, Player* player2);
        
        bool verify_num_players() const;
        
        int get_round() const;
        Round* find_round(int round);
       
        int find_singles_info(string name);
        void menu();
        void update_points_win(int round_number, vector<Player*> players) ;
        
        
        vector<Player *> players_vec(char gender,int type) ;
        void display_round_results(int round) const;
        void run_wimbledon();
        void set_initial_players();
        void wildcard(int num,char gender);
        int finished();
        Player* get_winner(int type, char gender);
    };


