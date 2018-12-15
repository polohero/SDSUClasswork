using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Configuration;



namespace Games.BlackjackClient
{
    public static class Config
    {
        public static string PlayerName
        {
            get
            {
                const string PLAYER_NAME = "playerName";
                return getStringFromConfig(PLAYER_NAME);
            }
        }

        public static bool SinglePlayerMode
        {
            get
            {
                const string SINGLE_PLAYER = "singlePlayerMode";
                return getBoolFromConfig(SINGLE_PLAYER);
            }
        }


        public static bool UseEmotiv
        {
            get
            {
                const string USER_NAME = "useEmotiv";
                return getBoolFromConfig(USER_NAME);
            }
        }

        public static bool RunService
        {
            get
            {
                const string RUN_SERVICE = "runService";
                return getBoolFromConfig(RUN_SERVICE);
            }
        }

        private static string getStringFromConfig(string configName)
        {
            NameValueCollection setup = (NameValueCollection)ConfigurationManager.GetSection(CONFIG_SECTION_NAME);

            return setup[configName];
        }

        private static bool getBoolFromConfig(string configName)
        {

            NameValueCollection setup = (NameValueCollection)ConfigurationManager.GetSection(CONFIG_SECTION_NAME);

            return bool.Parse(setup[configName]);
        }

        private const string CONFIG_SECTION_NAME = "BlackjackClient";
    }
}
