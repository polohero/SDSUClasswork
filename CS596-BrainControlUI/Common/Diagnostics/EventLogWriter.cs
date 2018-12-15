using System;
using System.Diagnostics;
using System.Reflection;



namespace Games.Common.Diagnostics
{
    /// <summary>
    /// This class writes log entries to the 
    /// event log
    /// </summary>
    public sealed class EventLogWriter
    {
        #region C-tors

        /// <summary>
        /// Default c-tor.  This will use the name
        /// of the host process as the event source 
        /// name
        /// </summary>
        public EventLogWriter()
        {
            initialize();
        }

        /// <summary>
        /// This method will allow you to set the source 
        /// for the event log
        /// </summary>
        /// <param name="source">The event source name</param>
        public EventLogWriter(string source)
        {
            _source = source;

            initialize();
        }

        #endregion

        #region Public Methods

        /// <summary>
        /// Writes the message to the event log
        /// </summary>
        /// <param name="message">The message text to write</param>
        public void Write(string message)
        {
            EventLog.WriteEntry(_source, message);
        }

        /// <summary>
        /// Writes the message to the event log and sets
        /// the corresponding severity
        /// </summary>
        /// <param name="message">The message text to write to the log</param>
        /// <param name="severity">The severity for the entry</param>
        public void Write(string message, LogEntrySeverityEnum severity)
        {
            EventLog.WriteEntry(
                _source,
                message,
                convertSeverity(severity)
            );
        }

        /// <summary>
        /// Checks to see if the source exists in the event log.
        /// You will need to create the source if it doesn't exist
        /// prior to writing to the event log.
        /// </summary>
        /// <returns>true if source exists</returns>
        public bool SourceExists()
        {
            return EventLog.SourceExists(_source);
        }

        /// <summary>
        /// Creates the event log source.  You will need 
        /// administrative rights to create a new event 
        /// source.
        /// </summary>
        public void CreateSource()
        {
            EventLog.CreateEventSource(
                _source,
                _logName
            );
        }

        /// <summary>
        /// Removes the source from the event log
        /// </summary>
        public void RemoveSource()
        {
            EventLog.DeleteEventSource(_source);
        }

        #endregion

        #region Private Methods

        /// <summary>
        /// Converts our severity to one of the 
        /// severities defined by the Windows event log
        /// </summary>
        /// <param name="severity">The LogEntrySeverityEnum</param>
        /// <returns>A corresponding EventLogEntryType severity</returns>
        private EventLogEntryType convertSeverity(LogEntrySeverityEnum severity)
        {
            switch (severity)
            {
                case LogEntrySeverityEnum.Debug:
                    return EventLogEntryType.Information;

                case LogEntrySeverityEnum.Error:
                    return EventLogEntryType.Error;

                case LogEntrySeverityEnum.Warning:
                    return EventLogEntryType.Warning;

                case LogEntrySeverityEnum.Success:
                    return EventLogEntryType.SuccessAudit;

                case LogEntrySeverityEnum.Failure:
                    return EventLogEntryType.FailureAudit;

                default:
                    // If we have anything undefined,
                    // treat it like the sky is falling
                    // down
                    return EventLogEntryType.Error;
            }
        }

        /// <summary>
        /// Common method called by all C-tors
        /// to initialize the object state
        /// </summary>
        private void initialize()
        {
            // Did the caller give us
            // the source, or do we 
            // need to create one?
            if (null == _source)
            {
                const char DELIMITER = ',';

                string source = Assembly.GetExecutingAssembly().FullName;

                _source = source.Split(new char[] { DELIMITER })[0];
            }

            if (null == _logName)
            {
                // make it the same as the source
                _logName = "Application";
            }
        }

        #endregion

        #region Private Attributes

        string _source;
        string _logName;

        #endregion
    }
}
