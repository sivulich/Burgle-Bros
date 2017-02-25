#pragma once

#ifndef FSM_H
#define FSM_H

// TEMPLATE FSM
// STATE EVENT and ACTION are enums starting from 0!

template <typename STATE, typename EVENT, typename ACTION>
class FSM
{
public:
	// Each combination of state-event implies an action and a next state.
	// So the elements of the table are StateCells
	typedef struct
	{
		ACTION  action;
		STATE  nextState;
	} StateCell;

	// Construct the FSM with its initial state
	FSM(const StateCell *table, STATE initialState, STATE numberOfStates, EVENT numberOfEvents)
	{
		currentState = initialState;
		this->table = table;
		this->numberOfStates = numberOfStates;
		this->numberOfEvents = numberOfEvents;
	}
	//
	void setState(STATE state) { currentState = state; }
	//
	STATE getState() { return currentState; }

	// When an event ocurrs call this function and pass a void pointer to the 
	// data the action function will modify
	void runStep(EVENT event, void * userData)
	{
		if (event < numberOfEvents)		// Check if its a valid event
		{
			int i = (int)currentState * (int)numberOfEvents + (int)event;

			DoAction(table[i].action, userData);
			currentState = table[i].nextState;
		}
	}


private:
	// Pure virtual function, should be implemented in derived class
	// When inheriting, complete the template with your STATES EVENTS and ACTIONS
	// 
	virtual void DoAction(ACTION action, void * userData) = 0;
	//virtual EVENT DoAction(ACTION action, void * userData) = 0;
private:
	//  Pointer to the table of StateCells
	const StateCell *  table;

	STATE currentState;

	STATE numberOfStates;
	EVENT numberOfEvents;
};

#endif // FSM_H
