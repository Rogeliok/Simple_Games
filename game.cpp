// Copyright Rogelio Keira [2023]

#include <iostream>
#include <fstream>
#include <Windows.h>

using namespace std;

#define WRONG_INPUT(arg) else if (Is_end(arg)) cout << endl << "wrong input" << endl << endl;

#define INPUT_CHECK(arg) cin >> arg; while (arg[0] != '1' && arg[0] != '2' && Is_end(arg)) { cout << endl << "wrong input" << endl << endl; cin >> arg; }

string hangman[10] = {"#################\n"  // 0
            "# -------       #\n"
            "# |     |       #\n"
            "# |     0       #\n"
            "# |             #\n"
            "# |             #\n"
            "# |             #\n"
            "# |             #\n"
            "# |             #\n"
            "# |             #\n"
            "# |             #\n"
            "#################\n", 
            "#################\n"  // 1
            "# -------       #\n"
            "# |     |       #\n"
            "# |     0       #\n"
            "# |    /|\\      #\n"
            "# |             #\n"
            "# |             #\n"
            "# |             #\n"
            "# |             #\n"
            "# |             #\n"
            "# |             #\n"
            "#################\n",
            "#################\n"  // 2
            "# -------       #\n"
            "# |     |       #\n"
            "# |     0       #\n"
            "# |    /|\\      #\n"
            "# |   /         #\n"
            "# |             #\n"
            "# |             #\n"
            "# |             #\n"
            "# |             #\n"
            "# |             #\n"
            "#################\n",
            "#################\n"  // 3
            "# -------       #\n"
            "# |     |       #\n"
            "# |     0       #\n"
            "# |    /|\\      #\n"
            "# |   / |       #\n"
            "# |             #\n"
            "# |             #\n"
            "# |             #\n"
            "# |             #\n"
            "# |             #\n"
            "#################\n",
            "#################\n"  // 4
            "# -------       #\n"
            "# |     |       #\n"
            "# |     0       #\n"
            "# |    /|\\      #\n"
            "# |   / | \\     #\n"
            "# |             #\n"
            "# |             #\n"
            "# |             #\n"
            "# |             #\n"
            "# |             #\n"
            "#################\n",
            "#################\n"  // 5
            "# -------       #\n"
            "# |     |       #\n"
            "# |     0       #\n"
            "# |    /|\\      #\n"
            "# |   / | \\     #\n"
            "# |     |       #\n"
            "# |             #\n"
            "# |             #\n"
            "# |             #\n"
            "# |             #\n"
            "#################\n",
            "#################\n"  // 6
            "# -------       #\n"
            "# |     |       #\n"
            "# |     0       #\n"
            "# |    /|\\      #\n"
            "# |   / | \\     #\n"
            "# |     |       #\n"
            "# |    /        #\n"
            "# |             #\n"
            "# |             #\n"
            "# |             #\n"
            "#################\n",
            "#################\n"  // 7
            "# -------       #\n"
            "# |     |       #\n"
            "# |     0       #\n"
            "# |    /|\\      #\n"
            "# |   / | \\     #\n"
            "# |     |       #\n"
            "# |    / \\      #\n"
            "# |             #\n"
            "# |             #\n"
            "# |             #\n"
            "#################\n"
            "#################\n"  // 8
            "# -------       #\n"
            "# |     |       #\n"
            "# |     0       #\n"
            "# |    /|\\      #\n"
            "# |   / | \\     #\n"
            "# |     |       #\n"
            "# |    / \\      #\n"
            "# |   /         #\n"
            "# |             #\n"
            "# |             #\n"
            "#################\n",
            "#################\n"  // 9
            "# -------       #\n"
            "# |     |       #\n"
            "# |     0       #\n"
            "# |    /|\\      #\n"
            "# |   / | \\     #\n"
            "# |     |       #\n"
            "# |    / \\      #\n"
            "# |   /   \\     #\n"
            "# |             #\n"
            "# |             #\n"
            "#################\n"};

bool Is_string_digit(string input_string) {
    int i = 0;
    while(input_string[i] != '\0')
        if(!isdigit(input_string[i++]))
            return false;
    return true;
}

bool Is_end(string input) { return !(input[0] == 'q' || input[0] == 'Q' || input[0] == '�' || input[0] == '�'); }

void interval_setting(int *number) {
    string input_string("0");
    while (Is_end(input_string)) {
        cin >> input_string;
        if (Is_string_digit(input_string)) {
            *number = stoi(input_string);
            break;
        } WRONG_INPUT(input_string)
    }
}

string get_word(char difficulty) {
    string word = "\0";
    ifstream file("words.txt", ios_base::in);
    srand(time(NULL));
    if(file) {
        do {
            getline(file, word);
        } while(word[0] != difficulty && !file.eof());
        int number = rand() % 10;
        for (int i = 0; i < number && !file.eof(); i++) getline(file, word);
        file.close();
        word.erase(0, 2);
    } else cout << "Computer_Game: �� ������� ������� �������";
    return word;
}

void Write_log_Guess(bool game_flag, int try_count, int guessed_number, int game_Guess_count, int game_note_count, int a, int b, int guesser_flag) {
    ofstream log_file("Computer_Game.log", ios_base::app);
    if (!log_file) {
        cout << "Computer_Game: �� ������� ������� ���� �����������" << endl;
        return;
    }
    log_file << "game: ������ �����" << endl << "\t���� �����: " << game_Guess_count << endl;
    log_file << "\t" << "��������� ����� " << (guesser_flag == 1 ? "�������" : "���������") << endl;
    if (game_flag) log_file << "\t������: �������� ���� ��������" << endl;
    else log_file << "\t������: ������" << endl;
    log_file << "\t���� �������� �����: " << (game_flag && guesser_flag == 1 ? -1 : guessed_number) << endl;
    log_file << "\t������� ��������: �� " << a << " �� " << b << endl;
    log_file << "\t������� ��: " << try_count << " �������" << endl;
    log_file << "\t������ �����: " << game_note_count << endl << endl;
    log_file.close();
}

void Write_log_Gallows(string buffer, string guessed_word, int wrong_count, int game_Gallows_count, int game_note_count, int try_count) {
    ofstream log_file("Computer_Game.log", ios_base::app);
    if (!log_file) {
        cout << "Computer_Game: �� ������� ������� ���� �����������" << endl;
        return;
    }
    log_file << "game: ��������" << endl << "\t���� ����� " << game_Gallows_count << endl;
    if (buffer == guessed_word) log_file  << "\t������: �������" << endl;
    else if (buffer != guessed_word && 10 > wrong_count) log_file  << "\t������: ���� ���������� ��������" << endl;
    else log_file  << "\t������: ��������" << endl;
    int lenght_flag = (int)guessed_word.length(), count = 0;
        for (int j = 0; j < lenght_flag; j++) 
            if(guessed_word[j] == '_') count++;
        count = lenght_flag - count;
    log_file << "\t���� �������� �����: " << buffer << endl;
    log_file << "\t������� ���������: " << (int)buffer.length() - 8 << " �� 3" << endl;
    log_file << "\t������������ ������: " << count << " �� " << (int)buffer.length();
    log_file << " ���� �� " << try_count << " �������" << endl;
    log_file << "\t���������� ���������� ������: " << 10 - wrong_count << endl;
    log_file << "\t������ �����: " << game_note_count << endl;
    log_file.close();
}

int game_Guess(int *game_Guess_count, int *game_note_count) {
    cout << "���� \"������ �����\" ��������" << endl;
    cout << "����������� ����� ��������� � ��������� �� 0 �� 100" << endl;
    bool game_flag = true;
    int number = 0, try_count = 0;
    int a = 0, b = 100;
    int left = a, right = b + 1;
    int digit = 0;
    string input_string;
    while (Is_end(input_string)) {
        cout << "�����/����� - q or �" << endl;
        cout << "�������� �������� �������� ������������� ����� ?" << endl << "1 - ��" << endl << "2 - ���" << endl;
        INPUT_CHECK(input_string)
        if (input_string[0] == '1') {
            cout << "������ ������ ������� ��������� (����� �����)" << endl;
            interval_setting(&a);
            cout << "������ ������� ������� ��������� (����� �����)" << endl;
            interval_setting(&b);
            if (b < a) swap(a, b);
            else if (a == b) b += 50;
            left = a;
            right = b + 1;
            cout << "����� �������� �������� ������������� ����� �� " << a << " �� " << b << endl;
        }
        cout << "��� ���������� ����� ?" << endl << "1 - �������" << endl << "2 - ���������" << endl;
        INPUT_CHECK(input_string)
        char operating_mode = input_string[0];
        if (operating_mode == '1') {  // Human
            input_string.clear();
            if (*game_Guess_count > 1) cout << "�������� �������� ������������� ����� �� " << a << " �� " << b << endl;
            cout << "1 - ������    2 - ������    3 - ������" << endl;
            cout << "���������� ����� " << (left + right) / 2 << '?' << endl;
            while (game_flag && Is_end(input_string)) {
                cin >> input_string;
                if (Is_string_digit(input_string)) {
                    if (input_string[0] == '1') {
                        right = (left + right) / 2;
                        // cout << "���������� ����� " << (left + right) / 2 << '?' << " " << left << " " << right << endl;
                        cout << "���������� ����� " << (left + right) / 2 << '?' << endl;
                    }
                    else if (input_string[0] == '2') {
                        left = (right + left) / 2;
                        // cout << "���������� ����� " << (left + right) / 2 << '?' << " " << left << " " << right << endl;
                        cout << "���������� ����� " << (right + left) / 2 << '?' << endl;
                    }
                    else if (input_string[0] == '3') {
                        cout << "��� ���������� ����� ��� " << (right + left) / 2 << endl;
                        game_flag = false;
                    }
                    try_count++;
                } WRONG_INPUT(input_string)
            }
            Write_log_Guess(game_flag, try_count, (right + left) / 2, ++(*game_Guess_count), ++(*game_note_count), a, b, 1);
            left = a;
            right = b + 1;
        } else if (operating_mode == '2') {  // Computer
            srand(time(NULL));
            number = (b - a + 1) * rand() / RAND_MAX + a;
            input_string.clear();
            if (*game_Guess_count > 1) cout << "�������� �������� ������������� ����� �� " << a << " �� " << b << endl;
            cout << "����������" << endl;
            while (game_flag && Is_end(input_string)) {
                cin >> input_string;
                if(Is_string_digit(input_string)) {
                    digit = stoi(input_string);
                    if (digit > number) cout << "���������� ����� ������ ��� " << digit << endl;
                    else if (digit < number) cout << "���������� ����� ������ ��� " << digit << endl;
                    else {
                        cout << "��� ���������� ����� ��� " << number << endl;
                        game_flag = false;
                    }
                    try_count++;
                } WRONG_INPUT(input_string)
            }
            Write_log_Guess(game_flag, try_count, number, ++(*game_Guess_count), ++(*game_note_count), a, b, 2);
        } WRONG_INPUT(input_string)
        try_count = 0;
        game_flag = true;
    }
    return 0;
}

int game_Gallows(int *game_Gallows_count, int *game_note_count) {
    srand(time(NULL));
    cout  << endl << "���� \"��������\" ��������" << endl;    
    char input_string[128] = {'\0'};
    string buffer, guessed_word, wrong_letters;
    int coincidence_count = 0, wrong_count = 0, try_count = 0;
    while (Is_end(input_string)) {
        cout << "�������� ��������� 1 - ������  2 - �������  3 - �������" << endl << "���������� ������� 10" << endl << "����� - q, �" << endl << endl;
        cin >> input_string;
        if (Is_string_digit(input_string) && '0' < input_string[0] && input_string[0] < '4') {
            buffer = get_word(input_string[0]);
            for(int i = 0; i < (int)buffer.size(); i++) guessed_word += '_';
            while(buffer != guessed_word && wrong_count < 10 && Is_end(input_string)) {
                // cout << buffer << endl;  // ������� ��������
                cout << guessed_word << endl;
                if (wrong_count > 0) cout << "������������ �����: " << wrong_letters << endl;
                cout << "������� �����" << endl;
                cin >> input_string;
                if (('�' <= input_string[0] && input_string[0] <= '�') && Is_end(input_string)) {
                    for(int i = 0; buffer[i] != '\0'; i++) {
                        if (buffer[i] == input_string[0]) {
                            guessed_word[i] = input_string[0];
                            coincidence_count++;
                        }
                    }
                    if (guessed_word.find(input_string[0]) != string::npos) cout << endl << "����� ����� ��� ����" << endl << endl;
                    if (coincidence_count == 0) {
                        cout << hangman[wrong_count++] << endl;
                        if (wrong_letters.find(input_string[0]) == string::npos) wrong_letters += input_string[0];
                    }
                    coincidence_count = 0;
                } WRONG_INPUT(input_string)
                try_count++;
            }
            if (!Is_end(input_string)) {}
            else if(buffer == guessed_word) cout << "��� �� ������� �����  " << buffer << "  =)"  << endl;
            else cout << "�� ��������� ���������� ����� ����  " << buffer << "  =(" << endl;
            Write_log_Gallows(buffer, guessed_word, wrong_count, ++(*game_Gallows_count), ++(*game_note_count), try_count);
            wrong_count = 0;
            try_count = 0;
            wrong_letters.clear(); 
            guessed_word.clear();
        } WRONG_INPUT(input_string)
    }
    return 0;
}

int main(void) {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int game_Guess_count = 0, game_Gallows_count = 0, game_note_count = 0; 
    string input("0");
    ofstream log_file("Computer_Game.log", ios_base::out);
    if (log_file) log_file.close();
    while (Is_end(input)) {
        cout << endl << "�������� ����" << endl << "1 - ������ �����" << endl << "2 - ��������" << endl << "����� - q, �" << endl << endl;
        cin >> input;
        if (input[0] == '1' && (int)input.size() == 1) game_Guess(&game_Guess_count, &game_note_count);
        else if (input[0] == '2' && (int)input.size() == 1) game_Gallows(&game_Gallows_count, &game_note_count);
        WRONG_INPUT(input)
    }
    return 0;
}
