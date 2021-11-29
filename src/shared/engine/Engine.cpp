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

    void Engine::addCommande (Commande& cmd){
        if(cmd.getCommandeTypeId() == Deplacement){
            if (cmd.handleDeplacement(*m_currentState.getOrdreTour()[0], m_currentState.getDecor().getMap(), m_currentState.getDecor().getLargeur()) && cmd.handleCollision(m_currentState.getEntites())){
                cmd.execute(this.getState());
            }
        }
        else if(cmd.getCommandeTypeId() == Attaque){
            if(cmd.handleAttaque(*m_currentState.getOrdreTour()[0])){
                cmd.execute(this.getState());
            }
        }
    }

}