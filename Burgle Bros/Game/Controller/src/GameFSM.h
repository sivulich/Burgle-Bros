#pragma once
#pragma once
#define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#define BOOST_MPL_LIMIT_VECTOR_SIZE 50 //or whatever you need                       
#define BOOST_MPL_LIMIT_MAP_SIZE 50 //or whatever you need 
#define FUSION_MAX_VECTOR_SIZE 25


#include <iostream>
// Back-end:
#include <boost/msm/back/state_machine.hpp>
// Front-end:
#include <boost/msm/front/state_machine_def.hpp>
// Functors:
#include <boost/msm/front/functor_row.hpp>
#include <boost/msm/front/euml/common.hpp>
#include <boost/msm/front/euml/euml.hpp>

// Check
#include <boost/msm/back/mpl_graph_fsm_check.hpp>

#include <GameModel.h>
#include <GameGraphics.h>
#include <BurgleNetwork.h>
#include <Configs.h>
#include "./GameFSM.h"
#include "./GameState.h"
#include "./events.h"
#include "../../Sound/SoundEffects.h"
namespace msm = boost::msm;
namespace mpl = boost::mpl;
using namespace boost::msm::front;

class GameFSM_ : public msm::front::state_machine_def<GameFSM_>
{
public:
	// Default constructor
	GameFSM_() { };

	// Constructor which receives a pointer to the model
	GameFSM_(GameGraphics * g, Timer * t)
	{
		graphics = g;
		sound = new SoundEffects();
		network = nullptr;
		model = nullptr;

		guardTimer = t;
	};

	bool isRemote()
	{
		if (model != nullptr)
			return model->isRemote();
		else return false;
	}
	remoteInput getRemoteInput()
	{
		if (network != nullptr)
			return network->getRemoteInput();
		else
			return remoteInput();
	}
	void processTrick(string s)
	{
		if (model != nullptr)
		{
			if (s.substr(0, 8) == string("ADD_LOOT"))
				model->currentPlayer()->addLoot(toEnum_lootType(s.substr(9).c_str()));
			else if (s.substr(0, 4) == string("DROP"))
			{
				Loot * l = nullptr;
				if (s.substr(5) == string("GOLDBAR"))
					l = LootFactory().newLoot(GOLD_BAR);
				else if ((s.substr(5) == string("PERSIAN_KITTY")))
					l = LootFactory().newLoot(PERSIAN_KITTY);
				if (l != nullptr)
					model->getBoard()->getTile(model->currentPlayer()->getPosition())->setLoot(l);
			}
			else if (s.substr(0, 13) == string("SET_CHARACTER"))
				model->currentPlayer()->setCharacter(s.substr(14));

			else if (s.substr(0, 4) == string("MASK"))
				graphics->loadPlayerToken(s.substr(5));
			else if (s == "FLIP_ALL")
				model->flipAll();

		}
	}
	// FSM variables
	GameModel * model;
	GameGraphics * graphics;
	SoundEffects * sound;
	BurgleNetwork * network;
	Timer * guardTimer;
	enum MODE { UNSET, LOCAL, REMOTE };
	int gameMode;
	//-------------------------------------------------------------
	template <class EVT, class FSM>
	void on_entry(EVT const&  event, FSM& fsm)
	{
		DEBUG_MSG("Welcome to EDA Burgle Bros");

	}

	template <class EVT, class FSM>
	void on_exit(EVT const&  event, FSM& fsm)
	{
		DEBUG_MSG("Leaving EDA Burgle Bros");
		delete fsm.model;
		delete fsm.network;
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
			DEBUG_MSG("MENU SCREEN");
			fsm.graphics->showMenuScreen();
		}

		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{
			DEBUG_MSG("LEAVING MENU SCREEN");
		}
	};

	struct RulesScreen : public msm::front::state<>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			DEBUG_MSG("RULES SCREEN");
			fsm.graphics->showRulesScreen();
		}

		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{
			DEBUG_MSG("LEAVING RULES SCREEN");
		}
	};

	struct CreditsScreen : public msm::front::state<>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			DEBUG_MSG("CREDITS SCREEN");
			fsm.graphics->showCreditsScreen();
		}

		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{
			DEBUG_MSG("LEAVING CREDITS SCREEN");
		}
	};

	struct ModeScreen : public msm::front::state<>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			DEBUG_MSG("MODE SCREEN");
			fsm.gameMode = UNSET;
			fsm.graphics->showModeScreen();
		}

		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{
			if (is_same<EVT, ev::remote>::value)
				fsm.gameMode = REMOTE;
			else if (is_same<EVT, ev::local>::value)
				fsm.gameMode = LOCAL;
		}
	};

	struct SetupScreen : public msm::front::state<>
	{
		bool player1set;
		bool player2set;

		string name1, name2, character1, character2;

		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			DEBUG_MSG("SETUP SCREEN");

			player1set = false;
			player2set = false;
			name1 = name2 = character1 = character2 = "";
			DEBUG_MSG(player1set << " " << name1 << " " << character1);
			DEBUG_MSG(player2set << " " << name2 << " " << character2);

			if (fsm.gameMode == LOCAL)
				fsm.graphics->showSetupScreen(1);
			else if (fsm.gameMode == REMOTE)
				fsm.graphics->showSetupScreen();
		}

		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{
			DEBUG_MSG("LEAVING SETUP SCREEN");
		}
	};

	struct IPScreen : public msm::front::state<>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			DEBUG_MSG("Set IP direction");
			fsm.graphics->showIPScreen();
		}

		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{

		}



	};

	struct Connecting : public msm::front::state<>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			DEBUG_MSG("Connecting");
		}

	};


	// -------------------- ORTHOGONAL REGION ------------------
	// Playing state is always active, unless game is paused or there is an error
	struct playing : public msm::front::state<>
	{
		bool dialogBoxOpened;
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			DEBUG_MSG("Start playing");
			dialogBoxOpened = false;
		}

		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{
			DEBUG_MSG("Stop playing");
		}

	};

	struct paused : public msm::front::interrupt_state<mpl::vector<ev::resume, ev::close>>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			DEBUG_MSG("Paused");
		}

		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{
			DEBUG_MSG("Resuming");
		}
	};

	struct error : public msm::front::interrupt_state<ev::errorHandled>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			DEBUG_MSG("Entering Error");
		}

		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{
			DEBUG_MSG("Leaving Error");
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

	struct askConfirmationClose
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			if (event.remote == true)
			{
				fsm.graphics->showOkMessage(fsm.model->otherPlayer()->getName() + string(" has closed the game!"));
			}
			else
			{
				fsm.graphics->askQuestion("Are you sure you want to quit?");
			}
			source.dialogBoxOpened = true;
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
					source.character1 = event.character;
				else if (source.player2set == false)
					source.character2 = event.character;
			}
			else if (fsm.gameMode == REMOTE)
				source.character1 = event.character;
		}
	};

	struct doSetup
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			if (fsm.gameMode == LOCAL)
			{
				if (source.player1set == false && source.character1.empty() == false)
				{
					DEBUG_MSG(source.player1set << " " << source.name1 << " " << source.character1);
					DEBUG_MSG(source.player2set << " " << source.name2 << " " << source.character2);

					source.player1set = true;
					source.name1 = fsm.graphics->getPlayerName();
					fsm.graphics->showSetupScreen(2, source.character1);
				}
				else if (source.player2set == false && source.character2.empty() == false)
				{
					DEBUG_MSG(source.player1set << " " << source.name1 << " " << source.character1);
					DEBUG_MSG(source.player2set << " " << source.name2 << " " << source.character2);

					// If both have the same character
					if (source.character1 == source.character2)
					{
						fsm.graphics->showOkMessage("Both players can't have the same character!");
					}
					else
					{
						source.player2set = true;
						source.name2 = fsm.graphics->getPlayerName();

						// Both caracters set so go to game
						fsm.process_event(ev::play());
						fsm.graphics->showTempMessage("Loading...");
						fsm.graphics->render();
					}
				}
			}
			else if (fsm.gameMode == REMOTE && source.character1.empty() == false)
			{
				source.name1 = fsm.graphics->getPlayerName();
				fsm.process_event(ev::play());
				fsm.graphics->showTempMessage("Loading...");
				fsm.graphics->render();
			}

			
		}
	};

	struct doConnect
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{

			fsm.graphics->showTempMessage(string("Connecting... Please wait."));
			fsm.graphics->render();

			DEBUG_MSG("Connecting computers");
			string IP = fsm.graphics->getIP();
			fsm.network = new BurgleNetwork();
			fsm.network->connect(IP);
			while (!fsm.network->join()) {}

			fsm.graphics->removeDialogBox();
			if (fsm.network->error())
			{
				fsm.graphics->showOkMessage(fsm.network->errMessage());
				fsm.graphics->render();
				DEBUG_MSG(fsm.network->errMessage());
			}
			else
			{
				// CONNECTED
				fsm.process_event(ev::next());
			}

		}

	};

	struct restartGame
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			delete fsm.model;
			delete fsm.network;
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

	struct buildAndPassData
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			// Create model
			fsm.model = new GameModel();

			fsm.model->player1()->setName(source.name1);
			fsm.model->player1()->setCharacter(source.character1);
			fsm.model->player2()->setName(source.name2);
			fsm.model->player2()->setCharacter(source.character2);

			fsm.graphics->setModel(fsm.model);

			if (fsm.gameMode == LOCAL)
				fsm.model->setLocal();
			else if (fsm.gameMode == REMOTE)
				fsm.model->setRemote();

			// Pass pointers to submachine 
			GameState& s = fsm.get_state<GameState&>();
			s.model = fsm.model;
			s.graphics = fsm.graphics;
			s.network = fsm.network;
			s.guardTimer = fsm.guardTimer; // GameState needs guardTimer pointer to start it and stop it
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

	struct nameAndCharacSet
	{
		// Check if name and character are set
		template <class EVT, class FSM, class SourceState, class TargetState>
		bool operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			if (source.player1set == false)
				return !fsm.graphics->getPlayerName().empty() && !source.character1.empty();
			else if (source.player2set == false)
				return !fsm.graphics->getPlayerName().empty() && !source.character2.empty();
		}
	};

	struct dialogBoxOpened
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		bool operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			return 	source.dialogBoxOpened == true;
		}
	};

	// Transition table for main FSM
	struct transition_table : mpl::vector<
		//       Start        Event         Next         Action         Guard
		//  +------------+-------------+------------+--------------+--------------+
		Row < MenuScreen, ev::start, ModeScreen, none, none		>,
		Row < MenuScreen, ev::rules, RulesScreen, none, none		>,
		Row < MenuScreen, ev::credits, CreditsScreen, none, none		>,
		//  +------------+-------------+------------+--------------+--------------+
		Row < ModeScreen, ev::local, SetupScreen, none, none		>,
		Row < ModeScreen, ev::remote, IPScreen, none, none		>,
		Row < ModeScreen, ev::back, MenuScreen, none, none		>,
		//  +------------+-------------+------------+--------------+--------------+
		Row < RulesScreen, ev::back, MenuScreen, none, none		>,
		//  +------------+-------------+------------+--------------+--------------+
		Row < CreditsScreen, ev::back, MenuScreen, none, none		>,
		//  +------------+-------------+------------+--------------+--------------+
		Row < SetupScreen, ev::back, ModeScreen, none, isLocal	>,
		Row < SetupScreen, ev::back, IPScreen, none, Not_<isLocal>	>,
		Row < SetupScreen, ev::characterName, none, setUpCharacter, none		>,
		Row < SetupScreen, ev::next, none, doSetup, nameAndCharacSet		>,
		Row < SetupScreen, ev::play, GameState, buildAndPassData, none		>,
		//  +------------+-------------+------------+--------------+--------------+
		Row < IPScreen, ev::back, ModeScreen, none, none		>,
		Row < IPScreen, ev::connect, none, doConnect, none		>,
		Row < IPScreen, ev::next, SetupScreen, removeMessage, none		>,
		Row < IPScreen, ev::cancel, none, stopConnecting, none		>,
		//  +------------+-------------+------------+--------------+--------------+
		Row <GameState, ev::back, MenuScreen, restartGame, none		>,

		//--------------------------Orthogonal region-----------------------------//
		//  +------------+-------------+------------+--------------+--------------+
		Row <   playing, ev::close, none, askConfirmationClose, Not_<dialogBoxOpened>		>,
		Row <   playing, Or_<ev::yes,ev::ok>, exit, none, dialogBoxOpened>,
		Row <   playing, ev::no, playing, none, dialogBoxOpened>,
		//	Row <   playing, ev::errorReceived, error, none, none     >,				
		Row <   playing, ev::pause, paused, none, none		>,
		//  +------------+-------------+------------+--------------+--------------+
		Row <   paused, ev::pause, playing, none, none		>,
		Row <   paused, ev::close, exit, none, none		>
		//  +------------+-------------+------------+--------------+--------------+
		//Row <   error, ev::errorHandled, playing, none, none     >,
		//Row <   error, ev::close, exit, none, none     >
		//  +------------+-------------+------------+--------------+--------------+*/
	> {};

	typedef mpl::vector<playing, MenuScreen> initial_state;

	// Replaces the default no-transition response.
	template <class FSM, class EVT>
	void no_transition(EVT const&  event, FSM& fsm, int state)
	{
		DEBUG_MSG("no transition from state " << state << " on event " << typeid(event).name());
	}
};
// Pick a back-end
typedef msm::back::state_machine<GameFSM_> GameFSM;
//typedef msm::back::state_machine<GameFSM_, msm::back::mpl_graph_fsm_check> GameFSM;
