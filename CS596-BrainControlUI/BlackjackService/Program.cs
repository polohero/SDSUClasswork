using System;
using System.Diagnostics;
using System.Threading;
using System.Reflection;
using System.ServiceModel;
using System.ServiceProcess;
using System.Configuration.Install;

using Games.Common.WCF;
using Games.Common.Diagnostics;



namespace Games.BlackjackService
{
    class Program
    {
        #region Program Entry Point

        /// <summary>
        /// This is the application entry point
        /// </summary>
        /// <param name="args">The command line arguments</param>
        static int Main(string[] args)
        {
            // We won't have any arguments
            // if we are called by the SCM.
            // Since we have arguments, we
            // must be running interactively
            // with the user.
            if (args.Length > 0)
            {
                // Show some UI info
                showBanner();
            }

            LogHelper.Instance("BlackjackService");

            CommandLineParams parameters = null;
            try
            {
                // Parsing the command line can throw an 
                // exception.  So we are going to use two
                // separate try..catch blocks.  One will handle
                // command line parsing problems, and the 
                // other will handle processing-specific exceptions
                parameters = new CommandLineParams(args);
            }
            catch (Exception exception)
            {
                LogHelper.Instance().Write(exception.Message, LogEntrySeverityEnum.Error, exception);

                Console.WriteLine("There is a problem with the command line arguments - see event log for details.");

                return FAILED;
            }

            try
            {
                if (true == parameters.ShowHelp)
                {
                    showUsage();

                    return SUCCESS;
                }
                else if (true == parameters.InstallService)
                {
                    installService();

                    return SUCCESS;
                }
                else if (true == parameters.UninstallService)
                {
                    uninstallService();

                    return SUCCESS;
                }
                else if (args.Length > 0)
                {
                    runAsConsoleApplication(parameters);
                }
                else
                {
                    runAsService();
                }
            }
            catch (Exception exception)
            {
                LogHelper.Instance().Write(exception.Message, LogEntrySeverityEnum.Error, exception);

                Console.WriteLine("An unrecoverable problem was encountered - see event log for details.");

                return FAILED;
            }

            return SUCCESS;
        }

        #endregion

        #region Private Methods

        /// <summary>
        /// This method drives/orchestrates the desired
        /// functionality based on the action specified
        /// from the command line.
        /// </summary>
        /// <param name="parameters"></param>
        static private void runAsConsoleApplication(CommandLineParams parameters)
        {
            try
            {
                Console.WriteLine("Press any key to terminate...");

                ServiceHost blackjackHost =
                    new ServiceHost(typeof(BlackjackGameProcessor));
                blackjackHost.Open();

                // This will prevent the program
                // from terminating, while still 
                // allowing this primary thread to
                // be responsive and display console
                // i/o generated from the trace
                bool done = false;
                do
                {
                    done = Console.KeyAvailable;
                    Thread.Sleep(100);

                } while (done == false);

                blackjackHost.Close();

                Console.WriteLine("Finished.");
            }
            catch (Exception exception)
            {
                Console.WriteLine(exception.Message);
            }

            Console.Read();
        }

        /// <summary>
        /// Displays usage info on the console to the 
        /// end user
        /// </summary>
        static private void showUsage()
        {
            Console.WriteLine("\r\nUsage:");
            Console.WriteLine("\r\noptional");
            Console.WriteLine("  -console   run as a console application");
            Console.WriteLine("  -install   installs as an NT Service]");
            Console.WriteLine("  -uninstall uninstalls as an NT Service");
            Console.WriteLine("  -help  shows this screen");
            Console.WriteLine("  /?     shows this screen");
        }

        /// <summary>
        /// Displays the program banner on the console for the 
        /// user
        /// </summary>
        static private void showBanner()
        {
            Console.WriteLine("Copyright (C) 2014 Cory Wixom cory.wixom@gmail.com\r\nSDSU CS 596 Brain control user interfaces.");
        }

        #endregion

        #region Service Helpers

        /// <summary>
        /// Sets up the process to run as an
        /// NT service
        /// </summary>
        static void runAsService()
        {
            ServiceBase[] services;

            services = new ServiceBase[] { new BlackjackService() };

            ServiceBase.Run(services);
        }

        /// <summary>
        /// Attempts to install/register the executable
        /// with the Service Control Manager (SCM).
        /// </summary>
        static void installService()
        {
            // The installer will barf if the event source
            // is already defined.  So we need to clean
            // up our house.
            EventLogWriter elv = new EventLogWriter();

            if (elv.SourceExists() == true)
            {
                elv.RemoveSource();
            }

            string executable = Assembly.GetExecutingAssembly().Location;

            ManagedInstallerClass.InstallHelper(
                new string[] { executable }
                );

            // We should now have the event source.
            // Let's make sure           
            if (elv.SourceExists() != true)
            {
                elv.CreateSource();
            }


        }

        /// <summary>
        /// Attempts to uninstall/unregister the executable
        /// with the Service Control Manager (SCM).
        /// </summary>
        static void uninstallService()
        {
            string executable = Assembly.GetExecutingAssembly().Location;

            ManagedInstallerClass.InstallHelper(
                new string[] { "/u", executable }
                );
        }


        #endregion

        #region Private Const Declarations

        const int FAILED = -1;
        const int NO_CMD_LINE = 0;
        const int SUCCESS = 1;

        #endregion
    }
}
