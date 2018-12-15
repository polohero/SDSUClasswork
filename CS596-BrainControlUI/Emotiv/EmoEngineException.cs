namespace Emotiv
{
    using System;
    using System.Runtime.Serialization;

    public class EmoEngineException : ApplicationException
    {
        private int errorCode;

        public EmoEngineException()
        {
        }

        public EmoEngineException(string message) : base(message)
        {
        }

        protected EmoEngineException(SerializationInfo info, StreamingContext context) : base(info, context)
        {
        }

        public EmoEngineException(string message, Exception inner) : base(message, inner)
        {
        }

        public int ErrorCode
        {
            get
            {
                return this.errorCode;
            }
            set
            {
                this.errorCode = value;
            }
        }
    }
}

