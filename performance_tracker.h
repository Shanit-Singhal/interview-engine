#ifndef PERFORMANCE_TRACKER_H
#define PERFORMANCE_TRACKER_H

#include <unordered_map>
#include <queue>
#include <string>

class PerformanceTracker {
private:
    struct TopicStats {
        int correct = 0;
        int total = 0;
        double get_accuracy() const { return total > 0 ? static_cast<double>(correct) / total : 0.0; }
    };

    std::unordered_map<std::string, TopicStats> topic_stats;
    std::priority_queue<std::pair<double, std::string>, 
                        std::vector<std::pair<double, std::string>>, 
                        std::greater<>> weak_topics;

public:
    void record_answer(int question_id, bool correct, const std::string& topic);
    std::string get_weakest_topic() const;
    void print_stats() const;
};

#endif // PERFORMANCE_TRACKER_H