/*
 *Author:       Ryan Wagner
 *Date:         August 20, 2014
 *Description:  Basic user security program, asks for a name and password
 *              exiting on 5 unsuccessful attempts.
 *Input:        Username/Password/Commands
 *Output:       Login messages.
 */

#include<iostream>
#include<fstream>
#include<string>

using namespace std;

int checkUser(char *name, char *pass);
void homeScreen(char *name, char *pass);

int main(void){
  int correct=0,i=0;
  char name[100],pass[100];
  while (!correct && i<5){
    cout<<"User: ";
    cin>>name;
    cout<<"Pass: ";
    cin>>pass;
    correct = checkUser(name,pass);
    i++;
    if(!correct){
      cout<<"Attempt ("<<i<<") Failed."<<endl;
    }
    else{
      homeScreen(name,pass);
    }
  }
  if(i==5)
    cout<<"Login failed, aborting."<<endl;

  return 0;
}

int checkUser(char *name, char *pass){
  ifstream input;
  input.open("pass.txt");
  int correct = 0;
  if(input.is_open()){
    while(input.good() && !correct){
      char trueInfo[256];
      input.getline(trueInfo,256);
      if(input.good()){
        char trueUser[256];
        (void)strncpy(trueUser,trueInfo,strrchr(trueInfo,' ')-trueInfo);   
        char * truePass = strrchr(trueInfo,' ')+1;
        (strcmp(name,trueUser) || strcmp(pass,truePass))?correct=0:correct=1;
      }
    }
    input.close();
  }
  else{/*EMPTY*/}
  return correct;
}

void homeScreen(char *name, char *pass){
  cout<<"Welcome back "<<name<<"!\n";
  char input[256], cmds[256], list[1000];
  while (strncmp(input,"quit",strlen(input))){
    cout<<">";
    cin>>input;
    ifstream command;
    command.open("commandList.txt");
    if(!command){
      cout<<"File read error."<<endl;
    }
    else{
      while(command.getline(cmds,256)){
        strcat(list,cmds);
      }
      command.close();
    }
    if(!strstr(list , input)){
      cout<<"Command not found."<<endl;
    }
    else if(strcmp(input, "quit"))
      cout<<"Input recognized ["<<input<<"]"<<endl;
    else
      cout<<"Abort Sequence Recognized."<<endl;
  }
}
