#include "Engine.h"

namespace engine {


Engine::Engine () {

}

Engine::~Engine () {
    
}


void Engine::init (){
    
}

state::State& Engine::getState (){
    return m_currentState;
}

Json::Value Engine::getRecord (){
    return m_record;
}

void Engine::addCommande (std::unique_ptr<Commande> cmd){
    
}

}