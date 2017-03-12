/*#pragma once
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


namespace msm = boost::msm;
namespace mpl = boost::mpl;
using namespace boost::msm::front;

// front-end: define the FSM structure 
struct GameFSM_ : public msm::front::state_machine_def<GameFSM_>
{
	template <class Event, class FSM>
	void on_entry(Event const&, FSM&) { std::cout << "Entering GameFSM" << std::endl; }
	template <class Event, class FSM>
	void on_exit(Event const&, FSM&) { std::cout << "Leaving GameFSM" << std::endl; }
	// Events

	struct move { int ID = 0; };
	struct peek {};
	struct throwDice {};
	struct useToken {};
	struct addToken {};
	struct pass {};
	struct pause {};
	struct resume {};
	struct gameOver {};
	struct burglarsWin {};
	struct playAgain {};
	struct close {};
	struct errorReceived {};
	struct errorHandled {};
	struct offerLoot {};
	struct requestLoot {};
	struct createAlarm {};
	struct spyPatrol {};
	struct placeCrow {};
	struct pickUpLoot {};
	struct yes {};
	struct no {};
	struct coord {};
	// Flags
	struct gameClosed {};

	// The list of FSM states
	// Player turn is a fsm itself (submachine)
	struct playerTurn_ : public msm::front::state_machine_def<playerTurn_>
	{

		// every (optional) entry/exit methods get the event passed.
		template <class Event, class FSM>
		void on_entry(Event const&, FSM&) { std::cout << "Entering player turn (aca roll dice for loot) " << std::endl; }
		template <class Event, class FSM>
		void on_exit(Event const&, FSM&) { std::cout << "Leaving player turn" << std::endl; }
	
		
		
		//States
		struct chooseAction : public msm::front::state<>
		{
			template <class Event, class FSM>
			void on_entry(Event const&, FSM&) { std::cout << "Entering choose action" << std::endl; }
			template <class Event, class FSM>
			void on_exit(Event const&, FSM&) { std::cout << "Leaving choose action" << std::endl; }
		};

		struct chooseTile : public msm::front::state<>
		{
			//const std::type_info& previousEvent;

			template <class Event, class FSM>
			void on_entry(Event const& event, FSM& fsm)
			{ 
				std::cout << "Entering choose tile" << std::endl;
				//previousEvent = typeid(Event);
			}

			template <class Event, class FSM>
			void on_exit(Event const&, FSM&) { std::cout << "Leaving choose tile" << std::endl; }
			
		};

		struct askConfirmation : public msm::front::state<>
		{
			template <class Event, class FSM>
			void on_entry(Event const&, FSM&) { std::cout << "Entering ask confirmation" << std::endl; }
			template <class Event, class FSM>
			void on_exit(Event const&, FSM&) { std::cout << "Leaving ask confirmation" << std::endl; }
		};

		struct chekActionTokens : public msm::front::state<>
		{
			template <class Event, class FSM>
			void on_entry(Event const&, FSM&) { std::cout << "Entering checkActionTokens" << std::endl; }
			template <class Event, class FSM>
			void on_exit(Event const&, FSM&) { std::cout << "Leaving checkActionTokens" << std::endl; }
		};



		typedef chooseAction initial_state;

		// Actions
		struct doMove
		{
			template <class EVT, class FSM, class SourceState, class TargetState>
			void operator()(EVT const&, FSM& fsm, SourceState&, TargetState&)
			{
				std::cout << "Moving" << std::endl;
			}
		};

		struct doPeek
		{
			template <class EVT, class FSM, class SourceState, class TargetState>
			void operator()(EVT const&, FSM&, SourceState&, TargetState&)
			{
				std::cout << "Peeking" << std::endl;
			}
		};

		struct doUseToken
		{
			template <class EVT, class FSM, class SourceState, class TargetState>
			void operator()(EVT const&, FSM&, SourceState&, TargetState&)
			{
				std::cout << "Using token" << std::endl;
			}
		};

		struct doAddToken
		{
			template <class EVT, class FSM, class SourceState, class TargetState>
			void operator()(EVT const&, FSM&, SourceState&, TargetState&)
			{
				std::cout << "Adding token" << std::endl;
			}
		};

		struct doThrowDice
		{
			template <class EVT, class FSM, class SourceState, class TargetState>
			void operator()(EVT const&, FSM&, SourceState&, TargetState&)
			{
				std::cout << "Throwing dice" << std::endl;
			}
		};

		struct doCreateAlarm
		{
			template <class EVT, class FSM, class SourceState, class TargetState>
			void operator()(EVT const&, FSM&, SourceState&, TargetState&)
			{
				std::cout << "Creating alarm" << std::endl;
			}
		};

		struct doSpyPatrol
		{
			template <class EVT, class FSM, class SourceState, class TargetState>
			void operator()(EVT const&, FSM&, SourceState&, TargetState&)
			{
				std::cout << "Spying patrol deck" << std::endl;
			}
		};

		struct doPlaceCrow
		{
			template <class EVT, class FSM, class SourceState, class TargetState>
			void operator()(EVT const&, FSM&, SourceState&, TargetState&)
			{
				std::cout << "Placing crow token" << std::endl;
			}
		};

		struct doPickUpLoot
		{
			template <class EVT, class FSM, class SourceState, class TargetState>
			void operator()(EVT const&, FSM&, SourceState&, TargetState&)
			{
				std::cout << "Pick up loot" << std::endl;
			}
		};

		struct doAsk
		{
			template <class EVT, class FSM, class SourceState, class TargetState>
			void operator()(EVT const&, FSM&, SourceState&, TargetState&)
			{
				std::cout << "Ask confirmation" << std::endl;
			}
		};
		struct  doOfferLoot
		{
			template <class EVT, class FSM, class SourceState, class TargetState>
			void operator()(EVT const&, FSM&, SourceState&, TargetState&)
			{
				std::cout << "Ask confirmation" << std::endl;
			}
		};
		struct doRequestLoot
		{
			template <class EVT, class FSM, class SourceState, class TargetState>
			void operator()(EVT const&, FSM&, SourceState&, TargetState&)
			{
				std::cout << "Ask confirmation" << std::endl;
			}
		};


		// Guards
		struct isMoving 
		{
			template <class EVT, class FSM, class SourceState, class TargetState>
			bool operator()(EVT const&, FSM&, SourceState& source, TargetState&)
			{
				std::cout << "is Moving?" << std::endl;
				if (typeid(SourceState) == typeid(chooseTile))
					return source.previousEvent == typeid(move);
					return true;
				else return false;
			}
		};
		struct isPeeking 
		{
			template <class EVT, class FSM, class SourceState, class TargetState>
			bool operator()(EVT const&, FSM&, SourceState&, TargetState&)
			{
				std::cout << "" << std::endl;
				if (typeid(SourceState) == typeid(chooseTile))
					return source.previousEvent == typeid(peek);
				else return false;
			}
		};
		struct isOffering 
		{
			template <class EVT, class FSM, class SourceState, class TargetState>
			bool operator()(EVT const&, FSM&, SourceState&, TargetState&)
			{
				std::cout << "" << std::endl;
				if (typeid(SourceState) == typeid(chooseTile))
					return source.previousEvent == typeid(offerLoot);
				else return false;
			}
		};
		struct isRequesting 
		{
			template <class EVT, class FSM, class SourceState, class TargetState>
			bool operator()(EVT const&, FSM&, SourceState&, TargetState&)
			{
				std::cout << "" << std::endl;
				if (typeid(SourceState) == typeid(chooseTile))
					return source.previousEvent == typeid(requestLoot);
				else return false;
			}
		};
		struct needsConfirmation
		{
			template <class EVT, class FSM, class SourceState, class TargetState>
			bool operator()(EVT const&, FSM&, SourceState&, TargetState&)
			{
				std::cout << "" << std::endl;
			}
		};
		struct transition_table : mpl::vector<
			//       Start         Event             Next          Action         Guard
			//  +------------+---------------+-----------------+--------------+--------------+
			Row <chooseAction, peek          , chooseTile      , none         , none       >,
			Row <chooseAction, move          , chooseTile      , none         , none       >,
			Row <chooseAction, createAlarm   , chooseTile      , none         , none       >,
			Row <chooseAction, placeCrow     , chooseTile      , doPlaceCrow  , none       >,
			Row <chooseAction, useToken      , chekActionTokens, doUseToken   , none       >,
			Row <chooseAction, addToken      , chekActionTokens, doAddToken   , none       >,
			Row <chooseAction, throwDice     , chekActionTokens, doThrowDice  , none       >,
			Row <chooseAction, spyPatrol     , chekActionTokens, doSpyPatrol  , none       >,
			Row <chooseAction, pickUpLoot    , chekActionTokens, doPickUpLoot , none       >,
			Row <chooseAction, offerLoot     , askConfirmation , doAsk        , none       >,
			Row <chooseAction, requestLoot   , askConfirmation , doAsk        , none       >,

			Row<chekActionTokens, yes, chooseAction, none, none>,
			Row<chekActionTokens, no, none,none , none >,

			Row<chooseTile, coord, askConfirmation , none, needsConfirmation>,
			Row<chooseTile, coord, chekActionTokens, doMove, isMoving >,
			Row<chooseTile, coord, chekActionTokens, doPeek, isPeeking  >,
			Row<chooseTile, coord, chekActionTokens, doPlaceCrow, isPeeking  >,
			Row<chooseTile, coord, chekActionTokens, createAlarm, isPeeking  >,

			Row<askConfirmation, yes, chekActionTokens, doMove       , isMoving>, // Desde un tile
			Row<askConfirmation, no , chekActionTokens, none         , none         >,
			Row<askConfirmation, yes, chekActionTokens, doOfferLoot  , isOffering >, // desde offer loot
			Row<askConfirmation, no , chekActionTokens, none         , isOffering>,
			Row<askConfirmation, yes, chekActionTokens, doRequestLoot, isRequesting >, // desde request loot
			Row<askConfirmation, no , chekActionTokens, none         , isRequesting>
		> {};

	};
	typedef msm::back::state_machine<playerTurn_> playerTurn;

	struct guardTurn : public msm::front::state<>
	{
		template <class Event, class FSM>
		void on_entry(Event const&, FSM&) { std::cout << "Entering guard turn" << std::endl; }
		template <class Event, class FSM>
		void on_exit(Event const&, FSM&) { std::cout << "Leaving guard turn" << std::endl; }
	};

	struct gameEnded : public msm::front::state<>
	{
		template <class Event, class FSM>
		void on_entry(Event const&, FSM&) { std::cout << "Entering gameOver" << std::endl; }
		template <class Event, class FSM>
		void on_exit(Event const&, FSM&) { std::cout << "Leaving gameOver" << std::endl; }
	};

	struct playing : public msm::front::state<>
	{
		template <class Event, class FSM>
		void on_entry(Event const&, FSM&) { std::cout << "Entering playing" << std::endl; }
		template <class Event, class FSM>
		void on_exit(Event const&, FSM&) { std::cout << "Leaving playing" << std::endl; }
	};

	struct paused : public msm::front::interrupt_state<mpl::vector<resume, close>>
	{
		template <class Event, class FSM>
		void on_entry(Event const&, FSM&) { std::cout << "Entering paused" << std::endl; }
		template <class Event, class FSM>
		void on_exit(Event const&, FSM&) { std::cout << "Leaving paused" << std::endl; }
	};

	struct error : public msm::front::interrupt_state<errorHandled>
	{
		template <class Event, class FSM>
		void on_entry(Event const&, FSM&) { std::cout << "Entering Error" << std::endl; }
		template <class Event, class FSM>
		void on_exit(Event const&, FSM&) { std::cout << "Leaving Error" << std::endl; }
	};

	struct exit : public msm::front::terminate_state<>
	{
		typedef mpl::vector1<gameClosed> flag_list;
		template <class Event, class FSM>
		void on_entry(Event const&, FSM&) { std::cout << "Entering exit" << std::endl; }
		template <class Event, class FSM>
		void on_exit(Event const&, FSM&) { std::cout << "Leaving exit" << std::endl; }
	};

	// transition actions
	struct changeTurns
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const&, FSM&, SourceState&, TargetState&)
		{
			std::cout << "Changing turns" << std::endl;
		}
	};

	struct moveGuard
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const&, FSM&, SourceState&, TargetState&)
		{
			std::cout << "Moving guard" << std::endl;
		}
	};

	struct resetGame
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const&, FSM&, SourceState&, TargetState&)
		{
			std::cout << "Moving guard" << std::endl;
		}
	};


	// Transition table for player
	struct transition_table : mpl::vector<
		//       Start        Event         Next         Action         Guard
		//  +------------+-------------+------------+--------------+--------------+
		Row < playerTurn, pass, guardTurn, none, none     >,
		Row < playerTurn, gameOver, gameEnded, none, none     >,
		Row < playerTurn, burglarsWin, gameEnded, none, none     >,
		//  +------------+-------------+------------+--------------+--------------+
		Row < guardTurn, move, none, moveGuard, none     >,
		Row < guardTurn, pass, playerTurn, changeTurns, none     >,
		//  +------------+-------------+------------+--------------+--------------+
		Row < gameEnded, playAgain, playerTurn, resetGame, none     >,
		//  +------------+-------------+------------+--------------+--------------+

		//--------------------------Orthogonal region-----------------------------//
		//  +------------+-------------+------------+--------------+--------------+
		Row < playing, close, exit, none, none     >,
		Row < playing, errorReceived, error, none, none     >,
		Row < playing, pause, paused, none, none     >,
		//  +------------+-------------+------------+--------------+--------------+
		Row < paused, resume, playing, none, none     >,
		Row < paused, close, exit, none, none     >,
		//  +------------+-------------+------------+--------------+--------------+
		Row < error, errorHandled, playing, none, none     >,
		Row < error, close, exit, none, none >
		//  +------------+-------------+------------+--------------+--------------+
	> {};

	typedef mpl::vector<playing, playerTurn> initial_state;

	// Replaces the default no-transition response.
	template <class FSM, class Event>
	void no_transition(Event const& e, FSM&, int state)
	{
		std::cout << "no transition from state " << state
			<< " on event " << typeid(e).name() << std::endl;
	}
};
// Pick a back-end
typedef msm::back::state_machine<GameFSM_> GameFSM;*/
