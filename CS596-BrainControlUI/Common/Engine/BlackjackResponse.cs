using System;



namespace Games.Common.Engine
{
    public sealed class BlackjackResponse
    {
        BlackjackResponse()
        {

        }

        public BlackjackResponse(
            BlackjackTable table,
            BlackjackResult result,
            string message = "")
        {
            Table = table;
            Result = result;
            Message = message;
        }

        /// <summary>
        /// The current state of the table.
        /// </summary>
        public BlackjackTable Table
        {
            get;
            set;
        }

        /// <summary>
        /// The result for the response.
        /// </summary>
        public BlackjackResult Result
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
