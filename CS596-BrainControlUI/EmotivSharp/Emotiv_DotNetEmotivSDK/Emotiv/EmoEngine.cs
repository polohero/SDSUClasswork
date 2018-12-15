namespace Emotiv
{
    using System;
    using System.Collections.Generic;
    using System.Diagnostics;
    using System.Runtime.CompilerServices;
    using System.Runtime.InteropServices;
    using System.Text;

    public class EmoEngine
    {
        private IntPtr hData = EdkDll.EE_DataCreate();
        private IntPtr hEvent = EdkDll.EE_EmoEngineEventCreate();
        private static EmoEngine instance;
        private Dictionary<uint, EmoState> lastEmoState = new Dictionary<uint, EmoState>();

        public event AffectivEmoStateUpdatedEventHandler AffectivEmoStateUpdated;

        public event CognitivAutoSamplingNeutralCompletedEventHandler CognitivAutoSamplingNeutralCompleted;

        public event CognitivEmoStateUpdatedEventHandler CognitivEmoStateUpdated;

        public event CognitivSignatureUpdatedEventHandler CognitivSignatureUpdated;

        public event CognitivTrainingCompletedEventHandler CognitivTrainingCompleted;

        public event CognitivTrainingDataErasedEventHandler CognitivTrainingDataErased;

        public event CognitivTrainingFailedEventHandler CognitivTrainingFailed;

        public event CognitivTrainingRejectedEventHandler CognitivTrainingRejected;

        public event CognitivTrainingResetEventHandler CognitivTrainingReset;

        public event CognitivTrainingStartedEventEventHandler CognitivTrainingStarted;

        public event CognitivTrainingSucceededEventHandler CognitivTrainingSucceeded;

        public event EmoEngineConnectedEventHandler EmoEngineConnected;

        public event EmoEngineDisconnectedEventHandler EmoEngineDisconnected;

        public event EmoEngineEmoStateUpdatedEventHandler EmoEngineEmoStateUpdated;

        public event EmoStateUpdatedEventHandler EmoStateUpdated;

        public event ExpressivEmoStateUpdatedEventHandler ExpressivEmoStateUpdated;

        public event ExpressivTrainingCompletedEventHandler ExpressivTrainingCompleted;

        public event ExpressivTrainingDataErasedEventHandler ExpressivTrainingDataErased;

        public event ExpressivTrainingFailedEventHandler ExpressivTrainingFailed;

        public event ExpressivTrainingRejectedEventHandler ExpressivTrainingRejected;

        public event ExpressivTrainingResetEventHandler ExpressivTrainingReset;

        public event ExpressivTrainingStartedEventEventHandler ExpressivTrainingStarted;

        public event ExpressivTrainingSucceededEventHandler ExpressivTrainingSucceeded;

        public event InternalStateChangedEventHandler InternalStateChanged;

        public event UserAddedEventHandler UserAdded;

        public event UserRemovedEventHandler UserRemoved;

        private EmoEngine()
        {
        }

        public void CognitivGetActionSensitivity(uint userId, out int pAction1SensitivityOut, out int pAction2SensitivityOut, out int pAction3SensitivityOut, out int pAction4SensitivityOut)
        {
            errorHandler(EdkDll.EE_CognitivGetActionSensitivity(userId, out pAction1SensitivityOut, out pAction2SensitivityOut, out pAction3SensitivityOut, out pAction4SensitivityOut));
        }

        public float CognitivGetActionSkillRating(uint userId, EdkDll.EE_CognitivAction_t action)
        {
            float pActionSkillRatingOut = 0f;
            errorHandler(EdkDll.EE_CognitivGetActionSkillRating(userId, action, out pActionSkillRatingOut));
            return pActionSkillRatingOut;
        }

        public int CognitivGetActivationLevel(uint userId)
        {
            int pLevelOut = 0;
            errorHandler(EdkDll.EE_CognitivGetActivationLevel(userId, out pLevelOut));
            return pLevelOut;
        }

        public uint CognitivGetActiveActions(uint userId)
        {
            uint pActiveActionsOut = 0;
            errorHandler(EdkDll.EE_CognitivGetActiveActions(userId, out pActiveActionsOut));
            return pActiveActionsOut;
        }

        public float CognitivGetOverallSkillRating(uint userId)
        {
            float pOverallSkillRatingOut = 0f;
            errorHandler(EdkDll.EE_CognitivGetOverallSkillRating(userId, out pOverallSkillRatingOut));
            return pOverallSkillRatingOut;
        }

        public uint CognitivGetSignatureCacheSize(uint userId)
        {
            uint pSizeOut = 0;
            errorHandler(EdkDll.EE_CognitivGetSignatureCacheSize(userId, out pSizeOut));
            return pSizeOut;
        }

        public uint CognitivGetSignatureCaching(uint userId)
        {
            uint pEnabledOut = 0;
            errorHandler(EdkDll.EE_CognitivGetSignatureCaching(userId, out pEnabledOut));
            return pEnabledOut;
        }

        public uint CognitivGetTrainedSignatureActions(uint userId)
        {
            uint pTrainedActionsOut = 0;
            errorHandler(EdkDll.EE_CognitivGetTrainedSignatureActions(userId, out pTrainedActionsOut));
            return pTrainedActionsOut;
        }

        public EdkDll.EE_CognitivAction_t CognitivGetTrainingAction(uint userId)
        {
            EdkDll.EE_CognitivAction_t _t;
            errorHandler(EdkDll.EE_CognitivGetTrainingAction(userId, out _t));
            return _t;
        }

        public uint CognitivGetTrainingTime(uint userId)
        {
            uint pTrainingTimeOut = 0;
            errorHandler(EdkDll.EE_CognitivGetTrainingTime(userId, out pTrainingTimeOut));
            return pTrainingTimeOut;
        }

        public void CognitivSetActionSensitivity(uint userId, int action1Sensitivity, int action2Sensitivity, int action3Sensitivity, int action4Sensitivity)
        {
            errorHandler(EdkDll.EE_CognitivSetActionSensitivity(userId, action1Sensitivity, action2Sensitivity, action3Sensitivity, action4Sensitivity));
        }

        public void CognitivSetActivationLevel(uint userId, int level)
        {
            errorHandler(EdkDll.EE_CognitivSetActivationLevel(userId, level));
        }

        public void CognitivSetActiveActions(uint userId, uint activeActions)
        {
            errorHandler(EdkDll.EE_CognitivSetActiveActions(userId, activeActions));
        }

        public void CognitivSetSignatureCacheSize(uint userId, uint size)
        {
            errorHandler(EdkDll.EE_CognitivSetSignatureCacheSize(userId, size));
        }

        public void CognitivSetSignatureCaching(uint userId, uint enabled)
        {
            errorHandler(EdkDll.EE_CognitivSetSignatureCaching(userId, enabled));
        }

        public void CognitivSetTrainingAction(uint userId, EdkDll.EE_CognitivAction_t action)
        {
            errorHandler(EdkDll.EE_CognitivSetTrainingAction(userId, action));
        }

        public void CognitivSetTrainingControl(uint userId, EdkDll.EE_CognitivTrainingControl_t control)
        {
            errorHandler(EdkDll.EE_CognitivSetTrainingControl(userId, control));
        }

        public void CognitivStartSamplingNeutral(uint userId)
        {
            errorHandler(EdkDll.EE_CognitivStartSamplingNeutral(userId));
        }

        public void CognitivStopSamplingNeutral(uint userId)
        {
            errorHandler(EdkDll.EE_CognitivStopSamplingNeutral(userId));
        }

        public void Connect()
        {
            errorHandler(EdkDll.EE_EngineConnect());
            this.OnEmoEngineConnected(new EmoEngineEventArgs(uint.MaxValue));
        }

        public void Disconnect()
        {
            errorHandler(EdkDll.EE_EngineDisconnect());
            this.OnEmoEngineDisconnected(new EmoEngineEventArgs(uint.MaxValue));
        }

        public void EE_SaveUserProfile(uint userID, string szOutputFilename)
        {
            errorHandler(EdkDll.EE_SaveUserProfile(userID, szOutputFilename));
        }

        public uint EngineGetNumUser()
        {
            uint pNumUserOut = 0;
            errorHandler(EdkDll.EE_EngineGetNumUser(out pNumUserOut));
            return pNumUserOut;
        }

        public static void errorHandler(int errorCode)
        {
            if (errorCode != 0)
            {
                string message = "";
                switch (errorCode)
                {
                    case 0x300:
                        message = "A supplied buffer is not large enough";
                        break;

                    case 0x301:
                        message = "Parameter is out of range";
                        break;

                    case 770:
                        message = "Parameter is invalid";
                        break;

                    case 0x303:
                        message = "Parameter is locked";
                        break;

                    case 0x200:
                        message = "EmoEngine is unable to acquire EEG input data";
                        break;

                    case 0x101:
                        message = "Invalid profile archive";
                        break;

                    case 0x102:
                        message = "The base profile does not have a user ID";
                        break;

                    case 1:
                        message = "Unknown error";
                        break;

                    case 0x500:
                        message = "EmoEngine has not been initialized";
                        break;

                    case 0x501:
                        message = "Connection with remote instance of EmoEngine has been lost";
                        break;

                    case 0x502:
                        message = "Unable to establish connection with remote instance of EmoEngine.";
                        break;

                    case 0x400:
                        message = "User ID supplied to the function is invalid";
                        break;

                    case 0x600:
                        message = "There are no new EmoEngine events at this time.";
                        break;

                    case 0x700:
                        message = "The gyro could not be calibrated.  The headset must remain still for at least 0.5 secs.";
                        break;

                    case 0x800:
                        message = "The requested operation failed due to optimization settings.";
                        break;

                    default:
                        message = "Unknown error";
                        break;
                }
                EmoEngineException exception = new EmoEngineException(message);
                exception.ErrorCode = errorCode;
                throw exception;
            }
        }

        public EdkDll.EE_ExpressivSignature_t ExpressivGetSignatureType(uint userId)
        {
            EdkDll.EE_ExpressivSignature_t _t;
            errorHandler(EdkDll.EE_ExpressivGetSignatureType(userId, out _t));
            return _t;
        }

        public int ExpressivGetThreshold(uint userId, EdkDll.EE_ExpressivAlgo_t algoName, EdkDll.EE_ExpressivThreshold_t thresholdName)
        {
            int pValueOut = 0;
            errorHandler(EdkDll.EE_ExpressivGetThreshold(userId, algoName, thresholdName, out pValueOut));
            return pValueOut;
        }

        public uint ExpressivGetTrainedSignatureActions(uint userId)
        {
            uint pTrainedActionsOut = 0;
            errorHandler(EdkDll.EE_ExpressivGetTrainedSignatureActions(userId, out pTrainedActionsOut));
            return pTrainedActionsOut;
        }

        public int ExpressivGetTrainedSignatureAvailable(uint userId)
        {
            int pfAvailableOut = 0;
            errorHandler(EdkDll.EE_ExpressivGetTrainedSignatureAvailable(userId, out pfAvailableOut));
            return pfAvailableOut;
        }

        public EdkDll.EE_ExpressivAlgo_t ExpressivGetTrainingAction(uint userId)
        {
            EdkDll.EE_ExpressivAlgo_t _t;
            errorHandler(EdkDll.EE_ExpressivGetTrainingAction(userId, out _t));
            return _t;
        }

        public uint ExpressivGetTrainingTime(uint userId)
        {
            uint pTrainingTimeOut = 0;
            errorHandler(EdkDll.EE_ExpressivGetTrainingTime(userId, out pTrainingTimeOut));
            return pTrainingTimeOut;
        }

        public void ExpressivSetSignatureType(uint userId, EdkDll.EE_ExpressivSignature_t sigType)
        {
            errorHandler(EdkDll.EE_ExpressivSetSignatureType(userId, sigType));
        }

        public void ExpressivSetThreshold(uint userId, EdkDll.EE_ExpressivAlgo_t algoName, EdkDll.EE_ExpressivThreshold_t thresholdName, int value)
        {
            errorHandler(EdkDll.EE_ExpressivSetThreshold(userId, algoName, thresholdName, value));
        }

        public void ExpressivSetTrainingAction(uint userId, EdkDll.EE_ExpressivAlgo_t action)
        {
            errorHandler(EdkDll.EE_ExpressivSetTrainingAction(userId, action));
        }

        public void ExpressivSetTrainingControl(uint userId, EdkDll.EE_ExpressivTrainingControl_t control)
        {
            errorHandler(EdkDll.EE_ExpressivSetTrainingControl(userId, control));
        }

        ~EmoEngine()
        {
            if (this.hEvent != IntPtr.Zero)
            {
                EdkDll.EE_EmoEngineEventFree(this.hEvent);
            }
            if (this.hData != IntPtr.Zero)
            {
                EdkDll.EE_DataFree(this.hData);
            }
        }

        public Profile GetUserProfile(uint userId)
        {
            Profile profile = new Profile();
            errorHandler(EdkDll.EE_GetUserProfile(userId, profile.GetHandle()));
            return profile;
        }

        public uint HardwareGetVersion(uint userId)
        {
            uint num;
            errorHandler(EdkDll.EE_HardwareGetVersion(userId, out num));
            return num;
        }

        public void HeadsetGetGyroDelta(uint userId, out int pXOut, out int pYOut)
        {
            errorHandler(EdkDll.EE_HeadsetGetGyroDelta(userId, out pXOut, out pYOut));
        }

        public EdkDll.InputSensorDescriptor_t HeadsetGetSensorDetails(EdkDll.EE_InputChannels_t channelId)
        {
            EdkDll.InputSensorDescriptor_t _t;
            errorHandler(EdkDll.EE_HeadsetGetSensorDetails(channelId, out _t));
            return _t;
        }

        public void HeadsetGyroRezero(uint userId)
        {
            errorHandler(EdkDll.EE_HeadsetGyroRezero(userId));
        }

        public void LoadUserProfile(uint userID, string szInputFilename)
        {
            errorHandler(EdkDll.EE_LoadUserProfile(userID, szInputFilename));
        }

        protected virtual void OnAffectivEmoStateUpdated(EmoStateUpdatedEventArgs e)
        {
            if (this.AffectivEmoStateUpdated != null)
            {
                this.AffectivEmoStateUpdated(this, e);
            }
        }

        protected virtual void OnCognitivAutoSamplingNeutralCompleted(EmoEngineEventArgs e)
        {
            if (this.CognitivAutoSamplingNeutralCompleted != null)
            {
                this.CognitivAutoSamplingNeutralCompleted(this, e);
            }
        }

        protected virtual void OnCognitivEmoStateUpdated(EmoStateUpdatedEventArgs e)
        {
            if (this.CognitivEmoStateUpdated != null)
            {
                this.CognitivEmoStateUpdated(this, e);
            }
        }

        protected virtual void OnCognitivSignatureUpdated(EmoEngineEventArgs e)
        {
            if (this.CognitivSignatureUpdated != null)
            {
                this.CognitivSignatureUpdated(this, e);
            }
        }

        protected virtual void OnCognitivTrainingCompleted(EmoEngineEventArgs e)
        {
            if (this.CognitivTrainingCompleted != null)
            {
                this.CognitivTrainingCompleted(this, e);
            }
        }

        protected virtual void OnCognitivTrainingDataErased(EmoEngineEventArgs e)
        {
            if (this.CognitivTrainingDataErased != null)
            {
                this.CognitivTrainingDataErased(this, e);
            }
        }

        protected virtual void OnCognitivTrainingFailed(EmoEngineEventArgs e)
        {
            if (this.CognitivTrainingFailed != null)
            {
                this.CognitivTrainingFailed(this, e);
            }
        }

        protected virtual void OnCognitivTrainingRejected(EmoEngineEventArgs e)
        {
            if (this.CognitivTrainingRejected != null)
            {
                this.CognitivTrainingRejected(this, e);
            }
        }

        protected virtual void OnCognitivTrainingReset(EmoEngineEventArgs e)
        {
            if (this.CognitivTrainingReset != null)
            {
                this.CognitivTrainingReset(this, e);
            }
        }

        protected virtual void OnCognitivTrainingStarted(EmoEngineEventArgs e)
        {
            if (this.CognitivTrainingStarted != null)
            {
                this.CognitivTrainingStarted(this, e);
            }
        }

        protected virtual void OnCognitivTrainingSucceeded(EmoEngineEventArgs e)
        {
            if (this.CognitivTrainingSucceeded != null)
            {
                this.CognitivTrainingSucceeded(this, e);
            }
        }

        protected virtual void OnEmoEngineConnected(EmoEngineEventArgs e)
        {
            this.lastEmoState.Clear();
            if (this.EmoEngineConnected != null)
            {
                this.EmoEngineConnected(this, e);
            }
        }

        protected virtual void OnEmoEngineDisconnected(EmoEngineEventArgs e)
        {
            if (this.EmoEngineDisconnected != null)
            {
                this.EmoEngineDisconnected(this, e);
            }
        }

        protected virtual void OnEmoEngineEmoStateUpdated(EmoStateUpdatedEventArgs e)
        {
            if (this.EmoEngineEmoStateUpdated != null)
            {
                this.EmoEngineEmoStateUpdated(this, e);
            }
        }

        protected virtual void OnEmoStateUpdated(EmoStateUpdatedEventArgs e)
        {
            if (this.EmoStateUpdated != null)
            {
                this.EmoStateUpdated(this, e);
            }
        }

        protected virtual void OnExpressivEmoStateUpdated(EmoStateUpdatedEventArgs e)
        {
            if (this.ExpressivEmoStateUpdated != null)
            {
                this.ExpressivEmoStateUpdated(this, e);
            }
        }

        protected virtual void OnExpressivTrainingCompleted(EmoEngineEventArgs e)
        {
            if (this.ExpressivTrainingCompleted != null)
            {
                this.ExpressivTrainingCompleted(this, e);
            }
        }

        protected virtual void OnExpressivTrainingDataErased(EmoEngineEventArgs e)
        {
            if (this.ExpressivTrainingDataErased != null)
            {
                this.ExpressivTrainingDataErased(this, e);
            }
        }

        protected virtual void OnExpressivTrainingFailed(EmoEngineEventArgs e)
        {
            if (this.ExpressivTrainingFailed != null)
            {
                this.ExpressivTrainingFailed(this, e);
            }
        }

        protected virtual void OnExpressivTrainingRejected(EmoEngineEventArgs e)
        {
            if (this.ExpressivTrainingRejected != null)
            {
                this.ExpressivTrainingRejected(this, e);
            }
        }

        protected virtual void OnExpressivTrainingReset(EmoEngineEventArgs e)
        {
            if (this.ExpressivTrainingReset != null)
            {
                this.ExpressivTrainingReset(this, e);
            }
        }

        protected virtual void OnExpressivTrainingStarted(EmoEngineEventArgs e)
        {
            if (this.ExpressivTrainingStarted != null)
            {
                this.ExpressivTrainingStarted(this, e);
            }
        }

        protected virtual void OnExpressivTrainingSucceeded(EmoEngineEventArgs e)
        {
            if (this.ExpressivTrainingSucceeded != null)
            {
                this.ExpressivTrainingSucceeded(this, e);
            }
        }

        protected virtual void OnInternalStateChanged(EmoEngineEventArgs e)
        {
            if (this.InternalStateChanged != null)
            {
                this.InternalStateChanged(this, e);
            }
        }

        protected virtual void OnUserAdded(EmoEngineEventArgs e)
        {
            this.lastEmoState.Add(e.userId, new EmoState());
            if (this.UserAdded != null)
            {
                this.UserAdded(this, e);
            }
        }

        protected virtual void OnUserRemoved(EmoEngineEventArgs e)
        {
            this.lastEmoState.Remove(e.userId);
            if (this.UserRemoved != null)
            {
                this.UserRemoved(this, e);
            }
        }

        public void OptimizationDisable()
        {
            errorHandler(EdkDll.EE_OptimizationDisable());
        }

        public void OptimizationEnable(OptimizationParam param)
        {
            if (param == null)
            {
                throw new NullReferenceException();
            }
            errorHandler(EdkDll.EE_OptimizationEnable(param.GetHandle()));
        }

        public OptimizationParam OptimizationGetParam()
        {
            OptimizationParam param = new OptimizationParam();
            errorHandler(EdkDll.EE_OptimizationGetParam(param.GetHandle()));
            return param;
        }

        public bool OptimizationIsEnabled()
        {
            bool pEnabledOut = false;
            errorHandler(EdkDll.EE_OptimizationIsEnabled(out pEnabledOut));
            return pEnabledOut;
        }

        public void ProcessEvents()
        {
            this.ProcessEvents(0);
        }

        public void ProcessEvents(int maxTimeMilliseconds)
        {
            Stopwatch stopwatch = new Stopwatch();
            stopwatch.Start();
            while (EdkDll.EE_EngineGetNextEvent(this.hEvent) == 0)
            {
                if ((maxTimeMilliseconds != 0) && (stopwatch.ElapsedMilliseconds >= maxTimeMilliseconds))
                {
                    return;
                }
                uint pUserIdOut = 0;
                EdkDll.EE_EmoEngineEventGetUserId(this.hEvent, out pUserIdOut);
                EmoEngineEventArgs e = new EmoEngineEventArgs(pUserIdOut);
                switch (EdkDll.EE_EmoEngineEventGetType(this.hEvent))
                {
                    case EdkDll.EE_Event_t.EE_CognitivEvent:
                    {
                        switch (EdkDll.EE_CognitivEventGetType(this.hEvent))
                        {
                            case EdkDll.EE_CognitivEvent_t.EE_CognitivTrainingStarted:
                            {
                                this.OnCognitivTrainingStarted(e);
                                continue;
                            }
                            case EdkDll.EE_CognitivEvent_t.EE_CognitivTrainingSucceeded:
                            {
                                this.OnCognitivTrainingSucceeded(e);
                                continue;
                            }
                            case EdkDll.EE_CognitivEvent_t.EE_CognitivTrainingFailed:
                            {
                                this.OnCognitivTrainingFailed(e);
                                continue;
                            }
                            case EdkDll.EE_CognitivEvent_t.EE_CognitivTrainingCompleted:
                            {
                                this.OnCognitivTrainingCompleted(e);
                                continue;
                            }
                            case EdkDll.EE_CognitivEvent_t.EE_CognitivTrainingDataErased:
                            {
                                this.OnCognitivTrainingDataErased(e);
                                continue;
                            }
                            case EdkDll.EE_CognitivEvent_t.EE_CognitivTrainingRejected:
                            {
                                this.OnCognitivTrainingRejected(e);
                                continue;
                            }
                            case EdkDll.EE_CognitivEvent_t.EE_CognitivTrainingReset:
                            {
                                this.OnCognitivTrainingReset(e);
                                continue;
                            }
                            case EdkDll.EE_CognitivEvent_t.EE_CognitivAutoSamplingNeutralCompleted:
                            {
                                this.OnCognitivAutoSamplingNeutralCompleted(e);
                                continue;
                            }
                            case EdkDll.EE_CognitivEvent_t.EE_CognitivSignatureUpdated:
                            {
                                this.OnCognitivSignatureUpdated(e);
                                continue;
                            }
                        }
                        continue;
                    }
                    case EdkDll.EE_Event_t.EE_ExpressivEvent:
                    {
                        switch (EdkDll.EE_ExpressivEventGetType(this.hEvent))
                        {
                            case EdkDll.EE_ExpressivEvent_t.EE_ExpressivTrainingStarted:
                            {
                                this.OnExpressivTrainingStarted(e);
                                continue;
                            }
                            case EdkDll.EE_ExpressivEvent_t.EE_ExpressivTrainingSucceeded:
                            {
                                this.OnExpressivTrainingSucceeded(e);
                                continue;
                            }
                            case EdkDll.EE_ExpressivEvent_t.EE_ExpressivTrainingFailed:
                            {
                                this.OnExpressivTrainingFailed(e);
                                continue;
                            }
                            case EdkDll.EE_ExpressivEvent_t.EE_ExpressivTrainingCompleted:
                            {
                                this.OnExpressivTrainingCompleted(e);
                                continue;
                            }
                            case EdkDll.EE_ExpressivEvent_t.EE_ExpressivTrainingDataErased:
                            {
                                this.OnExpressivTrainingDataErased(e);
                                continue;
                            }
                            case EdkDll.EE_ExpressivEvent_t.EE_ExpressivTrainingRejected:
                            {
                                this.OnExpressivTrainingRejected(e);
                                continue;
                            }
                            case EdkDll.EE_ExpressivEvent_t.EE_ExpressivTrainingReset:
                            {
                                this.OnExpressivTrainingReset(e);
                                continue;
                            }
                        }
                        continue;
                    }
                    case EdkDll.EE_Event_t.EE_InternalStateChanged:
                        break;

                    case EdkDll.EE_Event_t.EE_UserAdded:
                    {
                        this.OnUserAdded(e);
                        continue;
                    }
                    case EdkDll.EE_Event_t.EE_UserRemoved:
                    {
                        this.OnUserRemoved(e);
                        continue;
                    }
                    case EdkDll.EE_Event_t.EE_EmoStateUpdated:
                    {
                        EmoState emoState = new EmoState();
                        errorHandler(EdkDll.EE_EmoEngineEventGetEmoState(this.hEvent, emoState.GetHandle()));
                        EmoStateUpdatedEventArgs args2 = new EmoStateUpdatedEventArgs(pUserIdOut, emoState);
                        this.OnEmoStateUpdated(args2);
                        if (!emoState.EmoEngineEqual(this.lastEmoState[pUserIdOut]))
                        {
                            args2 = new EmoStateUpdatedEventArgs(pUserIdOut, new EmoState(emoState));
                            this.OnEmoEngineEmoStateUpdated(args2);
                        }
                        if (!emoState.AffectivEqual(this.lastEmoState[pUserIdOut]))
                        {
                            args2 = new EmoStateUpdatedEventArgs(pUserIdOut, new EmoState(emoState));
                            this.OnAffectivEmoStateUpdated(args2);
                        }
                        if (!emoState.CognitivEqual(this.lastEmoState[pUserIdOut]))
                        {
                            args2 = new EmoStateUpdatedEventArgs(pUserIdOut, new EmoState(emoState));
                            this.OnCognitivEmoStateUpdated(args2);
                        }
                        if (!emoState.ExpressivEqual(this.lastEmoState[pUserIdOut]))
                        {
                            args2 = new EmoStateUpdatedEventArgs(pUserIdOut, new EmoState(emoState));
                            this.OnExpressivEmoStateUpdated(args2);
                        }
                        this.lastEmoState[pUserIdOut] = (EmoState) emoState.Clone();
                        continue;
                    }
                    default:
                    {
                        continue;
                    }
                }
                this.OnInternalStateChanged(e);
            }
        }

        public void RemoteConnect(string ip, ushort port)
        {
            errorHandler(EdkDll.EE_EngineRemoteConnect(ip, port));
            this.OnEmoEngineConnected(new EmoEngineEventArgs(uint.MaxValue));
        }

        public void ResetDetection(uint userId, EdkDll.EE_EmotivSuite_t suite, uint detectionBitVector)
        {
            errorHandler(EdkDll.EE_ResetDetection(userId, suite, detectionBitVector));
        }

        public void SetHardwarePlayerDisplay(uint userId, uint playerNum)
        {
            errorHandler(EdkDll.EE_SetHardwarePlayerDisplay(userId, playerNum));
        }

        public void SetUserProfile(uint userId, Profile profile)
        {
            if (profile == null)
            {
                throw new NullReferenceException();
            }
            byte[] bytes = profile.GetBytes();
            errorHandler(EdkDll.EE_SetUserProfile(userId, bytes, (uint) bytes.Length));
        }

        public void SoftwareGetVersion(out string pszVersionOut, out uint pBuildNumOut)
        {
            StringBuilder builder = new StringBuilder(0x80);
            errorHandler(EdkDll.EE_SoftwareGetVersion(builder, (uint) builder.Capacity, out pBuildNumOut));
            pszVersionOut = builder.ToString();
        }

        public static EmoEngine Instance
        {
            get
            {
                if (instance == null)
                {
                    instance = new EmoEngine();
                }
                return instance;
            }
        }

        public delegate void AffectivEmoStateUpdatedEventHandler(object sender, EmoStateUpdatedEventArgs e);

        public delegate void CognitivAutoSamplingNeutralCompletedEventHandler(object sender, EmoEngineEventArgs e);

        public delegate void CognitivEmoStateUpdatedEventHandler(object sender, EmoStateUpdatedEventArgs e);

        public delegate void CognitivSignatureUpdatedEventHandler(object sender, EmoEngineEventArgs e);

        public delegate void CognitivTrainingCompletedEventHandler(object sender, EmoEngineEventArgs e);

        public delegate void CognitivTrainingDataErasedEventHandler(object sender, EmoEngineEventArgs e);

        public delegate void CognitivTrainingFailedEventHandler(object sender, EmoEngineEventArgs e);

        public delegate void CognitivTrainingRejectedEventHandler(object sender, EmoEngineEventArgs e);

        public delegate void CognitivTrainingResetEventHandler(object sender, EmoEngineEventArgs e);

        public delegate void CognitivTrainingStartedEventEventHandler(object sender, EmoEngineEventArgs e);

        public delegate void CognitivTrainingSucceededEventHandler(object sender, EmoEngineEventArgs e);

        public delegate void EmoEngineConnectedEventHandler(object sender, EmoEngineEventArgs e);

        public delegate void EmoEngineDisconnectedEventHandler(object sender, EmoEngineEventArgs e);

        public delegate void EmoEngineEmoStateUpdatedEventHandler(object sender, EmoStateUpdatedEventArgs e);

        public delegate void EmoStateUpdatedEventHandler(object sender, EmoStateUpdatedEventArgs e);

        public delegate void ExpressivEmoStateUpdatedEventHandler(object sender, EmoStateUpdatedEventArgs e);

        public delegate void ExpressivTrainingCompletedEventHandler(object sender, EmoEngineEventArgs e);

        public delegate void ExpressivTrainingDataErasedEventHandler(object sender, EmoEngineEventArgs e);

        public delegate void ExpressivTrainingFailedEventHandler(object sender, EmoEngineEventArgs e);

        public delegate void ExpressivTrainingRejectedEventHandler(object sender, EmoEngineEventArgs e);

        public delegate void ExpressivTrainingResetEventHandler(object sender, EmoEngineEventArgs e);

        public delegate void ExpressivTrainingStartedEventEventHandler(object sender, EmoEngineEventArgs e);

        public delegate void ExpressivTrainingSucceededEventHandler(object sender, EmoEngineEventArgs e);

        public delegate void InternalStateChangedEventHandler(object sender, EmoEngineEventArgs e);

        public delegate void ProfileEventEventHandler(object sender, EmoEngineEventArgs e);

        public delegate void UserAddedEventHandler(object sender, EmoEngineEventArgs e);

        public delegate void UserRemovedEventHandler(object sender, EmoEngineEventArgs e);
    }
}

