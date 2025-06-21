#ifndef QUESTION_DATABASE_H
#define QUESTION_DATABASE_H

#include "question.h"
#include <unordered_map>
#include <vector>
#include <random>
#include <memory>

class QuestionDatabase {
private:
    struct Node {
        Question question;
        std::unique_ptr<Node> left, right;
        Node(const Question& q) : question(q), left(nullptr), right(nullptr) {}
    };

    std::unordered_map<std::string, std::vector<int>> topic_to_ids;
    std::unordered_map<int, Question> id_to_question;
    std::unique_ptr<Node> root;

    void insert_bst(std::unique_ptr<Node>& node, const Question& question);

public:
    QuestionDatabase(const std::string& filename);
    const Question* get_random_question(const std::string& preferred_topic, std::mt19937& rng) const;
};

#endif // QUESTION_DATABASE_H