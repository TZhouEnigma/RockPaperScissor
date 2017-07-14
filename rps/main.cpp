//
//  main.cpp
//  rps
//
//  Created by chuxiang zhou on 7/11/17.
//  Copyright © 2017 chuxiang zhou. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>


using namespace std;

//assuming that the contestant's choice is dependent on the previous "state"
//and there is a hidden Markov model which eixsts within a person's brain that describes
//the decision making process. The HMM can be generalized as:
//              R
//            /   \
//           /     \
//          /       \
//         /         \
//        S<--------->S
//
//

//Data used for randomizing RPS picker for testing purposes, generated using Wolfram Alpha
int mat[100]={3, 1, 1, 3, 1, 2, 1, 1, 3, 2, 3, 2, 2, 1, 2, 1, 1, 1, 3, 1, 1, 2, 3, 1, 2, 3, 3, 1, 3, 3, 3, 3, 1, 2, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 2, 2, 1, 2, 1, 2, 3, 1, 3, 1, 2, 2, 3, 1, 2, 1, 3, 2, 3, 2, 3, 2, 2, 1, 3, 2, 2, 2, 2, 3, 1, 3, 2, 2, 2, 1, 2, 2, 2, 2, 1, 1, 1, 3, 2, 3, 3, 3, 2, 3, 1, 1, 2, 1, 2, 3};



//Construct a HMM class
class HMM{
    
public:
    double left;
    double right;
    double stay;
    HMM *LEFT;
    HMM *RIGHT;
    double Showleft();
    double ShowRight();
    double ShowStay();
    void setSide(HMM &a,HMM &b);
    void AdjustProb(double left_prob, double right_prob,double stay);
    
    HMM(double left_prob, double right_prob,double stay);
    
};

HMM::HMM(double left_prob, double right_prob, double stay){
    this->left = left_prob;
    this->right = right_prob;
    this->stay = stay;
}
double HMM::Showleft(){
    return this->left;
}
double HMM::ShowRight(){
    return this->right;
}

double HMM::ShowStay(){
    return this->stay;
}


void HMM::AdjustProb(double left_prob, double right_prob,double stay){
    this->left += left_prob;
    this->right += right_prob;
    this->stay += stay;
}

void HMM::setSide(HMM &a,HMM &b){
    this->LEFT=&a;
    this->RIGHT=&b;
    
}


// Decision function based on existing HMM
char computer_Pick(HMM &R,HMM &P, HMM &S, char prev){
    char ans = '\0';
    
    if(prev == 'R'){
        if(R.Showleft()>=R.ShowRight() && R.Showleft()>= R.ShowStay()) ans='S';
        if(R.ShowRight()>=R.Showleft() && R.ShowRight()>= R.ShowStay()) ans='R';
        if(R.ShowStay()>=R.ShowRight() && R.ShowStay()>= R.Showleft()) ans='P';
        
    }
    if(prev == 'P'){
        if(P.Showleft()>=P.ShowRight() && P.Showleft()>= P.ShowStay()) ans='R';
        if(P.ShowRight()>=P.Showleft() && P.ShowRight()>= P.ShowStay()) ans='P';
        if(P.ShowStay()>=P.ShowRight() && P.ShowStay()>= P.Showleft()) ans='S';
        }
    if(prev == 'S'){
        
        if(S.Showleft()>=S.ShowRight() && S.Showleft()>= S.ShowStay()) ans='P';
        if(S.ShowRight()>=S.Showleft() && S.ShowRight()>= S.ShowStay()) ans='S';
        if(S.ShowStay()>=S.ShowRight() && S.ShowStay()>= S.Showleft()) ans='R';
    }
    
    cout<<"Computer picked: "<<ans<<"\n "<<endl;
    
    return ans;
}

char result(char human,char ai){
 if(human==ai)  return 'T';
 else if((human=='R' && ai=='P') || (human=='P' && ai=='S') || (human=='S' && ai=='R')){
     return 'L';
 }
   return 'W';
    
}


//random RPS generator
char randRPS(int in){
    
    int random = mat[in] ;
    if(random == 1) return 'R';
    if(random == 2) return 'P';
    
    return 'S';
        
}


int main(){
    
    
    HMM Rock(0,0,0);
    HMM Paper(0,0,0);
    HMM Scissors(0,0,0);
    
    Rock.setSide(Paper, Scissors);
    Paper.setSide(Scissors, Rock);
    Scissors.setSide(Rock, Paper);
    
    
    int numtries=100;
    int count=1;
    char previous;
    
    cout<<"Welcome to the challenge! \nEnter R,P OR S for wrap, paper or scissors"<<endl;
    cin>>previous;//Initial state
    
    double win=0;
    double winOrLose=0;
    
    
    while(count<numtries){
        
    
  
        char Choose;
        
      
   //  UNCOMMENT the folloing two lines to play against computer
  //   cout<<"Enter R,P OR S for wrap paper and scissors"<<endl;
  //   cin>>Choose;
   
        Choose = randRPS(count);  //COMMENT out this line to play against computer
        cout<<"Using randomized data,you picked "<<Choose<<endl; //COMMENT out this line to play against computer
        char res= result(Choose, computer_Pick(Rock, Paper, Scissors, previous));
        if(res=='W'){
            ++win;
            ++winOrLose;
            cout<<"YOU WIN! \nYour winning percentage is now: "<< double(win/double(winOrLose))<<endl;
        }
        else if(res=='T'){
            cout<<"TIE GAME! \nYour winning percentage is now: "<< double(win/double(winOrLose))<<endl;
        }
        else{
            ++winOrLose;
            cout<<"YOU LOSE! \nYour winning percentage is now: "<< double(win/double(winOrLose))<<endl;
        }
       
        
        
      //If the user choose the same as last round
        if(Choose==previous){
            if(Choose=='R')
            Rock.AdjustProb(0,0,0.01);
            if(Choose=='P')
            Paper.AdjustProb(0,0,0.01);
            if(Choose=='S')
            Scissors.AdjustProb(0,0,0.01);
        }
        
        
    else if(Choose=='R' and previous=='P'){
            Paper.AdjustProb(0,0.01,0);

    }
    else if(Choose=='R' and previous=='S'){
        Scissors.AdjustProb(0.01,0,0);
        
    }
    
    else if(Choose=='P' and previous=='S'){
        Scissors.AdjustProb(0,0.01,0);
        
    }
        
    else if(Choose=='P' and previous=='R'){
        Rock.AdjustProb(0.01,0,0);
        
    }
        
    else if(Choose=='S' and previous=='P'){
        Paper.AdjustProb(0.01,0,0);
        
    }
    
    else if(Choose=='S' and previous=='R'){
        Rock.AdjustProb(0,0.01,0);
        
    }
        count++;
        previous=Choose;
    
    }
    
    cout<<"\n \nYou won "<<win<<" and lost "<<winOrLose-win<< "out of total 100 games! \n"<<endl;
    
    cout<<"Your total winning percentage is "<<double(win/double(winOrLose))<<","<<endl;

   
    return 0;
    
}

