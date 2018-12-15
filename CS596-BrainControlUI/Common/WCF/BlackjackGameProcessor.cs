using System;
using System.ServiceModel;
using System.Runtime.Serialization;
using System.IO;

using Games.Common.Engine;
using Games.Common.Diagnostics;



namespace Games.Common.WCF
{
    public class BlackjackGameProcessor : IGameProcessor
    {
        #region Constructors

        public BlackjackGameProcessor() { }

        #endregion

        #region Public Methods

        /// <summary>
        /// Processes the incoming blackjack request.
        /// </summary>
        /// <param name="request"></param>
        /// <returns></returns>
        public BlackjackResponse Process(BlackjackRequest request)
        {
            BlackjackResponse response = null;

            try
            {
                response = _engine.Process(request);
            }
            catch (Exception exception)
            {
                response = new BlackjackResponse(
                    request.Table,
                    BlackjackResult.Failure,
                    exception.Message);

                LogHelper.Instance().Write(
                    "Error processing request: " + toString(request),
                    LogEntrySeverityEnum.Error,
                    exception);

            }

            return response;
        }

        #endregion

        #region Private Methods

        private string toString(BlackjackRequest request)
        {
            try
            {
                return request.ToString();
            }
            catch (Exception exception)
            {
                return exception.Message;
            }
        }

        #endregion

        #region Private Attributes

        private static BlackjackEngine _engine = new BlackjackEngine();

        #endregion
    }
}
