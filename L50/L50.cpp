#include <iostream>
#include <map>
#include <list>
#include <string>
#include <fstream>

using namespace std;

class Dictionary
{
    map<string, list<string>> dic;

public:

    void AddWord()
    {
        string word;
        int count;

        cout << "Enter word: ";
        cin >> word;

        if (dic.find(word) != dic.end())
        {
            cout << "Word already exists" << endl;
            return;
        }

        cout << "Enter number of translations: ";
        cin >> count;

        list<string> translations;

        for (int i = 0; i < count; i++)
        {
            string translate;

            cout << "Enter translation " << i + 1 << ": ";
            cin >> translate;

            translations.push_back(translate);
        }

        dic.insert(make_pair(word, translations));

        cout << "Word added" << endl;
    }

    void FindWord()
    {
        string word;

        cout << "Enter word: ";
        cin >> word;

        auto it = dic.find(word);

        if (it == dic.end())
        {
            cout << "Word not found" << endl;
            return;
        }

        cout << "Translations: ";

        for (string translate : it->second)
        {
            cout << translate << " ";
        }

        cout << endl;
    }

    void AddTranslate()
    {
        string word;

        cout << "Enter word: ";
        cin >> word;

        auto it = dic.find(word);

        if (it == dic.end())
        {
            cout << "Word not found" << endl;
            return;
        }

        string translate;

        cout << "Enter new translation: ";
        cin >> translate;

        it->second.push_back(translate);

        cout << "Translation added" << endl;
    }

    void SaveToFile()
    {
        ofstream file("dictionary.txt");

        if (!file)
        {
            cout << "File cannot be opened" << endl;
            return;
        }

        for (auto word : dic)
        {
            file << word.first;

            for (string translate : word.second)
            {
                file << " " << translate;
            }

            file << endl;
        }

        file.close();

        cout << "Dictionary saved" << endl;
    }

    void LoadFromFile()
    {
        ifstream file("dictionary.txt");

        if (!file)
        {
            cout << "File not found" << endl;
            return;
        }

        dic.clear();

        string word;

        while (file >> word)
        {
            string translate;
            list<string> translations;

            while (file.peek() != '\n' && file >> translate)
            {
                translations.push_back(translate);
            }

            dic.insert(make_pair(word, translations));
        }

        file.close();

        cout << "Dictionary loaded" << endl;
    }
};


int main()
{
    Dictionary dictionary;

    int choice;

    do
    {
        cout << "\n========== DICTIONARY ==========" << endl;
        cout << "1. Add word with translations" << endl;
        cout << "2. Find translations" << endl;
        cout << "3. Add translation" << endl;
        cout << "6. Save dictionary to file" << endl;
        cout << "7. Load dictionary from file" << endl;
        cout << "0. Exit" << endl;
        cout << "Choose: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            dictionary.AddWord();
            break;

        case 2:
            dictionary.FindWord();
            break;

        case 3:
            dictionary.AddTranslate();
            break;

        case 6:
            dictionary.SaveToFile();
            break;

        case 7:
            dictionary.LoadFromFile();
            break;

        case 0:
            cout << "Goodbye my friend" << endl;
            break;

        default:
            cout << "Wrong choice" << endl;
        }

    } while (choice != 0);
}
