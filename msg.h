#ifndef msg_h
#define msg_h

#include "Player_Agent.h"

using namespace std;

class Player_Agent;

struct msg {
public:
    string type_flag; // = {"appoint_vote_msg", "killing_vote_msg", "chat_msg", "notif_msg"}
};

struct killing_vote_msg : public msg {
    killing_vote_msg(const Player_Agent* _sender, const Player_Agent* _target);
    
    //type_flag = "killing_vote_flag"
    
    const Player_Agent* sender;
    const Player_Agent* target;
    
    float weigh;
};

struct elect_vote_msg : public msg {
    elect_vote_msg (const Player_Agent* _sender, const Player_Agent* _choice);
    
    //type_flag = "elect_vote_msg"
    
    const Player_Agent* sender;
    const Player_Agent* choice;
};

struct chat_msg : public msg {
    chat_msg(const string& _text);
    
    //type_flag = "chat_msg"
    
    const Player_Agent* sender;
    string text;
};

struct notif_msg : public msg {
    notif_msg();
    
    //type_flag = "notif_msg"
    
    const Player_Agent* sender; //sender = nullptr 时为系统通知，反之为来自某一玩家的消息
    const Player_Agent* receiver;
    
    bool is_killing_vote_msg; //是否是death vote轮次产生的msg
};

#endif /* msg_h */
