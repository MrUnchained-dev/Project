#pragma once
#define STORAGE
#include <iostream>


class Storage{
private:
    static int Cash;
    static int Gems;

public:
    Storage(){
        Cash = 0;
        Gems = 0;
    }

    static void changeNetCash(int sum){
        Cash += sum;
    }

    static void changeNetGems(int sum){
        Gems += sum;
    }

    static int showCash(){
        return Cash;
    }

    static int showGems(){
        return Gems;
    }

};

int Storage::Cash = 0;
int Storage::Gems = 0;