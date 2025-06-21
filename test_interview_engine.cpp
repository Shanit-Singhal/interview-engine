#include "test_framework.h"
#include "question_database.h"
#include "performance_tracker.h"
#include <fstream>

void test_load_questions() {
    std::ofstream file("test_questions.txt");
    file << "Array,1,Find max element,Use max_element,Iterate array\n";
    file.close();

    QuestionDatabase db("test_questions.txt");
    std::mt19937 rng(std::random_device{}());
    const Question* q = db.get_random_question("", rng);
    TestFramework::assert_true(q != nullptr, "Question should not be null");
    TestFramework::assert_equal(q->topic, "Array", "Topic should be Array");
    TestFramework::assert_true(q->difficulty == 1, "Difficulty should be 1");
    TestFramework::assert_equal(q->text, "Find max element", "Question text mismatch");
}

void test_performance_tracker() {
    PerformanceTracker tracker;
    tracker.record_answer(1, true, "Array");
    tracker.record_answer(2, false, "Array");
    tracker.record_answer(3, true, "Tree");
    TestFramework::assert_equal(tracker.get_weakest_topic(), "Array", "Weakest topic should be Array");
}

int main() {
    TestFramework tf;
    tf.add_test("LoadQuestions", test_load_questions);
    tf.add_test("PerformanceTracker", test_performance_tracker);
    tf.run_tests();
    return 0;
}