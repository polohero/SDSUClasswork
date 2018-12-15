using System;
using System.Collections.Generic;

using Games.Common.Cards;



namespace Games.Common.Hands
{
    /// <summary>
    /// A specific type of hand for blackjack.
    /// </summary>
    public class BlackjackHand : Hand
    {
        #region Constructors

        public BlackjackHand(IEnumerable<Card> cards)
            : base(cards)
        {

        }

        public BlackjackHand() 
            : base()
        {

        }

        #endregion

        #region Public Properties

        public int MAX_VALUE = 21;

        /// <summary>
        /// Returns the value of the blackjack hand.
        /// </summary>
        public override int Value
        {
            get
            {
                return value();
            }
        }

        /// <summary>
        /// Returns whether or not the hand has busted
        /// IE, gone over the max value.
        /// </summary>
        public bool IsBusted
        {
            get
            {
                return Value > MAX_VALUE;
            }
        }


        #endregion

        #region Private Methods

        /// <summary>
        /// Calculates the value of the blackjack hand.
        /// </summary>
        /// <returns></returns>
        private int value()
        {
            const int FACE_CARD_VALUE = 10;
            const int ACE_ONE = 1;
            const int ACE_ELEVEN = 11;

            int value = 0;

            // First add up all the non-ace cards.
            // If the card is a face card it has
            // it's own value.
            foreach (Card card in Cards)
            {
                if (false == card.IsAce)
                {
                    value += card.IsFaceCard 
                        ? FACE_CARD_VALUE 
                        : card.Value;
                }
            }

            // Then add the aces.
            // If the Ace puts it over the max value
            // then we should use 1, otherwise use
            // 11.
            foreach (Card card in Cards)
            {
                if (true == card.IsAce)
                {
                    value += (value + ACE_ELEVEN) > MAX_VALUE
                        ? ACE_ONE
                        : ACE_ELEVEN;
                }
            }

            return value;
        }

        #endregion

    }
}
