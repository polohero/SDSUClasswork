using System.Runtime.Serialization;



namespace Games.Common.Cards
{
    /// <summary>
    /// The symbol associated with each card.
    /// </summary>
    [DataContract]
    public enum SymbolEnum
    {
        [EnumMember(Value = "Undefined")]
        Undefined = 0,
        [EnumMember(Value = "Ace")]
        Ace = 1,
        [EnumMember(Value = "Two")]
        Two = 2,
        [EnumMember(Value = "Three")]
        Three = 3,
        [EnumMember(Value = "Four")]
        Four = 4,
        [EnumMember(Value = "Five")]
        Five = 5,
        [EnumMember(Value = "Six")]
        Six = 6,
        [EnumMember(Value = "Seven")]
        Seven = 7,
        [EnumMember(Value = "Eight")]
        Eight = 8,
        [EnumMember(Value = "Nine")]
        Nine = 9,
        [EnumMember(Value = "Ten")]
        Ten = 10,
        [EnumMember(Value = "Jack")]
        Jack = 11,
        [EnumMember(Value = "Queen")]
        Queen = 12,
        [EnumMember(Value = "King")]
        King = 13
    }
}
