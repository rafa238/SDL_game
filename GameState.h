#ifndef __GAMESTATE__
#define __GAMESTATE__
#include<string>

class GameState {
public:

    virtual ~GameState(){};
    virtual void update() = 0;
    virtual void render() = 0;
    virtual bool onEnter() = 0;
    virtual bool onExit() = 0;
    virtual std::string getStateID() const = 0;
};

#endif
