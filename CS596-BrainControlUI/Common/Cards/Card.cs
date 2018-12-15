using System;
using System.Runtime.Serialization;



namespace Games.Common.Cards
{
    public class Card : IComparable<Card>
    {
        #region Constructors

        public Card() { }

        /// <summary>
        /// The constructor used to build a card.
        /// </summary>
        /// <param name="suit">The suit of the card.</param>
        /// <param name="symbol">The symbol of the card.</param>
        public Card(
            SuitEnum suit,
            SymbolEnum symbol)
        {
            Suit = suit;
            Symbol = symbol;
            SuitString = suit.ToString();
            SymbolString = symbol.ToString();
            CardValue = (int)symbol;
            IsAce = Symbol == SymbolEnum.Ace;
            IsFaceCard = Value >= (int)SymbolEnum.Jack;
        }


        #endregion

        #region Public Properties

        public string SuitString
        {
            get;
            set;
        }

        public string SymbolString
        {
            get;
            set;
        }

        /// <summary>
        /// The suit associated with this card.
        /// </summary>
        public SuitEnum Suit
        {
            get;
            private set;
        }

        /// <summary>
        /// The symbol associated with this card.
        /// </summary>
        public SymbolEnum Symbol
        {
            get;
            private set;
        }

        public bool IsAce
        {
            get;
            set;
        }

        public virtual int Value
        {
            get
            {
                return CardValue;
            }
        }

        public bool IsFaceCard
        {
            get;
            set;
        }

        public int CardValue
        {
            get;
            set;
        }

        #endregion

        #region Public Methods

        /// <summary>
        /// Returns the string representation of the card.
        /// </summary>
        /// <returns>The string of the card.</returns>
        public override string ToString()
        {
            return String.Format("{0} of {1}", SymbolString, SuitString);
        }

        /// <summary>
        /// Compares to other card class.
        /// </summary>
        /// <param name="other">The card to compare to.</param>
        /// <returns>The result of the comparison.</returns>
        public int CompareTo(Card other)
        {
            const int SAME = 0;
            const int NULLED = -1;

            if (null == other)
            {
                return NULLED;
            }

            int comparison = SuitString.CompareTo(other.SuitString);

            if (SAME != comparison)
            {
                return comparison;
            }

            return SymbolString.CompareTo(other.SymbolString);
        }

        /// <summary>
        /// Checks if objects are equal.
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
            if (false == (obj is Card))
            {
                return false;
            }

            Card other = (Card)obj;

            return SAME == CompareTo(other);
        }

        /// <summary>
        /// Returns the hash of the object.
        /// </summary>
        /// <returns></returns>
        public override int GetHashCode()
        {
            return ToString().GetHashCode();
        }

        #endregion


    }
}
