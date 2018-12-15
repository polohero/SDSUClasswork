using System;
using System.ServiceModel;

using Games.Common.Engine;



namespace Games.Common.WCF
{
    [ServiceContract]
    public interface IGameProcessor
    {
        /// <summary>
        /// Processes a blackjack request.
        /// </summary>
        /// <param name="request"></param>
        /// <returns></returns>
        [OperationContract]
        BlackjackResponse Process(BlackjackRequest request);
    }
}
