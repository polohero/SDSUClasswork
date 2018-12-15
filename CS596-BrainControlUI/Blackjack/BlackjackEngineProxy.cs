using System;
using System.IO;
using System.ServiceModel;
using System.Collections.Generic;
using System.Runtime.Serialization;

using Games.Common.Cards;
using Games.Common.Decks;
using Games.Common.Hands;
using Games.Common.Engine;
using Games.Common.WCF;



namespace Games.BlackjackClient
{
    public class BlackjackEngineProxy 
    {
        private BlackjackResponse send(BlackjackRequest request)
        {
            // If the client is configured for single player mode,
            // just call the enginer directly.
            if (true == Config.SinglePlayerMode)
            {
                return _singlePlayerEngine.Process(request);
            }

            GameEngineProxy proxy =
                new GameEngineProxy();
           
            try
            {
                proxy.Open();

                return proxy.Process(request);
            }
            finally
            {
                if (proxy != null &&
                    proxy.State == CommunicationState.Opened)
                {
                    proxy.Close();
                }
            }
        }

        public BlackjackResponse LeaveTable(
            BlackjackTable table,
            BlackjackPlayer player)
        {
            return send(new BlackjackRequest(player, BlackjackAction.LeaveTable, table));
        }

        public BlackjackResponse Chat(
            BlackjackTable table,
            BlackjackPlayer player,
            string message)
        {
            return send(new BlackjackRequest(player, BlackjackAction.Chat, table, message));
        }

        public BlackjackResponse Get(
            BlackjackTable table,
            BlackjackPlayer player)
        {
            return send(new BlackjackRequest(player, BlackjackAction.Get, table));
        }

        public BlackjackResponse Join(BlackjackTable table,
            BlackjackPlayer player)
        {
            return send(new BlackjackRequest(player, BlackjackAction.JoinTable, table));
        }

        public BlackjackResponse Start(BlackjackTable table,
            BlackjackPlayer player)
        {
            return send(new BlackjackRequest(player, BlackjackAction.Start, table));
        }

        public BlackjackResponse Hit(BlackjackTable table,
            BlackjackPlayer player)
        {
            return send(new BlackjackRequest(player, BlackjackAction.Hit, table));
        }

        public BlackjackResponse Stay(BlackjackTable table,
            BlackjackPlayer player)
        {
            return send(new BlackjackRequest(player, BlackjackAction.Stay, table));
        }

        public BlackjackResponse Evaluate(BlackjackTable table,
            BlackjackPlayer player)
        {
            return send(new BlackjackRequest(player, BlackjackAction.Evaluate, table));
        }


        private static BlackjackEngine _singlePlayerEngine = new BlackjackEngine();
    }
}
