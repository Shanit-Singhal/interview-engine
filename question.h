#ifndef QUESTION_H
#define QUESTION_H

#include <string>

struct Question {
    int id;
    std::string topic;
    int difficulty; // 1 (Easy), 2 (Medium), 3 (Hard)
    std::string text;
    std::string answer;
    std::string hint;

    Question(int id_, std::string topic_, int diff, std::string txt, std::string ans, std::string hnt)
        : id(id_), topic(topic_), difficulty(diff), text(txt), answer(ans), hint(hnt) {}
};

#endif // QUESTION_H