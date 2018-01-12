#pragma once
#define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#define BOOST_MPL_LIMIT_VECTOR_SIZE 30 //or whatever you need                       
#define BOOST_MPL_LIMIT_MAP_SIZE 30 //or whatever you need 

#include <iostream>
// Back-end:
#include <boost/msm/back/state_machine.hpp>
// Front-end:
#include <boost/msm/front/state_machine_def.hpp>
// Functors:
#include <boost/msm/front/functor_row.hpp>
#include <boost/msm/front/euml/common.hpp>
#include <boost/msm/front/euml/euml.hpp>

#include <GameModel.h>
#include <GameGraphics.h>
#include <BurgleNetwork.h>
#include <Configs.h>
#include "./events.h"

namespace msm = boost::msm;
namespace mpl = boost::mpl;
using namespace boost::msm::front;


struct GameState_ : public msm::front::state_machine_def<GameState_>
{
	// INICIALIZAR PUNTEROS!

	// FSM variables
	GameModel * model;
	GameGraphics * graphics;
	BurgleNetwork * network;
	Timer * guardTimer;
	action_ID currentAction; // Stores current action chosen by player

	//-------------------------------------------------------------
	template <class EVT, class FSM>
	void on_entry(EVT const&  event, FSM& fsm)
	{
		fsm.model->currentPlayer()->setCharacter(RAVEN);
		fsm.model->otherPlayer()->setCharacter(PETERMAN);
		fsm.model->currentPlayer()->setName(string("TOBIAS"));
		fsm.model->otherPlayer()->setName(string("JULIETA"));
		std::cout << "Entering Burgle Bros Finite State Machine" << std::endl;
		fsm.model->setBoard();
		
		fsm.graphics->showGameScreen();

	}

	template <class EVT, class FSM>
	void on_exit(EVT const&  event, FSM& fsm)
	{
		std::cout << "Leaving Burgle Bros Finite State Machine" << std::endl;
	}

	//----------------------- STATES -----------------------------//

	struct chooseInitialPos : public msm::front::state<>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			std::cout << "Choose initial pos: ";
			vector<Coord> v;
			v.push_back(Coord(0, 0, 0));
			v.push_back(Coord(0, 0, 1));
			v.push_back(Coord(0, 0, 2));
			v.push_back(Coord(0, 0, 3));
			v.push_back(Coord(0, 1, 0));
			v.push_back(Coord(0, 1, 1));
			v.push_back(Coord(0, 1, 2));
			v.push_back(Coord(0, 1, 3));
			v.push_back(Coord(0, 2, 0));
			v.push_back(Coord(0, 2, 1));
			v.push_back(Coord(0, 2, 2));
			v.push_back(Coord(0, 2, 3));
			v.push_back(Coord(0, 3, 0));
			v.push_back(Coord(0, 3, 1));
			v.push_back(Coord(0, 3, 2));
			v.push_back(Coord(0, 3, 3));

			fsm.graphics->setTilesClickable(v);
		}

		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{
			// Desmarcar las tiles 
			fsm.graphics->setAllClickable();
		}
	};


	struct chooseAction : public msm::front::state<>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			std::cout << "Choose action: ";
			vector<string> v = fsm.model->currentPlayer()->getActions();
			for (auto& s : v)
				std::cout << s << " ";
			std::cout << std::endl;

			//fsm.graphics->showActions(v);
		}

		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{
			// Desmarcar las tiles 
			fsm.graphics->setAllClickable();
		}
	};

	struct creatingAlarm : public msm::front::state<>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			std::cout << "" << std::endl;
		}

		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{
			std::cout << "" << std::endl;
		}
	};

	struct placingCrow : public msm::front::state<>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			std::cout << "" << std::endl;
		}

		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{
			std::cout << "" << std::endl;
		}
	};
	struct offeringLoot : public msm::front::state<>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			std::cout << "" << std::endl;
		}

		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{
			std::cout << "" << std::endl;
		}
	};

	struct requestingLoot : public msm::front::state<>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			std::cout << "" << std::endl;
		}

		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{
			std::cout << "" << std::endl;
		}
	};
	
	struct chekActionTokens : public msm::front::state<>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			std::cout << "Action tokens left: " << fsm.model->currentPlayer()->getActionTokens() << std::endl;
			if (fsm.model->currentPlayer()->getActionTokens() == 0)
			{
				fsm.process_event(ev::no());
				std::cout << "Your turn ends" << std::endl;
			}
			else
			{
				fsm.process_event(ev::yes());
				std::cout << "Keep playing" << std::endl;
			}

		}
	};

	struct askConfirmation : public msm::front::state<>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			std::cout << "Are you sure? yes/no" << std::endl;
		}


		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{
			std::cout << "Okay..." << std::endl;
		}

	};
	struct guardTurn : public msm::front::state<>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			std::cout << "Its guards turn" << std::endl;
			fsm.guardTimer->start();
		}

		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{
			std::cout << "Leaving guard turn" << std::endl;
			fsm.guardTimer->stop();
		}

	};
	
	struct gameEnded : public msm::front::state<>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			if (typeid(EVT) == typeid(ev::burglarsWin))
				std::cout << "You win!" << std::endl;
			else if (typeid(EVT) == typeid(ev::gameOver))
				std::cout << "You loose!" << std::endl;
		}
	};


	//----------------------- ACTIONS -----------------------------//
	
	struct doSetInitialPos
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Setting initial position to  " << event.c << std::endl;
			fsm.model->setInitialPosition(event.c);
		}
	};

	struct doMove
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Moving to  " << event.c << std::endl;
			bool b = fsm.model->currentPlayer()->move(event.c);
			if (b == false)
				std::cout << "Cant move!" << std::endl;

			fsm.currentAction = NO_TYPE;
		}
	};

	struct doPeek
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Peeking" << std::endl;
			bool b = fsm.model->currentPlayer()->peek(event.c);
			if (b == false)
				std::cout << "Cant peek!" << std::endl;

			fsm.currentAction = NO_TYPE;
		}
	};

	struct doUseToken
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Using token" << std::endl;
		}
	};

	struct doAddToken
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Adding token" << std::endl;
			fsm.model->currentPlayer()->addToken();
		}
	};

	struct doThrowDice
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Throwing dice" << std::endl;
		}
	};

	struct doAddDice
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Adding dice to the safe " << std::endl;
			fsm.model->currentPlayer()->addDice();
		}
	};


	struct doCreateAlarm
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Creating alarm" << std::endl;
		}
	};

	struct doSpyPatrol
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Spying patrol deck" << std::endl;
		}
	};

	struct doPlaceCrow
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Placing crow token" << std::endl;
		}
	};

	struct doPickUpLoot
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Pick up loot" << std::endl;
		}
	};

	struct doAsk
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Ask confirmation" << std::endl;
		}
	};

	struct  doOfferLoot
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Offer loot" << std::endl;
		}
	};

	struct doRequestLoot
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Request loot" << std::endl;
		}
	};

	struct needsConfirmation
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		bool operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{

			return false;
		}
	};

	struct changeTurn
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Changing turns" << std::endl;
			fsm.model->changeTurn();
		}
	};

	struct moveGuard
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Moving guard" << std::endl;
			fsm.model->moveGuard();
			if (fsm.model->guardIsMoving() == false)
			{
				fsm.process_event(ev::pass());
				fsm.guardTimer->stop();
			}
		}
	};

	struct resetGame
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Reset game" << std::endl;
		}
	};


	struct showMove
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Tiles availables to move: ";
			vector<Coord> v = fsm.model->currentPlayer()->whereCanIMove();
			Coord::printVec(v);
			std::cout << std::endl;

			fsm.currentAction = MOVE;
			// Distinguir las tiles disponibles para moverse
			fsm.graphics->setTilesClickable(v);
		}
	};

	struct showPeek
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Tiles availables to peek: ";
			vector<Coord> v = fsm.model->currentPlayer()->whereCanIPeek();
			Coord::printVec(v);
			std::cout << std::endl;
			fsm.currentAction = PEEK;
			// Distinguir las tiles disponibles para moverse
			fsm.graphics->setTilesClickable(v);

		}
	};
	
	///////////// GUARDSSSSS
	struct isMoving
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		bool operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			return 	fsm.currentAction == MOVE;
		}
	};

	struct isPeeking
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		bool operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			return fsm.currentAction == PEEK;
		}
	};

	// Transition table
	struct transition_table : mpl::vector<
		//       Start        Event         Next         Action         Guard
		//  +------------+-------------+------------+--------------+--------------+
		
		Row < chooseInitialPos, ev::coord, chooseAction, doSetInitialPos, none       >,
		Row < chooseAction, ev::pass, guardTurn, none, none       >,
		Row < chooseAction, ev::pass, guardTurn, none, none       >,
		Row < chooseAction, ev::movee, none, showMove, none       >,
		Row < chooseAction, ev::peek, none, showPeek, none       >,
		Row < chooseAction, ev::coord, chekActionTokens, doMove, isMoving       >,
		Row < chooseAction, ev::coord, chekActionTokens, doPeek, isPeeking       >,
		Row < chooseAction, ev::addToken, chekActionTokens, doAddToken, none       >,
		Row < chooseAction, ev::addDice, chekActionTokens, doAddDice, none       >,
		//Row < chooseAction,   throwDice   , throwingDice,    none,        none       >,
		//Row < chooseAction,   useToken    , usingToken,      none,        none       >,

		//Row < chooseAction,   offerLoot   , offeringLoot,    none,        none       >,
		//Row < chooseAction,   requestLoot , requestingLoots , none,        none       >,
		//Row < chooseAction,   createAlarm , creatingAlarm   ,   none,        none       >,
		//Row < chooseAction,   spyPatrol   , guardTurn,       none,        none       >,
		//Row < chooseAction,   placeCrow   , guardTurn,       none,        none       >,
		//Row < chooseAction,   pickUpLoot  , guardTurn,       none,        none       >,
		//  +------------+-------------+------------+--------------+--------------+
		Row < chekActionTokens, ev::no, guardTurn, none, none     >,
		Row < chekActionTokens, ev::yes, chooseAction, none, none     >,
		//  +------------+-------------+------------+--------------+--------------+
		Row < guardTurn, ev::movee, none, moveGuard, none     >,
		Row < guardTurn, ev::pass, chooseAction, changeTurn, none     >,
		Row < guardTurn, ev::gameOver, gameEnded, none, none     >,
		//  +------------+-------------+------------+--------------+--------------+
		Row < gameEnded, ev::playAgain, chooseAction, resetGame, none     >
		//  +------------+-------------+------------+--------------+--------------+

	> {};
	
	// Replaces the default no-transition response.
	template <class FSM, class EVT>
	void no_transition(EVT const&  event, FSM& fsm, int state)
	{
		std::cout << "no transition from state " << state
			<< " on event " << typeid(event).name() << std::endl;
	}

typedef chooseInitialPos initial_state;
};
// Pick a back-end
typedef msm::back::state_machine<GameState_> GameState;