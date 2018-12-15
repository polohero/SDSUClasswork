using System;
using System.Text;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;

using Games.Common.Cards;
using Games.Common.Hands;
using Games.Common.Decks;
using Games.Common.Engine;



namespace Games.Tests
{
    /// <summary>
    /// Summary description for CommonTests
    /// </summary>
    [TestClass]
    public class CommonTests
    {
        public CommonTests()
        {
            //
            // TODO: Add constructor logic here
            //
        }

        private TestContext testContextInstance;

        /// <summary>
        ///Gets or sets the test context which provides
        ///information about and functionality for the current test run.
        ///</summary>
        public TestContext TestContext
        {
            get
            {
                return testContextInstance;
            }
            set
            {
                testContextInstance = value;
            }
        }

        #region Additional test attributes
        //
        // You can use the following additional attributes as you write your tests:
        //
        // Use ClassInitialize to run code before running the first test in the class
        // [ClassInitialize()]
        // public static void MyClassInitialize(TestContext testContext) { }
        //
        // Use ClassCleanup to run code after all tests in a class have run
        // [ClassCleanup()]
        // public static void MyClassCleanup() { }
        //
        // Use TestInitialize to run code before running each test 
        // [TestInitialize()]
        // public void MyTestInitialize() { }
        //
        // Use TestCleanup to run code after each test has run
        // [TestCleanup()]
        // public void MyTestCleanup() { }
        //
        #endregion

        [TestMethod]
        public void TestCard()
        {
            Card card = new Card(SuitEnum.Clubs, SymbolEnum.Jack);
            Assert.IsTrue(
                card.Suit == SuitEnum.Clubs,
                "Suit should be clubs.");
            Assert.IsTrue(
                card.Symbol == SymbolEnum.Jack,
                "Symbol should be jack.");
            Assert.IsTrue(
                true == card.IsFaceCard,
                "Card is a face card.");
            Assert.IsTrue(
                false == card.IsAce,
                "Card is a not an ace.");

            card = new Card(SuitEnum.Clubs, SymbolEnum.Ace);
            Assert.IsTrue(
                false == card.IsFaceCard,
                "Card is not a face card.");
            Assert.IsTrue(
                true == card.IsAce,
                "Card is an ace.");

            card = new Card(SuitEnum.Clubs, SymbolEnum.Eight);
            Assert.IsTrue(
                false == card.IsFaceCard,
                "Card is not a face card.");

            Card compareCard = new Card(SuitEnum.Clubs, SymbolEnum.Eight);

            Assert.IsTrue(
                true == card.Equals(compareCard),
                "Cards should be equal.");

            TestContext.WriteLine(card.ToString());
        }

        [TestMethod]
        public void TestHand()
        {
            Card jackOfClubs = new Card(SuitEnum.Clubs, SymbolEnum.Jack);
            Card aceOfSpaces = new Card(SuitEnum.Spades, SymbolEnum.Ace);
            Card eightOfHearts = new Card(SuitEnum.Hearts, SymbolEnum.Eight);
            Card nineOfHearts = new Card(SuitEnum.Hearts, SymbolEnum.Nine);

            Hand hand =
                new Hand(new Card[] { jackOfClubs, aceOfSpaces, eightOfHearts });

            Assert.IsTrue(
                hand.Cards.Count == 3,
                "Should be 3 cards.");

            Hand hand2 =
                new Hand(new Card[] { jackOfClubs, aceOfSpaces, eightOfHearts });

            Assert.IsTrue(
                hand.Equals(hand2),
                "Hands are equal.");

            hand2 = new Hand(new Card[] { jackOfClubs, aceOfSpaces, nineOfHearts });

            Assert.IsTrue(
                false == hand.Equals(hand2),
                "Hands are not equal.");

            TestContext.WriteLine(hand.ToString());
        }

        [TestMethod]
        public void TestBlackjackHand()
        {
            Card jackOfClubs = new Card(SuitEnum.Clubs, SymbolEnum.Jack);
            Card aceOfSpades = new Card(SuitEnum.Spades, SymbolEnum.Ace);
            Card aceOfHearts = new Card(SuitEnum.Hearts, SymbolEnum.Ace);
            Card eightOfHearts = new Card(SuitEnum.Hearts, SymbolEnum.Eight);
            Card nineOfHearts = new Card(SuitEnum.Hearts, SymbolEnum.Nine);

            BlackjackHand hand =
                new BlackjackHand(new Card[] { jackOfClubs, aceOfSpades, eightOfHearts });

            Assert.IsTrue(
                hand.Cards.Count == 3,
                "Should be 3 cards.");

            BlackjackHand hand2 =
                new BlackjackHand(new Card[] { jackOfClubs, aceOfSpades, eightOfHearts });

            Assert.IsTrue(
                hand.Equals(hand2),
                "Hands are equal.");

            hand2 = new BlackjackHand(new Card[] { jackOfClubs, aceOfSpades, nineOfHearts });

            Assert.IsTrue(
                false == hand.Equals(hand2),
                "Hands are not equal.");

            Assert.IsTrue(
                hand.Value == 19,
                "Blackjack hand value is 19");

            hand = new BlackjackHand(new Card[] { jackOfClubs, aceOfSpades, eightOfHearts,aceOfHearts });
            Assert.IsTrue(
                hand.Value == 20,
                "Blackjack hand value is 20");


            TestContext.WriteLine(hand.ToString());
        }

        [TestMethod]
        public void TestDeck()
        {
            Deck deck = Deck.Create();

            Assert.IsTrue(
                deck.Count == 52,
                "There should be 52 cards in the deck.");

            string currentDeck =
                deck.ToString();

            deck.Shuffle();

            string afterShuffle = 
                deck.ToString();

            Assert.IsTrue(
                currentDeck != afterShuffle,
                "Decks should not be the same");

            Assert.IsTrue(
                deck.Count == 52,
                "There should be 52 cards in the deck.");
            Assert.IsTrue(
                deck.Remaining == 52,
                "There should be 52 cards in the deck.");
            Assert.IsTrue(
                deck.Dealt == 0,
                "There should be 52 cards in the deck.");

            //TestContext.WriteLine(currentDeck);
            //TestContext.WriteLine(afterShuffle);


            Card topCard = deck.TopCard;

            Card card = deck.Deal();

            Assert.IsTrue(
                deck.Count == 52,
                "There should be 52 cards in the deck.");
            Assert.IsTrue(
                deck.Remaining == 51,
                "There should be 52 cards in the deck.");
            Assert.IsTrue(
                deck.Dealt == 1,
                "There should be 52 cards in the deck.");
            Assert.IsTrue(
                topCard.Equals(card),
                "Top card and dealt card should be the same.");

            TestContext.WriteLine("Deck before deal: " + afterShuffle);
            TestContext.WriteLine("Top Card: " + card);
            TestContext.WriteLine("Deck after deal: " + deck.ToString());
        }

        [TestMethod]
        public void TestGameEngine()
        {
            BlackjackEngine engine =
                new BlackjackEngine();

            BlackjackPlayer player =
                new BlackjackPlayer("Cory");

            BlackjackPlayer player2 =
            new BlackjackPlayer("Bob");

            BlackjackTable table =
                new BlackjackTable(
                    "1",
                    "Yes",
                    null,
                    null);

          BlackjackResponse response1 =  engine.Process(
                new BlackjackRequest(
                    player,
                    BlackjackAction.JoinTable,
                    table));


          BlackjackResponse response2 = engine.Process(
                new BlackjackRequest(
                    player2,
                    BlackjackAction.JoinTable,
                    table));


          BlackjackResponse response3 = engine.Process(
                          new BlackjackRequest(
                              player,
                              BlackjackAction.Start,
                              table));

          BlackjackResponse response4 = engine.Process(
                          new BlackjackRequest(
                              player2,
                              BlackjackAction.Stay,
                              table));
        }

        [TestMethod]
        public void TestGameEngine_Leave()
        {
            BlackjackEngine engine =
                new BlackjackEngine();

            BlackjackPlayer player =
                new BlackjackPlayer("Cory");

            BlackjackPlayer player2 =
            new BlackjackPlayer("Bob");

            BlackjackTable table =
                new BlackjackTable(
                    "1",
                    "Yes",
                    null,
                    null);

            BlackjackResponse response1 = engine.Process(
                  new BlackjackRequest(
                      player,
                      BlackjackAction.JoinTable,
                      table));


            BlackjackResponse response2 = engine.Process(
                  new BlackjackRequest(
                      player2,
                      BlackjackAction.JoinTable,
                      table));


            BlackjackResponse response3 = engine.Process(
                            new BlackjackRequest(
                                player,
                                BlackjackAction.LeaveTable,
                                table));

            BlackjackResponse response4 = engine.Process(
                            new BlackjackRequest(
                                player2,
                                BlackjackAction.LeaveTable,
                                table));
        }
    }
}