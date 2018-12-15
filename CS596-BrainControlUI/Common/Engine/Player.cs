using System;
using System.ServiceModel;
using System.Runtime.Serialization;



namespace Games.Common.Engine
{
    /// <summary>
    /// Represents a player sitting at a table.
    /// </summary>
    [KnownType(typeof(BlackjackPlayer))]
    public class Player
    {
        #region Constructors

        public Player() { }

        /// <summary>
        /// Constructor to create a player.
        /// </summary>
        /// <param name="id">The ID of the player</param>
        /// <param name="name">The name of the player.</param>
        public Player(string name)
        {
            Name = name;
            State = PlayerStateEnum.Waiting;
        }

        #endregion

        #region Public Properties

        /// <summary>
        ///  The name of the player.
        /// </summary>
        public string Name
        {
            get;
            set;
        }

        public PlayerStateEnum State
        {
            get;
            set;
        }

        #endregion

        #region Public Methods

        public override bool Equals(object obj)
        {
            if (null == obj)
            {
                return false;
            }

            if (false == (obj is Player))
            {
                return false;
            }

            Player other =
                (Player)obj;

            return other.Name == Name;
        }

        public override int GetHashCode()
        {
            return Name.GetHashCode();
        }

        public override string ToString()
        {
            return Name;
        }

        #endregion
    }
}
