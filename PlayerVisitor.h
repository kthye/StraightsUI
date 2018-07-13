#ifndef PLAYER_VISITOR_H
#define PLAYER_VISITOR_H

class HumanPlayer;
class ComputerPlayer;

class PlayerVisitor {
public:
    virtual ~PlayerVisitor() = default;

    // called when the visitor visits a human player
    virtual void visitPlayer(const HumanPlayer & hp) const = 0;

    // called when the visitor visits a computer player
    virtual void visitPlayer(const ComputerPlayer & cp) const = 0;
};

#endif
