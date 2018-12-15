using System;



namespace Games.Common.Engine
{
    public sealed class BlackjackRequest
    {
        BlackjackRequest()
        {

        }

        public BlackjackRequest(
            Player player,
            BlackjackAction action,
            BlackjackTable table,
            string message = "")
        {
            Player = player;
            Action = action;
            Table = table;
            Message = message;
        }

        public BlackjackTable Table
        {
            get;
            set;
        }

        public Player Player
        {
            get;
            set;
        }

        public BlackjackAction Action
        {
            get;
            set;
        }

        public string Message
        {
            get;
            set;
        }
    }
}
