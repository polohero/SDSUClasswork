using System;
using System.Collections.Generic;
using System.Text;

namespace EmotivSharp
{
    public class EmotivPower : IDisposable
    {
        #region vars
        #region base
        public event d1 DIE;
        public event BaseData.d_CognitivEvent NewCognitivEvent;
        public event BaseData.d_EmoState NewEmoState;
        public event BaseData.d_ExpressivEvent NewExpressivEvent;
        public event BaseData.d_FacialEvent NewFacialEvent;
        public event BaseData.d_AffectivEvent NewAffectivEvent;
        public event BaseData.d_HeadsetRawDataEvent NewHeadsetRawDataEvent;
        public event BaseData.d_HeadsetBaseEvent NewHeadsetBaseEvent;
        private string IP = "127.0.0.1";
        private ushort PortFake = 1726;
        private ushort PortReal = 3008;

        System.Threading.Thread InputThread;

        public enum headsetConnectionType
        {
            Real, Fake, AskUser
        }
        #endregion ---base---

        private IntPtr m_EmoEnginEvent;
        private IntPtr m_EmoState;
        Emotiv.EmoEngine m_EmoEngine;
        bool headsetDataFound = false;
       public delegate void d1();
        uint UserID;
        public void UpdateUserID()
        {
            try
            {
                // hold the spinning thread
                Semaphore_ThreadTakeInput.WaitOne();

                uint UserID_Temp;
                Emotiv.EdkDll.EE_EmoEngineEventGetUserId(m_EmoEnginEvent, out UserID_Temp);

                UserID = UserID_Temp;

            }
            finally
            {
                // restart spinning thread
                Semaphore_ThreadTakeInput.Release();
            }
        }

        public float timeStamp;

        public HeadsetRawData myRawData;
        public HeadsetBase myHeadsetBase;
        public Training myTraining;
        public Cognitiv myCognitiv;
        public Expressiv myExpressiv;
        public Affectiv myAffectiv;
        public User myUser;
        #endregion ---vars---
        #region ERROR_CODE
        public enum ERROR_CODE_emun
        {
            //! Default success value
            EDK_OK = 0x0000,
            //! An internal error occurred
            EDK_UNKNOWN_ERROR = 0x0001,

            //! The contents of the buffer supplied to EE_SetUserProfile aren't a valid, serialized EmoEngine profile.
            EDK_INVALID_PROFILE_ARCHIVE = 0x0101,
            //! Returned from EE_EmoEngineEventGetUserId if the event supplied contains a base profile (which isn't associated with specific user).
            EDK_NO_USER_FOR_BASEPROFILE = 0x0102,

            //! The EmoEngine is unable to acquire EEG data for processing.
            EDK_CANNOT_ACQUIRE_DATA = 0x0200,

            //! The buffer supplied to the function isn't large enough
            EDK_BUFFER_TOO_SMALL = 0x0300,
            //! A parameter supplied to the function is out of range
            EDK_OUT_OF_RANGE = 0x0301,
            //! One of the parameters supplied to the function is invalid
            EDK_INVALID_PARAMETER = 0x0302,
            //! The parameter value is currently locked by a running detection and cannot be modified at this time.
            EDK_PARAMETER_LOCKED = 0x0303,
            //! The current training action is not in the list of expected training actions
            EDK_COG_INVALID_TRAINING_ACTION = 0x0304,
            //! The current training control is not in the list of expected training controls
            EDK_COG_INVALID_TRAINING_CONTROL = 0x0305,
            //! One of the field in the action bits vector is invalid
            EDK_COG_INVALID_ACTIVE_ACTION = 0x0306,
            //! The current action bits vector contains more action types than it is allowed
            EDK_COG_EXCESS_MAX_ACTIONS = 0x0307,
            //! A trained signature is not currently available for use - addition actions (including neutral) may be required
            EDK_EXP_NO_SIG_AVAILABLE = 0x0308,
            //! A filesystem error occurred that prevented the function from succeeding
            EDK_FILESYSTEM_ERROR = 0x0309,

            //! The user ID supplied to the function is invalid
            EDK_INVALID_USER_ID = 0x0400,

            //! The EDK needs to be initialized via EE_EngineConnect or EE_EngineRemoteConnect
            EDK_EMOENGINE_UNINITIALIZED = 0x0500,
            //! The connection with a remote instance of the EmoEngine (made via EE_EngineRemoteConnect) has been lost
            EDK_EMOENGINE_DISCONNECTED = 0x0501,
            //! The API was unable to establish a connection with a remote instance of the EmoEngine.
            EDK_EMOENGINE_PROXY_ERROR = 0x0502,

            //! There are no new EmoEngine events at this time
            EDK_NO_EVENT = 0x0600,

            //! The gyro is not calibrated. Ask the user to stay still for at least 0.5s
            EDK_GYRO_NOT_CALIBRATED = 0x0700,

            //! Operation failure due to optimization
            EDK_OPTIMIZATION_IS_ON = 0x0800,

            //! Reserved return value
            EDK_RESERVED1 = 0x0900
        }

        #endregion ---ERROR_CODE---
        #region Thread Sync stuff
        static System.Threading.Semaphore Semaphore_ThreadTakeInput = new System.Threading.Semaphore(1, 1);
        static System.Threading.Semaphore Semaphore_ThreadTakeInput1 = new System.Threading.Semaphore(1, 1);
        static System.Threading.Semaphore Semaphore_ThreadTakeInput2 = new System.Threading.Semaphore(1, 1);
        static System.Threading.Semaphore Semaphore_ThreadTakeInput3 = new System.Threading.Semaphore(1, 1);
        static System.Threading.Semaphore Semaphore_ThreadTakeInput4 = new System.Threading.Semaphore(1, 1);

        AsyncCallback callBack1 = new AsyncCallback(unLock1);
        AsyncCallback callBack2 = new AsyncCallback(unLock2);
        AsyncCallback callBack3 = new AsyncCallback(unLock3);
        AsyncCallback callBack4 = new AsyncCallback(unLock4);
        static void unLock1(IAsyncResult ar)
        {
            Semaphore_ThreadTakeInput1.Release();
        }
        static void unLock2(IAsyncResult ar)
        {
            Semaphore_ThreadTakeInput2.Release();
        }
        static void unLock3(IAsyncResult ar)
        {
            Semaphore_ThreadTakeInput3.Release();
        }
        static void unLock4(IAsyncResult ar)
        {
            Semaphore_ThreadTakeInput4.Release();
        }
        System.ComponentModel.AsyncOperation async1 = System.ComponentModel.AsyncOperationManager.CreateOperation(null);
        System.ComponentModel.AsyncOperation async2 = System.ComponentModel.AsyncOperationManager.CreateOperation(null);
        System.ComponentModel.AsyncOperation async3 = System.ComponentModel.AsyncOperationManager.CreateOperation(null);
        System.ComponentModel.AsyncOperation async4 = System.ComponentModel.AsyncOperationManager.CreateOperation(null);
        //   AsyncCallback completedCallback = new AsyncCallback(null);
        #endregion ---Thread Sync stuff---
        #region BaseData
        public class BaseData
        {
            #region delegates
            public delegate void d_AffectivEvent(AffectivState.AffectivData AffectivEvent_Data);
            public delegate void d_CognitivEvent(CognitivState.CognitivData CognitivEvent_Data);
            public delegate void d_EmoState(EmoState.EmoData EmoState_Data);
            public delegate void d_ExpressivEvent(FacialState.ExpressivData ExpressivEvent_Data);
            public delegate void d_FacialEvent(FacialState.FacialData FacialEvent_Data);
            public delegate void d_HeadsetRawDataEvent(HeadsetRawDataState.HeadsetRawData_Data AffectivEvent_Data);
            public delegate void d_HeadsetBaseEvent(HeadsetBaseState.HeadsetBaseData HeadsetBaseData);
            #endregion ---delegates---

            #region EmoState
            public class EmoState
            {
                public class EmoData
                {
                    public float TimeStamp;
                    public EmoAction_emun myEmoAction;
                    public float actionPower;
                }
                public enum EmoAction_emun
                {
                    COG_DISAPPEAR = 0x2000,
                    COG_DROP = 0x10,
                    COG_LEFT = 0x20,
                    COG_LIFT = 8,
                    COG_NEUTRAL = 1,
                    COG_PULL = 4,
                    COG_PUSH = 2,
                    COG_RIGHT = 0x40,
                    COG_ROTATE_CLOCKWISE = 0x200,
                    COG_ROTATE_COUNTER_CLOCKWISE = 0x400,
                    COG_ROTATE_FORWARDS = 0x800,
                    COG_ROTATE_LEFT = 0x80,
                    COG_ROTATE_REVERSE = 0x1000,
                    COG_ROTATE_RIGHT = 0x100
                }
            }
            #endregion ---EmoState---
            #region CognitivState
            public class CognitivState
            {
                public class CognitivData
                {
                    public CognitivAction_enum myCognitivAction;
                    public CognitivEvent_enum myCognitivEvent;
                    public float actionPower;
                    public float TimeStamp;
                }

                public int[] ActionSensitivity;
                float ActionSkillRating;
                int ActivationLevel;
                uint ActiveActions;
                float OverallSkillRating;
                uint SignatureCacheSize;
                uint SignatureCaching;
                uint TrainedSignatureActions;
                BaseData.CognitivState.CognitivAction_enum TrainingAction;
                uint TrainingTime;

                public enum CognitivEvent_enum
                {
                    EE_CognitivNoEvent,
                    EE_CognitivTrainingStarted,
                    EE_CognitivTrainingSucceeded,
                    EE_CognitivTrainingFailed,
                    EE_CognitivTrainingCompleted,
                    EE_CognitivTrainingDataErased,
                    EE_CognitivTrainingRejected,
                    EE_CognitivTrainingReset,
                    EE_CognitivAutoSamplingNeutralCompleted,
                    EE_CognitivSignatureUpdated
                }
                public enum CognitivAction_enum
                {
                    COG_DISAPPEAR = 0x2000,
                    COG_DROP = 0x10,
                    COG_LEFT = 0x20,
                    COG_LIFT = 8,
                    COG_NEUTRAL = 1,
                    COG_PULL = 4,
                    COG_PUSH = 2,
                    COG_RIGHT = 0x40,
                    COG_ROTATE_CLOCKWISE = 0x200,
                    COG_ROTATE_COUNTER_CLOCKWISE = 0x400,
                    COG_ROTATE_FORWARDS = 0x800,
                    COG_ROTATE_LEFT = 0x80,
                    COG_ROTATE_REVERSE = 0x1000,
                    COG_ROTATE_RIGHT = 0x100
                }
                public enum CognitivTrainingControl_enum
                {
                    COG_NONE,
                    COG_START,
                    COG_ACCEPT,
                    COG_REJECT,
                    COG_ERASE,
                    COG_RESET
                }
            }
            #endregion ---CognitivState---
            #region FacialState
            public class FacialState
            {
                public class FacialData
                {
                    public float TimeStamp;
                    public FaceExpressiv_enum myFaceActionUpper;
                    public FaceExpressiv_enum myFaceActionLower;
                    public float UpperFaceAmp;
                    public float LowerFaceAmp;


                    public bool Blink;
                    public bool WinkLeft;
                    public bool WinkRight;
                    public bool LookingLeft;
                    public bool LookingRight;
                }
                public class ExpressivData
                {
                    public float TimeStamp;
                    public ExpressivEvent_enum myExpressivAction;
                    public bool TrainedSignatureAvailable;
                }
                public enum FaceExpressiv_enum
                {
                    EXP_NEUTRAL = 0x0001,
                    EXP_BLINK = 0x0002,
                    EXP_WINK_LEFT = 0x0004,
                    EXP_WINK_RIGHT = 0x0008,
                    EXP_HORIEYE = 0x0010,
                    EXP_EYEBROW = 0x0020,
                    EXP_FURROW = 0x0040,
                    EXP_SMILE = 0x0080,
                    EXP_CLENCH = 0x0100,
                    EXP_LAUGH = 0x0200,
                    EXP_SMIRK_LEFT = 0x0400,
                    EXP_SMIRK_RIGHT = 0x0800
                }
                public enum ExpressivEvent_enum
                {
                    EE_ExpressivNoEvent,
                    EE_ExpressivTrainingStarted,
                    EE_ExpressivTrainingSucceeded,
                    EE_ExpressivTrainingFailed,
                    EE_ExpressivTrainingCompleted,
                    EE_ExpressivTrainingDataErased,
                    EE_ExpressivTrainingRejected,
                    EE_ExpressivTrainingReset
                }
            }
            #endregion ---FacialState---
            #region AffectivState
            public class AffectivState
            {
                public class AffectivData
                {
                    public float TimeStamp;
                    public float ExcitementShortTerm;
                    public float ExcitementLongTerm;
                    public float EngagementBoredom;
                }
                public enum AffectivAlgo_enum
                {
                    AFF_ENGAGEMENT_BOREDOM = 8,
                    AFF_EXCITEMENT = 1,
                    AFF_FRUSTRATION = 4,
                    AFF_MEDITATION = 2
                }
            }
            #endregion ---AffectivState---
            #region HeadsetState
            public class HeadsetBaseState
            {
                public class HeadsetBaseData
                {
                    public float TimeStamp;
                    public SignalStrength_enum SignalStrength;
                    public bool HeadsetOn;

                    public int BatteryChargeLevel;
                    public int BatteryChargeMax;
                    public int? BatteryChargePercentage;
                }
                public enum SignalStrength_enum
                {
                    NO_SIGNAL,
                    BAD_SIGNAL,
                    GOOD_SIGNAL
                }
                public enum EEG_ContactQuality_enum
                {
                    EEG_CQ_NO_SIGNAL,
                    EEG_CQ_VERY_BAD,
                    EEG_CQ_POOR,
                    EEG_CQ_FAIR,
                    EEG_CQ_GOOD
                }
            }
            #endregion ---HeadsetState---
            #region GyrotState
            public class GyroState
            {
                public class GyroData
                {
                    public int X;
                    public int Y;
                }
            }
            #endregion ---GyroState---
            #region HeadsetRawDataState
            /// <summary>
            /// mock
            /// </summary>
            public class HeadsetRawDataState
            {
                public class HeadsetRawData_Data
                {

                }

                public enum InputChannels_enum
                {
                    EE_CHAN_CMS,
                    EE_CHAN_DRL,
                    EE_CHAN_FP1,
                    EE_CHAN_AF3,
                    EE_CHAN_F7,
                    EE_CHAN_F3,
                    EE_CHAN_FC5,
                    EE_CHAN_T7,
                    EE_CHAN_P7,
                    EE_CHAN_O1,
                    EE_CHAN_O2,
                    EE_CHAN_P8,
                    EE_CHAN_T8,
                    EE_CHAN_FC6,
                    EE_CHAN_F4,
                    EE_CHAN_F8,
                    EE_CHAN_AF4,
                    EE_CHAN_FP2
                }
                [System.Runtime.InteropServices.StructLayout(System.Runtime.InteropServices.LayoutKind.Sequential)]
                public class InputSensorDescriptor_pack
                {
                    public InputChannels_enum channelID;
                    public int Exists;
                    public string zLabel;
                    public double xLoc;
                    public double yLoc;
                    public double zLoc;
                }
            }
            #endregion ---HeadsetRawDataState---

            #region TrainingState
            public class TrainingState
            {
                public class TrainingData
                {

                }
            }
            #endregion ---TrainingState---
        }
        #endregion ---BaseData---
     
        #region con
        public EmotivPower(headsetConnectionType useRealHeadSet)
        {
            m_EmoEnginEvent = Emotiv.EdkDll.EE_EmoEngineEventCreate();
            m_EmoState = Emotiv.EdkDll.EE_EmoStateCreate();
            m_EmoEngine = Emotiv.EmoEngine.Instance;

            myRawData = new HeadsetRawData(this);
            myHeadsetBase = new HeadsetBase(this);

            myCognitiv = new Cognitiv(this);
            myAffectiv = new Affectiv(this);
            myExpressiv = new Expressiv(this);
            myUser = new User(this);

            myTraining = new Training(this);


            UpdateUserID();
 
            
            if (InputThread == null)
            {
                ThreadTakeInput();
            }
 
            bool conected = false;
            while (!conected)
            {
                if (useRealHeadSet == headsetConnectionType.Real)
                {
                    Emotiv.EdkDll.EE_EngineConnect();
                    System.Threading.Thread.SpinWait(10);
                    if (!headsetDataFound)
                    {
                        System.Threading.Thread.Sleep(500);
                        if (!headsetDataFound)
                            conected = true;
                    }
                    else
                        conected = true;
                }
                else
                    if (useRealHeadSet == headsetConnectionType.Fake)
                    {
                        if (Emotiv.EdkDll.EE_EngineRemoteConnect(IP, PortFake) == Emotiv.EdkDll.EDK_OK)
                        { conected = true; }
                    }
                    else
                        if (useRealHeadSet == headsetConnectionType.AskUser)
                        {
                            System.Windows.Forms.DialogResult DR = System.Windows.Forms.MessageBox.Show("Connect to head set:\nUse Real Headset = Yes\nUseEmoComposer = NO\nUse Control Panal= Cancle", "real or fake headset??", System.Windows.Forms.MessageBoxButtons.YesNoCancel, System.Windows.Forms.MessageBoxIcon.Question);

                            if (System.Windows.Forms.DialogResult.Yes == DR)
                            {
                                Emotiv.EdkDll.EE_EngineConnect();
                                System.Threading.Thread.Sleep(100);
                                if (!headsetDataFound)
                                {
                                    System.Threading.Thread.Sleep(500);
                                    if (headsetDataFound)
                                        conected = true;
                                }
                                else
                                    conected = true;
                            }
                            else
                                if (System.Windows.Forms.DialogResult.No == DR)
                                {
                                    if (Emotiv.EdkDll.EE_EngineRemoteConnect(IP, PortFake) == Emotiv.EdkDll.EDK_OK)
                                    { conected = true; }
                                }
                                else
                                    if (Emotiv.EdkDll.EE_EngineRemoteConnect(IP, PortReal) == Emotiv.EdkDll.EDK_OK)
                                    { conected = true; }
                        }
                if (!conected)
                {
                    System.Windows.Forms.DialogResult DR = System.Windows.Forms.MessageBox.Show("Could not connect to EPOC\nTry again??", "Try Fake Headset again??", System.Windows.Forms.MessageBoxButtons.YesNo, System.Windows.Forms.MessageBoxIcon.Question);
                    if (System.Windows.Forms.DialogResult.Yes == DR)
                    {

                    }
                    else
                        throw new System.Exception("Fail: to Connect Headset");
                }

            }


        }
        #endregion ---con---

        #region pollInput
        private void ThreadTakeInput()
        {


            InputThread = new System.Threading.Thread(new System.Threading.ThreadStart(ThreadTakeInput1));
            InputThread.IsBackground = true;
            InputThread.Start();

        }
        private void ThreadTakeInput1()
        {
            #region vars
            int fails = 0;
#if DEBUG
                int lagOut = 0;
#endif
            long lastTics_Update = 0;
            long lastFail_Time = System.DateTime.Now.Ticks;
            uint OnUserID;
            long DataPackStartTicks;
            Emotiv.EdkDll.EE_Event_t eventTypeIN;
            long dataRate_updateTime = 1500000;
            long dataRate_dropLagTimeout = 1000000000;

            #endregion ---vars---

                while (true)
                {
                    try
                    {
                        #region while
                        #region head lock
                        long sleep = dataRate_updateTime - (System.DateTime.Now.Ticks - lastTics_Update);
                        if (System.DateTime.Now.Ticks - dataRate_updateTime < lastTics_Update)
                        {
                            if (sleep > 0 && sleep < dataRate_updateTime * 2)
                            {
                                System.Threading.Thread.Sleep((int)(sleep / System.TimeSpan.TicksPerMillisecond));
                            }
                        }
                        #endregion ---head lock---

                        Semaphore_ThreadTakeInput.WaitOne();
                        lastTics_Update = System.DateTime.Now.Ticks;

                        #region get data
                        try
                        {
                            // 99.9% this is ok but it can crash
                            if (Emotiv.EdkDll.EE_EngineGetNextEvent(m_EmoEnginEvent) != 0)
                            {
                                if (fails++ > 5)
                                {

                                    long dif = System.DateTime.Now.Ticks - lastFail_Time;
                                    if (dif < dataRate_updateTime * 10 && headsetDataFound)
                                    {
                                        System.Windows.Forms.DialogResult DR = System.Windows.Forms.MessageBox.Show("Connection to helmet lost!!\nReconnect headset??", "Reconnect headset??", System.Windows.Forms.MessageBoxButtons.YesNo, System.Windows.Forms.MessageBoxIcon.Question);

                                        if (System.Windows.Forms.DialogResult.Yes == DR)
                                            fails = 0;
                                        else
                                        {
                                            if (DIE != null)
                                                DIE();
                                            return;
                                        }
                                    }
                                    else
                                    {

                                        fails = 0;
                                    }
                                    lastFail_Time = System.DateTime.Now.Ticks;

                                }
                                continue;
                            }
                            else
                                fails = 0;

                            DataPackStartTicks = System.DateTime.Now.Ticks;

                            OnUserID = 99999;
                            Emotiv.EdkDll.EE_EmoEngineEventGetUserId(m_EmoEnginEvent, out OnUserID);
                            // set Time Stamp
                            timeStamp = Emotiv.EdkDll.ES_GetTimeFromStart(m_EmoState);

                            if (System.DateTime.Now.Ticks - DataPackStartTicks > dataRate_dropLagTimeout)
                            {
#if DEBUG
                                if(lagOut++ > 1000)
                                {
                                    lagOut = 0;
                                    throw new System.Exception("Lag Fails Data stream #u9f8dsgf8igy7ds");
                                }
#endif
                                continue;
                            }
                        }
                        catch (System.Exception e)
                        {
#if DEBUG
                            if (fails++ <= 1000)
                            {
                                fails = 0;
                                throw new System.Exception("EE_EngineGetNextEvent Error: " + e.Message + " #iydgv8ufgyvdiuf");
                            }
#endif
                            continue;
                        }
                        #endregion ---get data---

                        // update EmoState
                        Emotiv.EdkDll.EE_EmoEngineEventGetEmoState(m_EmoEnginEvent, m_EmoState);
                        eventTypeIN = Emotiv.EdkDll.EE_EmoEngineEventGetType(m_EmoEnginEvent);

                        #region send Data
                        switch (eventTypeIN)
                        {
                            #region EE_CognitivEvent
                            case Emotiv.EdkDll.EE_Event_t.EE_CognitivEvent:
                                {
                                    Training.TrainingTypes val = (Training.TrainingTypes)System.Enum.ToObject(typeof(Training.TrainingTypes), eventTypeIN);
                                    myTraining.FireEvent(val, UserID);
                                    break;
                                }
                            #endregion ---EE_CognitivEvent---

                            #region EE_ExpressivEvent
                            case Emotiv.EdkDll.EE_Event_t.EE_ExpressivEvent:
                                {
                                    Expressiv.ExpressivTypes val = (Expressiv.ExpressivTypes)System.Enum.ToObject(typeof(Expressiv.ExpressivTypes), eventTypeIN);
                                    myExpressiv.FireEvent(val, UserID);
                                    break;

                                }
                            #endregion ---EE_ExpressivEvent---

                            #region Device
                            case Emotiv.EdkDll.EE_Event_t.EE_InternalStateChanged:
                                break;

                            case Emotiv.EdkDll.EE_Event_t.EE_UserAdded:
                            case Emotiv.EdkDll.EE_Event_t.EE_UserRemoved:
                                {
                                    User.UserTypes val = (User.UserTypes)System.Enum.ToObject(typeof(User.UserTypes), eventTypeIN);
                                    myUser.FireEvent(val, UserID);
                                    break;
                                }
                            #endregion ---Device---

                            #region EE_EmoStateUpdated
                            case Emotiv.EdkDll.EE_Event_t.EE_EmoStateUpdated:
                                {
                                    headsetDataFound = true;

                                    ///////////////////////////
                                    //BaseData.BaseData.HeadsetState HeadsetDate = new BaseData.HeadsetState();
                                    //////////////////////////////////////////
                                    //////////////////////////////////

                                    #region NewEmoState
                                    if (NewEmoState != null)
                                    {
                                        //     the0nex.EmotivPower.BaseData.EmoState.EmoData EmoData = null;


                                        //    Emotiv.EdkDll.EE_CognitivAction_t actionType = Emotiv.EdkDll.ES_CognitivGetCurrentAction(m_EmoState);
                                        //   float actionPower = Emotiv.EdkDll.ES_CognitivGetCurrentActionPower(m_EmoState);

                                        //   EmoData = new the0nex.EmotivPower.BaseData.EmoState.EmoData();
                                        //   EmoData.actionPower = actionPower * 100;
                                        //  EmoData.myEmoAction = (BaseData.EmoState.EmoAction_emun)actionType;

                                        //     Semaphore_ThreadTakeInput1.WaitOne();
                                        //      NewEmoState.BeginInvoke(EmoData, callBack1, async1);
                                    }
                                    #endregion ---NewEmoState---

                                    #region NewHeadsetRawDataEvent
                                    if (NewHeadsetRawDataEvent != null)
                                    {
                                        try
                                        {
                                            BaseData.HeadsetRawDataState.HeadsetRawData_Data HeadsetRawData_Data = myRawData.BuildHeadsetRawDataState;
                                            NewHeadsetRawDataEvent.Invoke(HeadsetRawData_Data);
                                        }
                                        catch
                                        {
                                            System.Windows.Forms.MessageBox.Show("Sorry you can't get RAW data:( #uyfgs7u6gdf");
                                        }
                                    }
                                    #endregion ---NewHeadsetRawDataEvent---

                                    #region NewAffectivEvent
                                    if (NewAffectivEvent != null)
                                    {
                                        BaseData.AffectivState.AffectivData AffectivData = myAffectiv.BuildAffectivState;
                                        NewAffectivEvent.Invoke(AffectivData);
                                    }
                                    #endregion ---NewAffectivEvent---

                                    #region NewCognitivEvent
                                    if (NewCognitivEvent != null)
                                    {
                                        BaseData.CognitivState.CognitivData CognitivData = myCognitiv.BuildCognitivState;
                                        NewCognitivEvent.Invoke(CognitivData);
                                    }
                                    #endregion ---NewCognitivEvent---

                                    #region face
                                    if (NewExpressivEvent != null)
                                    {
                                        BaseData.FacialState.ExpressivData ExpressivData = myExpressiv.BuildExpressiv;
                                        NewExpressivEvent.Invoke(ExpressivData);
                                    }

                                    if (NewFacialEvent != null)
                                    {
                                        BaseData.FacialState.FacialData FacialData = myExpressiv.BuildFacial;
                                        NewFacialEvent.Invoke(FacialData);
                                    }
                                    #endregion ---face---

                                    #region base
                                    if (NewHeadsetBaseEvent != null)
                                    {
                                        BaseData.HeadsetBaseState.HeadsetBaseData HeadsetBaseData = myHeadsetBase.GetHeadsetBaseState;
                                        NewHeadsetBaseEvent.Invoke(HeadsetBaseData);
                                    }
                                    #endregion ---base---
                                    break;

                                }
                            #endregion ---EE_EmoStateUpdated---

                            default:
                                {
                                    break;
                                }
                        }
                        #endregion ---switch---
                        #endregion ---while---
                    }
                    catch(System.Exception e)
                    {
                        string s = e.Message;
                    }
                    finally
                    {
                        Semaphore_ThreadTakeInput.Release();
                    }
                }
        }
        #endregion ---pollInput---
        #region sub classes
        #region Affectiv
        public class Affectiv
        {
            #region AffectivData
            public BaseData.AffectivState.AffectivData BuildAffectivState
            {
                get
                {
                    BaseData.AffectivState.AffectivData AffectivData = new BaseData.AffectivState.AffectivData();
                    AffectivData.TimeStamp = theEmotivPower.timeStamp;
                    // Affectiv Suite results
                    AffectivData.ExcitementShortTerm = AffectivGetExcitementShortTermScore();
                    AffectivData.ExcitementLongTerm = AffectivGetExcitementLongTermScore();

                    AffectivData.EngagementBoredom = AffectivGetEngagementBoredomScore();

                    return AffectivData;
                }
            }
            #endregion ---AffectivData---

            #region vars
            readonly EmotivPower theEmotivPower;
            #endregion ---vars---

            #region con
            public Affectiv(EmotivPower EmotivPowerIN)
            {
                theEmotivPower = EmotivPowerIN;
            }
            #endregion ---con---

            #region Functions
            //! Returns the long term excitement level of the user
            /*!
                \param state - EmoStateHandle

                \return excitement level (0.0 to 1.0)

                \sa AffectivGetExcitementShortTermScore
            */
            float AffectivGetExcitementLongTermScore()
            {
                return Emotiv.EdkDll.ES_AffectivGetExcitementLongTermScore(theEmotivPower.m_EmoState);
            }

            //! Returns short term excitement level of the user
            /*!
                \param state - EmoStateHandle

                \return excitement level (0.0 to 1.0)

                \sa ES_AffectivGetExcitementLongTermScore
            */
            float AffectivGetExcitementShortTermScore()
            {
                return Emotiv.EdkDll.ES_AffectivGetExcitementShortTermScore(theEmotivPower.m_EmoState);
            }

            //! Query whether the signal is too noisy for Affectiv detection to be active
            /*!
                \param state - EmoStateHandle
                \param type  - Affectiv detection type

                \return detection state (0: Not Active, 1: Active)

                \sa EE_AffectivAlgo_t
            */
            bool AffectivIsActive(BaseData.AffectivState.AffectivAlgo_enum type)
            {
                return Emotiv.EdkDll.ES_AffectivIsActive(theEmotivPower.m_EmoState, (Emotiv.EdkDll.EE_AffectivAlgo_t)type);

            }

            //! Returns meditation level of the user
            /*!
                \param state - EmoStateHandle

                \return meditation level (0.0 to 1.0)
            */

            float AffectivGetMeditationScore()
            {
                return Emotiv.EdkDll.ES_AffectivGetMeditationScore(theEmotivPower.m_EmoState);
            }
            //! Returns frustration level of the user
            /*!
                \param state - EmoStateHandle

                \return frustration level (0.0 to 1.0)
            */
            float AffectivGetFrustrationScore()
            {
                return Emotiv.EdkDll.ES_AffectivGetFrustrationScore(theEmotivPower.m_EmoState);
            }
            //! Returns engagement/boredom level of the user
            /*!
                \param state - EmoStateHandle

                \return engagement/boredom level (0.0 to 1.0)
            */
            float AffectivGetEngagementBoredomScore()
            {
                return Emotiv.EdkDll.ES_AffectivGetEngagementBoredomScore(theEmotivPower.m_EmoState);
            }
            #endregion ---Functions---
        }
        #endregion ---Affectiv---
        #region Cognitiv
        public class Cognitiv
        {
            #region CognitivData
            public BaseData.CognitivState.CognitivData BuildCognitivState
            {
                get
                {
                    BaseData.CognitivState.CognitivData CognitivData = new BaseData.CognitivState.CognitivData();

                    CognitivData.TimeStamp = theEmotivPower.timeStamp;

                    //------------------------CognitivGetCurrentAction---------------------------
                    BaseData.CognitivState.CognitivAction_enum actionType = CognitivGetCurrentAction();
                    float actionPower = CognitivGetCurrentActionPower();


                    CognitivData.actionPower = actionPower * 100;
                    CognitivData.myCognitivAction = actionType;

                    //NewCognitivEvent.BeginInvoke(CognitivData, callBack1, async1);
                    //------------------------CognitivGetCurrentAction---------------------------


                    Emotiv.EdkDll.EE_CognitivEvent_t eventType = Emotiv.EdkDll.EE_CognitivEventGetType(theEmotivPower.m_EmoEnginEvent);
                    CognitivData.myCognitivEvent = (BaseData.CognitivState.CognitivEvent_enum)eventType;

                    return CognitivData;
                }
            }
            #endregion ---CognitivData---

            #region vars
            readonly EmotivPower theEmotivPower;
            #endregion ---vars---

            #region con
            public Cognitiv(EmotivPower EmotivPowerIN)
            {
                theEmotivPower = EmotivPowerIN;
            }
            #endregion ---con---

            #region GET Functions
            public BaseData.CognitivState.CognitivAction_enum CognitivGetCurrentAction()
            {
                Emotiv.EdkDll.EE_CognitivAction_t actionType = Emotiv.EdkDll.ES_CognitivGetCurrentAction(theEmotivPower.m_EmoState);
                return (BaseData.CognitivState.CognitivAction_enum)actionType;
            }
            public float CognitivGetCurrentActionPower()
            {
                return Emotiv.EdkDll.ES_CognitivGetCurrentActionPower(theEmotivPower.m_EmoState);
            }
            public int[] CognitivGetActionSensitivity()
            {
                int pAction1SensitivityOut;
                int pAction2SensitivityOut;
                int pAction3SensitivityOut;
                int pAction4SensitivityOut;
                int error = Emotiv.EdkDll.EE_CognitivGetActionSensitivity(theEmotivPower.UserID, out  pAction1SensitivityOut, out pAction2SensitivityOut, out pAction3SensitivityOut, out pAction4SensitivityOut);
                int[] outArray = new int[4] { pAction1SensitivityOut, pAction2SensitivityOut, pAction3SensitivityOut, pAction4SensitivityOut };

                if ((ERROR_CODE_emun)error != ERROR_CODE_emun.EDK_OK)
                    throw new System.Exception("error: CognitivGetActionSensitivity (" + error + ") #9pjollw35");

                return outArray;
            }
            public float CognitivGetActionSkillRating(EmotivPower.BaseData.CognitivState.CognitivAction_enum actionType)
            {
                float pActionSkillRatingOut;
                int error = Emotiv.EdkDll.EE_CognitivGetActionSkillRating(theEmotivPower.UserID, (Emotiv.EdkDll.EE_CognitivAction_t)actionType, out pActionSkillRatingOut);
                if ((ERROR_CODE_emun)error != ERROR_CODE_emun.EDK_OK)
                    throw new System.Exception("error: CognitivGetActionSkillRating (" + error + ") #gy7igd5r5657");

                return pActionSkillRatingOut;
            }
            public int CognitivGetActivationLevel()
            {
                int pLevelOut;
                int error = Emotiv.EdkDll.EE_CognitivGetActivationLevel(theEmotivPower.UserID, out pLevelOut);
                if ((ERROR_CODE_emun)error != ERROR_CODE_emun.EDK_OK)
                    throw new System.Exception("error: CognitivGetActivationLevel (" + error + ") #7jnr6u76");

                return pLevelOut;
            }
            public uint CognitivGetActiveActions()
            {
                uint pActiveActionsOut;
                int error = Emotiv.EdkDll.EE_CognitivGetActiveActions(theEmotivPower.UserID, out pActiveActionsOut);
                if ((ERROR_CODE_emun)error != ERROR_CODE_emun.EDK_OK)
                    throw new System.Exception("error: CognitivGetActiveActions (" + error + ") #b7rhnn6u7u");

                return pActiveActionsOut;
            }
            public float CognitivGetOverallSkillRating()
            {
                float pOverallSkillRatingOut;
                int error = Emotiv.EdkDll.EE_CognitivGetOverallSkillRating(theEmotivPower.UserID, out pOverallSkillRatingOut);
                if ((ERROR_CODE_emun)error != ERROR_CODE_emun.EDK_OK)
                    throw new System.Exception("error: CognitivGetOverallSkillRating (" + error + ") #n6uyjnyjg");

                return pOverallSkillRatingOut;
            }
            public uint CognitivGetSignatureCacheSize()
            {
                uint pSizeOut;
                int error = Emotiv.EdkDll.EE_CognitivGetSignatureCacheSize(theEmotivPower.UserID, out pSizeOut);
                if ((ERROR_CODE_emun)error != ERROR_CODE_emun.EDK_OK)
                    throw new System.Exception("error: CognitivGetSignatureCacheSize (" + error + ") #b5s4et4n66");

                return pSizeOut;
            }
            public uint CognitivGetSignatureCaching()
            {
                uint pEnabledOut;
                int error = Emotiv.EdkDll.EE_CognitivGetSignatureCaching(theEmotivPower.UserID, out pEnabledOut);
                if ((ERROR_CODE_emun)error != ERROR_CODE_emun.EDK_OK)
                    throw new System.Exception("error: CognitivGetSignatureCaching (" + error + ") #7nmgm8ur8fm");

                return pEnabledOut;
            }
            public uint CognitivGetTrainedSignatureActions()
            {
                uint pTrainedActionsOut;
                int error = Emotiv.EdkDll.EE_CognitivGetTrainedSignatureActions(theEmotivPower.UserID, out pTrainedActionsOut);
                if ((ERROR_CODE_emun)error != ERROR_CODE_emun.EDK_OK)
                    throw new System.Exception("error: CognitivGetTrainedSignatureActions (" + error + ") #7n86im7yug");

                return pTrainedActionsOut;
            }
            public BaseData.CognitivState.CognitivAction_enum CognitivGetTrainingAction()
            {
                Emotiv.EdkDll.EE_CognitivAction_t pActionOut;
                int error = Emotiv.EdkDll.EE_CognitivGetTrainingAction(theEmotivPower.UserID, out pActionOut);
                if ((ERROR_CODE_emun)error != ERROR_CODE_emun.EDK_OK)
                    throw new System.Exception("error: CognitivGetTrainingAction (" + error + ") #i978polh");

                return (EmotivPower.BaseData.CognitivState.CognitivAction_enum)pActionOut;
            }
            public uint CognitivGetTrainingTime()
            {
                uint pTrainingTimeOut;
                int error = Emotiv.EdkDll.EE_CognitivGetTrainingTime(theEmotivPower.UserID, out  pTrainingTimeOut);
                if ((ERROR_CODE_emun)error != ERROR_CODE_emun.EDK_OK)
                    throw new System.Exception("error: CognitivGetTrainingTime (" + error + ") #ig897g");

                return pTrainingTimeOut;
            }
            #endregion ---GET Functions---

            #region SET Functions
            public ERROR_CODE_emun CognitivSetActionSensitivity(int action1Sensitivity, int action2Sensitivity, int action3Sensitivity, int action4Sensitivity)
            {
                return (ERROR_CODE_emun)Emotiv.EdkDll.EE_CognitivSetActionSensitivity(theEmotivPower.UserID, action1Sensitivity, action2Sensitivity, action3Sensitivity, action4Sensitivity);
            }
            public ERROR_CODE_emun CognitivSetActivationLevel(int level)
            {
                return (ERROR_CODE_emun)Emotiv.EdkDll.EE_CognitivSetActivationLevel(theEmotivPower.UserID, level);
            }
            public ERROR_CODE_emun CognitivSetActivationLevel(uint activeActions)
            {
                return (ERROR_CODE_emun)Emotiv.EdkDll.EE_CognitivSetActiveActions(theEmotivPower.UserID, activeActions);
            }
            public ERROR_CODE_emun CognitivSetSignatureCacheSize(uint size)
            {
                return (ERROR_CODE_emun)Emotiv.EdkDll.EE_CognitivSetSignatureCacheSize(theEmotivPower.UserID, size);
            }
            public ERROR_CODE_emun CognitivSetSignatureCaching(uint enabled)
            {
                return (ERROR_CODE_emun)Emotiv.EdkDll.EE_CognitivSetSignatureCaching(theEmotivPower.UserID, enabled);
            }
            public ERROR_CODE_emun CognitivSetTrainingAction(EmotivPower.BaseData.CognitivState.CognitivAction_enum action)
            {
                return (ERROR_CODE_emun)Emotiv.EdkDll.EE_CognitivSetTrainingAction(theEmotivPower.UserID, (Emotiv.EdkDll.EE_CognitivAction_t)action);
            }
            public ERROR_CODE_emun CognitivSetTrainingControl(EmotivPower.BaseData.CognitivState.CognitivTrainingControl_enum action)
            {
                return (ERROR_CODE_emun)Emotiv.EdkDll.EE_CognitivSetTrainingControl(theEmotivPower.UserID, (Emotiv.EdkDll.EE_CognitivTrainingControl_t)action);
            }
            public ERROR_CODE_emun CognitivStartSamplingNeutral()
            {
                return (ERROR_CODE_emun)Emotiv.EdkDll.EE_CognitivStartSamplingNeutral(theEmotivPower.UserID);
            }
            public ERROR_CODE_emun CognitivStopSamplingNeutral()
            {
                return (ERROR_CODE_emun)Emotiv.EdkDll.EE_CognitivStopSamplingNeutral(theEmotivPower.UserID);
            }
            #endregion ---SET Functions---
        }
        #endregion ---Cognitiv---
        #region Expressiv
        public class Expressiv
        {
            #region ExpressivData
            public BaseData.FacialState.ExpressivData BuildExpressiv
            {
                get
                {
                    BaseData.FacialState.ExpressivData ExpressivData = new BaseData.FacialState.ExpressivData();
                    ExpressivData.TimeStamp = theEmotivPower.timeStamp;
                    ExpressivData.myExpressivAction = ExpressivEventGetType();

                    return ExpressivData;
                }
            }
            public BaseData.FacialState.FacialData BuildFacial
            {
                get
                {
                    BaseData.FacialState.FacialData FacialData = new BaseData.FacialState.FacialData();
                    FacialData.TimeStamp = theEmotivPower.timeStamp;

                    FacialData.myFaceActionUpper = ExpressivGetUpperFaceAction();
                    FacialData.myFaceActionLower = ExpressivGetLowerFaceAction();

                    FacialData.UpperFaceAmp = ExpressivGetUpperFaceActionPower();
                    FacialData.LowerFaceAmp = ExpressivGetLowerFaceActionPower();

                    FacialData.Blink = ExpressivIsBlink();
                    FacialData.WinkLeft = ExpressivIsLeftWink();
                    FacialData.WinkRight = ExpressivIsRightWink();
                    FacialData.LookingRight = ExpressivIsLookingRight();
                    FacialData.LookingLeft = ExpressivIsLookingLeft();
                    return FacialData;
                }
            }
            #endregion ---ExpressivData---
            #region event
            public delegate void sendUser(uint userID);
            public delegate void sendUserAndType(ExpressivTypes eventType, uint userID);
            public enum ExpressivTypes
            {
                ExpressivNoEvent,
                ExpressivTrainingStarted,
                ExpressivTrainingSucceeded,
                ExpressivTrainingFailed,
                ExpressivTrainingCompleted,
                ExpressivTrainingDataErased,
                ExpressivTrainingRejected,
                ExpressivTrainingReset

            };
            public event sendUserAndType sendEvent;
            #region FireEvent
            public void FireEvent(ExpressivTypes typeIN, uint UserID_IN)
            {
                if (sendEvent != null)
                {
                    sendEvent(typeIN, UserID_IN);
                }

            }
            #endregion ---FireEvent---
            #endregion ---event---

            #region vars
            readonly EmotivPower theEmotivPower;
            #endregion ---vars---

            #region con
            public Expressiv(EmotivPower EmotivPowerIN)
            {
                theEmotivPower = EmotivPowerIN;
            }
            #endregion ---con---

            #region Functions

            /// <summary>
            /// Returns the Expressiv-specific event type for an EE_ExpressivEvent event already retrieved using EE_EngineGetNextEvent
            /// </summary>
            /// <returns></returns>
            BaseData.FacialState.ExpressivEvent_enum ExpressivEventGetType()
            {
                Emotiv.EdkDll.EE_ExpressivEvent_t eventType = Emotiv.EdkDll.EE_ExpressivEventGetType(theEmotivPower.m_EmoEnginEvent);
                return (BaseData.FacialState.ExpressivEvent_enum)eventType;
            }


            //! Query whether the user is blinking at the time the EmoState is captured.
            /*!
                \param state - EmoStateHandle

                \return blink status (1: blink, 0: not blink)

            */
            bool ExpressivIsBlink()
            {
                return Emotiv.EdkDll.ES_ExpressivIsBlink((IntPtr)theEmotivPower.m_EmoState);

            }

            //! Query whether the user is winking left at the time the EmoState is captured.
            /*!
                \param state - EmoStateHandle

                \return left wink status (1: wink, 0: not wink)

                \sa ES_ExpressivIsRightWink
            */
            bool ExpressivIsLeftWink()
            {
                return Emotiv.EdkDll.ES_ExpressivIsLeftWink(theEmotivPower.m_EmoState);
            }

            //! Query whether the user is winking right at the time the EmoState is captured.
            /*!
                \param state - EmoStateHandle

                \return right wink status (1: wink, 0: not wink)

                \sa ES_ExpressivIsLeftWink
            */
            bool ExpressivIsRightWink()
            {
                return Emotiv.EdkDll.ES_ExpressivIsRightWink(theEmotivPower.m_EmoState);

            }
            //! Query whether the eyes of the user are opened at the time the EmoState is captured.
            /*!
                \param state - EmoStateHandle

                \return eye open status (1: eyes open, 0: eyes closed)

            */
            bool ExpressivIsEyesOpen()
            {
                return Emotiv.EdkDll.ES_ExpressivIsEyesOpen(theEmotivPower.m_EmoState);

            }
            //! Query whether the user is looking up at the time the EmoState is captured.
            /*!
                \param state - EmoStateHandle

                \return eyes position (1: looking up, 0: not looking up)

                \sa ES_ExpressivIsLookingDown
            */
            bool ExpressivIsLookingUp()
            {
                return Emotiv.EdkDll.ES_ExpressivIsLookingUp(theEmotivPower.m_EmoState);

            }

            //! Query whether the user is looking down at the time the EmoState is captured.
            /*!
                \param state - EmoStateHandle

                \return eyes position (1: looking down, 0: not looking down)

                \sa ES_ExpressivIsLookingUp
            */
            bool ExpressivIsLookingDown()
            {
                return Emotiv.EdkDll.ES_ExpressivIsLookingDown(theEmotivPower.m_EmoState);
            }

            //! Query whether the user is looking left at the time the EmoState is captured.
            /*!
                \param state - EmoStatehandle

                \return eye position (1: looking left, 0: not looking left)

                \sa ES_ExpressivIsLookingRight
            */
            bool ExpressivIsLookingLeft()
            {
                return Emotiv.EdkDll.ES_ExpressivIsLookingLeft(theEmotivPower.m_EmoState);
            }

            //! Query whether the user is looking right at the time the EmoState is captured.
            /*!
                \param state - EmoStatehandle

                \return eye position (1: looking right, 0: not looking right)

                \sa ES_ExpressivIsLookingLeft
            */
            bool ExpressivIsLookingRight()
            {
                return Emotiv.EdkDll.ES_ExpressivIsLookingRight(theEmotivPower.m_EmoState);

            }

            //! Query the eyelids state of the user
            /*!
                The left and right eyelid state are stored in the parameter leftEye and rightEye
                respectively. They are floating point values ranging from 0.0 to 1.0.
                0.0 indicates that the eyelid is fully opened while 1.0 indicates that the
                eyelid is fully closed.

                \param state - EmoStatehandle
                \param leftEye - the left eyelid state (0.0 to 1.0)
                \param rightEye - the right eyelid state (0.0 to 1.0)

            */
            float[] ExpressivGetEyelidState()
            {
                float[] tempData = new float[2];
                Emotiv.EdkDll.ES_ExpressivGetEyelidState(theEmotivPower.m_EmoState, out tempData[0], out tempData[1]);
                return tempData;
            }
            //! Query the eyes position of the user
            /*!
                The horizontal and vertical position of the eyes are stored in the parameter x and y
                respectively. They are floating point values ranging from -1.0 to 1.0.
		
                For horizontal position, -1.0 indicates that the user is looking left while
                1.0 indicates that the user is looking right.
		
                For vertical position, -1.0 indicates that the user is looking down while
                1.0 indicatest that the user is looking up.

                This function assumes that both eyes have the same horizontal or vertical positions.
                (i.e. no cross eyes)

                \param state - EmoStateHandle
                \param x - the horizontal position of the eyes
                \param y - the veritcal position of the eyes

            */
            float[] ExpressivGetEyeLocation()
            {
                float[] tempData = new float[2];
                Emotiv.EdkDll.ES_ExpressivGetEyeLocation(theEmotivPower.m_EmoState, out tempData[0], out tempData[1]);
                return tempData;
            }

            //! Returns the eyebrow extent of the user (Obsolete function)
            /*!
                \param state - EmoStateHandle
		
                \return eyebrow extent value (0.0 to 1.0)

                \sa ES_ExpressivGetUpperFaceAction, ES_ExpressivGetUpperFaceActionPower
            */
            float ExpressivGetEyebrowExtent()
            {
                return Emotiv.EdkDll.ES_ExpressivGetEyebrowExtent(theEmotivPower.m_EmoState);

            }

            //! Returns the smile extent of the user (Obsolete function)
            /*!
                \param state - EmoStatehandle
		
                \return smile extent value (0.0 to 1.0)

                \sa ES_ExpressivGetLowerFaceAction, ES_ExpressivGetLowerFaceActionPower
            */
            float ExpressivGetSmileExtent()
            {
                return Emotiv.EdkDll.ES_ExpressivGetSmileExtent(theEmotivPower.m_EmoState);

            }

            //! Returns the clench extent of the user (Obsolete function)
            /*!
                \param state - EmoStatehandle

                \return clench extent value (0.0 to 1.0)

                \sa ES_ExpressivGetLowerFaceAction, ES_ExpressivGetLowerFaceActionPower
            */
            float ExpressivGetClenchExtent()
            {
                return Emotiv.EdkDll.ES_ExpressivGetClenchExtent(theEmotivPower.m_EmoState);

            }


            //! Returns the detected upper face Expressiv action of the user
            /*!
                \param state - EmoStatehandle

                \return pre-defined Expressiv action types

                \sa ES_ExpressivGetUpperFaceActionPower
            */
            BaseData.FacialState.FaceExpressiv_enum ExpressivGetUpperFaceAction()
            {
                return (BaseData.FacialState.FaceExpressiv_enum)Emotiv.EdkDll.ES_ExpressivGetUpperFaceAction(theEmotivPower.m_EmoState);

            }

            //! Returns the detected upper face Expressiv action power of the user
            /*!
                \param state - EmoStatehandle

                \return power value (0.0 to 1.0)

                \sa ES_ExpressivGetUpperFaceAction
            */
            float ExpressivGetUpperFaceActionPower()
            {
                return Emotiv.EdkDll.ES_ExpressivGetUpperFaceActionPower(theEmotivPower.m_EmoState);

            }
            //! Returns the detected lower face Expressiv action of the user
            /*!
                \param state - EmoStatehandle

                \return pre-defined Expressiv action types

                \sa ES_ExpressivGetLowerFaceActionPower
            */

            BaseData.FacialState.FaceExpressiv_enum ExpressivGetLowerFaceAction()
            {
                return (BaseData.FacialState.FaceExpressiv_enum)Emotiv.EdkDll.ES_ExpressivGetLowerFaceAction(theEmotivPower.m_EmoState);
            }
            //! Returns the detected lower face Expressiv action power of the user
            /*!
                \param state - EmoStatehandle

                \return power value (0.0 to 1.0)

                \sa ES_ExpressivGetLowerFaceAction
            */
            float ExpressivGetLowerFaceActionPower()
            {
                return Emotiv.EdkDll.ES_ExpressivGetLowerFaceActionPower(theEmotivPower.m_EmoState);

            }
            //! Query whether the signal is too noisy for Expressiv detection to be active
            /*!
                \param state - EmoStateHandle
                \param type  - Expressiv detection type

                \return detection state (0: Not Active, 1: Active)

                \sa EE_ExpressivAlgo_t
            */
            bool ExpressivIsActive(Training.ExpressivAlgo_enum type)
            {
                return Emotiv.EdkDll.ES_ExpressivIsActive(theEmotivPower.m_EmoState, (Emotiv.EdkDll.EE_ExpressivAlgo_t)type);
            }
            #endregion ---Functions---
        }
        #endregion ---Expressiv---
        #region Gyro
        public class Gyro
        {
            #region GyroData
            public BaseData.GyroState.GyroData BuildGyroState
            {
                get
                {
                    BaseData.GyroState.GyroData GyroData = new BaseData.GyroState.GyroData();
                    int[] tempVal = GetGyroDelta();

                    GyroData.X = tempVal[0];
                    GyroData.Y = tempVal[1];
                    return GyroData;
                }
            }
            #endregion ---GyroData---

            #region vars
            readonly EmotivPower theEmotivPower;
            #endregion ---vars---

            #region con
            public Gyro(EmotivPower EmotivPowerIN)
            {
                theEmotivPower = EmotivPowerIN;
            }
            #endregion ---con---

            #region Functions
            /// <summary>
            /// Returns the delta of the movement of the gyro since the previous call
            /// </summary>
            /// <returns>
            /// int[0]  - horizontal displacement
            /// int[1]  - vertical displacment
            /// </returns>
            public int[] GetGyroDelta()
            {
                int[] XY = new int[2];

                int error = Emotiv.EdkDll.EE_HeadsetGetGyroDelta(theEmotivPower.UserID, out XY[0], out XY[1]);
                if (error != 0)
                    throw new System.Exception("GetGyroDelta Error:" + error);
                return XY;
            }

            /// <summary>
            /// Re-zero the gyro
            /// </summary>
            public void RezeroGyro()
            {
                int error = Emotiv.EdkDll.EE_HeadsetGyroRezero(theEmotivPower.UserID);
                if (error != 0)
                    throw new System.Exception("RezeroGyro Error:" + error);
            }
            #endregion ---Functions---
        }
        #endregion ---Gyro---
        #region HeadsetRawData
        public class HeadsetRawData
        {
            #region BuildHeadsetRawDataState
            public BaseData.HeadsetRawDataState.HeadsetRawData_Data BuildHeadsetRawDataState
            {
                get
                {
                    //  throw new System.Exception("do you have the edk.ddl with access to the RAW DATA. take this line out if you do #9hdfio8uh");

                    Array InputChannels_Array = Enum.GetValues(typeof(BaseData.HeadsetRawDataState.InputChannels_enum));
                    object[] dataArray = new object[InputChannels_Array.Length];

                    for (int i = InputChannels_Array.Length - 1; i >= 0; i--)
                    {

                        dataArray[i] = HeadsetGetSensorDetails((BaseData.HeadsetRawDataState.InputChannels_enum)InputChannels_Array.GetValue(i));
                    }







                    //SetDataAcquisition(true);

                    BaseData.HeadsetRawDataState.HeadsetRawData_Data HeadsetRawData = new BaseData.HeadsetRawDataState.HeadsetRawData_Data();

                    IntPtr data = DataCreate();

                    AcquisitionEnabled = CheckDataAcquisitionEnabled();
                    NumberOfSample = DataGetNumberOfSample(data);
                    BufferSizeInSec = DataGetBufferSizeInSec();
                    SamplingRate = DataGetSamplingRate();


                    double[] Buffer = new double[NumberOfSample];

                    Array DataChannel_Array = Enum.GetValues(typeof(DataChannel_enum));
                    RawData = new int[DataChannel_Array.Length];
                    for (int i = DataChannel_Array.Length - 1; i >= 0; i--)
                    {
                        RawData[i] = DataGet(data, (DataChannel_enum)DataChannel_Array.GetValue(i), Buffer, NumberOfSample);
                    }
                    return HeadsetRawData;
                }
            }
            #endregion ---BuildHeadsetRawDataState---

            #region vars
            readonly EmotivPower theEmotivPower;

            bool AcquisitionEnabled;
            uint NumberOfSample;
            float BufferSizeInSec;
            uint SamplingRate;
            int[] RawData;
            #endregion ---vars---

            #region con
            public HeadsetRawData(EmotivPower EmotivPowerIN)
            {
                theEmotivPower = EmotivPowerIN;
            }
            #endregion ---con---

            #region DataChannel_enum
            public enum DataChannel_enum
            {
                COUNTER,
                INTERPOLATED,
                RAW_CQ,
                AF3,
                F7,
                F3,
                FC5,
                T7,
                P7,
                O1,
                O2,
                P8,
                T8,
                FC6,
                F4,
                F8,
                AF4,
                GYROX,
                GYROY,
                TIMESTAMP,
                ES_TIMESTAMP,
                FUNC_ID,
                FUNC_VALUE,
                MARKER,
                SYNC_SIGNAL
            }
            #endregion ---DataChannel_enum---

            #region functions
            BaseData.HeadsetRawDataState.InputSensorDescriptor_pack HeadsetGetSensorDetails(BaseData.HeadsetRawDataState.InputChannels_enum channelID)
            {
                BaseData.HeadsetRawDataState.InputSensorDescriptor_pack Descriptor = new BaseData.HeadsetRawDataState.InputSensorDescriptor_pack();

                Emotiv.EdkDll.InputSensorDescriptor_t DescriptorOut = new Emotiv.EdkDll.InputSensorDescriptor_t();
                Emotiv.EdkDll.EE_InputChannels_t channel = (Emotiv.EdkDll.EE_InputChannels_t)channelID;

                int error = Emotiv.EdkDll.EE_HeadsetGetSensorDetails(channel, out DescriptorOut);
                if (error != 0)
                    throw new System.Exception("HeadsetGetSensorDetails Error:" + error);


                Descriptor.channelID = (BaseData.HeadsetRawDataState.InputChannels_enum)DescriptorOut.channelId;
                Descriptor.Exists = DescriptorOut.fExists;
                Descriptor.xLoc = DescriptorOut.xLoc;
                Descriptor.yLoc = DescriptorOut.yLoc;
                Descriptor.zLabel = DescriptorOut.pszLabel;
                Descriptor.zLoc = DescriptorOut.zLoc;

                return Descriptor;
            }

            bool CheckDataAcquisitionEnabled()
            {
                bool dataOut;
                Emotiv.EdkDll.EE_DataAcquisitionIsEnabled(theEmotivPower.UserID, out dataOut);
                return dataOut;
            }

            IntPtr DataCreate()
            {
                return Emotiv.EdkDll.EE_DataCreate();
            }

            public int DataGet(IntPtr hData, DataChannel_enum channel, double[] buffer, uint bufferSizeInSample)
            {
                return Emotiv.EdkDll.EE_DataGet(hData, (Emotiv.EdkDll.EE_DataChannel_t)channel, buffer, bufferSizeInSample);
            }

            public float DataGetBufferSizeInSec()
            {
                float BufferSizeInSec;
                int error = Emotiv.EdkDll.EE_DataGetBufferSizeInSec(out BufferSizeInSec);
                if (error != 0)
                    throw new System.Exception("DataGetBufferSizeInSec Error:" + error);
                return BufferSizeInSec;
            }

            public uint DataGetNumberOfSample(IntPtr Data)
            {
                uint Sample;

                int error = Emotiv.EdkDll.EE_DataGetNumberOfSample(Data, out Sample);
                if (error != 0)
                    throw new System.Exception("DataGetNumberOfSample Error:" + error);

                return Sample;
            }

            public uint DataGetSamplingRate()
            {
                uint SamplingRate;

                int error = Emotiv.EdkDll.EE_DataGetSamplingRate(theEmotivPower.UserID, out SamplingRate);
                if (error != 0)
                    throw new System.Exception("DataGetSamplingRate Error:" + error);

                return SamplingRate;
            }

            public void DataFree(IntPtr hData)
            {
                Emotiv.EdkDll.EE_DataFree(hData);
            }




            void SetDataAcquisition(bool SetDataAcquisition)
            {
                Emotiv.EdkDll.EE_DataAcquisitionEnable(theEmotivPower.UserID, SetDataAcquisition);
            }
            public void DataSetBufferSizeInSec(float bufferSizeInSec)
            {
                int error = Emotiv.EdkDll.EE_DataSetBufferSizeInSec(bufferSizeInSec);
                if (error != 0)
                    throw new System.Exception("DataSetBufferSizeInSec Error:" + error);
            }

            public void DataSetMarker(int marker)
            {
                int error = Emotiv.EdkDll.EE_DataSetMarker(theEmotivPower.UserID, marker);
                if (error != 0)
                    throw new System.Exception("DataSetMarker Error:" + error);
            }

            public void DataSetSychronizationSignal(int signal)
            {
                int error = Emotiv.EdkDll.EE_DataSetSychronizationSignal(theEmotivPower.UserID, signal);
                if (error != 0)
                    throw new System.Exception("DataSetMarker Error:" + error);
            }

            public void DataUpdateHandle(IntPtr hData)
            {
                int error = Emotiv.EdkDll.EE_DataUpdateHandle(theEmotivPower.UserID, hData);
                if (error != 0)
                    throw new System.Exception("DataSetMarker Error:" + error);
            }
            #endregion ---functions---
        }
        #endregion ---HeadsetRawData---
        #region HeadsetBase
        public class HeadsetBase
        {
            #region HeadsetState
            public BaseData.HeadsetBaseState.HeadsetBaseData GetHeadsetBaseState
            {
                get
                {
                    BaseData.HeadsetBaseState.HeadsetBaseData tempHeadsetState = new BaseData.HeadsetBaseState.HeadsetBaseData();
                    tempHeadsetState.BatteryChargeLevel = GetBatteryChargeLevel();
                    tempHeadsetState.BatteryChargePercentage = GetBatteryChargePercent();
                    tempHeadsetState.BatteryChargeMax = GetBatteryChargeMax();
                    tempHeadsetState.HeadsetOn = GetHeadsetOn();
                    tempHeadsetState.SignalStrength = GetWirelessSignalStatus();
                    // tempHeadsetState.TimeStamp
                    return tempHeadsetState;
                }
            }
            #endregion ---HeadsetState---

            #region vars
            readonly EmotivPower theEmotivPower;
            #endregion ---vars---

            #region con
            public HeadsetBase(EmotivPower EmotivPowerIN)
            {
                theEmotivPower = EmotivPowerIN;
            }
            #endregion ---con---

            #region ver data
            public uint GetHardwareGetVersion()
            {
                uint HwVersion;
                Emotiv.EdkDll.EE_HardwareGetVersion(theEmotivPower.UserID, out HwVersion);
                return HwVersion;
            }
            public string SoftwareGetVersion()
            {
                StringBuilder SB_Version = new StringBuilder();
                uint BuildNum;

                //ToDo: not Sure what this does
                uint VersionChars = 5;

                Emotiv.EdkDll.EE_SoftwareGetVersion(SB_Version, VersionChars, out BuildNum);
                return SB_Version.ToString() + " : " + BuildNum.ToString();
            }
            #endregion ---var data---
            #region Battery
            public int GetBatteryChargeLevel()
            {
                int chargeLevel;
                int maxChargeLevel;
                Emotiv.EdkDll.ES_GetBatteryChargeLevel(theEmotivPower.m_EmoState, out chargeLevel, out maxChargeLevel);
                return chargeLevel;
            }
            public int GetBatteryChargeMax()
            {
                int chargeLevel;
                int maxChargeLevel;
                Emotiv.EdkDll.ES_GetBatteryChargeLevel(theEmotivPower.m_EmoState, out chargeLevel, out maxChargeLevel);
                return maxChargeLevel;
            }
            public int? GetBatteryChargePercent()
            {
                int chargeLevel;
                int maxChargeLevel;
                Emotiv.EdkDll.ES_GetBatteryChargeLevel(theEmotivPower.m_EmoState, out chargeLevel, out maxChargeLevel);
                if (chargeLevel == -1)
                    return null;
                return (int)((((float)chargeLevel / maxChargeLevel)) * 100);
            }
            public bool GetHeadsetOn()
            {
                return System.Convert.ToBoolean(Emotiv.EdkDll.ES_GetHeadsetOn(theEmotivPower.m_EmoState));
            }
            public BaseData.HeadsetBaseState.SignalStrength_enum GetWirelessSignalStatus()
            {
                return (BaseData.HeadsetBaseState.SignalStrength_enum)Emotiv.EdkDll.ES_GetWirelessSignalStatus(theEmotivPower.m_EmoState);
            }
            #endregion ---Battery---

            #region Contact
            public BaseData.HeadsetBaseState.EEG_ContactQuality_enum GetContactQuality(int electrodID)
            {
                return (BaseData.HeadsetBaseState.EEG_ContactQuality_enum)Emotiv.EdkDll.ES_GetContactQuality(theEmotivPower.m_EmoState, electrodID);
            }

            public BaseData.HeadsetBaseState.EEG_ContactQuality_enum[] GetContactQualityFromAllChannels()
            {
                Emotiv.EdkDll.EE_EEG_ContactQuality_t[] tempArray = null;
                Emotiv.EdkDll.ES_GetContactQualityFromAllChannels(theEmotivPower.m_EmoState, out tempArray);
                BaseData.HeadsetBaseState.EEG_ContactQuality_enum[] Array = new BaseData.HeadsetBaseState.EEG_ContactQuality_enum[tempArray.Length];

                for (int i = 0; i < tempArray.Length; i++)
                {
                    Array[i] = (BaseData.HeadsetBaseState.EEG_ContactQuality_enum)tempArray[i];
                }

                return Array;
            }
            #endregion ---Contact---

            #region ExpressivSignatureTrained
            public bool GetExpressivSignatureTrained()
            {
                // Ask Helmit if it has TrainedSignatureAvailable
                int tempData;
                bool failToCheck = System.Convert.ToBoolean(Emotiv.EdkDll.EE_ExpressivGetTrainedSignatureAvailable(theEmotivPower.UserID, out tempData));

                if (failToCheck)
                    throw new System.Exception("Fail to check for Trained Signature.#90j0fhfh");

                return System.Convert.ToBoolean(tempData);
            }

            public bool SetExpressivSignatureTypeToTrained(EmotivPower.BaseData.FacialState.ExpressivData ExpressivData)
            {
                int result = Emotiv.EdkDll.EE_ExpressivSetSignatureType(theEmotivPower.UserID, (Emotiv.EdkDll.EE_ExpressivSignature_t)ExpressivData.myExpressivAction);
                return (result == Emotiv.EdkDll.EDK_EXP_NO_SIG_AVAILABLE);
            }
            #endregion ---ExpressivSignatureTrained---
        }
        #endregion ---HeadsetBase---
        #region User
        public class User
        {
            #region vars
            readonly EmotivPower theEmotivPower;
            public delegate void sendUser(uint userID_IN);
            public event sendUser NewUser;
            public event sendUser RemovedUser;
            #endregion ---vars---

            #region con
            public User(EmotivPower EmotivPowerIN)
            {
                theEmotivPower = EmotivPowerIN;
                theEmotivPower.m_EmoEngine.UserAdded += new Emotiv.EmoEngine.UserAddedEventHandler(m_EmoEngine_UserAdded);
                theEmotivPower.m_EmoEngine.UserRemoved += new Emotiv.EmoEngine.UserRemovedEventHandler(m_EmoEngine_UserRemoved);
            }
            #endregion ---con---

            void m_EmoEngine_UserAdded(object sender, Emotiv.EmoEngineEventArgs e)
            {
                uint userID = e.userId;
                if (NewUser != null)
                    NewUser(userID);
            }

            void m_EmoEngine_UserRemoved(object sender, Emotiv.EmoEngineEventArgs e)
            {
                uint userID = e.userId;

                if (RemovedUser != null)
                    RemovedUser(userID);
            }
         
            // not sure if it needs to send event
            #region send event
            public delegate void sendUserAndType(UserTypes eventType, uint userID);
            public enum UserTypes
            {
                UserAdded = 0x10,
                UserRemoved = 0x20
            };
            public event sendUserAndType sendEvent;
            #region FireEvent
            public void FireEvent(UserTypes typeIN, uint UserID_IN)
            {
                if (sendEvent != null)
                {
                    sendEvent(typeIN, UserID_IN);
                }
            }
            #endregion ---FireEvent---
            #endregion ---send event---

            public void SaveUserProfile(string fileNameIN)
            {
                Emotiv.EdkDll.EE_SaveUserProfile(theEmotivPower.UserID, fileNameIN);
            }
            public void LoadUserProfile(string fileNameIN)
            {
                Emotiv.EdkDll.EE_LoadUserProfile(theEmotivPower.UserID, fileNameIN);
            }
        }
        #endregion ---User---
        #region Training
        public class Training
        {
            #region TrainingData
            public BaseData.TrainingState.TrainingData GetTraining
            {
                get
                {
                    BaseData.TrainingState.TrainingData tempTrainingState = new BaseData.TrainingState.TrainingData();
                    // tempCognitivState.actionPower = 
                    return tempTrainingState;
                }
            }
            #endregion ---TrainingData---

            #region enum
            public enum ExpressivAlgo_enum
            {
                EXP_NEUTRAL = 0x0001,
                EXP_BLINK = 0x0002,
                EXP_WINK_LEFT = 0x0004,
                EXP_WINK_RIGHT = 0x0008,
                EXP_HORIEYE = 0x0010,
                EXP_EYEBROW = 0x0020,
                EXP_FURROW = 0x0040,
                EXP_SMILE = 0x0080,
                EXP_CLENCH = 0x0100,
                EXP_LAUGH = 0x0200,
                EXP_SMIRK_LEFT = 0x0400,
                EXP_SMIRK_RIGHT = 0x0800
            }
            public enum CognitivAction
            {
                NEUTRAL = 1,
                PUSH = 2,
                PULL = 4,
                LIFT = 8,
                DROP = 16,
                LEFT = 32,
                RIGHT = 64,
                ROTATE_LEFT = 128,
                ROTATE_RIGHT = 256,
                ROTATE_CLOCKWISE = 512,
                ROTATE_COUNTER_CLOCKWISE = 1024,
                ROTATE_FORWARDS = 2048,
                ROTATE_REVERSE = 4096,
                DISAPPEAR = 8192,
            }

            #endregion ---enum---

            #region event
            public delegate void sendUser(uint userID);
            public delegate void sendUserAndType(TrainingTypes eventType, uint userID);
            public enum TrainingTypes
            {
                CognitivNoEvent = 0,
                CognitivTrainingStarted = 1,
                CognitivTrainingSucceeded = 2,
                CognitivTrainingFailed = 3,
                CognitivTrainingCompleted = 4,
                CognitivTrainingDataErased = 5,
                CognitivTrainingRejected = 6,
                CognitivTrainingReset = 7,
                CognitivAutoSamplingNeutralCompleted = 8,
                CognitivSignatureUpdated = 9,
            };
            public event sendUserAndType sendEvent;
            #region FireEvent
            public void FireEvent(TrainingTypes typeIN, uint UserID_IN)
            {
                if (sendEvent != null)
                {
                    sendEvent(typeIN, UserID_IN);
                }

            }
            #endregion ---FireEvent---
            #endregion ---event---

            #region vars
            readonly EmotivPower theEmotivPower;
            #endregion ---vars---

            #region con
            public Training(EmotivPower theEmotivPowerIN)
            {
                theEmotivPower = theEmotivPowerIN;
            }
            #endregion ---con---
            
            #region functions
            Emotiv.EmoEngine.CognitivTrainingStartedEventEventHandler started = null;
            Emotiv.EmoEngine.CognitivTrainingSucceededEventHandler stop = null;
            System.Threading.Semaphore Semaphore_BlockTraining;
            public void Train(CognitivAction CognitivActionIN, uint userID_IN)
            {
                lock (this)
                {
                    Semaphore_BlockTraining = new System.Threading.Semaphore(0, 1);
                    // hold fore event to finish training
                    started = new Emotiv.EmoEngine.CognitivTrainingStartedEventEventHandler(Train1);
                    theEmotivPower.m_EmoEngine.CognitivTrainingStarted += started;

                    Emotiv.EdkDll.EE_CognitivAction_t val = (Emotiv.EdkDll.EE_CognitivAction_t)System.Enum.ToObject(typeof(Emotiv.EdkDll.EE_CognitivAction_t), CognitivActionIN);

                    if (val != Emotiv.EdkDll.EE_CognitivAction_t.COG_NEUTRAL)
                        theEmotivPower.m_EmoEngine.CognitivSetActiveActions(userID_IN, (uint)val);

                    theEmotivPower.m_EmoEngine.CognitivSetTrainingAction(userID_IN, val);
                    theEmotivPower.m_EmoEngine.CognitivSetTrainingControl(userID_IN, Emotiv.EdkDll.EE_CognitivTrainingControl_t.COG_START);


                    Semaphore_BlockTraining.WaitOne();
                }
            }
            void Train1(object sender, Emotiv.EmoEngineEventArgs e)
        {
                theEmotivPower.m_EmoEngine.CognitivTrainingStarted -= started;
                stop = new Emotiv.EmoEngine.CognitivTrainingSucceededEventHandler(Train2);
                theEmotivPower.m_EmoEngine.CognitivTrainingSucceeded += stop;
            }
            void Train2(object sender, Emotiv.EmoEngineEventArgs e)
            {
                theEmotivPower.m_EmoEngine.CognitivTrainingSucceeded -= stop;
                Semaphore_BlockTraining.Release();
            }
            public bool CheckForTrainedExpressivSignature()
            {
                int signatureAvailable;

                bool check = (Emotiv.EdkDll.EE_ExpressivGetTrainedSignatureAvailable(theEmotivPower.UserID, out signatureAvailable) == Emotiv.EdkDll.EDK_OK);

                if (!check)
                    throw new System.Exception("Fail: CheckForTrainedExpressivSignature #iyhf9i8dfh");

                return System.Convert.ToBoolean(signatureAvailable);
            }
            public bool SelectExpressivSignature(bool useUniversal)
            {
                Emotiv.EdkDll.EE_ExpressivSignature_t Signature;

                if (useUniversal)
                    Signature = Emotiv.EdkDll.EE_ExpressivSignature_t.EXP_SIG_UNIVERSAL;
                else
                    Signature = Emotiv.EdkDll.EE_ExpressivSignature_t.EXP_SIG_TRAINED;

                int result = Emotiv.EdkDll.EE_ExpressivSetSignatureType(theEmotivPower.UserID, (Emotiv.EdkDll.EE_ExpressivSignature_t)Signature);
                return (result != Emotiv.EdkDll.EDK_EXP_NO_SIG_AVAILABLE);
            }
            public bool SelectExpressivType(ExpressivAlgo_enum ExpressivType)
            {
                Emotiv.EdkDll.EE_ExpressivAlgo_t tempVar = (Emotiv.EdkDll.EE_ExpressivAlgo_t)ExpressivType;
                return (Emotiv.EdkDll.EE_ExpressivSetTrainingAction(theEmotivPower.UserID, tempVar) == Emotiv.EdkDll.EDK_OK);
            }
            public bool Start()
            {
                return (Emotiv.EdkDll.EE_ExpressivSetTrainingControl(theEmotivPower.UserID, Emotiv.EdkDll.EE_ExpressivTrainingControl_t.EXP_START) == Emotiv.EdkDll.EDK_OK);
            }
            public bool Accept()
            {
                return (Emotiv.EdkDll.EE_ExpressivSetTrainingControl(theEmotivPower.UserID, Emotiv.EdkDll.EE_ExpressivTrainingControl_t.EXP_ACCEPT) == Emotiv.EdkDll.EDK_OK);
            }
            public bool Reject()
            {
                return (Emotiv.EdkDll.EE_ExpressivSetTrainingControl(theEmotivPower.UserID, Emotiv.EdkDll.EE_ExpressivTrainingControl_t.EXP_REJECT) == Emotiv.EdkDll.EDK_OK);
            }
            public bool Erase()
            {
                return (Emotiv.EdkDll.EE_ExpressivSetTrainingControl(theEmotivPower.UserID, Emotiv.EdkDll.EE_ExpressivTrainingControl_t.EXP_ERASE) == Emotiv.EdkDll.EDK_OK);

            }
            #endregion ---functions---
        }
        #endregion ---Training---
        #endregion ---sub classes---

        #region IDisposable Members
        bool Disposed = false;
        public void Dispose()
        {
            if (Disposed)
                return;
            else
                Disposed = true;

            Semaphore_ThreadTakeInput.WaitOne(100);
            Semaphore_ThreadTakeInput1.WaitOne(100);
            Semaphore_ThreadTakeInput2.WaitOne(100);
            Semaphore_ThreadTakeInput3.WaitOne(100);

            System.Threading.Thread.Sleep(500);

            if (InputThread != null)
                InputThread.Abort();

            System.Threading.Thread.Sleep(100);

            Emotiv.EdkDll.EE_EngineDisconnect();
            Emotiv.EdkDll.EE_EmoStateFree(m_EmoState);
            Emotiv.EdkDll.EE_EmoEngineEventFree(m_EmoEnginEvent);
        }
        #endregion ---IDisposable Members---
    }
}