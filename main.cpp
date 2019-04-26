//Description: Takes a text file supplied by the user
//             and turns it into a word index, implemented
//             through the use of a BST

#include <iostream>
#include <fstream>
#include "bst.h"
#include "TT.h"
using namespace std;

int main(int argc, char* argv[]) {
    char choice1;
    int choice2;
    if (argc != 2) {
        cout << "Incorrect input. Correct format: ./<exectuable.out> <inputtext.txt>\n";
        return 1;
    }

    ifstream input(argv[1]);
    BST myTree;
    TT ttTree;
    std::cout << "options: (a) BST, (b) 2-3 Tree, (c) Compare BST and 2-3 Tree" << std::endl;
    while(1) {

        choice1 = NULL;

        cin >> choice1;

        //Print index
        if (choice1 == 'a') {
            myTree.buildTree(input);
            while (1) {
                choice2 = 0;
                cout << "Options: (1) display index, (2) search, (3) save index, (4) quit\n";
                cin >> choice2;

                //Print index
                if (choice2 == 1)
                    myTree.printTree(cout);

                    //Search index for a word
                else if (choice2 == 2)
                    myTree.contains();

                    //Save index
                else if (choice2 == 3) {
                    string outputFile;
                    cout << "Enter a filename to save your index to (Suggested: <filename>.txt) : ";
                    cin >> outputFile;
                    ofstream output(outputFile.c_str());
                    myTree.printTree(output);
                    output.close();
                    cout << "Saved\n";
                }

                    //Quit
                else
                    break;
            }
        }

            //Search index for a word
        else if (choice1 == 'b')
        {
            ttTree.buildTree(input);
        while (1) {
            choice2 = 0;
            cout << "Options: (1) display index, (2) search, (3) save index, (4) quit\n";
            cin >> choice2;

            //Print index
            if (choice2 == 1)
                ttTree.printTree(cout);

                //Search index for a word
            else if (choice2 == 2)
                ttTree.contains();

                //Save index
            else if (choice2 == 3) {
                string outputFile;
                cout << "Enter a filename to save your index to (Suggested: <filename>.txt) : ";
                cin >> outputFile;
                ofstream output(outputFile.c_str());
                ttTree.printTree(output);
                output.close();
                cout << "Saved\n";
            }

                //Quit
            else
                break;
        }
    }
                //Save index
            else if(choice1 == 'c'){
                ttTree.buildTreeNoOut(input);
                myTree.buildTreeNoOut(input);
                
                auto words = ttTree.getWords();
                
                auto startTime = clock();
                
                for (auto word : words)
                {
                    ttTree.find(word);
                }
                
                auto finishTime = clock();
                auto totalTime = (double) (finishTime - startTime)/CLOCKS_PER_SEC;
                
                std::cout << "final time TT is : " << totalTime << std::endl;
                
                startTime = clock();
                
                for (auto word : words)
                {
                    ttTree.find(word);
                }
                
                finishTime = clock();
                totalTime = (double) (finishTime - startTime)/CLOCKS_PER_SEC;
                
                std::cout << "final time BST is : " << totalTime << std::endl;

            }
                //Quit
            else
                break;
        }

    if(input.is_open()){


        input.close();


    }
    else{
        cout << "Invalid File Name. Restart Program.\n";
        return 2;
    }
    return 0;
}
