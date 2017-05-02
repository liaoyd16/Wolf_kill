#ifndef Event_h
#define Event_h

#include "Player_Agent.h"
#include "msg.h"
#include <queue>

using namespace std;

//declaration: virtual classes
class Player_Agent;
class msg;
class Rslt_maker;

typedef queue<msg>              msg_queue;
typedef queue<killing_vote_msg> kill_msg_queue;
typedef queue<elect_vote_msg>   elect_msg_queue;
typedef queue<chat_msg>         chat_msg_queue;
typedef queue<notif_msg>        notif_msg_queue;

/* Event = {
 Vote_Event = {
    Killing_Vote_Event, Elect_Vote_Event
 },
 Discuss_Event, Notification_Event
 
 } */

    //Event
class Event {

 protected:
    Player_Agent* member_list;
 public:
    Event();
    string Role;
    virtual ~Event() = 0;
};
    //Vote_Event
class Vote_Event : public Event {

 protected:
    //msg_queue vote_buff;
    friend class Rslt_maker;
 public:
    Vote_Event();
    void get_vote();
    void get_vote(Player_Agent&);
    virtual ~Vote_Event() = 0;
};

class Killing_Vote_Event : public Vote_Event {
 private:
    kill_msg_queue vote_buff;
};

class Elect_Vote_Event : public Vote_Event {
 private:
    elect_msg_queue vote_buff;
};

    //Discuss_Event
class Discuss_Event : public Event {

 private:
    chat_msg_queue chat_msg_buff; //消息队列
 public:
    Discuss_Event();
    void distribute_info();
    ~Discuss_Event();
};
    //Notification_Event
class Notification_Event {

 private:
    friend class Rslt_maker;
    notif_msg_queue notif_buff;
 public:
    Notification_Event();
    void notify(Player_Agent&);
    void notify();
    ~Notification_Event();
};

class Rslt_maker {
    
//result of police election
 private:
    struct{
        Player_Agent& PA;
        int count;
    } *elect_list;
 public:
    void fill_elect_list(Vote_Event&);
    
//result of killing vote
 private:
    struct{
        Player_Agent& PA;
        int count;
        Player_Agent* voter_list;
    } *charge_list;
 public:
    void fill_charged_list(Vote_Event&);

//send result to Notif_Event
    void add_notif_buff(Notification_Event& dest);
    /* Get result of election_vote, killing_vote, and death from elect_list & charged_list,
    then insert {elect info/charged info, death info} into dest.notif_buff */
};

#endif /* Event_h */
