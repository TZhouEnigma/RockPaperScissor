//
//  main.cpp
//  rps
//
//  Created by chuxiang zhou on 7/11/17.
//  Copyright © 2017 chuxiang zhou. All rights reserved.
//

#include <stdio.h>
#include <iostream>

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

char computer_Pick(HMM &R,HMM &P, HMM &S, char prev){
    char ans = '\0';
    
    if(prev == 'R'){
      /*  cout<<"the probability of you picking"<<endl;
        cout<<"Paper is:"<<R.Showleft()<<endl;
        cout<<"Scissor is:"<<R.ShowRight()<<endl;
        cout<<"Rock is:"<<R.ShowStay()<<endl;*/
        if(R.Showleft()>=R.ShowRight() && R.Showleft()>= R.ShowStay()) ans='S';
        if(R.ShowRight()>=R.Showleft() && R.ShowRight()>= R.ShowStay()) ans='R';
        if(R.ShowStay()>=R.ShowRight() && R.ShowStay()>= R.Showleft()) ans='P';
        
    }
    if(prev == 'P'){
      /*  cout<<"the probability of you picking"<<endl;
        cout<<"Paper is:"<<P.ShowStay()<<endl;
        cout<<"Scissor:"<<P.Showleft()<<endl;
        cout<<"Rock:"<<P.ShowRight()<<endl;
      */
        if(P.Showleft()>=P.ShowRight() && P.Showleft()>= P.ShowStay()) ans='R';
        if(P.ShowRight()>=P.Showleft() && P.ShowRight()>= P.ShowStay()) ans='P';
        if(P.ShowStay()>=P.ShowRight() && P.ShowStay()>= P.Showleft()) ans='S';
        }
    if(prev == 'S'){
        /*
        cout<<"the probability of you picking"<<endl;
        cout<<"Paper is:"<<S.ShowRight()<<endl;
        cout<<"Scissor:"<<S.ShowStay()<<endl;
        cout<<"Rock:"<<S.Showleft()<<endl;
         */
        if(S.Showleft()>=S.ShowRight() && S.Showleft()>= S.ShowStay()) ans='P';
        if(S.ShowRight()>=S.Showleft() && S.ShowRight()>= S.ShowStay()) ans='S';
        if(S.ShowStay()>=S.ShowRight() && S.ShowStay()>= S.Showleft()) ans='R';
    }
    
    cout<<"Computer picked: "<<ans<<endl;
    
    return ans;
}
int main(){
    
    
    HMM Rock(0,0,0);
    HMM Paper(0,0,0);
    HMM Scissors(0,0,0);
    
    Rock.setSide(Paper, Scissors);
    Paper.setSide(Scissors, Rock);
    Scissors.setSide(Rock, Paper);
    
    cout<<"hahahhh"<<endl;
    Rock.Showleft();
    
    int numtries=100;
    int count=0;
    char previous;
    
    cout<<"Welcome to the challenge! \n Enter R,P OR S for wrap paper and scissors"<<endl;
    cin>>previous;//Initial state
    
    
    
    while(count<numtries){
        
         computer_Pick(Rock, Paper, Scissors, previous);
        
    cout<<"Enter R,P OR S for wrap paper and scissors"<<endl;
        char Choose;
        cin>>Choose;
       
        
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
    
   /*
    cout<<"rock to paper:"<<Rock.Showleft()<<endl;
    cout<<"rock to Scissor:"<<Rock.ShowRight()<<endl;
    cout<<"rock to rock:"<<Rock.ShowStay()<<endl;
    
    
    cout<<"paper to paper:"<<Paper.ShowStay()<<endl;
    cout<<"paper to Scissor:"<<Paper.Showleft()<<endl;
    cout<<"paper to rock:"<<Rock.ShowRight()<<endl;
    
    cout<<"scissors to paper:"<<Scissors.ShowRight()<<endl;
    cout<<"scissors  to Scissor:"<<Scissors.ShowStay()<<endl;
    cout<<"scissors  to rock:"<<Scissors.Showleft()<<endl;
    */
    return 0;
    
}

