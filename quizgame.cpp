#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <ctime>   
#include <cstdlib> 
#include<algorithm>
using namespace std;

// Function to split a string
vector<string> split(const string &str, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(str);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Class for Player Registration and Login
class Player {
    string username;
    string password;

public:
    // Register a new player
    void registerPlayer() {
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        ofstream file("players.txt", ios::app); 
        file << username << " " << password << endl;
        file.close();

        cout << "Registration successful! You can now log in.\n";
    }

    // Login an existing player
    bool loginPlayer() {
        string enteredUsername, enteredPassword;
        cout << "Enter username: ";
        cin >> enteredUsername;
        cout << "Enter password: ";
        cin >> enteredPassword;

        ifstream file("players.txt");
        string fileUsername, filePassword;
        while (file >> fileUsername >> filePassword) {
            if (fileUsername == enteredUsername && filePassword == enteredPassword) {
                cout << "Login successful! Welcome " << enteredUsername << ".\n";
                return true;
            }
        }
        cout << "Invalid username or password.\n";
        return false;
    }
};

// Class for Quiz Gameplay
class Quiz {
    struct Question {
        string questionText;
        vector<string> options;
        char correctAnswer;
    };

    vector<Question> questions;
    int score = 0;

    
    void loadQuestions() {
        ifstream file("questions.txt");
        string line;
        while (getline(file, line)) {
            vector<string> parts = split(line, '|');
            if (parts.size() >= 5) {
                Question q;
                q.questionText = parts[0];
                q.options = {parts[1], parts[2], parts[3], parts[4]};
                q.correctAnswer = parts[5][0]; 
                questions.push_back(q);
            }
        }
        file.close();
    }

public:
    Quiz() {
        loadQuestions(); 
    }

    // Play the quiz
    void play() {
        if (questions.empty()) {
            cout << "No questions available! Please add questions to the questions.txt file.\n";
            return;
        }

        // Randomly shuffle the questions
          srand(time(0));
        vector<int> selectedIndexes;
        while (selectedIndexes.size() < 5 && selectedIndexes.size() < questions.size()) {
            int index = rand() % questions.size();
            if (std::find(selectedIndexes.begin(), selectedIndexes.end(), index) == selectedIndexes.end()) {
                selectedIndexes.push_back(index);
            }
        }
        cout << "Starting the quiz...\n";

        for (size_t i = 0; i < selectedIndexes.size(); ++i) {
            int idx = selectedIndexes[i];
            cout << "Q" << i + 1 << ": " << questions[idx].questionText << endl;
            cout << "A. " << questions[idx].options[0] << endl;
            cout << "B. " << questions[idx].options[1] << endl;
            cout << "C. " << questions[idx].options[2] << endl;
            cout << "D. " << questions[idx].options[3] << endl;

            cout << "Enter your answer (A/B/C/D): ";
            char answer;
            cin >> answer;
            answer = toupper(answer);

            if (answer == questions[idx].correctAnswer) {
                cout << "Correct!\n";
                ++score;
            } else {
                cout << "Wrong! The correct answer was " << questions[idx].correctAnswer << ".\n";
            }
        }

        cout << "Quiz finished! Your final score is " << score << "/" << selectedIndexes.size() << ".\n";
    }
};


int main() {
    Player player;
    Quiz quiz;
    int choice;

    while (true) {
        cout << "\nQuiz Game Menu:\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Play Quiz\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                player.registerPlayer();
                break;
            case 2:
                if (!player.loginPlayer()) {
                    cout << "Please register or try logging in again.\n";
                }
                break;
            case 3:
                quiz.play();
                break;
            case 4:
                cout << "Thank you for playing the Quiz Game! Goodbye.\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}
