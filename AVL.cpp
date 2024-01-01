#include <bits/stdc++.h>
using namespace std;

#define RH 1
#define EH 0
#define LH -1

struct node{
    int data;
    node *pLeft;
    node *pRight;
    int balFactor;
    // int height;
};

//make node
node *makeNode(int x);

//insert node x
int insert_node(node *&root, int x);

//delete node x
int delete_node(node *&root, int x);

//print data LNR 
void print_data(node *root);

void print_leaf_node(node *root);

void print_1child_node(node *root);

void print_2children_node(node *root);

// rotate 
void rotateLeft (node *&root);

void rotateRight (node *&root);

//the root is skewed to the left
void balance_left(node *&root);

//the root is skewed to the right
void balance_right(node *&root);

int maxNumInTree(node *root);

void readFile(node *&root, ifstream &inFile);

void menu(node *&root);

int main(){
    node *root = NULL;
    menu(root);
    return 0;
}

node *makeNode(int x){
    node *newNode = new node ();
    newNode->data = x;
    newNode->balFactor = EH;
    newNode->pLeft = NULL;
    newNode->pRight = NULL;
    // newNode->height = 1;
    return newNode;
}

int insert_node(node *&root, int x){
    //return -1 if not successful because of lack of memory
    //return 0 if x is found in avl tree
    //return 1 if root is balanced and father node doesn't change
    //return 2 if root is not balance and change father node
    if (root == NULL){
        root = makeNode(x);
        if (root == NULL)   return -1;
        return 2;
    }
    else if (root->data == x){
        //x is found in avl tree
        return 0;
    }
    else if (x < root->data){
        int res = insert_node(root->pLeft, x);
        //not change father node
        if (res < 2){
            return res;
        }
        switch(root->balFactor){
            case EH: root->balFactor = LH; return 2; //break
            case RH: root->balFactor = EH; return 1; //break
            case LH: balance_left(root); return 1;
        }
    }
    else //x > root->data
    {
        int res = insert_node(root->pRight, x);
        //not change father node
        if (res < 2){
            return res;
        }
        switch (root->balFactor){
            case EH: root->balFactor = RH; return 2; //break;
            case LH: root->balFactor = EH; return 1; //break;
            case RH: balance_right(root); return 1; //break;
        }
    }
}

void print_data(node *root){
    if (root != NULL){
        cout << root->data << " " << root->balFactor << " "  << endl;
        print_data(root->pLeft);
        print_data(root->pRight);
    }
}

void print_leaf_node(node *root){
    if (root != NULL){
        if (root->pLeft == NULL && root->pRight == NULL){
            cout << root->data << " " << root->balFactor << " "  << endl;
            return;
        }
        print_leaf_node(root->pLeft);
        print_leaf_node(root->pRight);
    }
}

void print_1child_node (node *root){
    if (root != NULL){
        if ((root->pLeft != NULL && root->pRight == NULL) || (root->pLeft == NULL && root->pRight != NULL)){
            cout << root->data << " " << root->balFactor << " "  << endl;
        }
        print_1child_node(root->pLeft);
        print_1child_node(root->pRight);
    }
}

void print_2children_node (node *root){
    if (root != NULL){
        if (root->pLeft != NULL && root->pRight != NULL){
            cout << root->data << " " << root->balFactor << " " << endl;
        }
        print_2children_node(root->pLeft);
        print_2children_node(root->pRight);
    }
}

int delete_node(node *&root, int x){
    if (root == NULL){
        return -1;
    }
    else if (x < root->data){
        int res = delete_node(root->pLeft, x);
        if (res < 2){
            return res;
        }
        if (root->balFactor == EH){
            root->balFactor = RH;
            return 2;
        }
        else if (root->balFactor = LH){
            root->balFactor = EH;
        }
        else {
            balance_right(root);
        }
    }
    else if (x > root->data){
        int res = delete_node(root->pRight, x);
        if (res < 2){
            return res;
        }
        if (root->balFactor == EH){
            root->balFactor = LH;
            return 2;
        }
        else if (root->balFactor = RH){
            root->balFactor = EH;
        }
        else {
            balance_left(root);
        }
    }
    else {
        // x is found
        if (root->pLeft == NULL){
            node *tmp = root;
            root = root->pRight;
            delete tmp;
            return 2;
        }
        else if (root->pRight == NULL){
            node *tmp = root;
            root = root->pLeft;
            delete tmp;
            return 2;
        }
        else{
            //tmp is used to delete root

            //find the max num in the left branch
            node *maxNumInLeftBranch = (root->pLeft);
            while(maxNumInLeftBranch->pRight != NULL){
                //change balance factor of father node
                maxNumInLeftBranch = maxNumInLeftBranch->pRight;
            }
            // tmp save data of max num in left branch
            int tmp = maxNumInLeftBranch->data;

            //delete node stand for x and change balfactor in father nodes's x
            delete_node(root, tmp);

            root->data = tmp;
            
            return 2;
        }
    }
}

int maxNumInTree(node *root){
    if (root->pRight == NULL)   return root->data;
    else return maxNumInTree(root->pRight);
}

void readFile (node *&root, ifstream &inFile){
    int n;
    inFile >> n;
    insert_node(root, n);
    while (!inFile.eof()){
        char comma;
        inFile >> comma;
        int tmp;
        inFile >> tmp;
        if (inFile) insert_node(root, tmp);
        else break;
    }
}

void rotateLeft(node *&root){
    node *T1 = root->pRight;
    root->pRight = T1->pLeft;
    T1->pLeft = root; 
    root = T1;
}

void rotateRight(node *&root){
    node *T1 = root->pLeft;
    root->pLeft = T1->pRight;
    T1->pRight = root;
    root = T1;
}

void balance_left(node *&root){
    //left branch is skewed to the left
    if (root->pLeft->balFactor == LH){
        rotateRight(root);
        //change balance factor
        root->balFactor = EH;
        root->pRight->balFactor = EH;
    }
    //left branch is skewed to the right
    else if (root->pLeft->balFactor == RH){
        node *T1 = root->pLeft;
        node *T2 = T1->pRight;
        if (T2->balFactor == LH){
            T1->balFactor = EH;
            root->balFactor = RH;
        }
        else if (T2->balFactor == RH){
            T1->balFactor = LH;
            root->balFactor = EH;
        }
        else {
            T1->balFactor = EH;
            root->balFactor = EH;
        }
        rotateLeft(root->pLeft);
        rotateRight(root);
        root->balFactor = EH;
    }
}

void balance_right(node *&root){
    //right branch is skewed to the right
    if (root->pRight->balFactor == RH){
        rotateLeft(root);
        //change balance factor
        root->balFactor = EH;
        root->pLeft->balFactor = EH;
    }
    //right branch is skewed to the left
    else if (root->pRight->balFactor == LH){
        node *T1 = root->pRight;
        node *T2 = T1->pLeft;
        if (T2->balFactor == LH){
            T1->balFactor = RH;
            root->balFactor = EH;
        }
        else if (T2->balFactor = RH){
            T1->balFactor = EH;
            root->balFactor = LH;
        }
        else {
            T1->balFactor = EH;
            root->balFactor = EH;
        }
        rotateRight(root->pRight);
        rotateLeft(root);
        root->balFactor = EH;
    }
}

void menu(node *&root){
    while (1){
        cout << "-------------MENU--------------\n";
        cout << "1. insert node\n";
        cout << "2. print leaf node\n";
        cout << "3. print 1 child node\n";
        cout << "4. print 2 children node\n";
        cout << "5. print all data in tree NLR\n";
        cout << "6. max num in tree\n";
        cout << "7. delete node\n";
        cout << "0. end\n";;
        cout << "nhap lua chon: ";
        int choice; cin >> choice;
        if (choice == 1) {
            cout << "nhap x: ";
            int x; cin >> x;
            insert_node(root, x);
        }
        else if (choice == 2){
            print_leaf_node(root);
        }
        else if (choice == 3){
            print_1child_node(root);
        }
        else if(choice == 4){
            print_2children_node(root);
        }
        else if (choice == 5){
            print_data(root);
        }
        else if (choice == 6){
            cout << maxNumInTree(root);
        }
        else if (choice == 7){
            cout << "nhap x can xoa: ";
            int x; cin >> x;
            delete_node(root, x);
        }
        else if (choice == 0){
            break;
        }
    }
    
}