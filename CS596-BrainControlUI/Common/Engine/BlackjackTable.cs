using System;
using System.Collections.Generic;

using Games.Common.Decks;



namespace Games.Common.Engine
{
    public class BlackjackTable : Table
    {
        #region Constructors

        BlackjackTable() { }

        public BlackjackTable(
            string id, 
            string name,
            Deck deck,
            Player owner) :
            base(id, name, GameTypeEnum.Blackjack, owner)
        {
            _playerPointer = -1;
            CurrentDeck = deck;
            Dealer = new BlackjackDealer();
        }

        #endregion

        #region Public Properties

        /// <summary>
        /// Moves the player pointer to the next
        /// player in the array.
        /// </summary>
        public void NextPlayer()
        {
            // Set the player to a "Played" status.
            Players[_playerPointer].State = PlayerStateEnum.Played;
            _playerPointer -= 1;

            if (_playerPointer >= 0)
            {
                Players[_playerPointer].State = PlayerStateEnum.Turn;
            }
        }

        /// <summary>
        /// Starts or restarts the blackjack
        /// game.
        /// </summary>
        public override void Start()
        {
            base.Start();

            _playerPointer = Players.Count - 1;

            Dealer.Hand.Clear();

            for (int i = 0; i < Players.Count; i++)
            {
                BlackjackPlayer player = (BlackjackPlayer)Players[i];
                player.State = PlayerStateEnum.Playing;
                player.Hand.Clear();
            }
            Players[_playerPointer].State = PlayerStateEnum.Turn;
            CurrentDeck.Shuffle();
            dealToEveryone();
        }

        /// <summary>
        /// Stops a current blackjack game and
        /// evaluates all of the hands against
        /// the dealer.
        /// </summary>
        public override void Stop()
        {
            base.Stop();
            _playerPointer = -1;

            // Finish off the dealers hand.
            Dealer.CompleteHand(this);

            // Loop through each player and assign them
            // a win or lose status based on the results
            // of comparing against the dealers hand.
            for (int i = 0; i < Players.Count; i++)
            {
                BlackjackPlayer player = (BlackjackPlayer)Players[i];

                // If someone busted the automatically
                // lose.
                if (true == player.Hand.IsBusted)
                {
                    player.State = PlayerStateEnum.Lost;
                    AddHistory(player + " busted. They lose.");
                }
                // If the dealer busted, everyong wins.
                else if (true == Dealer.Hand.IsBusted)
                {
                    player.State = PlayerStateEnum.Won;
                    AddHistory("Dealer busted. " + player + " wins.");
                }
                // Otherwise, we need to compare against
                // the dealer's hand.
                else
                {
                    if (player.Hand.Value > Dealer.Hand.Value)
                    {
                        player.State = PlayerStateEnum.Won;
                        AddHistory(player + " wins. " + player.Hand.Value + " vs " + Dealer.Hand.Value);
                    }
                    else if (player.Hand.Value == Dealer.Hand.Value)
                    {
                        player.State = PlayerStateEnum.Push;
                        AddHistory(player + " pushes with " + Dealer.Hand.Value);
                    }
                    else
                    {
                        player.State = PlayerStateEnum.Lost;
                        AddHistory(player + " loses. " + player.Hand.Value + " vs " + Dealer.Hand.Value);
                    }
                }
            }

            AddHistory("Waiting for " + Owner + " to start the next game.");
        }

        public bool IsLastPlayer
        {
            get
            {
                return isLastPlayer();
            }
        }

        /// <summary>
        /// The current blackjack dealer.
        /// </summary>
        public BlackjackDealer Dealer
        {
            get;
            set;
        }

        public Deck CurrentDeck
        {
            get;
            set;
        }

        #endregion

        #region Public Methods

        public int GetPlayersPointer(Player player)
        {
            for (int i = 0; i < Players.Count; i++)
            {
                Player current = Players[i];
                if (player.Name.Equals(current.Name))
                {
                    return i;
                }
            }

            return -1;
        }

        #endregion

        #region Private Methods

        /// <summary>
        /// Deals a card out to all players and the dealer.
        /// </summary>
        /// <param name="table"></param>
        private void dealToEveryone()
        {
            foreach (BlackjackPlayer blackJackPlayer in Players)
            {
                blackJackPlayer.Hand.AddCard(CurrentDeck.Deal());
            }

            Dealer.Hand.AddCard(CurrentDeck.Deal());

            foreach (BlackjackPlayer blackJackPlayer in Players)
            {
                blackJackPlayer.Hand.AddCard(CurrentDeck.Deal());
            }

            Dealer.Hand.AddCard(CurrentDeck.Deal());
        }

        private bool isLastPlayer()
        {
            return _playerPointer == 0;
        }

        #endregion

        #region Private Attributes

        private int _playerPointer = -1;

        #endregion
    }
}
