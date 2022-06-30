/************************************************
** Author: Andrea Hayes
** Date: October 5, 2020
** Module 13 - Classes
*************************************************/

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>

using namespace std;
int getInput();
// Class with member functions to get and set trivia information
class Question
{
    public:
        void setAsk(string a) {
            ask = a;
        }
        void setPossibleAnswer(string b, int i) {
            possibleAnswers[i] = b;
        }
        void setCorrectAnswer(int c) {
            correctAnswer=c;
        }
        string getAsk() {
            return ask;
        }
        string getPossibleAnswer(int i) {
            return possibleAnswers[i];
        }
        int getCorrectAnswer() {
            return correctAnswer;
        }
    
    private:
        string ask;
        string possibleAnswers[4];
        int correctAnswer;
};
bool askQuestion(Question);
int main() {

    ifstream in;
    // Open file
    in.open("trivia.txt"); 
    if (!in) 
    {
        cout << "Could not open file.";
        return 1;
    }
    // Puts file into string array then puts into them into a vector
    int lineNum = 0;
    string currentQuestion[6];
    vector <Question> triviaQuestions;
    while (!in.eof()) {
        getline(in, currentQuestion[lineNum % 6]);
        if (lineNum % 6==5) {
            Question *ptr=nullptr;
            ptr = new Question;
            ptr->setAsk(currentQuestion[0]);
            ptr->setPossibleAnswer(currentQuestion[1],0);
            ptr->setPossibleAnswer(currentQuestion[2],1);
            ptr->setPossibleAnswer(currentQuestion[3],2);
            ptr->setPossibleAnswer(currentQuestion[4],3);
            int correctAnswer = stoi(currentQuestion[5])-1;
            ptr->setCorrectAnswer(correctAnswer);
            triviaQuestions.push_back(*ptr);
        }
        lineNum++;
    }
   
    // Plays triva game
    int player1Total = 0, player2Total = 0;
    for (int i = 0; i < triviaQuestions.size();i++) {

        cout << "Question for Player " << i%2+1 << ": " << endl;
        
        bool playerCorrect = askQuestion(triviaQuestions[i]);
        if (playerCorrect) {
            if (i % 2 == 0) {
                player1Total++;
            }
            else {
                player2Total++;
            }
        }
        cout << endl;
    }
    // Displays results
    cout << endl;
    cout << "Player 1 answered " << player1Total << " question(s) correctly." << endl;
    cout << "Player 2 answered " << player2Total << " question(s) correctly." << endl;
    cout << endl;
    if (player1Total < player2Total) {
        cout << "Player 2 wins! Good game!" << endl;
    }
    else if (player1Total > player2Total) {
        cout << "Player 1 wins! Good game!" << endl;
    }
    else{
        cout << "It's a tie! Good game!" << endl;
    }

    return 0;
}
// Gets answer to question
int getInput()
{
    int number;
    do {
        cout << "Enter answer: ";
        cin >> number;
        if (number < 1 || number >4) {
            cout << "Enter a number between 1 and 4" << endl;
        }
    } while (number < 1 || number >4);
    return number;
}
// Checks if answer is correct 
bool askQuestion(Question q) {
    cout << q.getAsk() << endl;
    cout << "1." << q.getPossibleAnswer(0) << endl;
    cout << "2." << q.getPossibleAnswer(1) << endl;
    cout << "3." << q.getPossibleAnswer(2) << endl;
    cout << "4." << q.getPossibleAnswer(3) << endl;
    int inputAnswer = getInput();
    if (inputAnswer - 1 == q.getCorrectAnswer()) {
        cout << "That is correct." << endl;
        return true;
    }
    cout << "That is incorrect. The correct answer is " << q.getCorrectAnswer()+1 << endl;
    return false;
}


