#include <engine.h>
#include <state.h>
#include <typeinfo>
#include <iostream>

namespace engine {


    Engine::Engine () {
        
    }

    Engine::Engine (state::State& currentState) {
        m_currentState = currentState;
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

    void Engine::setState(state::State& currentState){
        m_currentState = currentState;
    }

    void Engine::setRecord(Json::Value record){
        m_record = record;
    }

    void Engine::addCommande (Commande& cmd){
        if(typeid(cmd) == typeid(Deplacement)){
            std::cout<<"ok"<<std::endl;
        }
    }

}
