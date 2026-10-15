
#include <iostream>
#include <string>
using namespace std;

class Rule {
public:
    string condition1, condition2, conclusion;

    Rule() {
        condition1 = "";
        condition2 = "";
        conclusion = "";
    }

    Rule(string c1, string c2, string result) {
        condition1 = c1;
        condition2 = c2;
        conclusion = result;
    }
};

class KnowledgeBase {
public:
    Rule rules[8];

    KnowledgeBase() {
        rules[0] = Rule("fever", "cough", "flu");
        rules[1] = Rule("flu", "body_ache", "viral_infection");
        rules[2] = Rule("viral_infection", "high_fever", "medical_attention");
        rules[3] = Rule("sneezing", "runny_nose", "common_cold");
        rules[4] = Rule("common_cold", "fever", "respiratory_infection");
        rules[5] = Rule("burning", "nausea", "possible_gastritis");
        rules[6] = Rule("hard_stool", "bloating", "possible_constipation");
        rules[7] = Rule("headache", "fever", "possible_infection");
    }
};

class InferenceEngine {
public:
    bool hasFact(string facts[], int count, string fact) {
        for (int i = 0; i < count; i++) {
            if (facts[i] == fact) {
                return true;
            }
        }
        return false;
    }

    void applyRules(string facts[], int& count, KnowledgeBase kb) {
        bool changed = true;

        while (changed) {
            changed = false;

            for (int i = 0; i < 8; i++) {
                bool first = hasFact(facts, count, kb.rules[i].condition1);
                bool second = hasFact(facts, count, kb.rules[i].condition2);

                if (first && second &&
                    !hasFact(facts, count, kb.rules[i].conclusion) &&
                    count < 50) {

                    facts[count] = kb.rules[i].conclusion;
                    count++;

                    cout << kb.rules[i].condition1 << " + "
                         << kb.rules[i].condition2 << " -> "
                         << kb.rules[i].conclusion << endl;

                    changed = true;
                }
            }
        }
    }
};

class ExpertSystem {
public:
    void run() {
        string facts[50];
        int count = 0;
        string symptom;
        char choice;

        KnowledgeBase kb;
        InferenceEngine engine;

        cout << "Expert System\n";
        cout << "Enter symptoms in lowercase.\n";
        cout << "Use underscores instead of spaces.\n";

        do {
            cout << "Enter symptom: ";
            cin >> symptom;

            if (!engine.hasFact(facts, count, symptom) && count < 50) {
                facts[count] = symptom;
                count++;
            }

            cout << "Enter another symptom? (y/n): ";
            cin >> choice;

        } while (choice == 'y' || choice == 'Y');

        int originalCount = count;

        cout << "\nInference Process:\n";
        engine.applyRules(facts, count, kb);

        cout << "\nFinal Results:\n";
        bool found = false;

        for (int i = originalCount; i < count; i++) {
            cout << facts[i] << endl;
            found = true;
        }

        if (!found) {
            cout << "No matching rule found.\n";
        }

        cout << "Educational demonstration only, not medical advice.\n";
    }
};

int main() {
    ExpertSystem system;
    system.run();

    return 0;
}
