using System;
using System.Text;
using System.Collections.Generic;
using System.Runtime.Serialization;



namespace Games.Common.Cards
{
    public class CardCollection
    {
        #region Constructors

        /// <summary>
        /// Creates a new collection based on an array of cards.
        /// </summary>
        /// <param name="cards"></param>
        public CardCollection(IEnumerable<Card> cards)
        {
            Cards = new List<Card>(cards);
        }

        /// <summary>
        /// Creates a new empty collection.
        /// </summary>
        public CardCollection()
        {
            const int INITIAL_CAPACITY = 10;
            Cards = new List<Card>(INITIAL_CAPACITY);
        }

        #endregion

        #region Protected Properties

        protected void Clear()
        {
            Cards.Clear();
        }

        /// <summary>
        /// Peeks at the top of the card list.
        /// </summary>
        /// <returns></returns>
        protected Card Peek
        {
            get
            {
                return peek();
            }
        }

        /// <summary>
        /// The collection of cards.
        /// </summary>
        protected List<Card> Cards
        {
            get;
            set;
        }

        #endregion

        #region Public Methods

        /// <summary>
        /// Returns a string representation of the card
        /// collection.
        /// </summary>
        /// <returns></returns>
        public override string ToString()
        {
            StringBuilder sb = new StringBuilder();

            foreach (Card card in Cards)
            {
                sb.AppendLine(card.ToString());
            }

            return sb.ToString();
        }

        #endregion

        #region Protected Methods

        /// <summary>
        /// Adds a card to the collection.
        /// </summary>
        /// <param name="card"></param>
        protected void Add(Card card)
        {
            validate(card);
            add(card);
        }

        /// <summary>
        /// Removes a card from the collection.
        /// </summary>
        /// <param name="card"></param>
        protected void Remove(Card card)
        {
            validate(card);
            remove(card);
        }

        #endregion

        #region Private Methods

        private Card peek()
        {
            if (Cards.Count == 0)
            {
                return null;
            }

            return Cards[0];
        }

        /// <summary>
        /// Loops through the cards and removes the
        /// specific card.
        /// </summary>
        /// <param name="card"></param>
        private void remove(Card card)
        {
            for (int i = Cards.Count - 1; i >= 0; i--)
            {
                Card current = Cards[i];
                if (true == current.Equals(card))
                {
                    Cards.RemoveAt(i);
                }
            }
        }

        /// <summary>
        /// Validates a card is allowed for an operation.
        /// </summary>
        /// <param name="card"></param>
        private void validate(Card card)
        {
            if (null == card)
            {
                throw new ArgumentNullException(
                    "A Card cannot be NULL.");
            }
        }

        /// <summary>
        /// Adds a new card to the collection.
        /// </summary>
        /// <param name="card"></param>
        private void add(Card card)
        {
            Cards.Add(card);
        }

        #endregion
    }
}
