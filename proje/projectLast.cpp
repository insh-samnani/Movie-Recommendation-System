#include<iostream>

#include<string>

#include<algorithm>

#include<fstream>

#include<vector>

#include<sstream>

#include <queue>

#include<map>

#include<windows.h>

#include<stdlib.h>


using namespace std;

class ArrayIndexOutOfBoundsException : public std::exception {
public: const char* what() const
    throw () {
    return "Exception: Index out of bound!";
}
};

template < typename Type >
class DynArr {
public:

    Type* arr;
    int size;
    int capacity;

    enum {
        SPARE_CAPACITY = 10
    };

    DynArr(int size_ = 0) {

        size = size_;
        capacity = size + SPARE_CAPACITY;
        arr = new(nothrow) Type[capacity];

        for (int i = 0; i < size; i++) {
            arr[i] = 0;
        }
    }

    DynArr(const DynArr& otherObject) {
        size = otherObject.size;
        capacity = otherObject.capacity;

        arr = new(nothrow) Type[size];
        for (int i = 0; i < size; i++) {
            arr[i] = otherObject.arr[i];
        }
    }

    Type& operator[](int index) {
        if (index < 0 || index >= size) {
            throw ArrayIndexOutOfBoundsException();
        }
        return arr[index];
    }

    ~DynArr() {
        delete[] arr;
    }

    void pushBack(int val) {
        if (size == capacity) {
            Type* new_arr = new(nothrow) Type[2 * capacity];
            for (int i = 0; i < size; i++) {
                new_arr[i] = arr[i];
            }
            delete arr;
            arr = new_arr;
            capacity = 2 * capacity;
        }
        arr[size++] = val;
    }

    void remove(int index) {
        if (index < 0 || index >= size) {
            throw ArrayIndexOutOfBoundsException();
        }
        for (int i = index; i < size - 1; i++) {
            arr[i] = arr[i + 1];
        }
        size -= 1;
    }

    int getSize() {
        return size;
    }

    void printArray() {
        for (int i = 0; i < size; i++) {
            cout << arr[i] << ",";
        }
        cout << endl;
    }

};

class MaxHeap {
public:

    DynArr < int > A;

    int getParent(int i) {
        return (i - 1) / 2;
    }

    int getLeft(int i) {
        return (2 * i + 1);
    }

    int getRight(int i) {
        return (2 * i + 2);
    }

    void sift_up(int i) {

        if (i && A[getParent(i)] < A[i]) {
            swap(A[i], A[getParent(i)]);
            sift_up(getParent(i));
        }
    }

    void sift_down(int i) {
        int left = getLeft(i);
        int right = getRight(i);

        int largest = i;

        if (left < size() && A[left] > A[i]) {
            largest = left;
        }

        if (right < size() && A[right] > A[largest]) {
            largest = right;
        }

        if (largest != i) {
            swap(A[i], A[largest]);
            sift_down(largest);
        }
    }

    unsigned int size() {
        return A.getSize();
    }

    bool empty() {
        return size() == 0;
    }

    void insert(int key) {
        A.pushBack(key);

        int index = size() - 1;
        sift_up(index);
    }

    int extractMax() {
        try {
            if (size() == 0) {
                throw out_of_range(
                    "index is out of range(Heap underflow)");
            }

            int max = getMax();

            A[0] = A[size() - 1];

            A.remove(size() - 1);

            sift_down(0);
            return max;
        }
        catch (const out_of_range& oor) {
            cout << endl << oor.what();
        }
    }

    int getMax() {
        try {

            if (size() == 0) {
                throw out_of_range(
                    "index is out of range(Heap underflow)");
            }

            return A[0];
        }
        catch (const out_of_range& oor) {
            cout << endl << oor.what();
        }
    }

    void remove(int i) {
        A[i] = INT_MAX;
        sift_up(i);
        extractMax();
    }

};

class qNode {
public:
    string tconst;
    string titleType;
    string primaryTitle;
    string originalTitle;
    string isAdult;
    string startYear;
    string endYear;
    string runtimeMinutes;
    string genre;
    float rate;
    qNode* next;

    qNode(string tconst = "\0", string titleType = "\0", string primaryTitle = "\0", string originalTitle = "\0", string isAdult = "\0", string startYear = "\0", string endYear = "\0", string runtimeMinutes = "\0", string genre = "\0", float rate = 0.0) {
        this->endYear = endYear;
        this->genre = genre;
        this->tconst = tconst;
        this->isAdult = isAdult;
        this->originalTitle = originalTitle;
        this->primaryTitle = primaryTitle;
        this->runtimeMinutes = runtimeMinutes;
        this->startYear = startYear;
        this->titleType = titleType;
        this->rate = rate;
        next = NULL;
    }

};
class QueueLL {
    qNode* front, * rear;

public:
    QueueLL() {
        front = rear = NULL;
    }

    bool isEmpty() {
        return (rear == NULL);
    }

    void enqueue(string tconst, string titleType, string primaryTitle, string originalTitle, string isAdult, string startYear, string endYear, string runtimeMinutes, string genre, float rate) {
        qNode* new_node = new qNode(tconst, titleType, primaryTitle, originalTitle, isAdult, startYear, endYear, runtimeMinutes, genre, rate);

        if (isEmpty()) {
            front = rear = new_node;
        }
        else {
            if (front->rate < rate) {
                new_node->next = front;
                front = new_node;
            }
            else {
                qNode* temp = front;
                while (temp->next != NULL && temp->next->rate >= rate) {
                    temp = temp->next;
                }
                new_node->next = temp->next;
                temp->next = new_node;
            }
        }
    }

    void peekFiveElements() {
        if (isEmpty()) {
            return;
        }
        qNode* temp = front;
        int count = 0;
        cout << "ORIGINAL TITLE" << "\t\t" << "START YEAR" << "\t\t" << "RUN TIME MINUTES" << "\t\t" << "GENRE" << "\t\t" << "RATINGS" << "\t\t";
        while (temp != NULL and count < 5) {
            count++;
            cout << temp->originalTitle << "\t\t" << temp->startYear << "\t\t" << temp->runtimeMinutes << "\t\t" << temp->genre << "\t\t" << temp->rate << endl;
            temp = temp->next;
        }
    }

};

class LinkedListNode {
public:

    string tconst;
    string titleType;
    string primaryTitle;
    string originalTitle;
    string isAdult;
    string startYear;
    string endYear;
    string runtimeMinutes;
    string genre;
    float rate;
    LinkedListNode* next;
    LinkedListNode* prev;

    LinkedListNode(string tconst = "\0", string titleType = "\0", string primaryTitle = "\0", string originalTitle = "\0", string isAdult = "\0", string startYear = "\0", string endYear = "\0", string runtimeMinutes = "\0", string genre = "\0", float rate = 0.0) {
        this->endYear = endYear;
        this->genre = genre;
        this->tconst = tconst;
        this->isAdult = isAdult;
        this->originalTitle = originalTitle;
        this->primaryTitle = primaryTitle;
        this->runtimeMinutes = runtimeMinutes;
        this->startYear = startYear;
        this->titleType = titleType;
        this->rate = rate;
        next = NULL;
        prev = NULL;
    }
};

class DoublyLinkedList {
    LinkedListNode* sorted;
    LinkedListNode* tail;
    int size;

public:
    LinkedListNode* head;

    DoublyLinkedList() {
        head = NULL;
        tail = NULL;
        size = 0;
        sorted = NULL;
    }

    void push_back(string tconst, string titleType, string primaryTitle, string originalTitle, string isAdult, string startYear, string endYear, string runtimeMinutes, string genre, float rate) {
        LinkedListNode* new_node = new LinkedListNode(tconst, titleType, primaryTitle, originalTitle, isAdult, startYear, endYear, runtimeMinutes, genre, rate);

        if (head == NULL) {
            head = new_node;
            tail = new_node;
            return;
        }

        tail->next = new_node;
        new_node->prev = tail;
        tail = new_node;

        size++;
    }

    void printList() {
        LinkedListNode* temp = head;

        while (temp != NULL) {
            cout << temp->primaryTitle << " " << temp->genre << " " << temp->rate << endl;
            temp = temp->next;
        }

        cout << "\n";
    }

    void sort_movies() {

        LinkedListNode* current = head;
        sorted = NULL;

        while (current != NULL) {
            LinkedListNode* nextt = current->next;
            sortedInsert(current);
            current = nextt;
        }

        head = sorted;
        LinkedListNode* temp = head;
        int count = 1;

        while (temp != NULL && count <= 5) {
            count++;
            cout << temp->genre << " " << temp->rate << endl;
            temp = temp->next;
        }

        cout << "\n";

    }

    void sortedInsert(LinkedListNode* newnode) {
        if (sorted == NULL || sorted->rate >= newnode->rate) {
            newnode->next = sorted;
            sorted = newnode;
        }
        else {
            LinkedListNode* current = sorted;

            while (current->next != NULL && current->next->rate >= newnode->rate) {
                current = current->next;
            }

            newnode->next = current->next;
            current->next = newnode;
        }
    }

    void insertionSort(LinkedListNode* start) //mark2
    {
        int swapped, i;
        LinkedListNode* ptr1;
        LinkedListNode* lptr = NULL;
        if (start == NULL)
            return;

        do {
            swapped = 0;
            ptr1 = start;

            while (ptr1->next != lptr) {
                if (ptr1->rate < ptr1->next->rate) {
                    swap(ptr1->rate, ptr1->next->rate);
                    swapped = 1;
                }
                ptr1 = ptr1->next;
            }
            lptr = ptr1;
            //start = ptr1;
        } while (swapped);

    }
    void printingTheGenresFunc1(LinkedListNode* temp) {
        int count = 1;
        cout << "ORIGINAL TITLE" << "\t" << "RATINGS" << endl;
        while (temp != NULL && count <= 5) {
            count++;
            cout << temp->originalTitle << "\t" << temp->rate << endl;
            temp = temp->next;
        }

        cout << "\n";
    }

};

class Node {
public:
    string tconst;
    string titleType;
    string primaryTitle;
    string originalTitle;
    string isAdult;
    string startYear;
    string endYear;
    string runtimeMinutes;
    string genre;
    Node* left;
    Node* right;

    Node(string tconst = "\0", string titleType = "\0", string primaryTitle = "\0", string originalTitle = "\0", string isAdult = "\0", string startYear = "\0", string endYear = "\0", string runtimeMinutes = "\0", string genre = "\0") {
        left = NULL;
        right = NULL;
        this->endYear = endYear;
        this->genre = genre;
        this->tconst = tconst;
        this->isAdult = isAdult;
        this->originalTitle = originalTitle;
        this->primaryTitle = primaryTitle;
        this->runtimeMinutes = runtimeMinutes;
        this->startYear = startYear;
        this->titleType = titleType;
    }
};

class Tree {
public:

    map < string, float > file2;
    map < string, string > final;
    map < int, string > file21;
    map < string, int > file211;
    Node* root;
    Tree* movies[26];

    Tree() {
        root = NULL;
        for (int i = 0; i < 26; i++) {
            movies[i] = NULL;
        }
    }

    void intializingTree() {
        for (int i = 0; i < 26; i++) {
            movies[i] = new(nothrow) Tree();
        }
    }

    void defaultGenrePrinting() {
        QueueLL* q1;
        int ascii;
        vector < string > vect{
          "Romance",
          "Comedy",
          "Crime",
          "Documentary",
          "Action"
        };
        q1 = new(nothrow) QueueLL[vect.size()];
        cout << endl << "FOLLOWING ARE THE RECOMMENDATIONS FOR HIGH RATED MOVIES FOR 5 GENRES INCLUDING: " << endl << endl;
        for (int i = 0; i < vect.size(); i++) {
            ascii = vect[i][0] - 65;
            if (ascii >= 0 and ascii <= 25) {
                Node* r = movies[ascii]->root;
                queue < Node* > qu;
                if (r != NULL) {
                    qu.push(r);
                    while (!qu.empty()) {
                        r = qu.front();

                        if (r->genre == vect[i]) {
                            q1[i].enqueue(r->tconst, r->titleType, r->primaryTitle, r->originalTitle, r->isAdult, r->startYear, r->endYear, r->runtimeMinutes, r->genre, file2[r->tconst]);
                        }
                        qu.pop();
                        if (r->left != NULL) {
                            qu.push(r->left);
                        }
                        if (r->right != NULL) {
                            qu.push(r->right);
                        }

                    }
                    cout << vect[i] << endl;
                    q1[i].peekFiveElements();

                    cout << "\n\n\n";
                }
            }
        }
    }

    void inOrderTraversal(Node* r, string geni, string titl) {
        queue < Node* > qu;

        if (r != NULL) {
            cout << "The primary titles of that show can be: " << endl;

            qu.push(r);

            while (!qu.empty()) {
                r = qu.front();
                if (r->genre == geni) {
                    if (r->titleType == titl) {
                        cout << r->primaryTitle << endl;
                    }
                }

                qu.pop();

                if (r->left != NULL) {
                    qu.push(r->left);
                }
                if (r->right != NULL) {
                    qu.push(r->right);
                }
            }
        }
    }
    void inOrderTraversal1(Node* r, string geni, string yy) {
        queue < Node* > qu;

        if (r != NULL) {
            qu.push(r);

            while (!qu.empty()) {
                r = qu.front();
                if (r->genre == geni) {
                    if (r->startYear == yy) {
                        cout << r->primaryTitle << endl;
                    }
                }

                qu.pop();

                if (r->left != NULL) {
                    qu.push(r->left);
                }
                if (r->right != NULL) {
                    qu.push(r->right);
                }
            }
        }
    }

    void movieAccToCustomer() {
        string gen, tt, y;
        int choice, choice1;
        cout << "Are you SATISFIED with our RECOMMENDED SYSTEM or you want to search more for your movie? \nEnter 1 to exit and 0 to continue: ";
        cin >> choice1;
        if (choice1 == 0) {
            cout << "\nHAVE A MOVIE, BUT ONLY REMEMBER ITS:\n\t1->Genre and Title Type\n\t2->Genre and Year\n\t0->Go to main: ";
            cin >> choice;
            cout << "\nThe genere was: " << endl << "PLEASE SELECT FROM: " << endl << "1- Romance" << endl << "2- News" << endl << "3- Sport" << endl << "4- Horror" << endl << "5- Drama" << endl << "6- Fantasy" << endl << "7- Comedy" << endl << "8- Music" << endl << "9- Crime" << endl << "10- Western" << endl << "11- War" << endl << "12- Biography" << endl << "13- History" << endl << "14- Mystery" << endl << "15- Adventure" << endl << "16- Family" << endl << "17- Sci-Fi" << endl << "18- Game-Show" << endl << "19- Talk-Show" << endl << "20- Thriller" << endl << "21- Adult" << endl << "22- Musical " << endl << "23- Action " << endl << "24 - Animation " << endl << "25- Documentary " << endl << "PLEASE ENTER IN SAME CASE AS GIVEN: " << endl;
            fflush(stdin);
            cin >> gen;
            fflush(stdin);

            if (gen == "Animation"
                or gen == "Documentary"
                or gen == "Action"
                or gen == "Romance"
                or gen == "News"
                or gen == "Sport"
                or gen == "Horror"
                or gen == "Drama"
                or gen == "Fantasy"
                or gen == "Comedy"
                or gen == "Music"
                or gen == "Crime"
                or gen == "Western"
                or gen == "War"
                or gen == "Biography"
                or gen == "History"
                or gen == "Mystery"
                or gen == "Adventure"
                or gen == "Family"
                or gen == "Sci-Fi"
                or gen == "Game-Show"
                or gen == "Talk-Show"
                or gen == "Thriller"
                or gen == "Adult"
                or gen == "Musical") {
                int ascii = gen[0] - 65;
                if (ascii >= 0 and ascii <= 25) {
                    switch (choice) {
                    case 1:
                        cout << "The Title Type was: ";
                        fflush(stdin);
                        cin >> tt;
                        cout << endl << "Movies with " << gen << " and " << tt << " are :\n\n";
                        inOrderTraversal(movies[ascii]->root, gen, tt);
                        break;
                    case 2:
                        cout << "The Year was:";
                        fflush(stdin);
                        cin >> y;
                        cout << endl << "Movies with " << gen << " and " << y << " are :\n\n";
                        inOrderTraversal1(movies[ascii]->root, gen, y);

                        break;
                    default:
                        break;
                    }
                }
            }
            else {
                cout << endl << "NO SUCH GENRE EXIST, SORRYYYYYY!!!!!!!!!!!" << endl;
                return;
            }
        }
        else if (choice1 == 1) {
            return;
        }
    }

    void insert(string tconst, string titleType, string primaryTitle, string originalTitle, string isAdult, string startYear, string endYear, string runtimeMinutes, string genre) {
        Node* newNode = new(nothrow) Node(tconst, titleType, primaryTitle, originalTitle, isAdult, startYear, endYear, runtimeMinutes, genre);

        if (root == NULL) {
            root = newNode;
            return;
        }
        else {
            Node* Current = root;
            Node* Parent = NULL;
            Node* temp = root;

            while (1) {
                Parent = Current;

                if (genre < Parent->genre) {
                    Current = Current->left;

                    if (Current == NULL) {
                        Parent->left = newNode;
                        return;
                    }
                }
                else {
                    Current = Current->right;

                    if (Current == NULL) {
                        Parent->right = newNode;
                        return;
                    }
                }
            }
        }
    }

    void filingData() //bari wali
    {
        vector < string > temp;
        string line, word;
        long long int count = 0;
        fstream file("Text.tsv", ios::in);

        if (file.is_open()) {
            while (getline(file, line)) {
                count++;

                temp.clear();

                stringstream str(line);
                while (getline(str, word, '\t')) {
                    temp.push_back(word);
                }
                stringstream ss(temp[8]);

                while (ss.good()) {
                    string substr;
                    getline(ss, substr, ',');
                    int ascii = substr[0] - 65;
                    if (ascii >= 0 and ascii <= 25) {
                        final.insert({
                          temp[0],
                          temp[1]
                            });
                        movies[ascii]->insert(temp[0], temp[1], temp[2], temp[3], temp[4], temp[5], temp[6], temp[7], substr);
                    }
                }

                if (count == 100000) {
                    break;
                }
            }

        }
        file.close();
    }

    void filingData1() {
        string word, line;
        string word1, word2;

        fstream file("data111.tsv", ios::in);

        if (file.is_open()) {

            while (getline(file, line)) {
                word = "\0";
                word1 = word2 = "\0";
                stringstream str(line);

                getline(str, word, '\t');
                getline(str, word1, '\t');
                getline(str, word2, '\t');
                file2.insert({
                  word,
                  stof(word1)
                    });
                file211.insert({
                  word,
                  stoi(word2)
                    });
                file21.insert({
                  stoi(word2),
                  word
                    });
            }
        }
    }
    void maker_recommendation() {
        int num;
        cout << endl << "HELLO HANDSOME PRODUCERRRRRR!!!!!!!" << endl;
        cout << endl << "Please tell us that how many genres will be involved in your movie? " << endl;
        cin >> num;

        DoublyLinkedList* l1;
        string* gen;
        l1 = new(nothrow) DoublyLinkedList[num];
        gen = new(nothrow) string[num];
        cout << endl << "LETS BEGINNNNN!!!!!" << endl << "Enter the genre on which you are interested to work on? " << endl << "PLEASE SELECT FROM: " << endl << "1- Romance" << endl << "2- News" << endl << "3- Sport" << endl << "4- Horror" << endl << "5- Drama" << endl << "6- Fantasy" << endl << "7- Comedy" << endl << "8- Music" << endl << "9- Crime" << endl << "10- Western" << endl << "11- War" << endl << "12- Biography" << endl << "13- History" << endl << "14- Mystery" << endl << "15- Adventure" << endl << "16- Family" << endl << "17- Sci-Fi" << endl << "18- Game-Show" << endl << "19- Talk-Show" << endl << "20- Thriller" << endl << "21- Adult" << endl << "22- Musical " << endl << "23- Action " << endl << "24 - Animation " << endl << "25- Documentary " << endl << "PLEASE ENTER IN SAME CASE AS GIVEN: " << endl << endl;
        for (int i = 0; i < num; i++) {
            cout << "Enter your genre " << i + 1 << ": ";

            fflush(stdin);
            cin >> gen[i];
            if (gen[i] == "Animation"
                or gen[i] == "Documentary"
                or gen[i] == "Action"
                or gen[i] == "Romance"
                or gen[i] == "News"
                or gen[i] == "Sport"
                or gen[i] == "Horror"
                or gen[i] == "Drama"
                or gen[i] == "Fantasy"
                or gen[i] == "Comedy"
                or gen[i] == "Music"
                or gen[i] == "Crime"
                or gen[i] == "Western"
                or gen[i] == "War"
                or gen[i] == "Biography"
                or gen[i] == "History"
                or gen[i] == "Mystery"
                or gen[i] == "Adventure"
                or gen[i] == "Family"
                or gen[i] == "Sci-Fi"
                or gen[i] == "Game-Show"
                or gen[i] == "Talk-Show"
                or gen[i] == "Thriller"
                or gen[i] == "Adult"
                or gen[i] == "Musical") {
                int ascii = gen[i][0];
                ascii = ascii - 65;

                if (ascii >= 0 and ascii <= 25) {
                    Node* r = movies[ascii]->root;

                    queue < Node* > qu;

                    if (r != NULL) {
                        qu.push(r);

                        while (!qu.empty()) {
                            r = qu.front();
                            if (r->genre == gen[i]) {
                                l1[i].push_back(r->tconst, r->titleType, r->primaryTitle, r->originalTitle, r->isAdult, r->startYear, r->endYear, r->runtimeMinutes, r->genre, file2[r->tconst]);
                            }

                            qu.pop();

                            if (r->left != NULL) {
                                qu.push(r->left);
                            }
                            if (r->right != NULL) {
                                qu.push(r->right);
                            }
                        }

                        l1[i].insertionSort(l1[i].head);
                    }
                }
            }
            else {
                cout << endl << "NO SUCH GENRE EXIST, SORRYYYYYY!!!!!!!!!!!" << endl;
                return;
            }
        }
        float bestTime = 0.0;

        cout << endl;
      
            for (int i = 0; i < num; i++)
            {
                LinkedListNode* temp = l1[i].head;
                if (stof(temp->runtimeMinutes) != 0) {
                    cout << "The recommended runtime hours for genre " << i << " based on ratings is: " << temp->runtimeMinutes << endl;
                    bestTime += stof(temp->runtimeMinutes);
                }
                else {
                    cout << "The recommended runtime hours for genre " << i << " based on ratings is: " << 3.0 << endl;
                    bestTime += 3.0;
                }
            }

            bestTime = bestTime / num;
            cout << "\nTherefore, the IDEAL DURATION of your movie will be: " << bestTime << endl << "ENJOYYYYYY!!!!!!!" << endl;
        }

    void user_recommendation() {
        string gen;
        //system("CLS");

        cout << endl << "OK SO MOVIEE BOYYYYY, OH BOYYYY!!!!!!!!!!!" << endl << "Enter your genre, MANNNNNNN" << endl << "Enter the genre on which you are interested to work on? " << endl << "PLEASE SELECT FROM: " << endl << "1- Romance" << endl << "2- News" << endl << "3- Sport" << endl << "4- Horror" << endl << "5- Drama" << endl << "6- Fantasy" << endl << "7- Comedy" << endl << "8- Music" << endl << "9- Crime" << endl << "10- Western" << endl << "11- War" << endl << "12- Biography" << endl << "13- History" << endl << "14- Mystery" << endl << "15- Adventure" << endl << "16- Family" << endl << "17- Sci-Fi" << endl << "18- Game-Show" << endl << "19- Talk-Show" << endl << "20- Thriller" << endl << "21- Adult" << endl << "22- Musical " << endl << "23- Action " << endl << "24 - Animation " << endl << "25- Documentary " << endl << "PLEASE ENTER IN SAME CASE AS GIVEN: ";
        fflush(stdin);
        cin >> gen;

        if (gen == "Animation"
            or gen == "Documentary"
            or gen == "Action"
            or gen == "Romance"
            or gen == "News"
            or gen == "Sport"
            or gen == "Horror"
            or gen == "Drama"
            or gen == "Fantasy"
            or gen == "Comedy"
            or gen == "Music"
            or gen == "Crime"
            or gen == "Western"
            or gen == "War"
            or gen == "Biography"
            or gen == "History"
            or gen == "Mystery"
            or gen == "Adventure"
            or gen == "Family"
            or gen == "Sci-Fi"
            or gen == "Game-Show"
            or gen == "Talk-Show"
            or gen == "Thriller"
            or gen == "Adult"
            or gen == "Musical") {
            int ascii = gen[0];
            ascii = ascii - 65;

            if (ascii >= 0 and ascii <= 25) {
                Node* mainn = movies[ascii]->root;

                if (mainn == NULL) {
                    //system("CLS");
                    cout << endl << endl << "Unable to find any movie matching genre of " << gen << ":( :( :(" << "SORRY MANNN" << endl;
                    return;
                }

                rec_list(mainn, gen);
            }
        }
        else {
            cout << endl << "NO SUCH GENRE EXIST, SORRYYYYYY!!!!!!!!!!!" << endl;

            return;
        }

    }

    void rec_list(Node* r, string gen) {
        DoublyLinkedList DLL;
        queue < Node* > qu;

        if (r != NULL) {
            qu.push(r);

            while (!qu.empty()) {
                r = qu.front();
                if (r->genre == gen) {
                    DLL.push_back(r->tconst, r->titleType, r->primaryTitle, r->originalTitle, r->isAdult, r->startYear, r->endYear, r->runtimeMinutes, r->genre, file2[r->tconst]);
                }

                qu.pop();

                if (r->left != NULL) {
                    qu.push(r->left);
                }
                if (r->right != NULL) {
                    qu.push(r->right);
                }
            }

            cout << endl << "WOOHAAAAAA!!!" << endl << "YOU CAN WATCH FOLLOWING MOVIES" << endl << "THESE ARE THE TOP RATED MOVIES " << endl << "WE HIGHLY RECOMMEND YOU" << endl << endl;

            DLL.insertionSort(DLL.head);
            DLL.printingTheGenresFunc1(DLL.head);
        }
    }

    void maker_recommendation2() {

        string genree;
        cout << endl << "WELCOME TO THE INDUSTRY!!!!!!!!!!!!!" << endl << "Enter the genre on which you are interested to work on? " << endl << "PLEASE SELECT FROM: " << endl << "1- Romance" << endl << "2- News" << endl << "3- Sport" << endl << "4- Horror" << endl << "5- Drama" << endl << "6- Fantasy" << endl << "7- Comedy" << endl << "8- Music" << endl << "9- Crime" << endl << "10- Western" << endl << "11- War" << endl << "12- Biography" << endl << "13- History" << endl << "14- Mystery" << endl << "15- Adventure" << endl << "16- Family" << endl << "17- Sci-Fi" << endl << "18- Game-Show" << endl << "19- Talk-Show" << endl << "20- Thriller" << endl << "21- Adult" << endl << "22- Musical " << endl << "23- Action " << endl << "24- Animation " << endl << "25- Documentary " << endl << "PLEASE ENTER IN SAME CASE AS GIVEN: ";
    cont:
        cin >> genree;

        if (genree == "Animation"
            or genree == "Documentary"
            or genree == "Action"
            or genree == "Romance"
            or genree == "News"
            or genree == "Sport"
            or genree == "Horror"
            or genree == "Drama"
            or genree == "Fantasy"
            or genree == "Comedy"
            or genree == "Music"
            or genree == "Crime"
            or genree == "Western"
            or genree == "War"
            or genree == "Biography"
            or genree == "History"
            or genree == "Mystery"
            or genree == "Adventure"
            or genree == "Family"
            or genree == "Sci-Fi"
            or genree == "Game-Show"
            or genree == "Talk-Show"
            or genree == "Thriller"
            or genree == "Adult"
            or genree == "Musical") {
            int ascii = genree[0];
            ascii = ascii - 65;

            if (ascii >= 0 and ascii <= 25) {
                Node* mainn = movies[ascii]->root;

                if (mainn == NULL) {
                    //system("CLS");
                    cout << endl << endl << "Unable to find any movie matching genre of " << genree << ":( :( :(" << "SORRY MANNN" << endl;
                    return;
                }

                rec_list_maker2(mainn, genree);
            }
        }
        else {
            cout << endl << "NO SUCH GENRE EXIST, SORRYYYYYY!!!!!!!!!!!" << endl;
            return;
        }

    }

    void rec_list_maker2(Node* r, string genree) {
        MaxHeap mh;
        queue < Node* > qu;

        if (r != NULL) {
            qu.push(r);

            while (!qu.empty()) {
                r = qu.front();
                if (r->genre == genree) {
                    mh.insert(file211[r->tconst]);
                }

                qu.pop();

                if (r->left != NULL) {
                    qu.push(r->left);
                }
                if (r->right != NULL) {
                    qu.push(r->right);
                }
            }

        }

        cout << endl << "WOHAAAAAAAAAAAAAA!!!!!!" << endl << "You can avail title types of following movies that had gained more number of voters: " << endl << "SHOW ID		TITLE TYPE" << endl << endl;

        for (int i = 0; i < 5; i++) {
            string id, type;
            int res;
            res = mh.extractMax();
            id = file21[res];
            cout << id << "\t" << final[id] << " " << endl;
        }

    }

};

void gotoxy(int x, int y) { //gotoxy function is used to move the cursor on the x/y axis

    static HANDLE h = NULL;
    if (!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = {
      x,
      y
    };
    SetConsoleCursorPosition(h, c); //here h stands for x-axis while c stands for y axis

}

void Title(void) { //function made for the title page

    int i;
    char p[] = " WELCOME TO OUR CONSOLE BASED MOVIE RECOMMENDATION SYSTEM ";
    gotoxy(20, 10); //20 spaces on x-axis and 10 on y-axis

    for (i = 0; i < 12; i++) {

        Sleep(55); //sleep function is used to delay the timing for the appearance of colon(:)
        cout << ":";
    }

    for (i = 0; i < strlen(p); i++) {

        Sleep(50);
        cout << p[i];
    }

    for (i = 0; i < 12; i++) {

        Sleep(55);
        cout << ":";
    }

    char d[] = {
      "A Project developed by"
    };
    gotoxy(49, 0);

    for (i = 0; i < strlen(d); i++) {

        Sleep(50);
        cout << d[i];
    }

    char S[] = {
      "Ismail Ahmed Ansari 20K-0228"
    }; //use of char to enter every element with a delay
    char I[] = {
      "  Insha Samnani 20K-0247"
    };
    char Y[] = {
      "  Yusra Adam 20K-0207"
    };
    gotoxy(50, 1);

    for (i = 0; i < strlen(S); i++) {

        Sleep(50);
        cout << S[i];
    }

    gotoxy(50, 2);

    for (i = 0; i < strlen(I); i++) {

        Sleep(50);
        cout << I[i]; //printing Insha

    }

    gotoxy(50, 3);

    for (i = 0; i < strlen(Y); i++) {

        Sleep(50);
        cout << Y[i]; //printing yusra
    }

    Sleep(2000);
}

int main() {
    Tree t1;
    t1.intializingTree();
    t1.filingData();
    t1.filingData1();

    system("color f4"); //setting color for console
    cin.get();
    Title(); //calling title function
    //system("CLS");

    int choice;

    cout << " HELLO!!!!!!!!!!!!!!!" << endl << endl;

    do {
        system("CLS");
        cout << endl << "ARE YOU A PRODUCER OR CUSTOMER?" << endl << "1- For PRODUCER" << endl << "2- For CUSTOMER" << endl << "0- To EXIT" << endl;
        cin >> choice;

        if (choice == 0) {
            exit(0);
        }
        else if (choice == 1) {
            int maker_choice;
            do {
                cout << endl << endl << "PLEASE ENTER YOUR CHOICE AS PER THE GIVEN OPTIONS: " << endl << "1- WANT APPROXIMATE TIME DURATION (in Hours) OF YOUR MOVIE BASED ON GENRE?" << endl << "2- WANT SUGGESTION FOR THE TITLE TYPE AS AN INITIAL MOVIE MAKER? " << endl << "0- To EXIT" << endl;
                cin >> maker_choice;

                if (maker_choice == 1) {
                    t1.maker_recommendation();
                }
                else if (maker_choice == 2) {
                    t1.maker_recommendation2();
                }
            } while (maker_choice != 0);

        }
        else if (choice == 2) {
            int user_choice;
            do {
                cout << endl << endl << "PLEASE ENTER YOUR CHOICE AS PER THE GIVEN OPTIONS: " << endl << "1- WANT MOVIES RECOMMENDATION?" << endl << "2- WANT A SEARCH AND RECOMMENDATION ENGINE?" << endl << "0- To EXIT" << endl;
                cin >> user_choice;

                if (user_choice == 1) {
                    t1.user_recommendation();
                }
                else if (user_choice == 2) {
                    t1.defaultGenrePrinting();
                    t1.movieAccToCustomer();
                }
            } while (user_choice != 0);

        }

        cout << endl;

    } while (choice != 0);

    return 0;

}