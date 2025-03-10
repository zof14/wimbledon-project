# wimbledon-project
simulation of wimbledon in C++ 

  WIMBLEDON PROJECT
 
  Main objective:

The main objective of the program is to simulate the execution of a tennis tournament "Wimbledon".
The program consists of five classes: Player, Ranking, Match, Round, and Wimbledon.

  Classes:

  In the Player class, users can add players and specify the type of matches each player will
participate in (singles, doubles, or both). Each Player object contains attributes such as name, gender,
age, nationality, match results, and information whether player is still participating. The class allows
users to get player information, add match results, and check if a player is still active in the
tournament.

  The Ranking class manages the ranking of players based on their performance in the
tournament. By cooperating with class Player it maintains separate rankings for male and female
players and constantly updates the points of winners. Users can add players to the ranking, update
player rankings, and display the current rankings.

  The Match class represents individual matches in the tournament. It contains references to
player objects participating in the match and tracks the match type (singles or doubles) and the result
(winner). Program can generate match results randomly or allow user to manually update them.

  The Round class organizes matches into rounds of the tournament. Each round contains
vectors of Match objects representing singles and doubles matches scheduled during round. This
class allows to can add matches to rounds, display round information, and run matches to determine
winners.

  The Wimbledon class is the main point of the program. It manages the the tournament and
keeps track of the current round. Users can add players, verify the correctness of player additions, and
schedule matches for each round. The Wimbledon class also determines the overall winner of each
match type (singles and doubles) and updates the tournament rankings accordingly.

  Summary
The limitations of the classes include encapsulation and data validation (which will be provided in following
stages). All 5 classes cooperate and intertwine in order to provide a smooth simulation of the tournament.
It should be noted that certain methods or members will undergo changes and improvements alongside
the development of the project
