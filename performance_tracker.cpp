#include "performance_tracker.h"
#include <iostream>
#include <iomanip>

void PerformanceTracker::record_answer(int question_id, bool correct, const std::string& topic) {
    auto& stats = topic_stats[topic];
    stats.total++;
    if (correct) stats.correct++;

    weak_topics = std::priority_queue<std::pair<double, std::string>, 
                                      std::vector<std::pair<double, std::string>>, 
                                      std::greater<>>();
    for (const auto& [t, s] : topic_stats) {
        weak_topics.push({s.get_accuracy(), t});
    }
}

std::string PerformanceTracker::get_weakest_topic() const {
    return weak_topics.empty() ? "" : weak_topics.top().second;
}

void PerformanceTracker::print_stats() const {
    std::cout << "\nPerformance Stats:\n";
    for (const auto& [topic, stats] : topic_stats) {
        std::cout << "Topic: " << topic << " | Correct: " << stats.correct 
                  << " | Total: " << stats.total 
                  << " | Accuracy: " << std::fixed << std::setprecision(2) 
                  << stats.get_accuracy() * 100 << "%\n";
    }
}