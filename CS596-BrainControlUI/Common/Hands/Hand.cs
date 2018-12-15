using System;
using System.Text;
using System.Collections.Generic;
using System.Runtime.Serialization;

using Games.Common.Cards;



namespace Games.Common.Hands
{
    /// <summary>
    /// Hand is a container class that holds a list of cards.
    /// </summary>
    [KnownType(typeof(BlackjackHand))]
    public class Hand : CardCollection, IComparable<Hand>
    {
        #region Constructors

        /// <summary>
        /// Creates a new hand based on an array of cards.
        /// </summary>
        /// <param name="cards"></param>
        public Hand(IEnumerable<Card> cards) : base(cards)
        {

        }

        /// <summary>
        /// Creates a new empty hand.
        /// </summary>
        public Hand() :  base()
        {

        }

        #endregion

        #region Public Properties

        public new void Clear()
        {
            Cards.Clear();
        }

        public int Count
        {
            get
            {
                return Cards.Count;
            }
        }

        public new List<Card> Cards
        {
            get
            {
                return base.Cards;
            }
        }


        /// <summary>
        /// Returns the value of the hand.
        /// </summary>
        public virtual int Value
        {
            get
            {
                return value();
            }
        }

        #endregion

        #region Public Methods

        public void AddCard(Card card)
        {
            Add(card);
        }

        /// <summary>
        /// Compares 2 hands.
        /// </summary>
        /// <param name="other">The other hand to compare to.</param>
        /// <returns></returns>
        public int CompareTo(Hand other)
        {
            const int NULLED = -1;

            if (null == other)
            {
                return NULLED;
            }

            return Value.CompareTo(other.Value);
        }

        /// <summary>
        /// Compares if 2 hands are equal.
        /// </summary>
        /// <param name="obj"></param>
        /// <returns></returns>
        public override bool Equals(object obj)
        {
            const int SAME = 0;

            if (null == obj)
            {
                return false;
            }
            if (false == (obj is Hand))
            {
                return false;
            }

            return SAME == CompareTo((Hand)obj);
        }

        /// <summary>
        /// Returns a hash for the hand.
        /// </summary>
        /// <returns></returns>
        public override int GetHashCode()
        {
            return Value;
        }

        /// <summary>
        /// Returns a string represenation of the Hand.
        /// </summary>
        /// <returns></returns>
        public override string ToString()
        {
            StringBuilder sb = new StringBuilder();

            sb.AppendLine("Value: " + Value);

            foreach (Card card in Cards)
            {
                sb.AppendLine(card.ToString());
            }

            return sb.ToString();
        }

        #endregion

        #region Private Methods


        /// <summary>
        /// Iterates through all the cards and returns the
        /// symbol value sum.
        /// </summary>
        /// <returns></returns>
        private int value()
        {
            int sum = 0;

            foreach (Card card in Cards)
            {
                sum += card.Value;
            }

            return sum;
        }

        #endregion
    }
}
