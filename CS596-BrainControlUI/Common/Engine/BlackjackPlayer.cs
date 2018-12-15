using System;
using System.Collections.Generic;

using Games.Common.Cards;
using Games.Common.Hands;



namespace Games.Common.Engine
{
    public class BlackjackPlayer : Player
    {
        #region Constructor

        BlackjackPlayer() { }

        public BlackjackPlayer(
            string name)
            : base(name)
        {
            Hand = new BlackjackHand();
        }

        public BlackjackPlayer(
            string name,
            BlackjackHand hand) : base(name)
        {
            Hand = hand;
        }

        #endregion

        #region Public Properties

        /// <summary>
        /// The current hand for the blackjack player.
        /// </summary>
        public BlackjackHand Hand
        {
            get;
            set;
        }

        #endregion
    }
}
