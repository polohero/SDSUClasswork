using System;
using System.Configuration;
using System.Collections.Generic;
using System.Collections.Specialized;

using Games.Common.Diagnostics;



namespace Games.BlackjackService
{
    public sealed class Config
    {
        public LogEntrySeverityEnum LogLevel
        {
            get;
            set;
        }
    }
}
