 #include <eosio/eosio.hpp>
 #include "json.hpp"
 #include <string>
 #include "json/json.h"

using namespace std;
using namespace eosio;
#define CHARM 500  // Entry fee CHARM
#define SCRAP 10   // Entry fee SCRAP
#define Hodl_symbol1 "CHARM"   // Allow Token1 type
#define Hodl_symbol2 "SCRAP"   // Allow Token2 type

#define CONTRACTN name("novarallydri") //Contract Name

CONTRACT novarallydri : public contract {
  public:
    using contract::contract;
    ACTION hi(name from, string message);
    ACTION clear();
    ACTION TotalScore(name user, );
    ACTION prizepayouts(name, owner)
    ACTION updateRace_table(name user, uint32_t raceNumber, int32_t order, int32_t groupID);
    ACTION totalScore(name user, bool endplay);
    ACTION addRacer(name user);

    const char *driver_name[21] = {'Steven', 'Ooze', 'Optimus', 'Otis', 'Carlton', 'Daniels', 'Beanpole', 'MTV', 'Viva', 'Squatorn', 'Spate', 'George', 'Square', 'Raagman', 'Divern', 'King', 'Earl', 'Tarsir', 'Scraptor', 'Vorder', 'Sammy', 'Snake', 'Scapegrace', 'Dilly', 'Dally', 'Zyca'};  

    const uint32_t *setPoints[8] = {10, 5, 3, 1, 1, 1, 1, 1};

    json::JSON carProps;
    carProps["Slamander"] = json::Array(1, 1, 1, 1, 1);
    carProps["Serpent"] = json::Array(1, 1, 1, 1, 1);
    carProps["Juker"] = json::Array(1, 1, 1, 1, 1);
    carProps["Prizefighter"] = json::Array(1, 1, 1, 1, 1);
    carProps["Skittle"] = json::Array(1, 1, 1, 1, 1);
    carProps["Ravager"] = json::Array(1, 1, 1, 1, 1);
    carProps["Rome"] = json::Array(1, 1, 1, 1, 1);
    carProps["Snout"] = json::Array(1, 1, 1, 1, 1);
    carProps["Turtle"] = json::Array(1, 1, 1, 1, 1);
    carProps["Vanessa"] = json::Array(1, 1, 1, 1, 1);

  private:
   int32_t racer = 0;
   bool startPlay = false;
   TABLE activePlayer
   {
       name user;
       int32_t groupID;
       char *selected_drivers[5];
       char *selected_cars[3];
       char *selected_strategys[3];
       race *race[5];
       uint32_t totalRacescore;
       uint64_t primary_key()const { return user.value; }
   };
   
   typedef multi_index<"activePlayer"_n, activePlayer> activePlayer_table;
   activePlayer_table _activePlayer;

   TABLE queue {
    name user;
    uint32_t groupID;
    uint64_t primary_key()const { return user.value; }
   }

   typedef multi_index<"queue"_n, queue> queue_table;
   queue_table _queue;

   TABLE raceResult {
      name user;
      uint32_t groupID;
      uint32_t *raceNumber[5];
      uint32_t *score[5];
      uint64_t primary_key()const { return user.value; }
   }  
   typedef multi_index<"raceResult"_n, raceResult> raceResult_table;
   raceResult_table _raceResult;

    TABLE messages {
      name    user;
      string  text;
      auto primary_key() const { return user.value; }
    };
    typedef multi_index<name("messages"), messages> messages_table;

    TABLE prizepayouts {
      name groupID[3][8];
      name ranking[3][3];
      uint32_t burn;
    }

    typedef multi_index<name("prizepayouts"), prizepayouts> prizepayouts_table;
    prizepayouts_table _prizepayouts;
    
    TABLE racerGroup {
      uint32_t groupID;
      name user[8];
      uint32_t totalRacescore[8];
      auto primary_key() const { return groupID.value; }

    }

    typedef multi_index<name("racerGroup"), racerGroup> racerGroup_table;
    prizepayouts_table _racerGroup;

  
    
    char *generateDrivers() {
      int lotteryNumbers = 0;
      int index = 0;
      int new_num;
      char *selectedDrivers[5] = {};
      for (int counter = 0; counter < 5; counter++)
      {	
          do{
              new_num = rand()%21;
              for( int i = 0; i < 5; i++ ){
                  if( new_num == lotteryNumbers[i] ){
                      new_num = 0;
                      break;
                  }
              }
          }while( new_num == 0 );
              lotteryNumbers[index] = new_num;
              selectedDrivers[index] = driver_name[new_num];
              index++;
      }
      return selectedDrivers;
    }
    char *generateCar() {
          int lotteryNumbers = 0;
          int index = 0;
          int new_num;
          char *selectedCars[3] = {};
          for (int counter = 0; counter < 3; counter++)
          {	
              do{
                  new_num = rand()%10;
                  for( int i = 0; i < 3; i++ ){
                      if( new_num == lotteryNumbers[i] ){
                          new_num = 0;
                          break;
                      }
                  }
              }while( new_num == 0 );
                  lotteryNumbers[index] = new_num;
                  selectedCars[index] = car_name[new_num];
                  index++;
          }
          return selectedCars;
    }
    char *generateStrategies() {
          int lotteryNumbers = 0;
          int index = 0;
          int new_num;
          char *selectedStrategies[3] = {};
          for (int counter = 0; counter < 3; counter++)
          {	
              do{
                  new_num = rand()%21;
                  for( int i = 0; i < 3; i++ ){
                      if( new_num == lotteryNumbers[i] ){
                          new_num = 0;
                          break;
                      }
                  }
              }while( new_num == 0 );
                  lotteryNumbers[index] = new_num;
                  selectedStrategies[index] = Strategies_name[new_num]
                  index++;
          }
          return selectedStrategies;

    }
};
