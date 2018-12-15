using System;
using System.Collections.Generic;



namespace Games.BlackjackService
{
    /// <summary>
    /// This class parses and tokenizes the command line 
    /// parameters, then exposes the values through
    /// properties.
    /// </summary>
    public sealed class CommandLineParams
    {
        #region C-tors

        /// <summary>
        /// Constructs with the command line argument array
        /// </summary>
        /// <param name="args">The command line argument array</param>
        public CommandLineParams(string[] args)
        {
            initialize(args);
        }

        #endregion

        #region Public Properties

        /// <summary>
        /// Set true if the program should run in console
        /// mode (command line instead of an NT service)
        /// </summary>
        public bool RunAsConsole
        {
            get { return _consoleMode; }
        }

        /// <summary>
        /// Set true if requesting to install the executable
        /// as an NT service
        /// </summary>
        public bool InstallService
        {
            get { return _installService; }
        }

        /// <summary>
        /// Set to true if requesting to uninstall the
        /// executable as an NT service.
        /// </summary>
        public bool UninstallService
        {
            get { return _uninstallService; }
        }

        public bool ShowHelp
        {
            get { return _showHelp; }
        }

        #endregion

        #region Private Methods

        /// <summary>
        /// This method will initialize the object.  It
        /// takes the argument array, parses and tokenizes
        /// the string into its constituent components
        /// </summary>
        /// <param name="args">the argument array</param>
        private void initialize(string[] args)
        {
            for (int i = 0; i < args.Length; i++)
            {
                switch (getArgToken(args[i]))
                {
                    case TOKEN_RUNAS_CONSOLE:
                        _consoleMode = true;
                        break;

                    case TOKEN_SERVICE_INSTALL:
                        _installService = true;
                        break;

                    case TOKEN_SERVICE_UNINSTALL:
                        _uninstallService = true;
                        break;

                    case TOKEN_SHOW_HELP:
                        _showHelp = true;
                        break;

                    case TOKEN_UNKNOWN:

                        break;
                }
            }
        }

        /// <summary>
        /// Tokenizes the input string
        /// </summary>
        /// <param name="arg">The string to tokenize</param>
        /// <returns>The corresponding token value, or TOKEN_UKNOWN if no match</returns>
        private int getArgToken(string arg)
        {
            for (int i = 0; i < _commands.Length; i++)
            {
                if (arg.ToLower() == _commands[i].ToLower())
                {
                    return _tokens[i];
                }
            }

            return TOKEN_UNKNOWN;
        }

        #endregion

        #region Private Attributes

        //
        // Manditory fields - require explicit values
        //


        private bool _consoleMode = false;
        private bool _installService = false;
        private bool _uninstallService = false;
        private bool _showHelp = false;

        #region Token definitions and Lookup Tables

        // Named const token definitions
        const int TOKEN_RUNAS_CONSOLE = 0;
        const int TOKEN_SERVICE_INSTALL = 1;
        const int TOKEN_SERVICE_UNINSTALL = 2;
        const int TOKEN_SHOW_HELP = 3;
        const int TOKEN_UNKNOWN = 99;


        // Add the command line args to
        // this array
        private static readonly string[] _commands = 
        {  
             "-console",
            "-install",
            "-uninstall", 
            "-help",
            "/?"
        };

        // Add the corresponding token 
        // value to this array.  Make sure
        // the two arrays align.
        private static readonly int[] _tokens = 
        {    
            TOKEN_RUNAS_CONSOLE, 
            TOKEN_SERVICE_INSTALL,
            TOKEN_SERVICE_UNINSTALL,
            TOKEN_SHOW_HELP
        };
        #endregion
        #endregion
    }
}
