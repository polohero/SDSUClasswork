using System.Runtime.Serialization;



namespace Games.Common.Cards
{
    /// <summary>
    /// The suit associated with a specific card.
    /// </summary>
     [DataContract]
    public enum SuitEnum
    {
        [EnumMember(Value = "Undefined")]
        Undefined = 0,
        [EnumMember(Value = "Hearts")]
        Hearts = 1,
        [EnumMember(Value = "Spades")]
        Spades = 2,
        [EnumMember(Value = "Clubs")]
        Clubs = 3,
        [EnumMember(Value = "Diamonds")]
        Diamonds = 4
    }
}
