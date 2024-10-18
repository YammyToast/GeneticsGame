#ifndef _MESSAGES_H_
#define _MESSAGES_H_

enum InMessageTypes
{
    GETUPDATE,
    ACTION

};

struct InMessageWrapper
{
    InMessageTypes type;
    char *body;
};

bool verify_data_is_json(const std::string& __json_string);
InMessageWrapper parse_incoming_json(const std::string& __json_string);

#endif