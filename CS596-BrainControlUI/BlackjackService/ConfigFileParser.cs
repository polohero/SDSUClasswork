using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Configuration;

using Games.Common.Diagnostics;



namespace Games.BlackjackService
{
    public static class ConfigFileParser
    {
        /// <summary>
        /// Reads the various values from the config file and
        /// returns a Configuration object
        /// </summary>
        /// <returns>Configuration object</returns>
        static public Config Load()
        {
            return readConfigFile();
        }

        static private Config readConfigFile()
        {
            const string CONFIG_SECTION_NAME = "BlackjackService";

            NameValueCollection setup = (NameValueCollection)ConfigurationManager.GetSection(CONFIG_SECTION_NAME);

            Config config = new Config();

            config.LogLevel = parseLogLevelString(setup["logLevel"]);


            return config;
        }

        static private LogEntrySeverityEnum parseLogLevelString(string logLevelString)
        {
            switch (logLevelString.ToLower())
            {
                case "spam":
                    return
                        LogEntrySeverityEnum.Debug |
                        LogEntrySeverityEnum.Error |
                        LogEntrySeverityEnum.Warning |
                        LogEntrySeverityEnum.Failure |
                        LogEntrySeverityEnum.Success;

                case "debug":
                    return
                        LogEntrySeverityEnum.Debug |
                        LogEntrySeverityEnum.Error |
                        LogEntrySeverityEnum.Warning;

                case "minimum":
                    return LogEntrySeverityEnum.Error;

                default:
                    return LogEntrySeverityEnum.Error | LogEntrySeverityEnum.Warning;
            }
        }
    }
}
