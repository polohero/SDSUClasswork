namespace Emotiv
{
    using System;

    public class Profile
    {
        private IntPtr hProfile = EdkDll.EE_ProfileEventCreate();

        public Profile()
        {
            EdkDll.EE_GetBaseProfile(this.hProfile);
        }

        ~Profile()
        {
            EdkDll.EE_EmoEngineEventFree(this.hProfile);
        }

        public byte[] GetBytes()
        {
            uint pProfileSizeOut = 0;
            EmoEngine.errorHandler(EdkDll.EE_GetUserProfileSize(this.hProfile, out pProfileSizeOut));
            byte[] destBuffer = new byte[pProfileSizeOut];
            EmoEngine.errorHandler(EdkDll.EE_GetUserProfileBytes(this.hProfile, destBuffer, pProfileSizeOut));
            return destBuffer;
        }

        public IntPtr GetHandle()
        {
            return this.hProfile;
        }
    }
}

