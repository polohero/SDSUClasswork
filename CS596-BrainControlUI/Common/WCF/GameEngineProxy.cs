using System;
using System.ServiceModel;
using System.Collections.Generic;

using Games.Common.Cards;
using Games.Common.Decks;
using Games.Common.Hands;
using Games.Common.Engine;



namespace Games.Common.WCF
{
    public class GameEngineProxy : ClientBase<IGameProcessor>, IGameProcessor
    {
        #region Public Const Declarations

        public const string DEFAULT_ENDPOINT_NAME = "";

        #endregion

        #region C-Tors

        public GameEngineProxy(string endpointConfigName = DEFAULT_ENDPOINT_NAME)
            : base( endpointConfigName )
        {

        }

        #endregion

        #region IGameProcessor Members

        public BlackjackResponse Process(BlackjackRequest request)
        {
            return Channel.Process(request);
        }

        #endregion
    }
}
