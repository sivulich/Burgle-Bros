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
//FOR and operator  And_<>
#include <boost/msm/front/euml/operator.hpp>
// Check
#include <boost/msm/back/mpl_graph_fsm_check.hpp>

#include <GameModel.h>
#include <GameGraphics.h>
#include <BurgleNetwork.h>
#include <Configs.h>
#include "./events.h"
#include "../../Sound/SoundEffects.h"
namespace msm = boost::msm;
namespace mpl = boost::mpl;
using namespace boost::msm::front;
using namespace euml;

struct GameState_ : public msm::front::state_machine_def<GameState_>
{
	// INICIALIZAR PUNTEROS!
	// FSM variables
	GameModel * model;
	GameGraphics * graphics;
	BurgleNetwork * network;
	int gameMode;
	Timer * guardTimer;
	// Stores current action chosen by player
	action_ID currentAction;

	//-------------------------------------------------------------
	template <class EVT, class FSM>
	void on_entry(EVT const&  event, FSM& fsm)
	{
		DEBUG_MSG("Entering Burgle Bros Finite State Machine");
		fsm.graphics->removeDialogBox();

		if (fsm.model->isLocal())
		{
			fsm.model->setBoard();
			fsm.graphics->showOkMessage("Choose initial position!");
			fsm.graphics->showGameScreen();
		}
		else if (fsm.model->isRemote())
		{
			if (fsm.network->isServer())
				fsm.model->setBoard();	
			// Cord will be random in next state

		}

	}

	template <class EVT, class FSM>
	void on_exit(EVT const&  event, FSM& fsm)
	{
		DEBUG_MSG("Leaving Burgle Bros");
		fsm.graphics->deleteGameScreen();
		if (fsm.model->isRemote())
			fsm.network->sendQuit();
	}

	//----------------------- STATES -----------------------------//


	struct chooseInitialPos : public msm::front::state<>
	{

		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{

			if (fsm.model->isLocal())
			{
				// Set only first floor clickable
				DEBUG_MSG("Choose initial pos: ");
				vector<Coord> v;
				for (int i = 0; i < 4; i++)
					for (int j = 0; j < 4; j++)
						v.push_back(Coord(0, i, j));
				fsm.graphics->setTilesClickable(v);
			}
			else if (fsm.model->isRemote())
			{
				string name = fsm.model->player1()->getName();
				characterType character = fsm.model->player1()->getCharacter();
				Coord initialPos = Coord(0, rand() % 4, rand() % 4);// random initialpos
				cout << "My name " << name << " My character " << character << endl;
				if (fsm.network->isServer())
				{

					pair<Coord, Coord> pos = fsm.model->getInitialGuardPos();
					vector<tileType> tiles = fsm.model->getBoardSetup();
					while (fsm.network->error() == false && fsm.network->startupPhase(name, character, pos.first, pos.second, tiles, initialPos) == false);
					if (fsm.network->error() == true)
						DEBUG_MSG(fsm.network->errMessage());
					else
						DEBUG_MSG("Info exchange ok");
					//fsm.model->setInitialPosition(initialPos);
				}
				else
				{
					while (fsm.network->startupPhase(name, character) == false && fsm.network->error() == false);
					if (fsm.network->error() == true)
						DEBUG_MSG(fsm.network->errMessage());
					else
						DEBUG_MSG("Info exchange ok");


					fsm.model->setBoard(fsm.network->remoteBoard());
					initialPos = fsm.network->startingPos();
					//fsm.model->setInitialPosition(fsm.network->startingPos());
					//DEBUG_MSG("The remote guard info is " << fsm.network->remoteGuardPos() << " " << fsm.network->remoteGuardTarget() );
					fsm.model->initGuard4Network(fsm.network->remoteGuardPos(), fsm.network->remoteGuardTarget());
				}

				// Set other player name
				fsm.model->player2()->setName(fsm.network->remoteName());
				fsm.model->player2()->setCharacter(fsm.network->remoteCharacter());

				if (fsm.network->iStart() == false)
					fsm.model->remotePlayerStarts();
				fsm.graphics->showGameScreen();

				fsm.process_event(ev::coord(initialPos));
			}

		}


		template <class EVT, class FSM>
		typename boost::enable_if<typename has_CoordProp<EVT>::type, void>::type
			on_exit(EVT const&  event, FSM& fsm)
		{
			//Set again all tiles clickable
			//if (fsm.model->otherPlayer()->isRemote())
				//fsm.network->sendQuit();
			fsm.graphics->setAllClickable();
		}

		template <class EVT, class FSM>
		typename boost::disable_if<typename has_CoordProp<EVT>::type, void>::type
			on_exit(EVT const&  event, FSM& fsm)
		{}
	};

	struct chooseAction : public msm::front::state<>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			fsm.graphics->printInHud(string("Choose an action"));
			vector<string> v = fsm.model->currentPlayer()->getActions();

			string actions;
			for (auto& s : v)
				actions = actions + string(" ") + s;
			DEBUG_MSG("Choose action: " + actions);
		}

		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{
			// Set all tiles clickable
			fsm.graphics->setAllClickable();
		}
	};

	struct chooseLoot : public msm::front::state<>
	{
		lootType chosenLoot;

		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			DEBUG_MSG("CHOOSE LOOT");
		}

		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{
			// Desmarcar las tiles 
			fsm.graphics->setAllClickable();
		}
	};

	struct checkActionTokens : public msm::front::state<>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			DEBUG_MSG("CHECK ACTION TOKENS");

			if (fsm.model->gameOver() == true)
				fsm.process_event(ev::gameOver());

			if (fsm.model->currentPlayer()->getActionTokens() == 0 || fsm.model->currentPlayer()->isOnRoof())
				fsm.process_event(ev::no());
			else
			{
				fsm.process_event(ev::yes());
				DEBUG_MSG("Action tokens left: " << fsm.model->currentPlayer()->getActionTokens());
			}

		}
	};

	struct askConfirmation : public msm::front::state<>
	{
		lootType lootToOffer;

		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			DEBUG_MSG("ASK CONFIRMATION");
		}

	};

	struct askConfirmationMove : public msm::front::state<>
	{
		Coord destinationCoord;
		int destinationSafeNumber;
		tileType destinationType;

		template <class EVT, class FSM>
		typename boost::enable_if<typename has_CoordProp<EVT>::type, void>::type
			on_entry(EVT const&  event, FSM& fsm)
		{
			DEBUG_MSG("ASK CONFIRMATION MOVE");
			destinationCoord = event.c;
			destinationSafeNumber = event.safeNumber;

			if (destinationCoord != ROOF)
			{
				Tile * tile = fsm.model->getBoard()->getTile(event.c);
				destinationType = tile->getType();

				if ((fsm.model->currentPlayer()->isLocal())) //&& fsm.model->otherPlayer()->isRemote()))
				{
					confirmation conf = fsm.model->currentPlayer()->needConfirmationToMove(event.c);
					if (tile->is(DEADBOLT))
					{
						if (conf == _ASK)
							fsm.graphics->askQuestion(string("To move to the deadbolt you must spend 3 action tokens. Are you sure?"));
						else if (conf == _CANT_MOVE)
						{
							fsm.graphics->showOkMessage(string("You cant move to the deadbolt! You don't have enough action tokens."));
							fsm.process_event(ev::no());
						}
					}
					else if (tile->is(LASER))
						fsm.graphics->askQuestion(string("Do you want to spend 1 extra action token to enter the laser room? If not you trigger an alarm."));
					else if (tile->is(KEYPAD) && conf == _DICE)
						fsm.process_event(ev::throwDice());

				}
				if (fsm.model->otherPlayer()->isRemote())
				{
					unsigned int safeNumber = fsm.model->getSafeNumber(event.c);
					fsm.network->sendMove(event.c, safeNumber);
					fsm.process_event(ev::waitForNetwork());
				}

			}
		}

		template <class EVT, class FSM>
		typename boost::disable_if<typename has_CoordProp<EVT>::type, void>::type
			on_entry(EVT const&  event, FSM& fsm) {};


		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{
			if (is_same<EVT, ev::yes>::value)
			{
				DEBUG_MSG("Passing coord");
				fsm.process_event(ev::coord(destinationCoord,destinationSafeNumber));
			}
			DEBUG_MSG("Leaving ask confirmation");
		}

	};

	struct beginTurn : public msm::front::state<>
	{

		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			DEBUG_MSG("BEGIN TURN");
			fsm.currentAction = NO_TYPE;
			fsm.graphics->printInHud(fsm.model->currentPlayer()->getName() + string("'s turn."));

			if (fsm.model->currentPlayer()->has(PERSIAN_KITTY) || fsm.model->currentPlayer()->has(CHIHUAHUA))
			{
				if (fsm.model->currentPlayer()->isLocal())
				{
					int dice = fsm.model->currentPlayer()->throwDice();

					if (fsm.model->otherPlayer()->isRemote())
					{
						fsm.network->sendLootDice(dice);
						fsm.process_event(ev::waitForNetwork());
					}
					fsm.process_event(ev::throwDice(dice));

				}
			}

			else fsm.process_event(ev::done());

		}

		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{
			fsm.currentAction = NO_TYPE;

		}
	};

	struct guardTurn : public msm::front::state<>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			// If player isnt on roof start timer to move the guard
			if (fsm.model->currentPlayer()->isOnRoof() == false)
			{
				DEBUG_MSG("GUARD TURN");
				fsm.guardTimer->start();
				//if (fsm.model->otherPlayer()->isRemote());
				//fsm.model->getGuardPath
			}
			// If player is on roof, the guard doesnt move
			else
				fsm.process_event(ev::passGuard());
		}

		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{
			if (fsm.model->currentPlayer()->isOnRoof() == false)
			{
				DEBUG_MSG("LEAVING GUARD TURN");
				fsm.guardTimer->stop();
			}
		}

	};

	struct gameEnded : public msm::front::state<>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			if (is_same<EVT, ev::burglarsWin>::value)
				fsm.graphics->showOkMessage(string("You win!"));
			else if (is_same<EVT, ev::gameOver>::value)
				fsm.graphics->showOkMessage(string("You lose!"));

		}
	};

	struct exitState : public exit_pseudo_state<ev::next>
	{

	};





	struct idle : public msm::front::state<>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			DEBUG_MSG("IDLE...");

		}
	};

	struct waitingForNetwork : public msm::front::interrupt_state<ev::ack>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			DEBUG_MSG("wAITING FOR NETWORK");

		}

		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{
			DEBUG_MSG("ACKNOWLEDGE RECEIVED");

		}
	};


	//----------------------- ACTIONS -----------------------------//

	struct doSetInitialPos
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			DEBUG_MSG("Setting initial position to  " << event.c);
			fsm.model->setInitialPosition(event.c);
		}
	};

	struct doMove
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{

			DEBUG_MSG("Moving to " << event.c.toString());
			fsm.graphics->printInHud(string("Moving to ") + event.c.toString());

			// Esto moverlo a where can I move
			if (event.c.floor == 3 && (fsm.model->currentPlayer()->getLoots().size() + fsm.model->otherPlayer()->getLoots().size()) != fsm.model->lootsToWin())
				fsm.graphics->showOkMessage(string("You can't leave without the loots!"));
			else
			{
				if (fsm.model->currentPlayer()->isRemote())
					fsm.model->getBoard()->getTile(event.c)->setSafeNumber(event.safeNumber);

				fsm.model->currentPlayer()->move(event.c);
				if (fsm.model->win())
					fsm.process_event(ev::burglarsWin());

				// If other player is remote and coming from chooseAction send move
				bool b = is_same<SourceState, chooseAction>::value;
				if (b && fsm.model->otherPlayer()->isRemote())
				{
					unsigned int safeNumber = fsm.model->getBoard()->getTile(event.c)->getSafeNumber();
					fsm.network->sendMove(event.c, safeNumber);
					fsm.process_event(ev::waitForNetwork());
				}
			}


			// If coming from ask confirmation state, the player agreed to spent tokens
			if (is_same<SourceState, askConfirmationMove>::value)
			{
				fsm.model->currentPlayer()->spentOK();
				if (fsm.model->otherPlayer()->isRemote()) {
					fsm.network->sendSpent('Y');
					fsm.process_event(ev::waitForNetwork());
				}
			}


			if (fsm.model->currentPlayer()->getCharacter() != ACROBAT)
				fsm.model->getBoard()->checkOnePlayer(fsm.model->currentPlayer(), fsm.model->currentPlayer()->getPosition().floor);

			fsm.model->check4Cameras();
			// HACER UNA FUNCION POSITION GUARD DEL MODELO
			//fsm.model->getBoard()->getFloor(fsm.model->currentPlayer()->getPosition().floor)->getGuard()->positionGuard();
			fsm.model->positionGuard();
			//COMENTO PARA PROBAR EL ROOF fsm.model->currentPlayer()->gettActions();
			fsm.currentAction = NO_TYPE;
		}
	};

	struct dontMove
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			Tile * destTile = fsm.model->getBoard()->getTile(source.destinationCoord);
			if (destTile->getType() == DEADBOLT || destTile->getType() == KEYPAD)
			{
				fsm.model->currentPlayer()->removeActionToken();
				destTile->turnUp();
			}
			else fsm.model->currentPlayer()->move(source.destinationCoord);

			if (fsm.model->otherPlayer()->isRemote())
			{
				if (destTile->getType() == DEADBOLT || destTile->getType() == LASER)
				{
					fsm.network->sendSpent('N');
					fsm.process_event(ev::waitForNetwork());
				}
				//				else	//KEYPAD
			}
		}
	};

	struct doPeek
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			DEBUG_MSG("Peeking " << event.c.toString());
			fsm.graphics->printInHud(string("Peeking ") + event.c.toString());

			if (fsm.model->currentPlayer()->isRemote())
				fsm.model->getBoard()->getTile(event.c)->setSafeNumber(event.safeNumber);

			
			 fsm.model->currentPlayer()->peek(event.c);
			
			// If other player is remote send peek 
			if (fsm.model->otherPlayer()->isRemote())
			{
				unsigned int safeNumber = fsm.model->getBoard()->getTile(event.c)->getSafeNumber();
				fsm.network->sendPeek(event.c, safeNumber);

				if (fsm.network->error())
					DEBUG_MSG(fsm.network->errMessage());

				fsm.process_event(ev::waitForNetwork());
			}

			fsm.currentAction = NO_TYPE;
		}
	};

	struct doUseToken
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			Coord tokenTile = fsm.model->currentPlayer()->useToken();
			if (tokenTile != NPOS)
			{
				if (fsm.model->otherPlayer()->isRemote())
				{
					DEBUG_MSG("Sending use token to " << fsm.model->otherPlayer()->getName());
					fsm.network->sendUseToken(tokenTile);
					fsm.process_event(ev::waitForNetwork());
				}
			}

		}
	};

	struct doAddToken
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			Coord coord2AddTkn;
			DEBUG_MSG("Adding token");
			coord2AddTkn = fsm.model->currentPlayer()->addToken();
			fsm.currentAction = NO_TYPE;
			if (fsm.model->otherPlayer()->isRemote() && coord2AddTkn != NPOS)
			{
				DEBUG_MSG("Sending add token to " << fsm.model->otherPlayer()->getName());
				fsm.network->sendAddToken(coord2AddTkn);
				fsm.process_event(ev::waitForNetwork());
			}
		}
	};

	struct doThrowDice
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			DEBUG_MSG("Throwing dice");
			//fsm.model->currentPlayer()->throwDice();
			fsm.currentAction = NO_TYPE;
		}
	};

	struct doCrackSafe
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			DEBUG_MSG("CRACKING SAFE");
			fsm.currentAction = SAFE_OPENED;

			Tile * currTile = fsm.model->getBoard()->getTile(fsm.model->currentPlayer()->getPosition());
			bool b = false;

			vector<int> dices;
			// If local sort 6 dices
			if (fsm.model->currentPlayer()->isLocal())
			{
				for (int i = 0; i < 6; i++)
					dices.push_back(fsm.model->currentPlayer()->throwDice());
			}
			// If remote get dices from other computer
			else if (fsm.model->currentPlayer()->isRemote())
				dices = event.dices;

			int currDice = 0;
			while (!((Safe *)currTile)->safeIsOpen())
			{
				if (dices[currDice]==0)
					DEBUG_MSG("A DICE WAS 0!");

				if (fsm.model->currentPlayer()->throwDice(dices[currDice]))// Cant throw more dices or safe crackes
				{
					currDice++;
					vector<int> dicesThrown(dices.begin(), dices.begin() + currDice);
					fsm.graphics->showDices(string("You threw this dices."), dicesThrown);

					// Add remaining zeros
					for (int i = currDice; i < 6; i++)
						dicesThrown.push_back(0);

					if (dicesThrown.size() != 6)
						DEBUG_MSG("DICES ARE MORE THAN 6");

					// Send the dices
					if (fsm.model->otherPlayer()->isRemote())
					{
						vector<int> d = dicesThrown;
						while (fsm.network->join() == false);
						fsm.network->sendThrowDice(d[0],d[1], d[2], d[3], d[4], d[5]);
					}

					if (((Safe *)currTile)->safeIsOpen())
					{
						fsm.model->getBoard()->setSilentAlarm(fsm.model->currentPlayer()->getPosition());

						// Send the SAFE OPENED PACKET
						if (fsm.model->otherPlayer()->isRemote())
						{
							lootType l = ((Safe *)currTile)->getLoot();
							while (fsm.network->join() == false);
							fsm.network->sendSafeOpened(l);
						}

						if (fsm.model->currentPlayer()->isLocal())
							fsm.process_event(ev::loot());
					}
					break;
				}
				currDice++;
			}

		}
	};

	struct setSafeLoot
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			DEBUG_MSG("Set safe loot");
			fsm.currentAction = NO_TYPE;

			if (event.type != NO_LOOT_TYPE)
			{
				Tile * currTile = fsm.model->getBoard()->getTile(fsm.model->currentPlayer()->getPosition());
				((Safe *)currTile)->setLoot(event.type);
			}

			fsm.model->currentPlayer()->getLootFromSafe();

		}
	};

	struct doOpenKeypad
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			DEBUG_MSG("Trying to open Keypad");
			Tile * destTile = fsm.model->getBoard()->getTile(source.destinationCoord);
			if (fsm.model->currentPlayer()->isLocal())
			{
				vector<int> dices;
				while (true)
				{
					int dice = fsm.model->currentPlayer()->throwDice();
					dices.push_back(dice);
					if (((Keypad *)destTile)->tryToOpen(dice, fsm.model->currentPlayer()) == true)// Cant throw more dices or keypad crackes
					{
						if (destTile->canMove(fsm.model->currentPlayer())) //Keypad decodes
						{
							fsm.graphics->showDices(string("You threw a 6 and decoded the keypad! Now you can enter freely."), dices);
							fsm.process_event(ev::yes());
						}
						else
						{
							fsm.graphics->showDices(string("You couldn't decode the keypad!"), dices);
							fsm.process_event(ev::no());
						}
						break;
					}
				}
			}
		}
	};

	struct doCreateAlarm
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			DEBUG_MSG("Creating Alarm");
			bool b = fsm.model->currentPlayer()->createAlarm(event.c);
			if (b)
			{
				if (fsm.model->otherPlayer()->isRemote())
				{
					DEBUG_MSG("Sending create alarm to " << fsm.model->otherPlayer()->getName());
					fsm.network->sendCreateAlarm(event.c);
					fsm.process_event(ev::waitForNetwork());
				}
			}
			else
				DEBUG_MSG("Cant create Alarm!");
			fsm.currentAction = NO_TYPE;
		}
	};

	struct doSpyPatrol
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Spying patrol deck" << std::endl;
			if ((Coord)event.c == NPOS) fsm.graphics->askQuestion("Do you want to keep the card on the top of the deck?");
			else if (event.tb == 'T' || event.tb == 'B')
			{
				fsm.model->getBoard()->getDeck(fsm.model->currentPlayer()->getPosition().floor)->moveCardtoTop(event.c);
				if (event.tb == 'T')
				{
					fsm.process_event(ev::yes());
					//hacer una dialog box avisando que el otro jugador decidió dejar la carta arriba
				}
				else if (event.tb == 'B')
				{
					fsm.process_event(ev::no());
					//hacer una dialog box avisando que el otro jugador decidió bajar la carta
				}
			}
			//else;//ACA HABRIA Q VER DEL ERROR
			fsm.model->spyPatrol(fsm.model->currentPlayer()->getPosition().floor);
			fsm.graphics->spyPatrolCard(fsm.model->currentPlayer()->getPosition().floor);
			fsm.currentAction = SPY_PATROL;
		}
	};

	struct doStayTop
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			Coord topCard;
			DEBUG_MSG("Card staying on top of deck");
			topCard = fsm.model->stopSpying(fsm.model->currentPlayer()->getPosition().floor);
			fsm.graphics->hideTopPatrol(fsm.model->currentPlayer()->getPosition().floor);
			if (fsm.model->otherPlayer()->isRemote() && topCard != NPOS)
			{
				DEBUG_MSG("Sending stay at top, card " << topCard << "to " << fsm.model->otherPlayer()->getName());
				fsm.network->sendSpyPatrol(topCard, 'T');
				fsm.process_event(ev::waitForNetwork());
			}
			fsm.currentAction = NO_TYPE;
		}
	};

	struct doSendBottom
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			Coord movingCard;
			std::cout << "Card  sent to bottom" << std::endl;
			fsm.graphics->hideTopPatrol(fsm.model->currentPlayer()->getPosition().floor);
			movingCard = fsm.model->sendBottom(fsm.model->currentPlayer()->getPosition().floor);
			if (fsm.model->otherPlayer()->isRemote() && movingCard != NPOS)
			{
				DEBUG_MSG("Sending go to bottom, card " << movingCard << "to " << fsm.model->otherPlayer()->getName());
				fsm.network->sendSpyPatrol(movingCard, 'B');
				fsm.process_event(ev::waitForNetwork());
			}
			fsm.currentAction = NO_TYPE;
		}
	};

	struct doPlaceCrow
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			DEBUG_MSG("Placing crow token");
			bool b = fsm.model->currentPlayer()->placeCrow(event.c);
			if (b)
			{
				if (fsm.model->otherPlayer()->isRemote())
				{
					DEBUG_MSG("Sending place crow to " << fsm.model->otherPlayer()->getName());
					fsm.network->sendPlaceCrow(event.c);
					fsm.process_event(ev::waitForNetwork());
				}
			}
			else
				DEBUG_MSG("Cant place crow token!");
			fsm.currentAction = NO_TYPE;
		}
	};

	struct doPickUpLoot
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			DEBUG_MSG("Pick up loot");
			fsm.model->currentPlayer()->pickUpLoot();
			if (fsm.model->otherPlayer()->isRemote())
			{
				DEBUG_MSG("Sending pick up loot to " << fsm.model->otherPlayer()->getName());
				fsm.network->sendPickupLoot();
				fsm.process_event(ev::waitForNetwork());
			}
			fsm.currentAction = NO_TYPE;
		}
	};

	struct  doOfferLoot
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			// Guardo en el estado askConfirmation el loot que quiero ofrecer
			target.lootToOffer = event.type;
			string name = fsm.model->currentPlayer()->getName();
			if (fsm.model->otherPlayer()->isRemote())
			{
				std::cout << "Sending offer loot to " << fsm.model->otherPlayer()->getName() << std::endl;
				fsm.network->sendOfferLoot(target.lootToOffer);
				fsm.process_event(ev::waitForNetwork());
			}
			if (!(fsm.model->currentPlayer()->isLocal() && fsm.model->otherPlayer()->isRemote()))
			{
				fsm.graphics->askQuestion(name + string(" is offering you the ") + string(toString(event.type)) + string(". Do you accept it?"));
			}
		}
	};

	struct doRequestLoot
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			// Guardo en el estado askConfirmation el loot que quiero pedir
			target.lootToOffer = event.type;
			string name = fsm.model->currentPlayer()->getName();
			if (fsm.model->otherPlayer()->isRemote())
			{
				std::cout << "Sending request loot to " << fsm.model->otherPlayer()->getName() << std::endl;
				fsm.network->sendRequestLoot(target.lootToOffer);
				fsm.process_event(ev::waitForNetwork());
			}
			if (!(fsm.model->currentPlayer()->isLocal() && fsm.model->otherPlayer()->isRemote()))
			{
				fsm.graphics->askQuestion(name + string(" is requesting you the ") + string(toString(event.type)) + string(". Do you accept?"));
			}
		}
	};

	struct doGetLoot
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Getting loot " << string(toString(source.lootToOffer)) << " from " << fsm.model->otherPlayer()->getName() << std::endl;
			if (fsm.model->currentPlayer()->isRemote())
			{
				DEBUG_MSG("Sending agree to " << fsm.model->otherPlayer()->getName());
				fsm.network->sendAgree();
				fsm.process_event(ev::waitForNetwork());
			}
			fsm.model->currentPlayer()->receiveLoot(source.lootToOffer);
		}
	};

	struct dontGetLoot
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			if (fsm.model->currentPlayer()->isLocal())
				fsm.graphics->showOkMessage(fsm.model->otherPlayer()->getName() + string(" rejected your request.") );
			if (fsm.model->currentPlayer()->isRemote())
			{
				DEBUG_MSG("Sending disagree to " << fsm.model->otherPlayer()->getName());
				fsm.network->sendDisagree();
				fsm.process_event(ev::waitForNetwork());
			}
		}
	};

	struct doGiveLoot
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Giving loot " << string(toString(source.lootToOffer)) << " to " << fsm.model->otherPlayer()->getName() << std::endl;
			if (fsm.model->currentPlayer()->isRemote())
			{
				DEBUG_MSG("Sending agree to " << fsm.model->otherPlayer()->getName());
				fsm.network->sendAgree();
				fsm.process_event(ev::waitForNetwork());
			}
			fsm.model->currentPlayer()->giveLoot(source.lootToOffer);
		}
	};

	struct dontGiveLoot
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			if (fsm.model->currentPlayer()->isLocal())
				fsm.graphics->showOkMessage(fsm.model->otherPlayer()->getName() + string(" rejected your offer."));
			if (fsm.model->currentPlayer()->isRemote())
			{
				DEBUG_MSG("Sending disagree to " << fsm.model->otherPlayer()->getName());
				fsm.network->sendDisagree();
				fsm.process_event(ev::waitForNetwork());
			}
		}
	};

	struct doEndTurn
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			DEBUG_MSG("Player turn ended");
			fsm.model->endTurn();
			fsm.currentAction = NO_TYPE;

			// If other player is remote send pass 
			if (is_same<EVT, ev::pass>::value && fsm.model->otherPlayer()->isRemote())
			{
				fsm.network->sendPass();
				fsm.process_event(ev::waitForNetwork());
			}
		}
	};

	struct changeTurn
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			if (fsm.model->otherPlayer()->isOnRoof())
			{
				DEBUG_MSG("Keep playing, you are alone!");
			}
			else
			{
				DEBUG_MSG("Changing turns");
				fsm.model->changeTurn();
				fsm.currentAction = NO_TYPE;
			}
		}
	};


	struct doKittyAction
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			vector<int> dices;
			dices.push_back(event.number);
			bool b = false;
			if (fsm.model->currentPlayer()->has(PERSIAN_KITTY) == true)
			{
				b = true;
				if (fsm.model->doKittyAction(event.number))
				{
					if (fsm.model->otherPlayer()->isRemote() || (fsm.model->otherPlayer()->isLocal() && fsm.model->currentPlayer()->isLocal()))
						fsm.graphics->showDices(string("You threw a 1/2. The kitty escaped your grasp."), dices);
					else fsm.graphics->showDices(string("The other player threw a 1,2. The kitty escaped his/her grasp."), dices);
				}
				else
				{
					if (fsm.model->otherPlayer()->isRemote() || (fsm.model->otherPlayer()->isLocal() && fsm.model->currentPlayer()->isLocal()))
						fsm.graphics->showDices(string("You haven't thrown a 1/2, or no alarm tiles where flipped. The kitty remains with you."), dices);
					else fsm.graphics->showDices(string("The other player hasn't thrown a 1/2, or no alarm tiles where flipped. The kitty remains."), dices);
				}
				std::cout << "Sending kitty loot dice to " << fsm.model->otherPlayer()->getName() << std::endl;
			}

			if (fsm.model->currentPlayer()->has(CHIHUAHUA))
			{
				fsm.currentAction = THROW_DICE;
				if (!b) fsm.process_event(ev::throwDice(event.number));
				else
				{
					if (fsm.model->currentPlayer()->isLocal())
					{
						int dice = fsm.model->currentPlayer()->throwDice();
						fsm.process_event(ev::throwDice(dice));

						if (fsm.model->otherPlayer()->isRemote())
						{
							std::cout << "Sending chihuahua loot dice to " << fsm.model->otherPlayer()->getName() << std::endl;
							fsm.network->sendLootDice(dice);
							fsm.process_event(ev::waitForNetwork());
						}
					}
				}
			}
			else
			{
				fsm.currentAction = NO_TYPE;
				fsm.process_event(ev::done());
			}
		}
	};

	struct doChihuahuaAction
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			vector<int> dices;
			dices.push_back(event.number);
			if (fsm.model->doChihuahuaAction(event.number))
			{
				if (fsm.model->otherPlayer()->isRemote() || (fsm.model->otherPlayer()->isLocal() && fsm.model->currentPlayer()->isLocal()))
				{
					fsm.graphics->showDices(string("You threw a 6. The alarm was triggered by the Chihuahua's barks"), dices);
				}
				else fsm.graphics->showDices(string("The other player threw a 6. The alarm was triggered by the Chihuahua's barks"), dices);
			}
			else
			{
				if (fsm.model->otherPlayer()->isRemote() || (fsm.model->otherPlayer()->isLocal() && fsm.model->currentPlayer()->isLocal()))
				{
					fsm.graphics->showDices(string("You didn't throw a 6. You silenced the Chihuahua before the alarm was triggered."), dices);
				}
				else fsm.graphics->showDices(string("The other player didn't throw a 6.The alarm wasn't triggered."), dices);
			}
			fsm.currentAction = NO_TYPE;
			fsm.process_event(ev::done());
		}
	};

	struct moveGuard
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			DEBUG_MSG("Moving guard");
			fsm.model->moveGuard();

			if (fsm.model->gameOver())
				fsm.process_event(ev::gameOver());
			else if (fsm.model->guardIsMoving() == false)
			{
				fsm.process_event(ev::passGuard());
			}
		}
	};

	struct resetGame
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			DEBUG_MSG("Reset game");
		}
	};


	struct showMove
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			fsm.currentAction = MOVE;
			if ((Coord)event.c != NPOS)
				fsm.process_event(ev::coord(event.c, event.safeNumber));
			else
			{
				fsm.graphics->printInHud(string("Choose a tile available to move..."));
				vector<Coord> v = fsm.model->currentPlayer()->whereCanIMove();

				string tiles, space(" ");
				for (auto&c : v)
					tiles += space + c.toString();
				DEBUG_MSG("Tiles availables to move: " + tiles);

				// Distinguir las tiles disponibles para moverse
				fsm.graphics->setTilesClickable(v);
			}

		}
	};

	struct showPeek
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			fsm.currentAction = PEEK;
			if ((Coord)event.c != NPOS)
			{
				fsm.process_event(ev::coord(event.c, event.safeNumber));
				DEBUG_MSG("Safe number in show peek " << event.safeNumber);
			}
			else
			{
				fsm.graphics->printInHud(string("Choose a tile available to peek..."));
				vector<Coord> v = fsm.model->currentPlayer()->whereCanIPeek();

				string tiles, space(" ");
				for (auto&c : v)
					tiles += space + c.toString();
				DEBUG_MSG("Tiles availables to peek: " + tiles);


				// Distinguir las tiles disponibles para moverse
				fsm.graphics->setTilesClickable(v);
			}

		}
	};

	struct showAlarm
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			fsm.currentAction = CREATE_ALARM;
			if ((Coord)event.c != NPOS)
				fsm.process_event(ev::coord(event.c));
			else
			{
				vector<Coord> v = fsm.model->currentPlayer()->getAdjacentJuicer();
				// Distinguir las tiles disponibles para crear la alarma
				fsm.graphics->setTilesClickable(v);

				string tiles, space(" ");
				for (auto&c : v)
					tiles += space + c.toString();
				DEBUG_MSG("Alarm can be created on the following tiles: " + tiles);
			}

		}
	};

	struct showCrow
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			fsm.currentAction = PLACE_CROW;
			if ((Coord)event.c != NPOS)
				fsm.process_event(ev::coord(event.c));
			else
			{
				vector<Coord> v = fsm.model->getTilesXDist(2, fsm.model->currentPlayer());
				// Distinguir las tiles disponibles para poner el Crow token
				fsm.graphics->setTilesClickable(v);


				string tiles, space(" ");
				for (auto& c : v)
					tiles += space + c.toString();
				DEBUG_MSG("Crow token can placed in following tiles: " + tiles);
			}

		}
	};

	struct showOfferLoot
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			DEBUG_MSG("Preparing to offer loot: ");
			fsm.currentAction = OFFER_LOOT;
			if (fsm.model->currentPlayer()->isLocal())
				fsm.graphics->showAvailableLoots(string("Choose the loot you want to offer:"), fsm.model->currentPlayer()->getAvailableLoots());
			else if (fsm.model->currentPlayer()->isRemote())
				fsm.process_event(ev::loot(event.type));
		}
	};

	struct prepRequest
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			fsm.currentAction = REQUEST_LOOT;
			DEBUG_MSG("Preparing to request loot: ");
			if (fsm.model->currentPlayer()->isLocal())
				fsm.graphics->showAvailableLoots(string("Choose the loot you want to request:"), fsm.model->otherPlayer()->getAvailableLoots());
			else if (fsm.model->currentPlayer()->isRemote())
				fsm.process_event(ev::loot(event.type));
		}
	};

	struct showEndMessage
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			if (is_same<EVT, ev::burglarsWin>::value)
				fsm.graphics->showOkMessage(string("You win!"));
			else if (is_same<EVT, ev::gameOver>::value)
				fsm.graphics->showOkMessage(string("Yow loose"));
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

	struct needsConfirmation
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		bool operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			return fsm.model->currentPlayer()->needConfirmationToMove(event.c) != _MOVE;
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

	struct isCreatingAlarm
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		bool operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			return fsm.currentAction == CREATE_ALARM;
		}
	};

	struct isSpying
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		bool operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			return fsm.currentAction == SPY_PATROL;
		}
	};

	struct isPlacingCrow
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		bool operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			return fsm.currentAction == PLACE_CROW;
		}
	};

	struct isAddingToken
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		bool operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			return fsm.currentAction == ADD_TOKEN;
		}
	};

	struct isThrowingDice
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		bool operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			return fsm.currentAction == THROW_DICE;
		}
	};

	struct isThrowing4Kitty
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		bool operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			return (fsm.currentAction == NO_TYPE);
		}
	};

	struct isThrowing4Chihuahua
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		bool operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			return (fsm.currentAction == THROW_DICE);
		}
	};

	struct isCrackingSafe
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		bool operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			return fsm.currentAction == SAFE_OPENED;
		}
	};

	struct isPickingLoot
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		bool operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			return fsm.currentAction == PICK_UP_LOOT;
		}
	};

	struct isOfferingLoot
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		bool operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			return fsm.currentAction == OFFER_LOOT;
		}
	};

	struct isRequestingLoot
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		bool operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			return fsm.currentAction == REQUEST_LOOT;
		}
	};

	struct gameIsRemote
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		bool operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			return fsm.model->isRemote();
		}
	};

	struct gameIsLocal
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		bool operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			return !fsm.model->isRemote();
		}
	};

	struct playerIsLocal
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		bool operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			return fsm.model->currentPlayer()->isLocal() == true;
		}
	};

	struct playerIsRemote
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		bool operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			return fsm.model->currentPlayer()->isLocal() == false;
		}
	};


	// Transition table
	struct transition_table : mpl::vector<
		//       Start		    Event			Next		Action            Guard
		//  +-----------+------------------+--------------+--------------+-----------------+-----------+

		Row < chooseInitialPos, ev::coord, chooseAction, doSetInitialPos, none				>,

		Row < chooseAction, ev::pass, guardTurn, doEndTurn, none				>,

		Row < chooseAction, ev::move, none, showMove, none				>,
		Row < chooseAction, ev::coord, checkActionTokens, doMove, And_<isMoving, Not_<needsConfirmation>>	>,
		Row < chooseAction, ev::coord, askConfirmationMove, none, And_<isMoving, needsConfirmation>			>,


		Row < chooseAction, ev::peek, none, showPeek, none				>,
		Row < chooseAction, ev::coord, checkActionTokens, doPeek, isPeeking			>,

		Row	< chooseAction, ev::createAlarm, none, showAlarm, none				>,
		Row	< chooseAction, ev::coord, checkActionTokens, doCreateAlarm, isCreatingAlarm   >,

		Row < chooseAction, ev::placeCrow, none, showCrow, none				>,
		Row	< chooseAction, ev::coord, chooseAction, doPlaceCrow, isPlacingCrow		>,

		Row < chooseAction, ev::throwDice, none, doCrackSafe, none				>,
		Row < chooseAction, ev::loot, checkActionTokens, setSafeLoot, isCrackingSafe			>,

		Row < chooseAction, ev::spyPatrol, askConfirmation, doSpyPatrol, none				>,
		Row < chooseAction, ev::addToken, checkActionTokens, doAddToken, none				>,
		Row < chooseAction, ev::useToken, chooseAction, doUseToken, none				>,
		Row < chooseAction, ev::offerLoot, chooseLoot, showOfferLoot, none				>,
		Row < chooseAction, ev::requestLoot, chooseLoot, prepRequest, none				>,
		Row < chooseAction, ev::pickUpLoot, chooseAction, doPickUpLoot, none				>,

		//  +------------+-------------+------------+--------------+--------------+
		Row < askConfirmation, ev::yes, checkActionTokens, doStayTop, isSpying			>,
		Row < askConfirmation, ev::no, checkActionTokens, doSendBottom, isSpying			>,
		Row < askConfirmation, ev::yes, chooseAction, doGiveLoot, isOfferingLoot	>,
		Row < askConfirmation, ev::no, chooseAction, dontGiveLoot, isOfferingLoot	>,
		Row < askConfirmation, ev::yes, chooseAction, doGetLoot, isRequestingLoot	>,
		Row < askConfirmation, ev::no, chooseAction, dontGetLoot, isRequestingLoot	>,
		//  +------------+-------------+------------+--------------+--------------+
		Row < askConfirmationMove, ev::yes, askConfirmationMove, none, none			>,
		Row < askConfirmationMove, ev::no, checkActionTokens, dontMove, none >,
		Row < askConfirmationMove, ev::coord, checkActionTokens, doMove, none			>,
		Row < askConfirmationMove, ev::throwDice, none, doOpenKeypad, none	>,

		//  +------------+-------------+------------+--------------+--------------+

		Row < chooseLoot, ev::loot, askConfirmation, doOfferLoot, isOfferingLoot	>,
		Row < chooseLoot, ev::loot, askConfirmation, doRequestLoot, isRequestingLoot	>,
		Row < chooseLoot, ev::cancel, chooseAction, none, none	>,
		//  +------------+-------------+------------+--------------+--------------+
		Row < checkActionTokens, ev::no, guardTurn, doEndTurn, none				>,
		Row < checkActionTokens, ev::yes, chooseAction, none, none				>,
		Row < checkActionTokens, ev::gameOver, gameEnded, none, none				>,
		Row < checkActionTokens, ev::burglarsWin, gameEnded, none, none				>,

		//  +------------+-------------+------------+--------------+--------------+
		Row < guardTurn, ev::moveGuard, none, moveGuard, none				>,
		Row < guardTurn, ev::passGuard, beginTurn, changeTurn, none				>,
		Row < guardTurn, ev::gameOver, gameEnded, none, none				>,
		//  +------------+-------------+------------+--------------+--------------+f
		Row < beginTurn, ev::done, chooseAction, none, none				>,
		Row < beginTurn, ev::throwDice, none, doKittyAction, isThrowing4Kitty	>,
		Row < beginTurn, ev::throwDice, none, doChihuahuaAction, isThrowing4Chihuahua	>,
		//  +------------+-------------+------------+--------------+--------------+
		Row < gameEnded, ev::playAgain, chooseAction, resetGame, none				>,
		Row < gameEnded, ev::ok, exitState, none, none				>
		//  +------------+-------------+------------+--------------+--------------+

		//Row < idle, ev::waitForNetwork, waitingForNetwork, none, none>,
		//Row < waitingForNetwork, ev::ack, idle, none, none			>

	> {};

	// Replaces the default no-transition response.
	template <class FSM, class EVT>
	void no_transition(EVT const&  event, FSM& fsm, int state)
	{
		DEBUG_MSG("no transition from state " << state << " on event " << typeid(event).name());
	}

	typedef mpl::vector<idle, chooseInitialPos> initial_state;
	//typedef chooseInitialPos initial_state;

};
// Pick a back-end
typedef msm::back::state_machine<GameState_> GameState;
//typedef msm::back::state_machine<GameState_, msm::back::mpl_graph_fsm_check> GameState;
