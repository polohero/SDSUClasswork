using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Games.Common.Decks;
using Games.Common.Cards;
using Games.Common.Hands;



namespace Games.Common.Engine
{
    public class BlackjackEngine
    {
        #region Constructors

        public BlackjackEngine()
        {
            _tables = new TableCollection();
        }

        #endregion

        #region Public Methods

        /// <summary>
        /// Handles any incoming requests for the blackjack Engine.
        /// </summary>
        /// <param name="request"></param>
        /// <returns></returns>
        public BlackjackResponse Process(BlackjackRequest request)
        {
            validateRequest(request);

            switch (request.Action)
            {
                case BlackjackAction.JoinTable:
                    return processJoin(request);
                case BlackjackAction.Start:
                    return processStart(request);
                case BlackjackAction.Hit:
                    return processHit(request);
                case BlackjackAction.Stay:
                    return processStay(request);
                case BlackjackAction.Get:
                    return processGet(request);
                case BlackjackAction.LeaveTable:
                    return processLeaveTable(request);
                case BlackjackAction.Chat:
                    return processChat(request);
                default:
                    throw new Exception(
                        "Unknown action type. " +
                        request.Action.ToString());
            }
        }

        #endregion

        #region Private Methods

        /// <summary>
        /// Returns all the current table information.
        /// </summary>
        /// <param name="request"></param>
        /// <returns></returns>
        private BlackjackResponse processChat(BlackjackRequest request)
        {
            BlackjackTable table = (BlackjackTable)_tables.Get(request.Table.ID);
            if (null == table)
            {
                throw new Exception(
                    "Cannot perform action. Table does not exist.");
            }

            BlackjackPlayer player = (BlackjackPlayer)table.Get(request.Player);
            if (null == player)
            {
                throw new Exception(
                    "Cannot perform action. Player does not exist at table.");
            }

            table.AddHistory(player.Name + ": " + request.Message);

            return new BlackjackResponse(
                table,
                BlackjackResult.Success);
            
        }

        /// <summary>
        /// Returns all the current table information.
        /// </summary>
        /// <param name="request"></param>
        /// <returns></returns>
        private BlackjackResponse processGet(BlackjackRequest request)
        {
            BlackjackTable table = (BlackjackTable)_tables.Get(request.Table.ID);
            if (null == table)
            {
                throw new Exception(
                    "Cannot perform action. Table does not exist.");
            }

            BlackjackPlayer player = (BlackjackPlayer)table.Get(request.Player);
            if (null == player)
            {
                throw new Exception(
                    "Cannot perform action. Player does not exist at table.");
            }

            return new BlackjackResponse(
                table,
                BlackjackResult.Success);
        }

        /// <summary>
        /// Evaluates all the current hands against the dealer.
        /// </summary>
        /// <param name="request"></param>
        /// <returns></returns>
        private BlackjackResponse processEvaluate(BlackjackRequest request)
        {
            BlackjackTable table = (BlackjackTable)_tables.Get(request.Table);

            if (null == table)
            {
                throw new Exception(
                    "Cannot perform action. Table does not exist.");
            }

            if (table.State != TableState.Started)
            {
                throw new Exception(
                    "Cannot perform action. Table has not started.");
            }

            table.Stop();

            return new BlackjackResponse(
                table,
                BlackjackResult.Success);
        }

        /// <summary>
        /// Processes a join action for the engine.
        /// </summary>
        /// <param name="request"></param>
        /// <returns></returns>
        private BlackjackResponse processJoin(BlackjackRequest request)
        {
            BlackjackTable table = (BlackjackTable)_tables.Get(request.Table);

            // If the table is not there. Create it.
            if (null == table)
            {
                table = new BlackjackTable(
                    request.Table.ID,
                    request.Table.Name,
                    // TODO: Future enhancement would be to deal with
                    // multiple decks. Currently we will just re-shuffle 
                    // after every hand.
                    Deck.Create(),
                    request.Player);
            }

            // If the table already contains that player
            // they cannot come through again.
            if (true == table.Contains(request.Player))
            {
                throw new Exception(
                    "Player " +
                    request.Player.Name +
                    " already exists at the table");
            }

            table.Add(request.Player);
            table.AddHistory("Player " + request.Player.Name + " added to table.");

            _tables.AddOrUpdate(table);

            return new BlackjackResponse(
                table,
                BlackjackResult.Success);
        }

        /// <summary>
        /// Processes a start action 
        /// </summary>
        /// <param name="request"></param>
        /// <returns></returns>
        private BlackjackResponse processStart(BlackjackRequest request)
        {
            BlackjackTable table = (BlackjackTable)_tables.Get(request.Table);

            if (null == table)
            {
                throw new Exception(
                    "Cannot start table. Table does not exist.");
            }

            if (table.State == TableState.Started)
            {
                throw new Exception(
                    "Cannot start table. Table is already started.");
            }

            table.Start();
            table.AddHistory("Starting game.");
  
            return new BlackjackResponse(
                table,
                BlackjackResult.Success);
        }

        /// <summary>
        /// Processes a hit request.
        /// </summary>
        /// <param name="request"></param>
        /// <returns></returns>
        private BlackjackResponse processHit(BlackjackRequest request)
        {
            BlackjackTable table = (BlackjackTable)_tables.Get(request.Table);
            if (null == table)
            {
                throw new Exception(
                    "Cannot perform action. Table does not exist.");
            }

            BlackjackPlayer player = (BlackjackPlayer)table.Get(request.Player);
            if (null == player)
            {
                throw new Exception(
                    "Cannot perform action. Player does not exist at table.");
            }

            if (table.State != TableState.Started)
            {
                throw new Exception(
                    "Cannot perform action. Table has not started.");
            }

            if (player.State != PlayerStateEnum.Turn)
            {
                throw new Exception("It is not " + player.Name + " turn.");
            }

            Card card = table.CurrentDeck.Deal();
            player.Hand.AddCard(card);
            table.AddHistory(
                "Player " + player.Name + " drew a " + card);

            BlackjackResponse response = null;

            if (true == player.Hand.IsBusted)
            {
                table.AddHistory(
                    "Player " + player.Name + " busted.");

                if (true == table.IsLastPlayer)
                {
                    response = processEvaluate(request);
                }
                else
                {
                    table.NextPlayer();

                    response = new BlackjackResponse(
                        table,
                        BlackjackResult.Busted);
                }
            }
            else
            {
                response = new BlackjackResponse(
                    table,
                    BlackjackResult.Success);
            }

            return response;
        }

        private BlackjackResponse processLeaveTable(BlackjackRequest request)
        {
            BlackjackTable table = (BlackjackTable)_tables.Get(request.Table);
            if (null == table)
            {
                throw new Exception(
                    "Cannot perform action. Table does not exist.");
            }

            BlackjackPlayer player = (BlackjackPlayer)table.Get(request.Player);
            if (null == player)
            {
                throw new Exception(
                    "Cannot perform action. Player does not exist at table.");
            }
            if (table.State == TableState.Started)
            {
                throw new Exception(
                    "Cannot perform action. Game has started. Finish the game first.");
            }

            table.Remove(player);
            table.AddHistory(player + " has left the table.");
            if (null != table.Owner)
            {
                table.AddHistory(table.Owner + " is the new owner of the table.");
            }
            else
            {
                _tables.Remove(table);
            }

            return new BlackjackResponse(
                table,
                BlackjackResult.Success);
        }

        /// <summary>
        /// Processes a stay request.
        /// </summary>
        /// <param name="request"></param>
        /// <returns></returns>
        private BlackjackResponse processStay(BlackjackRequest request)
        {
            BlackjackTable table = (BlackjackTable)_tables.Get(request.Table);
            if (null == table)
            {
                throw new Exception(
                    "Cannot perform action. Table does not exist.");
            }

            BlackjackPlayer player = (BlackjackPlayer)table.Get(request.Player);
            if (null == player)
            {
                throw new Exception(
                    "Cannot perform action. Player does not exist at table.");
            }

            if (table.State != TableState.Started)
            {
                throw new Exception(
                    "Cannot perform action. Table has not started.");
            }

            if (player.State != PlayerStateEnum.Turn)
            {
                throw new Exception("It is not " + player.Name + " turn.");
            }

            table.AddHistory(
                    "Player " + player.Name + " stays.");
            
            BlackjackResponse response = null;

            if (true == table.IsLastPlayer)
            {
                response = processEvaluate(request);
            }
            else
            {
                table.NextPlayer();

                response = new BlackjackResponse(
                   table,
                   BlackjackResult.Success);
            }

            return response;
        }

        private void validateRequest(BlackjackRequest request)
        {
            if (null == request)
            {
                throw new ArgumentNullException(
                    "Request cannot be NULL.");
            }

            if (null == request.Player)
            {
                throw new ArgumentNullException(
                    "Player cannot be NULL.");
            }
            if (true == string.IsNullOrEmpty(request.Player.Name))
            {
                throw new ArgumentNullException(
                    "Player name cannot be NULL or empty.");
            }
            if (null == request.Table)
            {
                throw new ArgumentNullException(
                    "Table cannot be null.");
            }
            if (true == string.IsNullOrEmpty(request.Table.ID))
            {
                throw new ArgumentNullException(
                    "Table ID cannot be NULL or empty.");
            }
        }

        #endregion

        #region Private Attributes

        private TableCollection _tables;

        #endregion
    }
}
