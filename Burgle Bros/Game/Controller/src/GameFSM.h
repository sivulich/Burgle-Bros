#pragma once
#pragma once
#define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#define BOOST_MPL_LIMIT_VECTOR_SIZE 50 //or whatever you need                       
#define BOOST_MPL_LIMIT_MAP_SIZE 50 //or whatever you need 

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
#include "./GameFSM.h"
#include "./GameState.h"
#include "./events.h"

namespace msm = boost::msm;
namespace mpl = boost::mpl;
using namespace boost::msm::front;

struct GameFSM_ : public msm::front::state_machine_def<GameFSM_>
{
	// Default constructor
	GameFSM_() { };

	// Constructor which receives a pointer to the model
	GameFSM_(GameModel * m, GameGraphics * g/*, BurgleNetwork * n*/, Timer * t)
	{
		model = m;
		graphics = g;
		//network = n;
		guardTimer = t;
	};

	// FSM variables
	GameModel * model;
	GameGraphics * graphics;
	//BurgleNetwork * network;
	Timer * guardTimer;
	enum { UNSET, LOCAL, REMOTE };
	int gameMode;
	//-------------------------------------------------------------
	template <class EVT, class FSM>
	void on_entry(EVT const&  event, FSM& fsm)
	{
		std::cout << "Welcome to EDA Burgle Bros" << std::endl;

		// Pass pointers to submachine 
		GameState& s = fsm.get_state<GameState&>();
		s.model = fsm.model;
		s.graphics = fsm.graphics;
		s.guardTimer = fsm.guardTimer;
		//s.network = fsm.network;
	}

	template <class EVT, class FSM>
	void on_exit(EVT const&  event, FSM& fsm)
	{
		std::cout << "" << std::endl;
	}

	// Flags
	struct gameClosed {};

	struct exitState : public exit_pseudo_state<none> {};

	//----------------------- STATES -----------------------------//

	struct MenuScreen : public msm::front::state<>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			std::cout << "Main Menu" << std::endl;
			fsm.graphics->showMenuScreen();
		}

		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{
			std::cout << "" << std::endl;
		}
	};

	struct RulesScreen : public msm::front::state<>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			std::cout << "Rules Menu" << std::endl;
			fsm.graphics->showRulesScreen();
		}

		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{
			std::cout << "" << std::endl;
		}
	};

	struct CreditsScreen : public msm::front::state<>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			std::cout << "Credits Menu" << std::endl;
			fsm.graphics->showCreditsScreen();
		}

		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{
			std::cout << "" << std::endl;
		}
	};

	struct ModeScreen : public msm::front::state<>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			std::cout << "Mode selection" << std::endl;
			fsm.gameMode = UNSET;
			fsm.graphics->showModeScreen();
		}

		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{
			std::cout << "" << std::endl;
		}
	};

	struct SetupScreen : public msm::front::state<>
	{
		bool player1set;
		bool player2set;

		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			if (fsm.gameMode == UNSET) // LOCAL
			{
				fsm.gameMode = LOCAL;
				//
				std::cout << "LocalSetup" << std::endl;
				fsm.graphics->showSetupScreen(1);
				player1set = false;
				player2set = false;
			}
			else // REMOTE
			{
				std::cout << "RemoteSetup" << std::endl;
				fsm.graphics->showSetupScreen();
			}

		}

		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{
			std::cout << "" << std::endl;
		}
	};

	struct IPScreen : public msm::front::state<>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			std::cout << "Set IP direction" << std::endl;
			fsm.gameMode = REMOTE;
			fsm.graphics->showIPScreen();
		}

	};

	struct Connecting : public msm::front::state<>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			std::cout << "Connecting" << std::endl;
		}

	};
	struct RemoteSetupScreen : public msm::front::state<>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			std::cout << "Set IP direction" << std::endl;
			fsm.graphics->showIPScreen();
		}

	};

	// -------------------- ORTHOGONAL REGION ------------------
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

	struct paused : public msm::front::interrupt_state<mpl::vector<ev::resume, ev::close>>
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

	struct error : public msm::front::interrupt_state<ev::errorHandled>
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
		{}

		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{}

	};


	//----------------------- ACTIONS -----------------------------//

	struct doMove
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{

		}
	};


	struct setUpCharacter
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			if (fsm.gameMode == LOCAL)
			{
				if (source.player1set == false)
					fsm.model->player1()->setCharacter(event.character);
				else if (source.player2set == false)
					fsm.model->player2()->setCharacter(event.character);
			}
			else if (fsm.gameMode == REMOTE)
			{
				fsm.model->player1()->setCharacter(event.character);
			}

		}
	};

	struct doSetup
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			if (fsm.gameMode == LOCAL)
			{
				if (source.player1set == false && fsm.model->player1()->hasCharacter())
				{
					source.player1set = true;
					fsm.model->player1()->setName(fsm.graphics->getPlayerName());
					fsm.graphics->showSetupScreen(2);
				}
				else if (source.player2set == false && fsm.model->player2()->hasCharacter())
				{
					// If both have the same character
					if (fsm.model->player1()->getCharacter() == fsm.model->player2()->getCharacter())
					{

					}
					else
					{
						source.player2set = true;
						fsm.model->player2()->setName(fsm.graphics->getPlayerName());
						// Both caracters set so go to game
						GameState& s = fsm.get_state<GameState&>();
						s.gameMode = LOCAL;
						fsm.model->setLocal();
						fsm.process_event(ev::play());
					}
				}
			}
			else if (fsm.gameMode == REMOTE)
			{
				// ACa ya se sabe el nombre y caracter de cada jugador
				// HACER EL INTERCAMBIO DE DATOS
				GameState& s = fsm.get_state<GameState&>();
				s.gameMode = REMOTE;
				fsm.model->setRemote();
				fsm.process_event(ev::play());
			}
		}
	};

	struct doConnect
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			cout << "Connecting computers" << endl;
			string IP = fsm.graphics->getIP();

			//fsm.network->connect(IP);
			//fsm.graphics->showCancelMessage(string("Connecting... Please wait."));
		}

	};

	struct removeMessage
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			//fsm.graphics->removeDialogBox();
		}

	};


	struct stopConnecting
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			//fsm.network->cancelConnecting();
		}

	};

	struct doRender
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			fsm.graphics->render();
		}

	};

	///////////// GUARDSSSSS

	struct isLocal
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		bool operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			return 	fsm.gameMode == LOCAL;
		}
	};

	struct isRemote
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		bool operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			return 	fsm.gameMode == REMOTE;
		}
	};

	// Transition table for main FSM
	struct transition_table : mpl::vector<
		//       Start        Event         Next         Action         Guard
		//  +------------+-------------+------------+--------------+--------------+
		Row < MenuScreen	, ev::start			, ModeScreen	, none				, none		>,
		Row < MenuScreen	, ev::rules			, RulesScreen	, none				, none		>,
		Row < MenuScreen	, ev::credits		, CreditsScreen	, none				, none		>,
		//  +------------+-------------+------------+--------------+--------------+
		Row < ModeScreen	, ev::local			, SetupScreen	, none				, none		>,
		Row < ModeScreen	, ev::remote		, IPScreen		, none				, none		>,
		Row < ModeScreen	, ev::back			, MenuScreen	, none				, none		>,
		//  +------------+-------------+------------+--------------+--------------+
		Row < RulesScreen	, ev::back			, MenuScreen	, none				, none		>,
		//  +------------+-------------+------------+--------------+--------------+
		Row < CreditsScreen	, ev::back			, MenuScreen	, none				, none		>,
		//  +------------+-------------+------------+--------------+--------------+
		Row < SetupScreen	, ev::back			, ModeScreen	, none				, isLocal	>,
		Row < SetupScreen	, ev::back			, IPScreen		, none				, isRemote	>,
		Row < SetupScreen	, ev::characterName	, none			, setUpCharacter	, none		>,
		Row < SetupScreen	, ev::next			, none			, doSetup			, none		>,
		Row < SetupScreen	, ev::play			, GameState		, none				, none		>,
		//  +------------+-------------+------------+--------------+--------------+
		Row < IPScreen		, ev::back			, ModeScreen	, none				, none		>,
		Row < IPScreen		, ev::connect		, none			, doConnect			, none		>,
		Row < IPScreen		, ev::next			, SetupScreen	, removeMessage		, none		>,
		Row < IPScreen		, ev::cancel		, none			, stopConnecting	, none		>,
//		Row < RemoteSetupScreen, ev::characterName, none, setUpCharacter, none >,
//		Row < RemoteSetupScreen, ev::next, none, doRemoteSetup, none >,
//	    Row < RemoteSetupScreen, ev::play, GameState, none, none >,
		//  +------------+-------------+------------+--------------+--------------+
		Row <GameState		, ev::back			, MenuScreen	, none				, none		>,

//--------------------------Orthogonal region-----------------------------//
//  +------------+-------------+------------+--------------+--------------+
		Row <   playing		, ev::close			, exit			, none				, none		>,
		//Row <   playing, ev::errorReceived, error, none, none     >,				
		Row <   playing		, ev::pause			, paused		, none				, none		>,
		//Row <   playing, ev::render, none, doRender, none     >,
		//  +------------+-------------+------------+--------------+--------------+
		Row <   paused		, ev::pause			, playing		, none				, none		>,
		Row <   paused		, ev::close			, exit			, none				, none		>
		/*Row <   paused, ev::render, paused, doRender, none     >,
		//  +------------+-------------+------------+--------------+--------------+
		Row <   error, ev::errorHandled, playing, none, none     >,
		Row <   error, ev::close, exit, none, none     >,
		Row <   error, ev::render, none, doRender, none     >
		//  +------------+-------------+------------+--------------+--------------+*/
			> {};

	typedef mpl::vector<playing, MenuScreen> initial_state;

	// Replaces the default no-transition response.
	template <class FSM, class EVT>
	void no_transition(EVT const&  event, FSM& fsm, int state)
	{
		std::cout << "no transition from state " << state << " on event " << typeid(event).name() << std::endl;
	}
};
// Pick a back-end
typedef msm::back::state_machine<GameFSM_> GameFSM;
