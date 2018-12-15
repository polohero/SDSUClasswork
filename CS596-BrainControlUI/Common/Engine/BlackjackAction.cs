


namespace Games.Common.Engine
{
    /// <summary>
    /// Defines an action that can be taken
    /// with the engine to communicate back to
    /// the client.
    /// </summary>
    public enum BlackjackAction
    {
        JoinTable = 1,
        Start = 2,
        Hit = 3,
        Stay = 4,
        Evaluate = 5,
        Get = 6,
        LeaveTable = 7,
        Chat = 8
    }
}
