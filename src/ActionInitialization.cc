#include "ActionInitialization.hh"
#include "EventAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "SteppingAction.hh"

namespace B1 {
ActionInitialization::ActionInitialization() {}

ActionInitialization::~ActionInitialization() {}

void ActionInitialization::BuildForMaster() const {
    RunAction* runAction = new RunAction;
    SetUserAction(runAction);
}

void ActionInitialization::Build() const {
    SetUserAction(new PrimaryGeneratorAction);

    RunAction* runAction = new RunAction;
    SetUserAction(runAction);

    EventAction* eventAction = new EventAction(runAction);
    SetUserAction(eventAction);

    SetUserAction(new SteppingAction(eventAction));
}
}    // namespace Fe55