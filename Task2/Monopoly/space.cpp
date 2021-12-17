#include <iostream>

#include "space.h"

// TODO: Implement here the methods of Space

Space :: Space(){
}

void Space :: setId(int newId){
    id = newId;
}

void Space :: setName(string newName){
    name = newName;
}

void Space :: setType(string newType){
    type = newType;
}

void Space :: setActionText(string newActionText){
    actionText = newActionText;
}

void Space :: setTax(int newTax){
    tax = newTax;
}

void Space :: setRent(int newRent){
    rent = newRent;
}

void Space :: setBuyingCost(int newBuyCost){
    buyCost = newBuyCost;
}

void Space :: setOwner(int newOwner){
    owner = newOwner;
}

int Space :: getId(){
    return id;
}

string Space :: getName(){
    return name;
}

string Space :: getType(){
    return type;
}

string Space :: getActionText(){
    return actionText;
}

int Space :: getRent(){
    return rent;
}

int Space :: getTax(){
    return tax;
}

int Space :: getBuyingCost(){
    return buyCost;
}

int Space :: getOwner(){
    return owner;
}
