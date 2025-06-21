C++ Interview Question Engine

A terminal-based C++ application designed to help prepare for MAANG interviews by randomly presenting DSA questions, tracking performance, and providing hints. Built to showcase advanced C++ and DSA skills.

Features->
<br>
 Question Database: Loads DSA questions from questions.txt using hash maps for O(1) topic-based lookups and a BST for organization.

 Performance Tracking: Tracks correct/incorrect answers by topic, using a priority queue to prioritize weaker areas.

 Random Question Selection: Selects questions randomly, with a bias towards weaker topics (70% chance).

 User Interaction: Supports commands for hints, answers, stats, and exiting.

 Unit Tests: Includes Google Test suite for question loading and performance tracking.

DSA Used->
<br>
 Hash Map: For O(1) question retrieval by topic and ID.
 Binary Search Tree (BST): For organizing questions by ID.
 Priority Queue: For prioritizing questions from weaker topics.
 File Handling: For loading questions from a text file.

C++ Features->
<br>
 Modern C++17 (e.g., structured bindings, std::unique_ptr).

 STL containers (std::unordered_map, std::vector, std::priority_queue).

 Exception handling for robust file I/O.
 
 Custom test framework for validation.

Prerequisites->
 C++17-compatible compiler (e.g., g++ 7 or later).
 Make (for Linux/macOS).

