using System;
using System.Runtime.Serialization;
using System.Collections.Generic;



namespace Games.Common.Engine
{
    /// <summary>
    /// A specifc table that contains a list of 
    /// players.
    /// </summary>
    public class Table
    {
        #region Contructors

        public Table() { }

        public Table(
            string id, 
            string name, 
            GameTypeEnum gameType,
            Player owner)
        {
            const int INITIAL_CAPACITY = 10;
            Players = new List<Player>(INITIAL_CAPACITY);
            History = new List<TableHistory>(INITIAL_CAPACITY);
            ID = id;
            Name = name;
            GameType = gameType;
            Owner = owner;
            State = TableState.Waiting;
        }

        #endregion

        #region Public Properties

        public Player Owner
        {
            get;
            set;
        }

        public TableState State
        {
            get;
            set;
        }

        /// <summary>
        /// History of the current game.
        /// </summary>
        public List<TableHistory> History
        {
            get;
            set;
        }

        /// <summary>
        /// The ID of the table.
        /// </summary>
        public string ID
        {
            get;
            set;
        }

        /// <summary>
        /// The name of the table.
        /// </summary>
        public string Name
        {
            get;
            set;
        }

        /// <summary>
        /// The type of the game.
        /// </summary>
        public GameTypeEnum GameType
        {
            get;
            set;
        }

        /// <summary>
        /// The players currently at the table.
        /// </summary>
        public List<Player> Players
        {
            get;
            set;
        }

        #endregion

        #region Public Methods

        public virtual void Start()
        {
            State = TableState.Started;
        }

        public virtual void Stop()
        {
            State = TableState.Stopped;
        }

        public Player Get(Player player)
        {
            validate(player);

            return get(player);
        }

        public void Remove(Player player)
        {
            validate(player);

            remove(player);

            if (Players.Count > 0)
            {
                Owner = Players[0];
            }
            else
            {
                Owner = null;
            }
        }

        /// <summary>
        /// Checks if a player already exists on a table.
        /// </summary>
        /// <param name="player"></param>
        /// <returns></returns>
        public bool Contains(Player player)
        {
            validate(player);
            return contains(player);
        }

        /// <summary>
        /// Adds a player to the collection.
        /// </summary>
        /// <param name="card"></param>
        public void Add(Player player)
        {
            validate(player);
            add(player);
        }

        public void AddHistory(string message)
        {
            History.Add(
                new TableHistory(
                    message,
                    DateTime.Now));
        }

        #endregion

        #region Private Methods

        private bool contains(Player player)
        {
            foreach (Player currentPlayer in Players)
            {
                if (currentPlayer.Equals(player))
                {
                    return true;
                }
            }

            return false;
        }

        private Player get(Player player)
        {
            foreach (Player currentPlayer in Players)
            {
                if (currentPlayer.Equals(player))
                {
                    return currentPlayer;
                }
            }

            return null;
        }

        /// <summary>
        /// Loops through the cards and removes the
        /// specific player.
        /// </summary>
        /// <param name="card"></param>
        private void remove(Player player)
        {
            for (int i = Players.Count - 1; i >= 0; i--)
            {
                Player current = Players[i];
                if (true == current.Equals(player))
                {
                    Players.RemoveAt(i);
                }
            }
        }

        /// <summary>
        /// Validates a card is allowed for an operation.
        /// </summary>
        /// <param name="card"></param>
        private void validate(Player player)
        {
            if (null == player)
            {
                throw new ArgumentNullException(
                    "A Player cannot be NULL.");
            }
        }

        /// <summary>
        /// Adds a new card to the collection.
        /// </summary>
        /// <param name="card"></param>
        private void add(Player player)
        {
            Players.Add(player);
        }

        #endregion
    }
}
