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

#include "../Controller/GameFSM.h"
#include "../Model/Header Files/Configs.h"

namespace msm = boost::msm;
namespace mpl = boost::mpl;
using namespace boost::msm::front;

struct GameFSM_ : public msm::front::state_machine_def<GameFSM_>
{
	GameFSM_() { model = nullptr; };
	GameFSM_(GameModel * m) : model(m)
	{
		
	};

	GameModel * model;

	
	
	template <class EVT, class FSM>
	void on_entry(EVT const&  event, FSM& fsm)
	{
		std::cout << "Entering Burgle Bros Finite State Machine" << std::endl;
		fsm.set_states(msm::back::states_ << GameFSM_::playerTurn(model));
		//GameFSM_::playerTurn& p = fsm.get_state<GameFSM_::playerTurn&>();
		//p.model = model;
	}

	template <class EVT, class FSM>
	void on_exit(EVT const&  event, FSM& fsm)
	{
		std::cout << "Leaving Burgle Bros Finite State Machine" << std::endl;
	}

	
	// Flags
	struct gameClosed {};


	struct exitState : public exit_pseudo_state<none> {};

	//----------------------- STATES -----------------------------//
	// Player turn is a fsm itself (submachine)
	struct playerTurn_ : public msm::front::state_machine_def<playerTurn_>
	{
		playerTurn_() { model = nullptr; };
		playerTurn_(GameModel * m) : model(m) {};
		GameModel * model;

		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
		
			/*std::cout << "Entering player turn (roll dice for loot here) " << std::endl;*/
			std::cout << typeid(fsm).name() << std::endl;//  .set_states(msm::back::states_ << playerTurn_::check(model));
			fsm.model->print();
			/*fsm.set_states(msm::back::states_ << playerTurn_::peeking(model));
			fsm.set_states(msm::back::states_ << playerTurn_::creatingAlarm(model));
			fsm.set_states(msm::back::states_ << playerTurn_::placingCrow(model));
			fsm.set_states(msm::back::states_ << playerTurn_::offeringLoot(model));
			fsm.set_states(msm::back::states_ << playerTurn_::requestingLoot(model));*/
		}
		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{
			std::cout << "Leaving player turn" << std::endl;
		}



		//----------------------- ACTIONS -----------------------------//

		struct doMove
		{
			template <class EVT, class FSM, class SourceState, class TargetState>
			void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
			{
				std::cout << "Mooving" << typeid(FSM).name() << std::endl;
//				fsm.model->currentPlayer()->move(source.c);
			}
		};

		struct doPeek
		{
			template <class EVT, class FSM, class SourceState, class TargetState>
			void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
			{
				std::cout << "Peeking" << std::endl;
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



		//----------------------- STATES -----------------------------//

		struct chooseAction : public msm::front::state<>
		{
			template <class EVT, class FSM>
			void on_entry(EVT const&  event, FSM& fsm)
			{
				std::cout << "Choose action" << std::endl;
			}

			template <class EVT, class FSM>
			void on_exit(EVT const&  event, FSM& fsm)
			{

			}

		};

		struct chooseTile : public msm::front::state<>
		{
//			Coord c;
			template <class EVT, class FSM>
			void on_entry(EVT const&  event, FSM& fsm)
			{
				std::cout << "Choose tile" << std::endl;
			}

			template <class EVT, class FSM>
			void on_exit(EVT const&  event, FSM& fsm)
			{
//				c = event.c;
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




		struct mooving_ : public msm::front::state_machine_def<mooving_>
		{
			mooving_() {};
			mooving_(GameModel * m) : model(m) {};
			GameModel * model;

			struct transition_table : mpl::vector<
				//       Start         Event             Next          Action         Guard
				Row <chooseTile, coord, exitState, doMove, none>,
				Row <chooseTile, coord, askConfirmation, none, needsConfirmation    >,
				Row <askConfirmation, yes, exitState, doMove, none >,
				Row <askConfirmation, no, exitState, none, none >
			> {};
			typedef chooseTile initial_state;
		};
		typedef msm::back::state_machine<mooving_> mooving;


		struct peeking_ : public msm::front::state_machine_def<peeking_>
		{
			peeking_() {};
			peeking_(GameModel * m) : model(m) {};
			GameModel * model;

			struct transition_table : mpl::vector<
				//       Start         Event             Next          Action         Guard
				Row <chooseTile, coord, exitState, doPeek, none        >
			> {};
			typedef chooseTile initial_state;
		};
		typedef msm::back::state_machine<peeking_> peeking;

		struct creatingAlarm_ : public msm::front::state_machine_def<creatingAlarm_>
		{
			creatingAlarm_() {};
			creatingAlarm_(GameModel * m) : model(m) {};
			GameModel * model;

			struct transition_table : mpl::vector<
				//       Start         Event             Next          Action         Guard
				Row <chooseTile, coord, exitState, doCreateAlarm, none        >
			> {};
			typedef chooseTile initial_state;
		};
		typedef msm::back::state_machine<creatingAlarm_> creatingAlarm;

		struct placingCrow_ : public msm::front::state_machine_def<placingCrow_>
		{
			placingCrow_() {};
			placingCrow_(GameModel * m) : model(m) {};
			GameModel * model;

			struct transition_table : mpl::vector<
				//       Start         Event             Next          Action         Guard
				Row <chooseTile, coord, exitState, doPlaceCrow, none        >
			> {};
			typedef chooseTile initial_state;
		};
		typedef msm::back::state_machine<placingCrow_> placingCrow;

		struct offeringLoot_ : public msm::front::state_machine_def<offeringLoot_>
		{
			offeringLoot_() {};
			offeringLoot_(GameModel * m) : model(m) {};
			GameModel * model;

			struct transition_table : mpl::vector<
				//       Start         Event             Next          Action         Guard
				//  +------------+---------------+-----------------+--------------+--------------+
				Row <askConfirmation, yes, exitState, doOfferLoot, none >,
				Row <askConfirmation, no, exitState, none, none >
			> {};
			typedef askConfirmation initial_state;
		};
		typedef msm::back::state_machine<offeringLoot_> offeringLoot;

		struct requestingLoot_ : public msm::front::state_machine_def<requestingLoot_>
		{
			requestingLoot_() {};
			requestingLoot_(GameModel * m) : model(m) {};
			GameModel * model;

			struct transition_table : mpl::vector<
				//       Start         Event             Next          Action         Guard
				//  +------------+---------------+-----------------+--------------+--------------+
				Row <askConfirmation, yes, exitState, doRequestLoot, none >,
				Row <askConfirmation, no, exitState, none, none >
			> {};
			typedef askConfirmation initial_state;
		};
		typedef msm::back::state_machine<requestingLoot_> requestingLoot;


		struct chekActionTokens : public msm::front::state<>
		{
			template <class EVT, class FSM>
			void on_entry(EVT const&  event, FSM& fsm)
			{
				std::cout << "Checking action tokens" << std::endl;
				if (true)
				{
					fsm.process_event(no());
					std::cout << "Your turn ends" << std::endl;
				}
				else
				{
					fsm.process_event(yes());
					std::cout << "Keep playing" << std::endl;
				}

			}
		};

		typedef chooseAction initial_state;

		struct transition_table : mpl::vector<
			//       Start         Event             Next          Action         Guard
			//  +------------+---------------+-----------------+--------------+--------------+
			Row <chooseAction, peek, peeking, none, none       >,
			Row <chooseAction, movee, mooving, none, none       >,
			Row <chooseAction, createAlarm, creatingAlarm, none, none       >,
			Row <chooseAction, placeCrow, placingCrow, none, none       >,
			Row <chooseAction, offerLoot, offeringLoot, none, none       >,
			Row <chooseAction, requestLoot, requestingLoot, none, none       >,
			Row <chooseAction, useToken, chooseAction, doUseToken, none       >,
			Row <chooseAction, addToken, chekActionTokens, doAddToken, none       >,
			Row <chooseAction, throwDice, chekActionTokens, doThrowDice, none       >,// CHEQUEAR SI CONSUMEN ACCIONES O NO!!
			Row <chooseAction, spyPatrol, chekActionTokens, doSpyPatrol, none       >,
			Row <chooseAction, pickUpLoot, chekActionTokens, doPickUpLoot, none       >,

			Row <peeking::exit_pt<exitState>, none, chekActionTokens, none, none       >,
			Row <mooving::exit_pt<exitState>, none, chekActionTokens, none, none       >,
			Row <creatingAlarm::exit_pt<exitState>, none, chekActionTokens, none, none       >,
			Row <placingCrow::exit_pt<exitState>, none, chekActionTokens, none, none       >,
			Row <offeringLoot::exit_pt<exitState>, none, chekActionTokens, none, none       >,
			Row <requestingLoot::exit_pt<exitState>, none, chekActionTokens, none, none       >,

			Row<chekActionTokens, yes, chooseAction, none, none>,
			Row<chekActionTokens, no, exitState, none, none >
		> {};

	};
	typedef msm::back::state_machine<playerTurn_> playerTurn;

	struct guardTurn : public msm::front::state<>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			std::cout << "Its guards turn" << std::endl;
		}

		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{
			std::cout << "Leaving guard turn" << std::endl;
		}

	};

	struct gameEnded : public msm::front::state<>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			if (typeid(EVT) == typeid(burglarsWin))
				std::cout << "You win!" << std::endl;
			else if (typeid(EVT) == typeid(gameOver))
				std::cout << "You loose!" << std::endl;
		}
	};


	// Playing state is always active, unless game is paused or there is an error
	struct playing : public msm::front::state<>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			std::cout << "Start playing" << std::endl;
		}

		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{
			std::cout << "Stop playing" << std::endl;
		}

	};

	struct paused : public msm::front::interrupt_state<mpl::vector<resume, close>>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			std::cout << "Paused" << std::endl;
		}

		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{
			std::cout << "Resuming" << std::endl;
		}

	};

	struct error : public msm::front::interrupt_state<errorHandled>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			std::cout << "Entering Error" << std::endl;
		}

		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{
			std::cout << "Leaving Error" << std::endl;
		}

	};

	struct exit : public msm::front::terminate_state<>
	{
		typedef mpl::vector1<gameClosed> flag_list;
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			std::cout << "Entering exit" << std::endl;
		}

		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{
			std::cout << "Leaving exit" << std::endl;
		}

	};


	// transition actions
	struct changeTurns
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Changing turns" << std::endl;
		}
	};

	struct moveGuard
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Moving guard" << std::endl;
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


	// Transition table for main FSM
	struct transition_table : mpl::vector<
		//       Start        Event         Next         Action         Guard
		//  +------------+-------------+------------+--------------+--------------+
		Row < playerTurn, pass, guardTurn, none, none         >,
		Row < playerTurn::exit_pt<exitState>, none, guardTurn, moveGuard, none         >,
		Row < playerTurn, gameOver, gameEnded, none, none         >,
		Row < playerTurn, burglarsWin, gameEnded, none, none         >,
		//  +------------+-------------+------------+--------------+--------------+
		Row < guardTurn, movee, none, moveGuard, none         >,
		Row < guardTurn, pass, playerTurn, changeTurns, none         >,
		Row < guardTurn, gameOver, gameEnded, none, none         >,
		//  +------------+-------------+------------+--------------+--------------+
		Row < gameEnded, playAgain, playerTurn, resetGame, none         >,
		//  +------------+-------------+------------+--------------+--------------+

		//--------------------------Orthogonal region-----------------------------//
		//  +------------+-------------+------------+--------------+--------------+
		Row < playing, close, exit, none, none         >,
		Row < playing, errorReceived, error, none, none         >,
		Row < playing, pause, paused, none, none         >,
		//  +------------+-------------+------------+--------------+--------------+
		Row < paused, resume, playing, none, none         >,
		Row < paused, close, exit, none, none         >,
		//  +------------+-------------+------------+--------------+--------------+
		Row < error, errorHandled, playing, none, none         >,
		Row < error, close, exit, none, none         >
		//  +------------+-------------+------------+--------------+--------------+
	> {};

	typedef mpl::vector<playing, playerTurn> initial_state;

	// Replaces the default no-transition response.
	template <class FSM, class EVT>
	void no_transition(EVT const&  event, FSM& fsm, int state)
	{
		std::cout << "no transition from state " << state
			<< " on event " << typeid(event).name() << std::endl;
	}
};
// Pick a back-end
typedef msm::back::state_machine<GameFSM_> GameFSM_imp;


GameFSM::GameFSM(GameModel * m) : FSM(new GameFSM_imp(m))
{

}

void GameFSM::start()
{
	static_pointer_cast<GameFSM_imp>(FSM)->start();
};
void GameFSM::stop()
{
	static_pointer_cast<GameFSM_imp>(FSM)->stop();
};

bool GameFSM::isRunning()
{	
	return static_pointer_cast<GameFSM_imp>(FSM)->is_flag_active<GameFSM_imp::gameClosed>() == false;
};

void GameFSM::processEvent(BaseEvent *  ev)
{
		static_pointer_cast<GameFSM_imp>(FSM)->process_event(*ev);

		delete ev;
}
/*
void GameFSM::processEvent(string s)
{
	if (s == "move")
		static_pointer_cast<GameFSM_imp>(FSM)->process_event(GameFSM_imp::move());
	else if (s == "peek")
		static_pointer_cast<GameFSM_imp>(FSM)->process_event(GameFSM_imp::peek());
	else if (s == "throwDice")
		static_pointer_cast<GameFSM_imp>(FSM)->process_event(GameFSM_imp::throwDice());
	else if (s == "addToken")
		static_pointer_cast<GameFSM_imp>(FSM)->process_event(GameFSM_imp::addToken());
	else if (s == "useToken")
		static_pointer_cast<GameFSM_imp>(FSM)->process_event(GameFSM_imp::useToken());
	else if (s == "pass")
		static_pointer_cast<GameFSM_imp>(FSM)->process_event(GameFSM_imp::pass());
	else if (s == "pause")
		static_pointer_cast<GameFSM_imp>(FSM)->process_event(GameFSM_imp::pause());
	else if (s == "resume")
		static_pointer_cast<GameFSM_imp>(FSM)->process_event(GameFSM_imp::resume());
	else if (s == "gameOver")
		static_pointer_cast<GameFSM_imp>(FSM)->process_event(GameFSM_imp::gameOver());
	else if (s == "burglarsWin")
		static_pointer_cast<GameFSM_imp>(FSM)->process_event(GameFSM_imp::burglarsWin());
	else if (s == "playAgain")
		static_pointer_cast<GameFSM_imp>(FSM)->process_event(GameFSM_imp::playAgain());
	else if (s == "close")
		static_pointer_cast<GameFSM_imp>(FSM)->process_event(GameFSM_imp::close());
	else if (s == "coord")
		static_pointer_cast<GameFSM_imp>(FSM)->process_event(GameFSM_imp::coord());
	else if (s == "errorReceived")
		static_pointer_cast<GameFSM_imp>(FSM)->process_event(GameFSM_imp::errorReceived());
	else if (s == "errorHandled")
		static_pointer_cast<GameFSM_imp>(FSM)->process_event(GameFSM_imp::errorHandled());
	else if (s == "yes")
		static_pointer_cast<GameFSM_imp>(FSM)->process_event(GameFSM_imp::yes());
	else if (s == "no")
		static_pointer_cast<GameFSM_imp>(FSM)->process_event(GameFSM_imp::no());

	static_pointer_cast<GameFSM_imp>(FSM)->process_event

}*/