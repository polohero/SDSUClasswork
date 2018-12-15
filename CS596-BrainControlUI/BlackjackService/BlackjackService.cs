using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Linq;
using System.ServiceProcess;
using System.Text;
using System.ServiceModel;

using Games.Common.WCF;
using Games.Common.Diagnostics;

namespace Games.BlackjackService
{
    partial class BlackjackService : ServiceBase
    {
        public BlackjackService()
        {
            InitializeComponent();
        }

        private ServiceHost _host;

        protected override void OnStart(string[] args)
        {
            LogHelper.Instance("BlackjackService");

            try
            {
                LogHelper.Instance().Write("Blackjack service starting", LogEntrySeverityEnum.Debug);

                _host = new ServiceHost(typeof(BlackjackGameProcessor));
                _host.Open();          
            }
            catch (Exception exception)
            {
                LogHelper.Instance().Write(
                  "A fatal exception occurred while starting the service",
                  LogEntrySeverityEnum.Error,
                  this.GetType(),
                  exception);

                // Throw it again to kill the service                
                throw;
            }
        }

        protected override void OnStop()
        {
            try
            {
                LogHelper.Instance().Write("Blackjack service stopping", LogEntrySeverityEnum.Debug);

                _host.Close();              
            }
            catch (Exception exception)
            {
                LogHelper.Instance().Write(
                  "A fatal exception occurred while stopping the service",
                  LogEntrySeverityEnum.Error,
                  this.GetType(),
                  exception);

                // Throw it again to kill the service                
                throw;
            }
        }
    }
}
