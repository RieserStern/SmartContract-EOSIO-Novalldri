#include <novarallydri.hpp>

ACTION novarallydri::hi(name from, string message) {
  require_auth(from);

  // Init the _message table
  messages_table _messages(get_self(), get_self().value);

  // Find the record from _messages table
  auto msg_itr = _messages.find(from.value);
  if (msg_itr == _messages.end()) {
    // Create a message record if it does not exist
    _messages.emplace(from, [&](auto& msg) {
      msg.user = from;
      msg.text = message;
    });
  } else {
    // Modify a message record if it exists
    _messages.modify(msg_itr, from, [&](auto& msg) {
      msg.text = message;
    });
  }
}

ACTION novarallydri::clear() {
  require_auth(get_self());

  messages_table _messages(get_self(), get_self().value);

  // Delete all records in _messages table
  auto msg_itr = _messages.begin();
  while (msg_itr != _messages.end()) {
    msg_itr = _messages.erase(msg_itr);
  }
}
///////////// * prizepayouts */////////////
ACTION novarallydri::prizepayouts(name, owner) {
int j = 0, k = 0, l = 0;;
  for(int i = 0; i< 24 ; i++)
  {
    switch(_activePlayer[i].groupID) {
      case 0:
        _prizepayouts.groupID[0][j] = _activePlayer[i].user.value;
        _prizepayouts.rank[0][j] = _activePlayer[i].totalRacescore;
        j++;
        break;
      case 1:
        _prizepayouts.groupID[1][k] = _activePlayer[i].user.value;
        _prizepayouts.rank[0][j] = _activePlayer[i].totalRacescore;

        k++;
        break;
      case 2:
        _prizepayouts.groupID[1][l] = _activePlayer[i].user.value;
        _prizepayouts.rank[0][j] = _activePlayer[i].totalRacescore;

        l++;
    }
  }
  
  for(i = 0; i< 3; i++)
  {
    int sorted,index = 0;
    [sorted index] = sort (_prizepayouts.rank[i])
    _prizepayouts.ranking[i][0] = _prizepayouts.groupID[i][index[0]];
    _prizepayouts.ranking[i][1] = _prizepayouts.groupID[i][index[1]];
    _prizepayouts.ranking[i][2] = _prizepayouts.groupID[i][index[2]];
  
  }
}
    ///////////// * end prizepayouts */////////////

ACTION novarallydri::updateRace_table(name user, uint32_t raceNumber, int32_t order, int32_t groupID) {
  auto itr = _raceResult.find(user.value);
  if (itr == _raceResult.end()) {
    // Create a message record if it does not exist
    _raceResult.emplace(user, [&](auto& r) {
      r.user = user;
      r.groupID = groupID;
      r.raceNumber[raceNumber] = raceNumber;
      r.score[raceNumber] = setPoints[order];
    });
  } else {
    // Modify a message record if it exists
    _raceResult.modify(itr, user, [&](auto& r) {
        r.raceNumber[raceNumber] = raceNumber;
        r.score[raceNumber] = setPoints[order];
    });
  }
}
ACTION novarallydri::totalScore(name user, bool endplay) {
  if(!endplay){
    return;
  }
  auto itr = _activePlayer.find(user.value);

          // Modify a message record if it exists
  _activePlayer.modify(itr, user, [&](auto& r) {
    auto itr_race = _raceResult.find(user.value);
    _activePlayer.modify(itr_race, user, [&](auto& race) {
      for(int i = 0 ; i < 5 ; i++) {
          r.totalRacescore += race.score[i];
      }
    });
  });
}
ACTION novarallydri::addRacer(name user) {
  auto itr = _queue.find(user.value);
  if (itr != _queue.end()) {
    return;
  }
  _queue.emplace(user, [&](auto& r) {
    r.user = user;

    racer++;
  });
  if(racer > 24) {
    int groupID_duplicate[3]={0}; 
    int k = 3, h=0;
    for(int i = 0; i < 25 ; i++) {
      int j = rnd()%k + h;
      groupID_duplicate[j] ++;
      if(groupID_duplicate[0] > 8)
      {
        k = 2; h = 1;
      }
      else if(groupID_duplicate[1] > 8)
      {
        k = 2; h = 1;
      }
      else {
        k = 2; h = 0;
      }
      _queue[i].groupID = j + 1;
      startPlay = true;
    }
  }
}
EOSIO_DISPATCH(novarallydri, (hi)(clear))
