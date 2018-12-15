using System;
using System.Text;
using System.Diagnostics;



namespace Games.Common.Diagnostics
{
    /// <summary>
    /// The LogHelper class provides helper methods to make it 
    /// easy to add diagnostic/logging info.  It is written
    /// as a singleton instead of a static utility class so we
    /// can provide synchronization if needed.
    /// </summary>
    public sealed class LogHelper
    {
        #region Public Methods

        /// <summary>
        /// Call this method first to get the object instance.
        /// Afterwards, you can call any of the instance members
        /// freely.
        /// </summary>
        /// <param name="source">The event log source name</param>
        /// <returns>The LogHelper instance</returns>
        static public LogHelper Instance(string source = "Service")
        {
            if (null == _logHelper)
            {
                _logHelper = new LogHelper(source);
            }

            return _logHelper;
        }

        /// <summary>
        /// This method will write the message to the 
        /// log along with the corresponding severity
        /// </summary>
        /// <param name="message">The message to write to the log</param>
        /// <param name="severity">The severity of the log entry</param>
        public void Write(string message, LogEntrySeverityEnum severity)
        {
            try
            {
                write(message, severity);
            }
            catch (Exception)
            {
                // Log failures should not 
                // cause our program to crash
            }
        }

        /// <summary>
        /// This method will write the message to the log
        /// along with select attributes from the exception object
        /// </summary>
        /// <param name="message">The message to write to the log</param>
        /// <param name="severity">The severity of the event</param>
        /// <param name="exception">The exception object</param>
        public void Write(string message, LogEntrySeverityEnum severity, Exception exception)
        {
            try
            {
                write(format(message, exception), severity);
            }
            catch (Exception)
            {
                // Log failures should not 
                // cause our program to crash
            }
        }

        /// <summary>
        /// This method will write the message to the log
        /// along with select attributes from the type object
        /// </summary>
        /// <param name="message">The message to write to the log</param>
        /// <param name="severity">The severity of the event</param>
        /// <param name="type">The type object</param>
        public void Write(string message, LogEntrySeverityEnum severity, Type type)
        {
            try
            {
                write(format(message, type), severity);
            }
            catch (Exception)
            {

            }
        }

        /// <summary>
        /// This method will write the message to the log
        /// along with select attributes from the exception object
        /// and the type object
        /// </summary>
        /// <param name="message">The message to write to the log</param>
        /// <param name="severity">The severity of the event</param>
        /// <param name="type">the type object</param>
        /// <param name="exception">The exception object</param>
        public void Write(string message, LogEntrySeverityEnum severity, Type type, Exception exception)
        {
            try
            {
                // Format the object type into the message
                string formattedMessage = format(message, type);

                // Decorate with the exception, then write it out
                write(format(formattedMessage, exception), severity);
            }
            catch (Exception)
            {

            }
        }


        /// <summary>
        /// Use this method to set the severities that should 
        /// be logged.  The mask is an OR combination of the
        /// various LogEntrySeverityEnum enums
        /// </summary>
        /// <param name="severityMask">An OR mask of LogEntrySeverityEnums</param>
        public void SetLoggableSeverities(LogEntrySeverityEnum severityMask)
        {
            _loggableSeverities = (int)severityMask;
        }

        #endregion

        #region Private Methods

        /// <summary>
        /// Our default c-tor.  We'll make this private
        /// so only our class can construct.
        /// </summary>
        private LogHelper(string source)
        {
            _logWriter = new EventLogWriter(source);
        }

        /// <summary>
        /// Writes the actual data to the log.
        /// </summary>
        /// <param name="message">The text to log</param>
        /// <param name="severity">The severity of the log entry</param>
        private void write(string message, LogEntrySeverityEnum severity)
        {
            try
            {
                validateEventSource();

                // Only write the entry if it meets our threshold
                if ((_loggableSeverities & (int)severity) > 0)
                {
                    Trace.WriteLine(message);
                    Trace.Flush();

                    _logWriter.Write(message, severity);
                }
            }
            catch (Exception)
            {
                // Log failures should not 
                // cause our program to crash
            }
        }

        /// <summary>
        /// Helper method that will format the log text
        /// and include selected attributes from the type
        /// object
        /// </summary>
        /// <param name="message">The message text</param>
        /// <param name="type">The type object</param>
        /// <returns></returns>
        private string format(string message, Type type)
        {
            StringBuilder builder = new StringBuilder();

            // We don't care about the fully qualified type
            // name.  We just want the class
            string[] parsed = type.ToString().Split(
                new char[] { '.' }, StringSplitOptions.RemoveEmptyEntries);

            // Always grab the last string in the 
            // parsed list
            string typeName = parsed[parsed.Length - 1];

            builder.AppendFormat("{0}:{1}\r\n", typeName, message);

            return builder.ToString();
        }

        /// <summary>
        /// Helper method that will format the log text
        /// and include selected attributes from the exception
        /// object
        /// </summary>
        /// <param name="message">The message text</param>
        /// <param name="exception">The exception object</param>
        /// <returns></returns>
        private string format(string message, Exception exception)
        {
            StringBuilder builder = new StringBuilder();

            builder.AppendFormat("{0}\r\n", message);

            builder.AppendFormat(
                "Exception Type: {0}\r\n\r\n" +
                "Exception Message: \r\n{1}\r\n\r\n" +
                "Stack Trace:\r\n{2}",
                exception.GetType().ToString(),
                exception.Message,
                exception.StackTrace);

            if (null != exception.InnerException)
            {
                builder.AppendFormat(
                "InnerException Type: {0}\r\n\r\n" +
                "InnerException Message: \r\n{1}\r\n\r\n" +
                "InnerException Stack Trace:\r\n{2}",
                exception.InnerException.GetType().ToString(),
                exception.InnerException.Message,
                exception.InnerException.StackTrace);
            }

            return builder.ToString();
        }

        /// <summary>
        /// This method will validate that the event log
        /// source exists.  If it doesn't, it will create
        /// the event source
        /// </summary>
        private void validateEventSource()
        {
            if (false == _logWriter.SourceExists())
            {
                _logWriter.CreateSource();
            }
        }

        #endregion

        #region Private Attributes

        // Our singleton instance
        private static LogHelper _logHelper = null;

        // We'll create this once and cache it at the
        // object level
        private EventLogWriter _logWriter;

        // This will be the mask of allowed log levels.  By default, we
        // will log everything
        private int _loggableSeverities = 0xffff;

        #endregion
    }
}
