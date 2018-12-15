using System;
using System.Collections.Generic;

using Games.Common.Cards;



namespace Games.Common.Decks
{
    public class Deck : CardCollection
    {
        #region Constructors

        /// <summary>
        /// Creates a new deck based on an array of cards.
        /// </summary>
        /// <param name="cards"></param>
        protected Deck(IEnumerable<Card> cards) : base(cards)
        {
            const int INITIAL_CAPACITY = 52;

            _dealtCards = new List<Card>(INITIAL_CAPACITY);
        }

        /// <summary>
        /// Creates a new empty deck.
        /// </summary>
        protected Deck()
            : base()
        {
            const int INITIAL_CAPACITY = 52;

            _dealtCards = new List<Card>(INITIAL_CAPACITY);
        }

        #endregion

        #region Public Methods

        public Card TopCard
        {
            get
            {
                return Peek;
            }
        }

        public int Count
        {
            get
            {
                return Cards.Count + _dealtCards.Count;
            }
        }

        public int Remaining
        {
            get
            {
                return Cards.Count;
            }
        }

        public int Dealt
        {
            get
            {
                return _dealtCards.Count;
            }
        }

        /// <summary>
        /// Creates a new deck based on the 
        /// </summary>
        /// <returns></returns>
        public static Deck Create(int numberOfDecks = 1)
        {
            Deck deck = new Deck();

            for (int i = 0; i < numberOfDecks; i++)
            {
                foreach (SuitEnum suit in (SuitEnum[])Enum.GetValues(typeof(SuitEnum)))
                {
                    if( SuitEnum.Undefined == suit){continue;}

                    foreach (SymbolEnum symbol in 
                             (SymbolEnum[])Enum.GetValues(typeof(SymbolEnum)))
                    {
                        if (SymbolEnum.Undefined == symbol) { continue; }

                        deck.Add(new Card(suit, symbol));
                    }
                }
            }

            return deck;
        }

        /// <summary>
        /// Deals a card from the top of the deck.
        /// </summary>
        /// <returns></returns>
        public virtual Card Deal()
        {
            if (Cards.Count == 0)
            {
                throw new Exception(
                    "Card list is currently empty, it cannot have a card dealt.");
            }

            return deal();
        }

        /// <summary>
        /// Shuffles a deck of cards.
        /// </summary>
        /// <returns></returns>
        public virtual void Shuffle()
        {
            shuffle();
        }

        #endregion

        #region Private Methods

        /// <summary>
        /// Deals a card.
        /// </summary>
        /// <returns></returns>
        private Card deal()
        {
            Card card = Cards[0];
            _dealtCards.Add(card);
            Cards.RemoveAt(0);

            return card;
        }

        /// <summary>
        /// Shuffles the whole deck by adding back
        /// anything that was dealt.
        /// </summary>
        private void shuffle()
        {
            foreach (Card card in _dealtCards)
            {
                Cards.Add(card);
            }

            _dealtCards.Clear();

            shuffleCards();
        }

        /// <summary>
        /// Shuffles anything currently in the deck.
        /// </summary>
        private void shuffleCards()
        {
            Random random = new Random();

            List<Card> newList =
                new List<Card>(Cards.Count);

            // Loop through the card collection backward,
            // and select a card at random from the 
            // Cards. Remove it from the list and add it
            // to a new list.
            for (int i = Cards.Count- 1; i >= 0; i--)
            {
                int randomIndex = random.Next(0, i);

                newList.Add(Cards[randomIndex]);
                Cards.RemoveAt(randomIndex);
            }

            Cards = newList;
        }

        #endregion

        #region Private Attributes

        /// <summary>
        /// A list to keep track of any cards that have been
        /// deal away.
        /// </summary>
        protected List<Card> _dealtCards;

        #endregion
    }
}
