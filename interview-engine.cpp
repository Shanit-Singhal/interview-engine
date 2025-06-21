#include "question_database.h"
#include "performance_tracker.h"
#include <iostream>
#include <string>
#include <random>

int main() {
    try {
        // Initialize random number generator
        std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<int> dist(0, 1000);

        // Initialize database and tracker
        QuestionDatabase db("questions.txt");
        PerformanceTracker tracker;

        std::cout << "Welcome to the C++ Interview Question Engine!\n";
        std::cout << "Type 'hint' for a hint, 'answer' to submit an answer, 'stats' to view performance, or 'exit' to quit.\n";

        while (true) {
            // Select a random question, biased towards weaker topics
            auto question = db.get_random_question(tracker.get_weakest_topic(), rng);
            if (!question) {
                std::cout << "No questions available. Exiting.\n";
                break;
            }

            std::cout << "\nTopic: " << question->topic << " | Difficulty: " << question->difficulty << "\n";
            std::cout << "Question: " << question->text << "\n";

            std::string input;
            while (true) {
                std::cout << "> ";
                std::getline(std::cin, input);
                if (input == "exit") return 0;
                if (input == "hint") {
                    std::cout << "Hint: " << question->hint << "\n";
                    continue;
                }
                if (input == "answer") {
                    std::string user_answer;
                    std::cout << "Enter your answer: ";
                    std::getline(std::cin, user_answer);
                    bool correct = (user_answer == question->answer);
                    tracker.record_answer(question->id, correct, question->topic);
                    std::cout << (correct ? "Correct!" : "Incorrect. Correct answer: " + question->answer) << "\n";
                    break;
                }
                if (input == "stats") {
                    tracker.print_stats();
                    continue;
                }
                std::cout << "Invalid command. Use 'hint', 'answer', 'stats', or 'exit'.\n";
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}