#include <iostream>
#include <memory>

#include "dialogue_scene.hpp"

int main(){
    std::unique_ptr<HITO::DialogueScene> dialogue_scene(new HITO::DialogueScene);
    if(dialogue_scene->init() == "no"){
        std::cout << "Initialilze failed";
        return 1;
    }
    std::string input;
    do{
        std::cin >> input;
        std:: cout << dialogue_scene->update(input);
    }
    while(input != "exit");
}