#ifndef TEST_FRAMEWORK_H
#define TEST_FRAMEWORK_H

#include <iostream>
#include <string>
#include <vector>

class TestFramework {
private:
    struct TestCase {
        std::string name;
        void (*test_func)();
        TestCase(const std::string& n, void (*f)()) : name(n), test_func(f) {}
    };

    std::vector<TestCase> tests;
    int passed = 0;
    int total = 0;

public:
    void add_test(const std::string& name, void (*test_func)()) {
        tests.emplace_back(name, test_func);
    }

    void run_tests() {
        std::cout << "Running " << tests.size() << " tests...\n";
        for (const auto& test : tests) {
            total++;
            std::cout << "Test: " << test.name << " ... ";
            try {
                test.test_func();
                std::cout << "PASSED\n";
                passed++;
            } catch (const std::exception& e) {
                std::cout << "FAILED (" << e.what() << ")\n";
            }
        }
        std::cout << "\nResults: " << passed << "/" << total << " tests passed\n";
    }

    static void assert_true(bool condition, const std::string& message) {
        if (!condition) {
            throw std::runtime_error(message);
        }
    }

    static void assert_equal(const std::string& a, const std::string& b, const std::string& message) {
        if (a != b) {
            throw std::runtime_error(message + " (expected: " + b + ", got: " + a + ")");
        }
    }
};

#endif // TEST_FRAMEWORK_H