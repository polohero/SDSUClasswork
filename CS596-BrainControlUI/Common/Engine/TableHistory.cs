using System;



namespace Games.Common.Engine
{
    /// <summary>
    /// A class that represents a time
    /// and message for the history of a 
    /// user.
    /// </summary>
    public class TableHistory
    {
        TableHistory() { }

        public TableHistory(
            string message,
            DateTime time)
        {
            Message = message;
            Time = time;
        }

        /// <summary>
        /// The message of the history.
        /// </summary>
        public string Message
        {
            get;
            set;
        }

        /// <summary>
        /// The date time the table history
        /// occurred.
        /// </summary>
        public DateTime Time
        {
            get;
            set;
        }

        public override string ToString()
        {
            return String.Format("{0} {1}", Time.ToLongTimeString(), Message);
        }
    }
}
