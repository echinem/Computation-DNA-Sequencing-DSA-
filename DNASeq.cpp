#include <bits/stdc++.h>
using namespace std;

class DNA {
private:
    string seq1, seq2;
    int size1, size2;
    vector<vector<int>>* M;
    vector<vector<pair<int, int>>>* dir;
    vector<vector<pair<int, int>>>* dir2;
    vector<char> mapSeq1, mapSeq2;
    vector<char> match;
    int score;

public:
    DNA() : M(nullptr), dir(nullptr) {}

    void printMatrix() {
        cout << endl << "SCORE MATRIX"<<endl;
        cout << setw(5) << "   ";
        for (int i = 0; i < size1; i++) {
            cout << setw(5) << seq1[i];
        }
        cout << endl;
        for (int i = 0; i < size2; i++) {
            cout << setw(5) << seq2[i];
            for (int j = 0; j < size1; j++) {
                cout << setw(5) << (*M)[i][j];
            }
            cout << endl;
        }
    }

    void printCoord() {
        cout << endl << "COORDINATES MATRIX"<<endl;
        cout << setw(6) << " ";
        for (int i = 0; i < size1; i++) {
            cout << setw(9) << seq1[i];
        }
        cout << endl;
        for (int i = 0; i < size2; i++) {
            cout << setw(5) << seq2[i];
            for (int j = 0; j < size1; j++) {
                cout << setw(6) << "(" << (*dir)[i][j].first << "," << (*dir)[i][j].second << ")";
            }
            cout << endl;
        }
    }
    void printCoord2(){
        cout << endl << "COORDINATES MATRIX"<<endl;
        cout << setw(6) << " ";
        for (int i = 0; i < size1; i++) {
            cout << setw(12) << seq1[i];
        }
        cout << endl;
        for (int i = 0; i < size2; i++) {
            cout << setw(5) << seq2[i];
            for (int j = 0; j < size1; j++) {
                cout << setw(6) << "(" << (*dir2)[i][j].first << "," << (*dir2)[i][j].second << ")";
            }
            cout << endl;
        }
    }

    void matrixInitialization() {
        M = new vector<vector<int>>(size2, vector<int>(size1, 0));
        dir = new vector<vector<pair<int, int>>>(size2, vector<pair<int, int>>(size1, {0, 0}));
        dir2 = new vector<vector<pair<int, int>>>(size2, vector<pair<int, int>>(size1, {-1, -1}));
        mapSeq1.clear();
        mapSeq2.clear();
        match.clear();
        score=0;
    }

    void matrixFilling() {
        int left, above, diag;
        int w = -2;
        for (int i = 1; i < size2; i++) {
            for (int j = 1; j < size1; j++) {
                left = (*M)[i][j - 1] + w;
                above = (*M)[i - 1][j] + w;
                diag = (*M)[i - 1][j - 1] + (seq1[j] == seq2[i] ? 2 : -1);
                (*M)[i][j] = max(diag, max(left, above));
                if (left == (*M)[i][j]) {
                    (*dir)[i][j] = max((*dir)[i][j],{i, j - 1});
                } else if (above == (*M)[i][j]) {
                    (*dir)[i][j] = max((*dir)[i][j],{i - 1, j});
                } else {
                    (*dir)[i][j] = max((*dir)[i][j],{i - 1, j - 1});
                }
            }
        }
    }

    void traceback(){
        vector<pair<int,int>> coords;
        int new_i, new_j;
        int j=size1-1, i=size2-1;
        while(i>0 && j>0){
            coords.push_back({i,j});
            (*dir2)[i][j]=(*dir)[i][j];
            new_i = (*dir)[i][j].first;
            new_j = (*dir)[i][j].second;
            if(new_i == i && new_j == j-1){//left
                mapSeq1.push_back(seq1[j]);
                mapSeq2.push_back('-');
            }else if(new_i == i-1 && new_j == j){//above
                mapSeq2.push_back(seq2[i]);
                mapSeq1.push_back('-');
            }else if(new_i == i-1 && new_j == j-1){//diag
                mapSeq1.push_back(seq1[j]);
                mapSeq2.push_back(seq2[i]);
            }
            i = new_i;
            j=new_j;
        }
        coords.push_back({0,0});
        score=0;
        for(i=0;i<mapSeq1.size();i++){
            if(mapSeq1[i]==mapSeq2[i]){
                score+=2;
                match.push_back('|');
            }else if(mapSeq1[i]=='-' || mapSeq2[i]=='-'){
                score-=2;
                match.push_back(' ');
            }else if(mapSeq1[i]!=mapSeq2[i]){
                score-=1;
                match.push_back(' ');
            }
        }
        reverse(mapSeq1.begin(), mapSeq1.end());
        reverse(mapSeq2.begin(), mapSeq2.end());
        reverse(match.begin(), match.end());

    }
    void ShowAlignment(){
        cout << endl << "Maximum score: " << score << endl;
        cout << "\nFINAL ALIGNMENT\n";
        cout << endl;
        for(int i=0; i<mapSeq1.size();i++){
            cout << mapSeq1[i] << " ";
        }
        cout << endl;
        for(int i=0; i<match.size();i++){
            cout << match[i] << " ";
        }
        cout << endl;
        for(int i=0; i<mapSeq2.size();i++){
            cout << mapSeq2[i] << " ";
        }
        cout << endl;
    }

    bool isValid(const string& str) {
        for (char c : str) {
            if (c != 'A' && c != 'G' && c != 'C' && c != 'T') {
                return false;
            }
        }
        return true;
    }

    void input() {
        string s1, s2;
        cout << endl <<
        "ENTER DNA SEQUENCES: " << endl;
        cout << "Sequence-1: ";
        cin >> s1;
        cout << "Sequence-2: ";
        cin >> s2;
        for(auto &c: s1){
            c=toupper(c);
        }
        for(auto &c: s2){
            c=toupper(c);
        }

        if (isValid(s1) && isValid(s2)) {
            seq1 = " " + s1;
            seq2 = " " + s2;
            size1 = seq1.size();
            size2 = seq2.size();
        } else {
            cout << "The DNA sequence contains invalid characters. Please enter a valid DNA sequence." << endl;
            input();
        }
    }

    ~DNA() {
        delete M;
        delete dir;
    }

    void TryYourself(){
        int choice;
        input();

        while(choice!=3){
            cout << endl << "[ 1 ] DIRECT ANSWER\n[ 2 ] VISUALIZATION\n[ 3 ] EXIT"<<endl;
            cout << endl << "Enter choice: ";
            cin >> choice;
            if(choice == 1){
                matrixInitialization();
                matrixFilling();
                traceback();
                ShowAlignment();
            }else if(choice == 2){
                char x;
                cout << endl << "~~~~~~~~~ NEEDLEMAN-WUNSCH ALGORITHM ~~~~~~~~~" << endl;
                cout << endl << "INITIALIZATION:\nA matrix of size [M+1][N+1] is created to store alignment scores for all possible alignments of sequences.\nThe first row and column of the matrix are initialized to zero.\n\tSCORING SCHEME:\n\t\tMatch: +2\n\t\tMisMatch: -1\n\t\tGap: -2" << endl;
                matrixInitialization();
                printMatrix();
                printCoord();
                cout << endl << "PRESS ANY KEY TO CONTINUE: ";
                cin >> x;
                cout << endl << "MATRIX FILLING:\nEach cell in the matrix is filled by comparing corresponding nucleotides in the sequences and assigning scores based on matches, mismatches, and gap insertions." << endl;
                matrixFilling();
                printMatrix();
                printCoord();
                cout << endl << "PRESS ANY KEY TO CONTINUE: ";
                cin >> x;
                cout << endl << "TRACEBACK STEP:\nAfter filling the matrix, a traceback is performed from the bottom-right corner to find the optimal alignment path.\nAligned sequences are generated based on the traceback path, inserting gaps as needed." << endl;
                traceback();
                printMatrix();
                printCoord2();
                cout << endl << "PRESS ANY KEY TO CONTINUE: ";
                cin >> x;
                cout << "Finally, the alignment score is calculated to assess the similarity between the sequences, and the aligned sequences along with the score are outputted."<< endl;
                ShowAlignment();
            }else if(choice == 3){
                break;
            }
        }

    }

    void Info(){
        cout << "\nDEFINITON:\nDNA alignment involves comparing sequences of nucleotides (A, T, C, G) from different DNA samples. DNA sequencing is utilized to analyze genetic information, study evolutionary relationships, and understand biological processes across various fields." << endl;
        cout << endl << "IMPORTANCE:\nDNA sequencing is crucial for decoding genetic information, understanding inherited traits, diagnosing diseases, and advancing medical research" << endl;
        cout << endl << "APPLICATIONS:\n\t- Medicine: Diagnosing genetic disorders, predicting disease risk, and developing personalized treatments.\n\t- Genetics: Studying genetic variation, population genetics, and evolutionary relationships.\n\t- Forensics: Identifying suspects, establishing family relationships, and resolving paternity disputes.\n\t- Agriculture: Improving crop breeding, enhancing crop yield, and developing genetically modified organisms (GMOs).\n\t- Evolutionary Biology: Understanding the evolutionary history and relatedness of species through phylogenetic analysis.";
        cout << endl << endl;
        char next;
        cout << endl << "PRESS ANY KEY TO CONTINUE: ";
        cin >> next;
    }

    void Goodbye(){
        cout << "\n\nGOODBYE!!!" << endl << "Exiting program." << endl;
    }

    void Menu(){
        int choice=0;
        do{
            cout << endl << "DNA SEQUENCE ALIGNMENT"<<endl<<endl;
            cout << "[1] INFORMATION\n[2] TRY YOURSELF\n[3] EXIT\n";
            cout << endl << "Enter choice: ";
            cin >> choice;
            if(choice == 1){
                Info();
            }else if(choice == 2){
                TryYourself();
            }
            else if(choice == 3){
                Goodbye();
            }else{
                cout << "Please enter correct choice: ";
                Menu();
            }
        }while(choice!=3);
    }

};

int main() {
    DNA obj;
    obj.Menu();
    return 0;
}
