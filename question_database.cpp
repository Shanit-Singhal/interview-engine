#include "question_database.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

QuestionDatabase::QuestionDatabase(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open questions file: " + filename);
    }

    std::string line;
    int id = 1;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::istringstream iss(line);
        std::string topic, text, answer, hint;
        int difficulty;
        std::getline(iss, topic, ',');
        iss >> difficulty;
        iss.ignore(1, ',');
        std::getline(iss, text, ',');
        std::getline(iss, answer, ',');
        std::getline(iss, hint);

        Question q(id++, topic, difficulty, text, answer, hint);
        topic_to_ids[topic].push_back(q.id);
        id_to_question[q.id] = q;
        insert_bst(root, q);
    }
    file.close();
}

void QuestionDatabase::insert_bst(std::unique_ptr<Node>& node, const Question& question) {
    if (!node) {
        node = std::make_unique<Node>(question);
        return;
    }
    if (question.id < node->question.id) {
        insert_bst(node->left, question);
    } else {
        insert_bst(node->right, question);
    }
}

const Question* QuestionDatabase::get_random_question(const std::string& preferred_topic, std::mt19937& rng) const {
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    bool use_preferred = !preferred_topic.empty() && topic_to_ids.find(preferred_topic) != topic_to_ids.end() && dist(rng) < 0.7;

    const auto& ids = use_preferred ? topic_to_ids.at(preferred_topic) : [&]() {
        std::vector<int> all_ids;
        for (const auto& [_, ids] : topic_to_ids) {
            all_ids.insert(all_ids.end(), ids.begin(), ids.end());
        }
        return all_ids;
    }();

    if (ids.empty()) return nullptr;
    std::uniform_int_distribution<size_t> id_dist(0, ids.size() - 1);
    int selected_id = ids[id_dist(rng)];
    return &id_to_question.at(selected_id);
}