#include <iostream>
#include <mcpp/mcpp.h>

#include "menuUtils.h"
#include "Maze.h"
#include "Agent.h"
#include "RecursiveBackTracking.h"
#include "ValidMaze.h"
#include "EscapeExtension.h"

#define NORMAL_MODE 0
#define TESTING_MODE 1

enum States{
    ST_Main,
    ST_GetMaze,
    ST_BuildMaze,
    ST_SolveMaze,
    ST_Creators,
    ST_Exit
};

int main(void){
    mcpp::MinecraftConnection mc; 
    mc.doCommand("time set day"); 

    //--------DATA-----------------------
    bool mode = NORMAL_MODE;
    unsigned static int x = 0;
    unsigned static int y = 0;
    //mazeArr array is the structure for the pattern
    char** mazeArr = nullptr; 
    char** temp1 = nullptr;
    char** temp2 = nullptr;
    char** temp3 = nullptr;
    //it is to save player's basepoint 
    mcpp::Coordinate PlayerPos = mc.getPlayerPosition();
    int baseX = PlayerPos.x;
    int baseY = PlayerPos.y;
    int baseZ = PlayerPos.z;
    //basepoint coordinate
    mcpp::Coordinate basePoint(baseX, baseY, baseZ);
    //new Maze object
    Maze* mcMaze = new Maze(basePoint, x, y, mode); 
    //new Agent object
    Agent* playerSolve = new Agent(mode, basePoint, x, y);
    Recursive* recursive = new Recursive();
    Valid* valid = new Valid();
    EscapeExtension* playerExtension = new EscapeExtension(basePoint);

    States curState = ST_Main;

    std::string mainMenuSelection;
    std::string generateMazeOption;
    std::string solveMazeOption;
    




    //------------BEGIN MENU LOGIC----------
    //State machine for menu
    printStartText();

    while (curState != ST_Exit){



        //--------MAIN MENU-----------------
        if(curState == ST_Main){
            printMainMenu();
            std::cin >> mainMenuSelection;
            //generate maze
            if(mainMenuSelection == "1"){ 
                curState = ST_GetMaze; 
            } 
            //build maze
            else if(mainMenuSelection == "2"){ 
                curState = ST_BuildMaze; 
            } 
            //solve maze
            else if(mainMenuSelection == "3"){ 
                curState = ST_SolveMaze; 
            } 
            //show team info
            else if(mainMenuSelection == "4"){ 
                curState = ST_Creators;
            } 
            else if(mainMenuSelection == "5") {
                //clean up and clear arraylist
                mcMaze->cleanUp(); 

                delete mcMaze;
                delete playerSolve;
                delete valid;
                delete recursive;
                delete playerExtension;

                mazeArr=mcMaze->deleteMaze(mazeArr,x);
                temp1 = mcMaze->deleteMaze(temp1,x);
                temp2 = mcMaze->deleteMaze(temp2,x);
                temp3 = mcMaze->deleteMaze(temp3,x);
                printExitMassage();
                curState = ST_Exit; 
            } 
        }




        //--------(1) GENERATE MAZE-----------------
        else if(curState == ST_GetMaze){
            printGenerateMazeMenu();
            std::cin >> generateMazeOption;

            //-------1: Read maze from terminal-------
            if(generateMazeOption == "1"){
                std::cout<<"In Minecraft, please navigate to " <<
                "where you need the maze\n" <<"to be built in Minecraft "
                << "and type - done:" << std::endl;

                std::string accept;
                std::cin >> accept;

                if(accept == "done"){
                    //RESETTING EVERYTHING
                    PlayerPos = mc.getPlayerPosition();
                    baseX = PlayerPos.x;
                    baseY = PlayerPos.y;
                    baseZ = PlayerPos.z;
                    basePoint = mcpp::Coordinate(baseX, baseY, baseZ);

                    //clear the maze
                    if(mazeArr != nullptr){
                        for (unsigned int i = 0; i < x; i++) {
                            delete[] mazeArr[i];
                        }
                    }
                
                    delete[] mazeArr;
                    mazeArr = nullptr;
                    
                    //get maze dimensions
                    std::cout<<"Enter the length and width of the maze";
                    std::cout << "(odd numbers only, minimum 3,"; 
                    std::cout << "and maximum 99).";
                    std::cout<<std::endl;

                    std::cout<<"Enter the length (x length)";
                    std::cout <<std::endl;
                    std::cin>>x;

                    if (std::cin.fail()){
                        curState = ST_Exit;
                    }

                    if ((x % 2 == 0) || (x < 3) || (x > 99)){
                        std::cout << "Invalid input.";
                        std::cout << std::endl;
                        curState = ST_GetMaze;
                        std::cin>>x;

                        if (std::cin.fail()){
                            curState = ST_Exit;
                        }
                    }

                    std::cout<<"Enter the width (z length)";
                    std::cout <<std::endl;
                    std::cin>>y;

                    if (std::cin.fail()){
                        curState = ST_Exit;
                    }

                    if ((y % 2 == 0) || (y < 3) || (y > 99)){
                        std::cout << "Invalid input.";
                        std::cout << std::endl;
                        curState = ST_GetMaze;
                        std::cin>>y;

                        if (std::cin.fail()){
                            curState = ST_Exit;
                        }
                    }

                    //initialise maze
                    mcMaze->resetMaze(basePoint, x, y);

                    //array for maze map
                    mazeArr = new char*[x];
                        for (unsigned int i = 0; i < x; i++) {
                        mazeArr[i] = new char[y];
                    }

                    temp3 = new char*[x];
                        for (unsigned int i = 0; i < x; i++) {
                        temp3[i] = new char[y];
                    }

                    temp1 = new char*[x];
                        for (unsigned int i = 0; i < x; i++) {
                        temp1[i] = new char[y];
                    }

                    temp2 = new char*[x];
                        for (unsigned int i = 0; i < x; i++) {
                        temp2[i] = new char[y];
                    }
                    
                    //read in the maze map
                    std::cout<<"Please enter the structure of the maze:"<<std::endl;
                    for (unsigned int i = 0; i < x; i++) {
                        for (unsigned int j = 0; j < y; j++) {
                            std::cin >> mazeArr[i][j];
                        }
                    }

                    for(unsigned int i =0; i < x; i++ ){
                        for(unsigned int j = 0; j < y; j++){
                            temp1[i][j] = mazeArr[i][j];
                            temp2[i][j] = mazeArr[i][j];
                            temp3[i][j] = mazeArr[i][j];
                        }
                    }

                    std::cout << "Maze read successfully" <<std::endl;
                    std::cout<< "**Printing Maze**" <<std::endl;
                    std::cout<<"BasePoint: (" << PlayerPos.x << ", "<< PlayerPos.y <<", "<< PlayerPos.z << ")" << std::endl;

                std::cout<<"Structure: "<<std::endl;
                for (unsigned int i = 0; i < x; i++) {
                    for (unsigned int j = 0; j < y; j++) {
                        std::cout << mazeArr[i][j];
                    }
                    std::cout << std::endl; 
                }

                    std::cout << "**End of Printing Maze**" <<std::endl;
                    std::cout << std::endl;

                    std::cout<<"Do you want to validate the maze? (Please select 1 or 2)"
                            <<"\n1)Yes"<<"\n2)No"<<std::endl;
                    std::string o;
                    std::cin>>o;

                    if(o=="1"){
                        valid = new Valid(x,y);
                        valid = new Valid(mazeArr, x, y);

                        bool hasLoop = valid->loopDetection1(temp1);
                        bool hasIsolatedCell = valid->isolatedCells1(temp2);
                        unsigned int numGate = valid->numGate(temp3);

                        if(hasIsolatedCell || hasLoop || numGate !=1){
                            std::cout << "The maze is not valid. Reason(s):"<<std::endl;
                            if(hasLoop){std::cout << "The maze has loop(s)."<<std::endl;}
                            if(hasIsolatedCell){std::cout << "The maze has isolated cell(s)."<<std::endl;}
                            if(numGate ==0){std::cout<<"The maze has no way out."<<std::endl;}
                            if(numGate >1){std::cout<<"The maze has more than 1 way out."<<std::endl;}
                            std::cout<<"\nDo you want to fix the maze? (Please select 1 or 2)"<<std::endl;
                            std::cout<<"\n1)Yes"<<std::endl;
                            std::cout<<"2)No"<<std::endl;
                            std::cin>>o;

                            if(o=="1"){
                                mazeArr = valid->getArr();

                                std::cout << "**Printing Maze**" <<std::endl;
                                std::cout<<"Structure: "<<std::endl;
                                for (unsigned int i = 0; i < x; i++) {
                                    for (unsigned int j = 0; j < y; j++) {
                                        std::cout << mazeArr[i][j];
                                    }
                                    std::cout << std::endl; 
                                }
                                std::cout << "**End of Printing Maze**" <<std::endl;
                            }

                            else if(std::cin.fail()){
                                curState = ST_Exit;
                            }

                            else{
                                std::cout<<"\nThe maze has been terminated. Please try again."; 
                                std::cout<< std::endl;

                                if(mazeArr != nullptr){
                                    for (unsigned int i = 0; i < x; i++) {
                                        delete[] mazeArr[i];
                                    }
                                }
                                
                                delete[] mazeArr;
                                mazeArr = nullptr;
                                }
                        }

                        else{ 
                            std::cout << "The maze is valid maze" << std::endl;
                        }
                    }
                    
                    else if (std::cin.fail()){
                        curState = ST_Exit;
                    }

                    else if(o == "2"){
                        curState = ST_Main;
                    }   

                }
                    
                else if (std::cin.fail()){
                    curState = ST_Exit;
                }

                else{
                    std::cout << "Input Error: Unknown input, ";
                    std::cout << "please type - done"<< std::endl;
                    curState = ST_GetMaze;
                }    

                curState = ST_Main;  
            }

            //-------2: Generate a random maze-------
            else if(generateMazeOption == "2"){

                std::cout<<"In Minecraft, Please navigate to where you need the maze\n";
                std::cout<< "to be built in Minecraft and type - done"<<std::endl;
                
                std::string accept;
                std::cin>>accept;

                if(accept == "done"){
                    //RESETTING EVERYTHING
                    PlayerPos = mc.getPlayerPosition();
                    baseX = PlayerPos.x;
                    baseY = PlayerPos.y;
                    baseZ = PlayerPos.z;
                    basePoint = mcpp::Coordinate(baseX, baseY, baseZ);

                    //get maze dimensions
                    std::cout <<std::endl;
                    std::cout<<"Enter the length and width of the maze ";
                    std::cout << "(odd numbers only, minimum 3,"; 
                    std::cout << "and maximum 99).";
                    std::cout<<std::endl;

                    std::cout <<std::endl;
                    std::cout<<"Enter the length (x length)";
                    std::cout <<std::endl;
                    std::cin>>x;

                    if (std::cin.fail()){
                    curState = ST_Exit;
                    }

                    while ((x % 2 == 0) || (x < 3) || (x > 99)){
                        std::cout << "Invalid input.";
                        std::cout << std::endl;
                        std::cin>>x;

                        if (std::cin.fail()){
                            curState = ST_Exit;
                        }
                    }

                    std::cout<<"Enter the width (z length)";
                    std::cout <<std::endl;
                    std::cin>>y;

                    if (std::cin.fail()){
                    curState = ST_Exit;
                    }

                    while ((y % 2 == 0) || (y < 3) || (y > 99)){
                        std::cout << "Invalid input.";
                        std::cout << std::endl;
                        curState = ST_GetMaze;
                        std::cin>>y;

                        if (std::cin.fail()){
                            curState = ST_Exit;
                        }
                    }

                    recursive = new Recursive(x,y);

                    //initialise maze
                    mcMaze->resetMaze(basePoint, x, y);

                    mazeArr = new char*[x];
                    for (unsigned int i = 0; i < x; i++) {
                        mazeArr[i] = new char[y];
                    }
                
                    recursive->generateMaze(mazeArr);

                    std::cout<< "**Printing Maze**" <<std::endl;
                    std::cout<<"BasePoint: (" << PlayerPos.x << ", "<< PlayerPos.y <<", "<< PlayerPos.z << ")" << std::endl;

                    std::cout<<"Structure:"<<std::endl;
                    for (unsigned int i = 0; i < x; i++) {
                        for (unsigned int j = 0; j < y; j++) {
                            std::cout << mazeArr[i][j];
                        }
                        std::cout << std::endl;
                    }

                    std::cout<<"**End of Printing Maze**"<<std::endl;
                    std::cout<<std::endl;
                }

                if (std::cin.fail()){
                    curState = ST_Exit;
                }

                else{
                    curState = ST_GetMaze;
                }

                curState =  ST_Main; 
            }

            //-----3: Back-------------
            else if(generateMazeOption == "3"){
                curState = ST_Main;
            }

            //-----Error handling (for generate maze menu)-------
            else{
                //error handling for EOF
                if (std::cin.fail()){
                curState = ST_Exit; 
                }

                std::cout<<"Error: please input a valid number between 1 and 3..."<<std::endl;
                curState = ST_GetMaze;
            }
        }



        //--------(2)BUILD THE MAZE-----------------
        else if(curState == ST_BuildMaze){ 
            if(mazeArr==nullptr){
                std::cout<<"Sorry there is no maze saved."<<
                "\nPlease allocate a new maze."<<std::endl;
                }

            else{
                std::cout<<"The maze is being built. Please standby!"<<std::endl;
                for(unsigned int i =0; i < x; i++){
                    if(mazeArr[i][0]=='.'){mazeArr[i][0]='C';}
                    if(mazeArr[i][y-1]=='.'){mazeArr[i][y-1]='C';}
                }
                for(unsigned int i = 0; i < y; i++){
                    if(mazeArr[0][i]=='.'){mazeArr[0][i]='C';}
                    if(mazeArr[x-1][i]=='.'){mazeArr[x-1][i]='C';}
                }
                
                //clean up maze first
                if (mcMaze->checkLinkedListEmpty() == false){
                    mcMaze->cleanUp();
                }

                //flatten terrain and build the maze code
                std::cout<<"Flattening the earth..."<<std::endl;
                std::cout<<"Readying the area..."<<std::endl;
                mcMaze->flattenMazeArea(x, y);
                std::cout<<"Building the maze..."<<std::endl;
                mcMaze->buildMaze(mazeArr, x, y);
                std::cout<<"The maze is built! Thank you for bearing with us."<<std::endl;
            }

            curState = ST_Main;
        }



        //--------(3)SOLVE THE MAZE-----------------
        else if(curState == ST_SolveMaze){
            printSolveMazeMenu();
            std::cin >> solveMazeOption;

            //----1: Solve manually-----
            if(solveMazeOption == "1"){

                //These flags or loops  will change the enetrance  or '.' to C . 
                //This c is to determine where is the carpet (exit) in the maze 
                for(unsigned int i =0; i < x; i++){
                    if(mazeArr[i][0]=='.'){mazeArr[i][0]='C';}
                    if(mazeArr[i][y-1]=='.'){mazeArr[i][y-1]='C';}
                }
                for(unsigned int i = 0; i < y; i++){
                    if(mazeArr[0][i]=='.'){mazeArr[0][i]='C';}
                    if(mazeArr[x-1][i]=='.'){mazeArr[x-1][i]='C';}
                }

                playerSolve->resetAgent(basePoint, x, y);
                playerSolve->placeRandomly(mazeArr);
                curState = ST_SolveMaze;
            }

            //----2: Show escape-------
            else if(solveMazeOption == "2"){
                std::string solveChoice;

                std::cout << "Select how you want to solve the maze: " << std::endl;
                std::cout << "1) Basic" << std::endl;
                std::cout << "2) Extension" << std::endl;
                std::cin >> solveChoice;

                if (solveChoice == "1") {
                    playerSolve->initialise();
                    playerSolve->walk();    
                }
                
                else if (solveChoice == "2"){
                    mcpp::Coordinate currentPosition = mc.getPlayerPosition();
                    playerExtension->pathBool(currentPosition.x, currentPosition.z);
                    curState = ST_SolveMaze;
                }
                else{
                    //error handling for EOF
                    if (std::cin.fail()){
                    curState = ST_Exit;
                    }
                    //invalid input
                    else{
                        std::cout<<"Error: please input a valid number between 1 and 2..." << std::endl;
                        curState = ST_SolveMaze;
                    }
                }
            }

            //----3: Back---------------
            else if(solveMazeOption == "3"){
                curState = ST_Main;
            }

            //---Error handling (for solve maze menu)-------
            else{
                //error handling for EOF
                if (std::cin.fail()){
                    curState = ST_Exit;
                }

                //invalid input
                else{
                    std::cout<<"Input Error: please input a valid number between 1 and 3..." << std::endl;
                    curState = ST_Main;
                }
            }
        }



        //--------(4)PRINT CREATORS-----------------
        else if(curState == ST_Creators){
            printTeamInfo();
            curState = ST_Main;
        }



        //--------(5)EXIT--------------------------
        else if (curState == ST_Exit){
        }



        //-----ERROR HANDLING (for main menu)---
        else{
            //error handling for EOF
            if (std::cin.fail()){
            curState = ST_Exit;
            }
            //invalid input
            else{
                std::cout<<"Error: please input a valid number between 1 and 5..." << std::endl;
                curState = ST_Main;
            }
        }
    }

    return EXIT_SUCCESS;
}