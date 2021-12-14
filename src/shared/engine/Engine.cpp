#include <engine.h>
#include <state.h>
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

    bool Engine::executerCommande (Commande& cmd){
        if(cmd.getCommandeTypeId() == Deplacement){
            if (cmd.handleDeplacement(*m_currentState.getOrdreTour()[0], m_currentState.getDecor().getMap(), m_currentState.getDecor().getLargeur()) && cmd.handleCollision(m_currentState.getEntites())){
                cmd.execute(&this->getState());
                std::cout << "Deplacement possible" << std::endl;
                return true;
            } else {
            std::cout << "Deplacement échoué" << std::endl;
            return false;
            }
        }
        else if(cmd.getCommandeTypeId() == Attaque){
            if(cmd.handleAttaque(*m_currentState.getOrdreTour()[0])){
                cmd.execute(&this->getState());
            }
        }
        else if(cmd.getCommandeTypeId() == ActionSupplementaire){
            if(cmd.handleActionSupplementaire(*m_currentState.getOrdreTour()[0])){
                cmd.execute(&this->getState());
            }
        }
    }

}