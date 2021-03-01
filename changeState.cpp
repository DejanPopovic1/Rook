#include "changeState.hpp"
#include "ToAlgNotation.hpp"

ChangeState::ChangeState(){

}

ChangeState::ChangeState(T_boardState *c, T_boardStates *bss){
    for(int i = 0; i < bss->fi; i++){
        validMoves[i] = toAlgebraicNotation(c, &(bss->bs[i]));
            }
}

T_boardState ChangeState::changeInputState(T_boardStates *bss, string usrInput){



}


vector<string> ChangeState::listValidMoves(T_boardStates *bss){


}
