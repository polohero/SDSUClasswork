using System;
using System.Collections.Generic;

using Games.Common.Hands;
using Games.Common.Cards;
using Games.Common.Decks;



namespace Games.Common.Engine
{
    /// <summary>
    /// Represents a dealer in blackjack.
    /// </summary>
    public class BlackjackDealer : Dealer
    {
        #region Constructors

        public BlackjackDealer()
        {
            Hand = new BlackjackHand();
        }

        public BlackjackDealer(BlackjackHand hand)
        {
            Hand = hand;
        }

        #endregion

        #region Public Properties

        /// <summary>
        /// The dealers current hand.
        /// </summary>
        public BlackjackHand Hand
        {
            get;
            set;
        }

        #endregion

        #region Public Methods

        /// <summary>
        /// Finishes out the dealers hand after all
        /// the players have completed.
        /// </summary>
        /// <param name="table"></param>
        public void CompleteHand(BlackjackTable table)
        {
            List<TableHistory> dealerHistory =
                new List<TableHistory>(10);

            while (Hand.Value < 17)
            {
                Card card = table.CurrentDeck.Deal();
                Hand.AddCard(card);
                table.AddHistory(
                    String.Format("Dealer takes a {0} ", card.ToString()));
            }
        }

        #endregion
    }
}
